#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "abstractshape.h"

class Ellipse : public AbstractShape
{
public:
	explicit Ellipse(QObject* parent = nullptr);
	explicit Ellipse(QPoint, QPoint, QObject* = nullptr);
	void paint(QPaintDevice* Dev, QPainter* painter) final;
	const bool containsPoint(QPoint point);
	const int getTypeNumber() final;
};

#endif // ELLIPSE_H
