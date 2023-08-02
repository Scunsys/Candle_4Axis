// This file is a part of "Candle" application.
// This file was originally ported from "GcodePreprocessorUtils.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODEPREPROCESSORUTILS_H
#define GCODEPREPROCESSORUTILS_H

#include <QObject>
#include <QMatrix4x4>
#include <cmath>
#include "pointsegment.h"
#include "gcodearg.h"

class GcodePreprocessorUtils : public QObject
{
    Q_OBJECT
public:
    static QString overrideSpeed(QString command, double speed, double *original = NULL);
    static QString removeComment(QString command);
    static QString parseComment(QString command);
    static QString truncateDecimals(int length, QString command);
    static QString removeAllWhitespace(QString command);
    static QList<float> parseCodes(const QStringList &args, char code);
    static QList<int> parseGCodes(QString command);
    static QList<int> parseMCodes(QString command);
    static GCodeArgList splitCommand(const QString &command);
    static QVector3D convertRToCenter(const QVector3D& start, const QVector3D& end, double radius, PointSegment::planes plane, bool clockwise);
    static QString generateG1FromPoints(const QVector3D& start, const QVector3D& end, bool absoluteMode, int precision);
    static double getAngle(QVector3D start, QVector3D end);
    static double calculateSweep(double startAngle, double endAngle, bool isCw);
    static QList<QVector3D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector3D start, QVector3D end, QVector3D center, bool clockwise, double R, double minArcLength, double arcPrecision, bool arcDegreeMode);
    static QList<QVector3D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector3D p1, QVector3D p2, QVector3D center, bool isCw, double radius, double startAngle, double sweep, int numPoints);
    static inline bool isDigit(char c);
    static inline bool isLetter(char c);
    static inline char toUpper(char c);
signals:

public slots:

private:

};

#endif // GCODEPREPROCESSORUTILS_H
