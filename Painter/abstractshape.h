#ifndef ABSTRACTSHAPE_H
#define ABSTRACTSHAPE_H

#include <QObject>
#include <QPainter>

class AbstractShape : public QObject
{
	Q_OBJECT
public:

	explicit AbstractShape(QObject *p = nullptr);
	explicit AbstractShape(QPoint, QPoint, QObject *p);
	virtual bool containsPoint(QPoint point) = 0;
	void setCoords(QPoint BotLeft, QPoint TopRight);
	void moveCoors(QPoint delta);
	virtual void paint(QPaintDevice* Dev, QPainter* painter) = 0;
	virtual int getTypeNumber() = 0;
	QPoint getTopRight();
	QPoint getBotLeft();
	QPoint getCenter();

signals:


protected:
	QPoint BotLeft, TopRight;
};

#endif // ABSTRACTSHAPE_H
