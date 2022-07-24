#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <fstream>
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "storagepairedid.h"

class PaintArea : public QWidget
{
	Q_OBJECT

public:
	enum ActionType{no_action, rectangle, triangle, ellipse, bond, move, erase};

	explicit PaintArea(QWidget *parent = nullptr);

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *event)override;
	void paintEvent(QPaintEvent *event) override;

public slots:
	void setActionRectangle();
	void setActionTriangle();
	void setActionEllipse();
	void setActionBond();
	void setActionMove();
	void setActionErase();
	void loadPaintArea();
	void savePaintArea();

signals:

private:

	void Reset();

	QPoint startPoint;
	bool firstPointSet;

	int firstPointShapeID;
	int secondPointShapeID;

	bool eventCancelled;

	AbstractShape* drawingShape = nullptr;
	QLine* drawingLine = nullptr;

	QVector<AbstractShape*> shapes;
	StoragePairedID lines;

	ActionType actionType;
};

#endif // PAINTAREA_H
