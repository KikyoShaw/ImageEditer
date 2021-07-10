#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImageEditer.h"

class ImageEditer : public QWidget
{
    Q_OBJECT

public:
    ImageEditer(QWidget *parent = Q_NULLPTR);

private:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::ImageEditerClass ui;
	//窗口移动属性值
	QPoint m_point;
	volatile bool m_bMove = false;
};
