#include "abstractshape.h"

AbstractShape::AbstractShape(QObject *parent)
	: QObject{parent}
{

}

AbstractShape::AbstractShape(QPoint p1, QPoint p2,QObject *parent = nullptr)
	: QObject{parent}
{
	BotLeft.setX(fmin(p1.x(), p2.x()));
	BotLeft.setY(fmax(p1.y(), p2.y()));
	TopRight.setX(fmax(p1.x(), p2.x()));
	TopRight.setY(fmin(p1.y(), p2.y()));
}

void AbstractShape::setCoords(QPoint p1, QPoint p2){
	BotLeft.setX(fmin(p1.x(), p2.x()));
	BotLeft.setY(fmax(p1.y(), p2.y()));
	TopRight.setX(fmax(p1.x(), p2.x()));
	TopRight.setY(fmin(p1.y(), p2.y()));
}

void AbstractShape::moveCoors(QPoint delta)
{
	BotLeft+=delta;
	TopRight+=delta;
}

QPoint AbstractShape::getTopRight()
{
	return TopRight;
}

QPoint AbstractShape::getBotLeft()
{
	return BotLeft;
}

QPoint AbstractShape::getCenter()
{
	return (BotLeft+TopRight)/2;
}
