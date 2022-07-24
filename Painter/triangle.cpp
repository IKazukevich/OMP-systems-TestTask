#include "triangle.h"

Triangle::Triangle(QObject *parent)
	: AbstractShape{parent}
{

}

Triangle::Triangle(QPoint p1, QPoint p2, QObject *parent)
	: AbstractShape{parent}
{
	BotLeft.setX(fmin(p1.x(), p2.x()));
	BotLeft.setY(fmax(p1.y(), p2.y()));
	TopRight.setX(fmax(p1.x(), p2.x()));
	TopRight.setY(fmin(p1.y(), p2.y()));
}

void Triangle::paint(QPaintDevice* Dev, QPainter* painter)
{
	QPoint p1(this->BotLeft.x(), this->BotLeft.y());						 // Нижняя левая точка треугольника
	QPoint p2(this->TopRight.x(), this->BotLeft.y());						 // Нижняя правая точка
	QPoint p3((this->BotLeft.x()+this->TopRight.x())/2, this->TopRight.y()); // Верхняя точка

	painter->drawLine(p1, p2);
	painter->drawLine(p2, p3);
	painter->drawLine(p3, p1);
}

float Triangle::area(QPoint p1, QPoint p2, QPoint p3)
{
   return abs((p1.x()*(p2.y()-p3.y()) + p2.x()*(p3.y()-p1.y())+ p3.x()*(p1.y()-p2.y()))/2.0);
}

const bool Triangle::containsPoint(QPoint point){
	QPoint p1(this->BotLeft.x(), this->BotLeft.y());
	QPoint p2(this->TopRight.x(), this->BotLeft.y());
	QPoint p3((this->BotLeft.x()+this->TopRight.x())/2, this->TopRight.y());

	float A = area (p1, p2, p3);
	float A1 = area (point, p2, p3);
	float A2 = area (p1, point, p3);
	float A3 = area (p1, p2, point);

	return (A == A1 + A2 + A3);
}

const int Triangle::getTypeNumber(){
	return 1;
}
