
#ifndef GCODEARG_H
#define GCODEARG_H

struct GCodeArg
{
    QChar cmd;
    QString param;
};

using GCodeArgList = QList<GCodeArg>;

#endif // GCODEARG_H
