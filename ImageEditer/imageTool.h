#pragma once

#include <QObject>

class ImageTool : public QObject
{
	Q_OBJECT

public:
	static ImageTool& getInstance();
	~ImageTool();

	//ͼƬԲ�ǻ�
	QPixmap getRoundRectPixmap(QPixmap srcPixMap, const QSize & size, int radius);
	//ת�Ҷ�ͼ
	QImage setGreyScale(QImage image);
	//ůɫ��
	QImage setWarm(QImage image, int value);
	//��ɫ��
	QImage setCool(QImage image, int value);
	//���Ͷ�
	QImage setSaturation(QImage image, int value);
	//��������
	QImage setBright(QImage image, int value);
	//ģ��
	QImage setBlur(QImage image);
	//ģ���ı߿�
	QImage setBlurFrame(QImage image, const QString &filePath);
	//��
	QImage setSharpen(QImage image);
	//��������Ч��(����һ��ͼƬЧ������һ��ͼƬ��)
	QImage setMetal(QImage image, const QString &filePath);
	//��ӱ߿�
	QImage setDrawFrame(QImage image, const QString &filePath);

private:
	ImageTool(QObject *parent = Q_NULLPTR);
	Q_DISABLE_COPY(ImageTool)
};

#define imageTool ImageTool::getInstance()