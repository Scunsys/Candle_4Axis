#ifndef QTSCRIPTSHELL_QLOCALSOCKET_H
#define QTSCRIPTSHELL_QLOCALSOCKET_H

#include <qlocalsocket.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QLocalSocket : public QLocalSocket
{
public:
    QtScriptShell_QLocalSocket(QObject*  parent = 0);
    ~QtScriptShell_QLocalSocket();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  event);
    void close();
    void customEvent(QEvent*  event);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  openMode = ReadWrite);
    qint64  pos() const;
    qint64  readData(char*  arg__1, qint64  arg__2);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  pos);
    qint64  size() const;
    void timerEvent(QTimerEvent*  event);
    bool  waitForBytesWritten(int  msecs = 30000);
    bool  waitForReadyRead(int  msecs = 30000);
    qint64  writeData(const char*  arg__1, qint64  arg__2);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QLOCALSOCKET_H
