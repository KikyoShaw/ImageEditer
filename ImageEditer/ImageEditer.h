#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageEditer.h"

class ImageEditer : public QWidget
{
    Q_OBJECT

public:
    ImageEditer(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImageEditerClass ui;
};
