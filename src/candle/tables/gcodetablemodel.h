// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODETABLEMODEL_H
#define GCODETABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include "../parser/gcodearg.h"

struct GCodeItem
{
    enum States { InQueue, Sent, Processed, Skipped };

    GCodeItem() = default;
    GCodeItem(QString&& c) : command(c), up_command(command.toUpper()) { updateArgs(); }
    GCodeItem(const QString& c) : command(c), up_command(command.toUpper()) { updateArgs(); }

    void setCommand(const QString& c);

    const QString& getCommand() const { return command; }
    const QString& getUCommand() const { return up_command; }

    const GCodeArgList& getArgs() const { return args; }

    char state = InQueue;
    QString response;
    int line = 0;

private:
    void updateArgs();

    QString command;
    QString up_command;
    GCodeArgList args;
};

class GCodeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GCodeTableModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<GCodeItem> &data();

signals:

public slots:

private:
    QList<GCodeItem> m_data;
    QStringList m_headers;
};

#endif // GCODETABLEMODEL_H
