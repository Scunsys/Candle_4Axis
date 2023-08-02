// This file is a part of "Candle" application.
// This file was originally ported from "GcodeParser.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODEPARSER_H
#define GCODEPARSER_H

#include <QObject>
#include <QVector3D>
#include <cmath>
#include "pointsegment.h"
#include "gcodepreprocessorutils.h"

class GcodeParser : public QObject
{
    Q_OBJECT
public:
    explicit GcodeParser(QObject *parent = 0);
    ~GcodeParser();

    bool getConvertArcsToLines() const { return m_convertArcsToLines; }
    void setConvertArcsToLines(bool convertArcsToLines) { m_convertArcsToLines = convertArcsToLines; }

    bool getRemoveAllWhitespace() const { return m_removeAllWhitespace; }
    void setRemoveAllWhitespace(bool removeAllWhitespace) { m_removeAllWhitespace = removeAllWhitespace; }

    double getSmallArcSegmentLength() const { return m_smallArcSegmentLength; }
    void setSmallArcSegmentLength(double smallArcSegmentLength) { m_smallArcSegmentLength = smallArcSegmentLength; }

    double getSmallArcThreshold() const { return m_smallArcThreshold; }
    void setSmallArcThreshold(double smallArcThreshold) { m_smallArcThreshold = smallArcThreshold; }

    double getSpeedOverride() const { return m_speedOverride; }
    void setSpeedOverride(double speedOverride) { m_speedOverride = speedOverride; }

    int getTruncateDecimalLength() const { return m_truncateDecimalLength; }
    void setTruncateDecimalLength(int truncateDecimalLength) { m_truncateDecimalLength = truncateDecimalLength; }

    void reset(const QVector3D &initialPoint = QVector3D(qQNaN(), qQNaN(), qQNaN()));
    PointSegment *addCommand(const QString& command);
    PointSegment *addCommand(const GCodeArgList &args);
    const QVector3D& getCurrentPoint() const { return m_currentPoint; }
    QList<PointSegment *> expandArc();
    QStringList preprocessCommands(const QStringList& commands);
    QStringList preprocessCommand(QString command);
    QStringList convertArcsToLines(const QString& command);
    const QList<PointSegment *> &getPointSegmentList() const { return m_points; }
    double getTraverseSpeed() const;
    void setTraverseSpeed(double traverseSpeed);
    int getCommandNumber() const;

signals:

public slots:

private:

    // Current state
    bool m_isMetric;
    bool m_inAbsoluteMode;
    bool m_inAbsoluteIJKMode;
    float m_lastGcodeCommand;
    QVector3D m_currentPoint;
    int m_commandNumber;
    PointSegment::planes m_currentPlane;

    // Settings
    double m_speedOverride;
    int m_truncateDecimalLength;
    bool m_removeAllWhitespace;
    bool m_convertArcsToLines;
    double m_smallArcThreshold;
    // Not configurable outside, but maybe it should be.
    double m_smallArcSegmentLength;

    double m_lastSpeed;
    double m_traverseSpeed;
    double m_lastSpindleSpeed;

    // The gcode.
    QList<PointSegment*> m_points;

    PointSegment *processCommand(const GCodeArgList &args);
    void setState(BaseSegment *bs, bool zOnly = false, bool fase = false) const;
    PointSegment *addLinearPointSegment(const QVector3D &nextPoint, bool fastTraverse);
    PointSegment *addArcPointSegment(const QVector3D &nextPoint, bool clockwise, const QVector3D &center);
    PointSegment *addArcPointSegment(const QVector3D &nextPoint, bool clockwise, double r);
    void setLastGcodeCommand(float num);
};

#endif // GCODEPARSER_H
