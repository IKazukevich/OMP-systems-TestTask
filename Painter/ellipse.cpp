#include "ellipse.h"

Ellipse::Ellipse(QObject *parent)
	: AbstractShape{parent}
{

}

Ellipse::Ellipse(QPoint p1, QPoint p2, QObject *parent)
	: AbstractShape{parent}
{
	BotLeft.setX(fmin(p1.x(), p2.x()));
	BotLeft.setY(fmax(p1.y(), p2.y()));
	TopRight.setX(fmax(p1.x(), p2.x()));
	TopRight.setY(fmin(p1.y(), p2.y()));
}

void Ellipse::paint(QPaintDevice* Dev, QPainter* painter)
{
	painter->drawEllipse(QRect(this->BotLeft, this->TopRight));
}

const bool Ellipse::containsPoint(QPoint point)
{
	float EllCenterX, EllCenterY, EllHeight, EllLength;
	EllCenterX = (this->BotLeft.x() + this->TopRight.x())/2;
	EllCenterY = (this->BotLeft.y() + this->TopRight.y())/2;
	EllLength = (this->TopRight.x() - this->BotLeft.x())/2;
	EllHeight = (this->BotLeft.y() - this->TopRight.y())/2;

	float result = (point.x() - EllCenterX) * (point.x() - EllCenterX) / (EllLength * EllLength)
			+ (point.y() - EllCenterY) * (point.y() - EllCenterY) / (EllHeight * EllHeight);
	return (result <= 1);
}

const int Ellipse::getTypeNumber(){
	return 3;
}
