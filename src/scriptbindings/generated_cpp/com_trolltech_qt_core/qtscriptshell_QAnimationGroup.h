#ifndef QTSCRIPTSHELL_QANIMATIONGROUP_H
#define QTSCRIPTSHELL_QANIMATIONGROUP_H

#include <qanimationgroup.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAnimationGroup : public QAnimationGroup
{
public:
    QtScriptShell_QAnimationGroup(QObject*  parent = 0);
    ~QtScriptShell_QAnimationGroup();

    void childEvent(QChildEvent*  event);
    void customEvent(QEvent*  event);
    int  duration() const;
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void timerEvent(QTimerEvent*  event);
    void updateCurrentTime(int  currentTime);
    void updateDirection(QAbstractAnimation::Direction  direction);
    void updateState(QAbstractAnimation::State  newState, QAbstractAnimation::State  oldState);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QANIMATIONGROUP_H
