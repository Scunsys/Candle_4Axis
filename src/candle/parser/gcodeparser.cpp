// This file is a part of "Candle" application.
// This file was originally ported from "GcodeParser.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QListIterator>
#include <QDebug>
#include "gcodeparser.h"

GcodeParser::GcodeParser(QObject *parent) : QObject(parent)
{
    m_isMetric = true;
    m_inAbsoluteMode = true;
    m_inAbsoluteIJKMode = false;
    m_lastGcodeCommand = -1;
    m_commandNumber = 0;

    // Settings
    m_speedOverride = -1;
    m_truncateDecimalLength = 40;
    m_removeAllWhitespace = true;
    m_convertArcsToLines = false;
    m_smallArcThreshold = 1.0;
    // Not configurable outside, but maybe it should be.
    m_smallArcSegmentLength = 0.3;
    m_lastSpeed = 0;
    m_lastSpindleSpeed = 0;
    m_traverseSpeed = 300;

    reset();
}

GcodeParser::~GcodeParser()
{
    foreach (PointSegment *ps, m_points) delete ps;
}

// Resets the current state.
void GcodeParser::reset(const QVector3D &initialPoint)
{
    qDebug() << "reseting gp" << initialPoint;

    foreach (PointSegment *ps, m_points) delete ps;
    m_points.clear();
    // The unspoken home location.
    m_currentPoint = initialPoint;
    m_currentPlane = PointSegment::XY;
    m_points.append(new PointSegment(m_currentPoint, -1));
}

/**
* Add a command to be processed.
*/
PointSegment* GcodeParser::addCommand(const QString& command)
{
    GCodeArgList args = GcodePreprocessorUtils::splitCommand(command);
    return addCommand(args);
}

/**
* Add a command which has already been broken up into its arguments.
*/
PointSegment* GcodeParser::addCommand(const GCodeArgList &args)
{
    if (args.isEmpty()) {
        return NULL;
    }
    return processCommand(args);
}

/**
* Warning, this should only be used when modifying live gcode, such as when
* expanding an arc or canned cycle into line segments.
*/
void GcodeParser::setLastGcodeCommand(float num) {
    m_lastGcodeCommand = num;
}

/**
* Expands the last point in the list if it is an arc according to the
* the parsers settings.
*/
QList<PointSegment*> GcodeParser::expandArc()
{
    const PointSegment *startSegment = m_points[m_points.size() - 2];
    const PointSegment *lastSegment = m_points[m_points.size() - 1];

    QList<PointSegment*> empty;

    // Can only expand arcs.
    if (!lastSegment->isArc()) {
        return empty;
    }

    // Get precalculated stuff.
    const QVector3D &start = startSegment->point();
    const QVector3D &end = lastSegment->point();
    const QVector3D &center = lastSegment->center();
    double radius = lastSegment->getRadius();
    bool clockwise = lastSegment->isClockwise();
    PointSegment::planes plane = startSegment->plane();

    //
    // Start expansion.
    //

    QList<QVector3D> expandedPoints = GcodePreprocessorUtils::generatePointsAlongArcBDring(plane, start, end, center, clockwise, radius, m_smallArcThreshold, m_smallArcSegmentLength, false);

    // Validate output of expansion.
    if (expandedPoints.length() == 0) {
        return empty;
    }

    // Remove the last point now that we're about to expand it.
    m_points.removeLast();
    m_commandNumber--;

    // Initialize return value
    QList<PointSegment*> psl;

    // Create line segments from points.
    PointSegment *temp;

    QListIterator<QVector3D> psi(expandedPoints);
    // skip first element.
    if (psi.hasNext()) psi.next();

    while (psi.hasNext()) {
        temp = new PointSegment(psi.next(), m_commandNumber++);
        temp->setIsMetric(lastSegment->isMetric());
        m_points.append(temp);
        psl.append(temp);
    }

    // Update the new endpoint.
    m_currentPoint = m_points.last()->point();

    return psl;
}

double GcodeParser::getTraverseSpeed() const
{
    return m_traverseSpeed;
}

void GcodeParser::setTraverseSpeed(double traverseSpeed)
{
    m_traverseSpeed = traverseSpeed;
}

int GcodeParser::getCommandNumber() const
{
    return m_commandNumber - 1;
}


PointSegment *GcodeParser::processCommand(const GCodeArgList &args)
{
    double v = qQNaN();
    QVector3D nextPoint(m_currentPoint);
    QVector3D ijkPoint(m_currentPoint);
    bool haveIJK = false;
    double r = 0;
    enum {
        MOVE_NONE,
        MOVE_G0,
        MOVE_G1,
        MOVE_G2,
        MOVE_G3,
        MOVE_G38_2,
    } mmode = MOVE_NONE;

    foreach (const GCodeArg& s, args) {
        v = s.param.toDouble();
        if (qIsNaN(v)) continue;

        if (!m_isMetric) {
            switch (s.cmd.toLatin1()) {
            case 'F':
            case 'X':
            case 'Y':
            case 'Z':
            case 'I':
            case 'J':
            case 'K':
            case 'R':
                v *= 25.4;
            }
        }

        switch (s.cmd.toLatin1()) {
        case 'F':
            m_lastSpeed = v;
            break;

        case 'S':
            m_lastSpindleSpeed = v;
            break;

        case 'P':
            break;

        case 'X':
            if (!m_inAbsoluteMode) v += m_currentPoint.x();
            nextPoint.setX(v);
            break;

        case 'Y':
            if (!m_inAbsoluteMode) v += m_currentPoint.y();
            nextPoint.setY(v);
            break;

        case 'Z':
            if (!m_inAbsoluteMode) v += m_currentPoint.z();
            nextPoint.setZ(v);
            break;

        case 'I':
            haveIJK = true;
            if (!m_inAbsoluteIJKMode) v += m_currentPoint.x();
            ijkPoint.setX(v);
            break;

        case 'J':
            haveIJK = true;
            if (!m_inAbsoluteIJKMode) v += m_currentPoint.y();
            ijkPoint.setY(v);
            break;

        case 'K':
            haveIJK = true;
            if (!m_inAbsoluteIJKMode) v += m_currentPoint.z();
            ijkPoint.setZ(v);
            break;

        case 'R':
            r = v;
            break;

        case 'G':
            if (v == 0.0f) mmode = MOVE_G0;
            else if (v == 1.0f) mmode = MOVE_G1;
            else if (v == 38.2f) mmode = MOVE_G38_2;
            else if (v == 2.0f) mmode = MOVE_G2;
            else if (v == 3.0f) mmode = MOVE_G3;
            else if (v == 17.0f) m_currentPlane = PointSegment::XY;
            else if (v == 18.0f) m_currentPlane = PointSegment::ZX;
            else if (v == 19.0f) m_currentPlane = PointSegment::YZ;
            else if (v == 20.0f) m_isMetric = false;
            else if (v == 21.0f) m_isMetric = true;
            else if (v == 90.0f) m_inAbsoluteMode = true;
            else if (v == 90.1f) m_inAbsoluteIJKMode = true;
            else if (v == 91.0f) m_inAbsoluteMode = false;
            else if (v == 91.1f) m_inAbsoluteIJKMode = false;

            if (mmode != MOVE_NONE) {
                m_lastGcodeCommand = v;
            }
        }
    }

    if (mmode == MOVE_NONE && nextPoint != m_currentPoint) {
        v = m_lastGcodeCommand;
        if (v == 0.0f) mmode = MOVE_G0;
        else if (v == 1.0f) mmode = MOVE_G1;
        else if (v == 38.2f) mmode = MOVE_G38_2;
        else if (v == 2.0f) mmode = MOVE_G2;
        else if (v == 3.0f) mmode = MOVE_G3;
    }

    if (mmode == MOVE_NONE) {
        return NULL;
    }

    switch (mmode) {
    case MOVE_G0:
    case MOVE_G1:
    case MOVE_G38_2:
        return addLinearPointSegment(nextPoint, mmode == MOVE_G0);

    default:
        if (haveIJK) return addArcPointSegment(nextPoint, mmode == MOVE_G2, ijkPoint);

        return addArcPointSegment(nextPoint, mmode == MOVE_G2, r);
    }
}

void GcodeParser::setState(BaseSegment *bs, bool zOnly, bool fast) const
{
    bs->setIsMetric(m_isMetric);
    bs->setIsZMovement(zOnly);
    bs->setIsFastTraverse(fast);
    bs->setIsAbsolute(m_inAbsoluteMode);
    bs->setSpeed(fast ? m_traverseSpeed : m_lastSpeed);
    bs->setSpindleSpeed(m_lastSpindleSpeed);
    bs->setPlane(m_currentPlane);
}

PointSegment *GcodeParser::addLinearPointSegment(const QVector3D &nextPoint, bool fastTraverse)
{
    PointSegment *ps = new PointSegment(nextPoint, m_commandNumber++);

    bool zOnly = false;

    // Check for z-only
    if ((m_currentPoint.x() == nextPoint.x()) &&
            (m_currentPoint.y() == nextPoint.y()) &&
            (m_currentPoint.z() != nextPoint.z())) {
        zOnly = true;
    }

    setState(ps, zOnly, fastTraverse);

    m_points.append(ps);

    // Save off the endpoint.
    m_currentPoint = nextPoint;

    return ps;
}

PointSegment *GcodeParser::addArcPointSegment(const QVector3D &nextPoint, bool clockwise, const QVector3D &center)
{
    QMatrix4x4 m;
    m.setToIdentity();
    switch (m_currentPlane) {
    case PointSegment::XY:
        break;
    case PointSegment::ZX:
        m.rotate(90, 1.0, 0.0, 0.0);
        break;
    case PointSegment::YZ:
        m.rotate(-90, 0.0, 1.0, 0.0);
        break;
    }

    double radius = sqrt(pow((double)((m * m_currentPoint).x() - (m * center).x()), 2.0)
                    + pow((double)((m * m_currentPoint).y() - (m * center).y()), 2.0));

    PointSegment *ps = new PointSegment(nextPoint, m_commandNumber++, center, radius, clockwise);

    setState(ps);

    m_points.append(ps);

    // Save off the endpoint.
    m_currentPoint = nextPoint;

    return ps;
}

PointSegment *GcodeParser::addArcPointSegment(const QVector3D &nextPoint, bool clockwise, double radius)
{
    QVector3D center = GcodePreprocessorUtils::convertRToCenter(m_currentPoint, nextPoint, radius, m_currentPlane, clockwise);

    PointSegment *ps = new PointSegment(nextPoint, m_commandNumber++, center, radius, clockwise);

    setState(ps);

    m_points.append(ps);

    // Save off the endpoint.
    m_currentPoint = nextPoint;

    return ps;
}

QStringList GcodeParser::preprocessCommands(const QStringList &commands) {

    QStringList result;

    foreach (const QString &command, commands) {
        result.append(preprocessCommand(command));
    }

    return result;
}

QStringList GcodeParser::preprocessCommand(QString command) {

    QStringList result;
    bool hasComment = false;

    // Remove comments from command.
    QString newCommand = GcodePreprocessorUtils::removeComment(command);
    QString rawCommand = newCommand;
    hasComment = (newCommand.length() != command.length());

    if (m_removeAllWhitespace) {
        newCommand = GcodePreprocessorUtils::removeAllWhitespace(newCommand);
    }

    if (newCommand.length() > 0) {

        // Override feed speed
        if (m_speedOverride > 0) {
            newCommand = GcodePreprocessorUtils::overrideSpeed(newCommand, m_speedOverride);
        }

        if (m_truncateDecimalLength > 0) {
            newCommand = GcodePreprocessorUtils::truncateDecimals(m_truncateDecimalLength, newCommand);
        }

        // If this is enabled we need to parse the gcode as we go along.
        if (m_convertArcsToLines) { // || this.expandCannedCycles) {
            QStringList arcLines = convertArcsToLines(newCommand);
            if (arcLines.length() > 0) {
                result.append(arcLines);
            } else {
                result.append(newCommand);
            }
        } else if (hasComment) {
            // Maintain line level comment.
            result.append(command.replace(rawCommand, newCommand));
        } else {
            result.append(newCommand);
        }
    } else if (hasComment) {
        // Reinsert comment-only lines.
        result.append(command);
    }

    return result;
}

QStringList GcodeParser::convertArcsToLines(const QString &command) {

    QStringList result;

    QVector3D start = m_currentPoint;

    PointSegment *ps = addCommand(command);

    if (ps == NULL || !ps->isArc()) {
        return result;
    }

    QList<PointSegment*> psl = expandArc();

    if (psl.length() == 0) {
        return result;
    }

    // Create an array of new commands out of the of the segments in psl.
    // Don't add them to the gcode parser since it is who expanded them.
    foreach (PointSegment* segment, psl) {
        const QVector3D &end = segment->point();
        result.append(GcodePreprocessorUtils::generateG1FromPoints(start, end, m_inAbsoluteMode, m_truncateDecimalLength));
        start = segment->point();
    }

    return result;

}
