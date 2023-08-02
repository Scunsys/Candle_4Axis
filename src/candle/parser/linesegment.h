// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2016 Hayrullin Denis Ravilevich

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QVector3D>
#include "basesegment.h"

class LineSegment : public BaseSegment
{
public:
    LineSegment() = default;

    LineSegment(const QVector3D& a, const QVector3D& b, int num) :
        BaseSegment(a, num),
        m_second(b)
    { }

    LineSegment(const QVector3D& a, const QVector3D& b, int num, const BaseSegment& bs) :
        BaseSegment(a, num, bs),
        m_second(b)
    { }

    const QVector3D &getStart() const { return getPoint(); }
    void setStart(const QVector3D& vector) { setPoint(vector); }

    const QVector3D &getEnd() const { return m_second; }
    void setEnd(const QVector3D& vector) { m_second = vector; }

    bool contains(const QVector3D &point) const;

    bool isHightlight() const { return m_isHightlight; }
    void setIsHightlight(bool isHightlight) { m_isHightlight = isHightlight; }

    int vertexIndex() const { return m_vertexIndex; }
    void setVertexIndex(int vertexIndex) { m_vertexIndex = vertexIndex; }

    bool drawn() const { return m_drawn; }
    void setDrawn(bool b) { m_drawn = b; }

private:
    QVector3D m_second;

    bool m_drawn = false;
    bool m_isHightlight = false;
    int m_vertexIndex = -1;
};

#endif // LINESEGMENT_H
