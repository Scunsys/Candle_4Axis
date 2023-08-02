
#ifndef BASESEGMENT_H
#define BASESEGMENT_H

#include <QVector3D>

class BaseSegment
{
public:
    enum planes {
        XY,
        ZX,
        YZ
    };

    BaseSegment() = default;

    BaseSegment(const QVector3D& p, int num) :
        m_point(p),
        m_lineNumber(num)
    { }

    BaseSegment(const QVector3D& p, int num, const BaseSegment& bs) :
        m_speed(bs.m_speed),
        m_spindleSpeed(bs.m_spindleSpeed),
        m_point(p),
        m_isZMovement(bs.m_isZMovement),
        m_isArc(bs.m_isArc),
        m_isFastTraverse(bs.m_isFastTraverse),
        m_isMetric(bs.m_isMetric),
        m_isAbsolute(bs.m_isAbsolute),
        m_lineNumber(num),
        m_plane(bs.m_plane)
    { }

    BaseSegment(const BaseSegment&) = default;

    int getLineNumber() const { return m_lineNumber; }

    const QVector3D &getPoint() const { return m_point; }
    void setPoint(const QVector3D& point) { m_point = point; }

    void setSpeed(double s) { m_speed = s; }
    double getSpeed() const { return m_speed; }

    void setIsZMovement(bool isZ) { m_isZMovement = isZ; }
    bool isZMovement() const { return m_isZMovement; }

    void setIsArc(bool isA) { m_isArc = isA; }
    bool isArc() const { return m_isArc; }

    void setIsFastTraverse(bool isF) { m_isFastTraverse = isF; }
    bool isFastTraverse() const { return m_isFastTraverse; }

    bool isMetric() const { return m_isMetric; }
    void setIsMetric(bool isMetric) { m_isMetric = isMetric; }

    bool isAbsolute() const { return m_isAbsolute; }
    void setIsAbsolute(bool isAbsolute) { m_isAbsolute = isAbsolute; }

    double getSpindleSpeed() const { return m_spindleSpeed; }
    void setSpindleSpeed(double spindleSpeed) { m_spindleSpeed = spindleSpeed; }

    planes plane() const { return m_plane; }
    void setPlane(const planes &plane) { m_plane = plane; }

private:
    double m_speed = 0;
    double m_spindleSpeed = 0;
    QVector3D m_point;

    bool m_isZMovement = false;
    bool m_isArc = false;
    bool m_isFastTraverse = false;
    bool m_isMetric = true;
    bool m_isAbsolute = true;
    int m_lineNumber = 0;

    planes m_plane = XY;
};

#endif // BASESEGMENT_H
