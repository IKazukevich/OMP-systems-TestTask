#include "rectangle.h"

Rectangle::Rectangle(QObject *parent)
	: AbstractShape{parent}
{

}

Rectangle::Rectangle(QPoint p1, QPoint p2, QObject *parent)
	: AbstractShape{parent}
{
	BotLeft.setX(fmin(p1.x(), p2.x()));
	BotLeft.setY(fmax(p1.y(), p2.y()));
	TopRight.setX(fmax(p1.x(), p2.x()));
	TopRight.setY(fmin(p1.y(), p2.y()));
}

void Rectangle::paint(QPaintDevice* Dev, QPainter* painter)
{
	painter->drawRect(QRect(this->BotLeft, this->TopRight));
}

bool Rectangle::containsPoint(QPoint point){
	QRect test(this->BotLeft, this->TopRight);
	return test.contains(point);
}

int Rectangle::getTypeNumber(){
	return 2;
}
