#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "abstractshape.h"
#include <QDebug>

class Triangle : public AbstractShape
{
public:
	explicit Triangle(QObject* parent = nullptr);
	explicit Triangle(QPoint, QPoint, QObject* = nullptr);
	void paint(QPaintDevice* Dev, QPainter* painter) final;
	const bool containsPoint(QPoint point);
	const int getTypeNumber() final;
private:
	float area(QPoint,QPoint,QPoint);
};

#endif // TRIANGLE_H
