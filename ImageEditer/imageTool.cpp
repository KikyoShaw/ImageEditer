#include "imageTool.h"
#include <QPixmap>
#include <QPainter>


ImageTool & ImageTool::getInstance()
{
	static ImageTool m_instance;
	return m_instance;
}

ImageTool::ImageTool(QObject *parent)
	:QObject(parent)
{

}

ImageTool::~ImageTool()
{
}

QPixmap ImageTool::getRoundRectPixmap(QPixmap srcPixMap, const QSize & size, int radius)
{
	//����������ݻ��ߴ�������
	if (srcPixMap.isNull()) {
		return srcPixMap;
	}

	//��ȡͼƬ�ߴ�
	int imageWidth = size.width();
	int imageHeight = size.height();

	//�����ߴ��ͼƬ,��֤ͼƬ��ʾ��������
	QPixmap newPixMap = srcPixMap.scaled(imageWidth, (imageHeight == 0 ? imageWidth : imageHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPixmap destImage(imageWidth, imageHeight);
	destImage.fill(Qt::transparent);
	QPainter painter(&destImage);
	// �����
	painter.setRenderHints(QPainter::Antialiasing, true);
	// ͼƬƽ������
	painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
	// ��ͼƬ�ü�ΪԲ��
	QPainterPath path;
	QRect rect(0, 0, imageWidth, imageHeight);
	path.addRoundedRect(rect, radius, radius);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, imageWidth, imageHeight, newPixMap);
	return destImage;
}

QImage ImageTool::setGreyScale(QImage image)
{
	QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
	QColor oldColor;
	for (int i = 0; i < newImage.width(); i++) 
	{
		for (int j = 0; j < newImage.height(); j++) 
		{
			oldColor = QColor(image.pixel(i, j));
			int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
			newImage.setPixel(i, j, qRgb(average, average, average));
		}
	}
	return newImage;
}

QImage ImageTool::setWarm(QImage image, int value)
{
	QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
	QColor oldColor;
	//�޸�rgb��r��g���ܴﵽЧ��
	int r, g, b;
	for (int i = 0; i < newImage.width(); i++) 
	{
		for (int j = 0; j < newImage.height(); j++) 
		{
			oldColor = QColor(image.pixel(i, j));
			r = oldColor.red() + value;
			g = oldColor.green() + value;
			b = oldColor.blue();
			//ֵ��0-255֮�䣬����0��255
			r = qBound(0, r, 255);
			g = qBound(0, g, 255);
			newImage.setPixel(i, j, qRgb(r, g, b));
		}
	}
	return newImage;
}

QImage ImageTool::setCool(QImage image, int value)
{
	QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
	QColor oldColor;
	//�޸�rgb��b���ܴﵽЧ��
	int r, g, b;
	for (int i = 0; i < newImage.width(); i++) 
	{
		for (int j = 0; j < newImage.height(); j++)
		{
			oldColor = QColor(image.pixel(i, j));
			r = oldColor.red();
			g = oldColor.green();
			b = oldColor.blue() + value;
			//ֵ��0-255֮�䣬����0��255
			b = qBound(0, b, 255);
			newImage.setPixel(i, j, qRgb(r, g, b));
		}
	}
	return newImage;
}

QImage ImageTool::setSaturation(QImage image, int value)
{
	QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
	QColor oldColor;
	QColor newColor;
	int h, s, l;
	for (int i = 0; i < newImage.width(); i++) 
	{
		for (int j = 0; j < newImage.height(); j++) 
		{
			oldColor = QColor(image.pixel(i, j));
			newColor = oldColor.toHsl();
			h = newColor.hue();
			s = newColor.saturation() + value;
			l = newColor.lightness();
			//ֵ��0-255֮�䣬����0��255
			s = qBound(0, s, 255);
			newColor.setHsl(h, s, l);
			newImage.setPixel(i, j, qRgb(newColor.red(), newColor.green(), newColor.blue()));
		}
	}
	return newImage;
}

QImage ImageTool::setBright(QImage image, int value)
{
	QColor oldColor;
	int r = 0, g = 0, b = 0;
	QImage newImage = QImage(image.width(), image.height(), QImage::Format_ARGB32);
	for (int i = 0; i < newImage.height(); ++i)
	{
		for (int j = 0; j < newImage.width(); ++j)
		{
			oldColor = QColor(image.pixel(j, i));
			r = oldColor.red() + value;
			g = oldColor.green() + value;
			b = oldColor.blue() + value;
			//ֵ��0-255֮�䣬����0��255
			r = qBound(0, r, 255);
			g = qBound(0, g, 255);
			b = qBound(0, b, 255);
			newImage.setPixel(j, i, qRgb(r, g, b));
		}
	}
	return newImage;
}

QImage ImageTool::setBlur(QImage image)
{
	QImage newImage = QImage(image);
	int kernel[5][5] = { { 0,0,1,0,0 },
	{ 0,1,3,1,0 },
	{ 1,3,7,3,1 },
	{ 0,1,3,1,0 },
	{ 0,0,1,0,0 } };
	int kernelSize = 5;
	int sumKernel = 27;
	int r, g, b;
	QColor color;
	for (int x = kernelSize / 2; x < newImage.width() - (kernelSize / 2); x++) 
	{
		for (int y = kernelSize / 2; y < newImage.height() - (kernelSize / 2); y++) 
		{
			r = 0;
			g = 0;
			b = 0;
			for (int i = -kernelSize / 2; i <= kernelSize / 2; i++) 
			{
				for (int j = -kernelSize / 2; j <= kernelSize / 2; j++) 
				{
					color = QColor(image.pixel(x + i, y + j));
					r += color.red()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					g += color.green()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					b += color.blue()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
				}
			}
			//ֵ��0-255֮�䣬����0��255
			r = qBound(0, r / sumKernel, 255);
			g = qBound(0, g / sumKernel, 255);
			b = qBound(0, b / sumKernel, 255);
			newImage.setPixel(x, y, qRgb(r, g, b));
		}
	}
	return newImage;
}

QImage ImageTool::setBlurFrame(QImage image, const QString & filePath)
{
	QImage newImage = QImage(image);
	QImage blurredImage = setBlur(newImage);
	QImage mask = QImage(filePath);
	QPainter painter;
	//�ȴ���ģ����
	painter.begin(&mask);
	painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
	painter.drawImage(0, 0, blurredImage);
	painter.end();
	//�ϳɵ�һ��ͼƬ
	painter.begin(&newImage);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(0, 0, mask);
	painter.end();
	return newImage;
}

QImage ImageTool::setSharpen(QImage image)
{
	QImage newImage = QImage(image);
	int kernel[3][3] = { { 0,-1,0 },
	{ -1,5,-1 },
	{ 0,-1,0 } };
	int kernelSize = 3;
	int sumKernel = 1;
	int r, g, b;
	QColor color;
	for (int x = kernelSize / 2; x < newImage.width() - (kernelSize / 2); x++) 
	{
		for (int y = kernelSize / 2; y < newImage.height() - (kernelSize / 2); y++) 
		{
			r = 0;
			g = 0;
			b = 0;
			for (int i = -kernelSize / 2; i <= kernelSize / 2; i++) 
			{
				for (int j = -kernelSize / 2; j <= kernelSize / 2; j++) 
				{
					color = QColor(image.pixel(x + i, y + j));
					r += color.red()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					g += color.green()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					b += color.blue()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
				}
			}
			//ֵ��0-255֮�䣬����0��255
			r = qBound(0, r / sumKernel, 255);
			g = qBound(0, g / sumKernel, 255);
			b = qBound(0, b / sumKernel, 255);
			newImage.setPixel(x, y, qRgb(r, g, b));
		}
	}
	return newImage;
}

QImage ImageTool::setMetal(QImage image, const QString & filePath)
{
	QImage newImage = QImage(filePath);
	QImage darkImage = setBright(image, -100);
	QImage greyImage = setGreyScale(darkImage);
	QPainter painter;
	painter.begin(&newImage);
	painter.setOpacity(0.5);
	painter.drawImage(0, 0, greyImage);
	painter.end();
	return newImage;
}

QImage ImageTool::setDrawFrame(QImage image, const QString & filePath)
{
	QImage newImage = QImage(image);
	QPainter painter;
	painter.begin(&newImage);
	painter.drawImage(0, 0, QImage(filePath));
	painter.end();
	return newImage;
}
