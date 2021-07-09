#pragma once

#include <QObject>

class ImageTool : public QObject
{
	Q_OBJECT

public:
	static ImageTool& getInstance();
	~ImageTool();

	//图片圆角化
	QPixmap getRoundRectPixmap(QPixmap srcPixMap, const QSize & size, int radius);
	//转灰度图
	QImage setGreyScale(QImage image);
	//暖色调
	QImage setWarm(QImage image, int value);
	//冷色调
	QImage setCool(QImage image, int value);
	//饱和度
	QImage setSaturation(QImage image, int value);
	//调节亮度
	QImage setBright(QImage image, int value);
	//模糊
	QImage setBlur(QImage image);
	//模糊的边框
	QImage setBlurFrame(QImage image, const QString &filePath);
	//锐化
	QImage setSharpen(QImage image);
	//特殊纹理效果(附加一张图片效果到另一张图片上)
	QImage setMetal(QImage image, const QString &filePath);
	//添加边框
	QImage setDrawFrame(QImage image, const QString &filePath);

private:
	ImageTool(QObject *parent = Q_NULLPTR);
	Q_DISABLE_COPY(ImageTool)
};

#define imageTool ImageTool::getInstance()