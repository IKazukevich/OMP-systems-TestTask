#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "abstractshape.h"

#include <QPoint>

class Rectangle : public AbstractShape
{
public:
	explicit Rectangle(QObject* parent = nullptr);
	explicit Rectangle(QPoint, QPoint, QObject* = nullptr);
	void paint(QPaintDevice* Dev, QPainter* painter) final;
	const bool containsPoint(QPoint point);
	const int getTypeNumber() final;
};

#endif // RECTANGLE_H
