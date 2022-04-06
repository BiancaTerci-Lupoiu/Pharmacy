#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10QT.h"

class Lab10QT : public QMainWindow
{
    Q_OBJECT

public:
    Lab10QT(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab10QTClass ui;
};
