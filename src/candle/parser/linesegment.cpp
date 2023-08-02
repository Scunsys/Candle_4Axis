// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include "linesegment.h"
#include <QDebug>

bool LineSegment::contains(const QVector3D &point) const
{
    double delta;
    QVector3D line = getEnd() - getStart();
    QVector3D pt = point - getStart();

    delta = (line - pt).length() - (line.length() - pt.length());

    return delta < 0.01;
}
