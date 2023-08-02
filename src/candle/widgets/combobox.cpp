// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QDebug>
#include <QKeyEvent>
#include "combobox.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
}

ComboBox::~ComboBox()
{
}

void ComboBox::storeText()
{
    if (count() == maxCount()) removeItem(maxCount() - 1);
    insertItem(0, currentText());
    setCurrentIndex(-1);
}

void ComboBox::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if (count() == maxCount()) removeItem(maxCount() - 1);  // TODO: Make removing selected item
    }
    QComboBox::keyPressEvent(e);

    if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) {
        emit returnPressed();
        setCurrentIndex(-1);
    }
}
