#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent)
	: QWidget{parent}
{
	this->actionType = PaintArea::ActionType::no_action;
	eventCancelled = true;
	drawingShape = nullptr;
	firstPointSet = false;
	drawingLine = nullptr;

	firstPointShapeID = -1;
	secondPointShapeID = -1;
}

void PaintArea::setActionRectangle(){
	qDebug() << "Button 1 pressed";
	this->actionType = PaintArea::ActionType::rectangle;
}

void PaintArea::setActionTriangle(){
	qDebug() << "Button 2 pressed";
	this->actionType = PaintArea::ActionType::triangle;
}

void PaintArea::setActionEllipse(){
	qDebug() << "Button 3 pressed";
	this->actionType = PaintArea::ActionType::ellipse;
}

void PaintArea::setActionBond(){
	qDebug() << "Button 4 pressed";
	this->actionType = PaintArea::ActionType::bond;
}

void PaintArea::setActionMove(){
	qDebug() << "Button 5 pressed";
	this->actionType = PaintArea::ActionType::move;
}

void PaintArea::setActionErase(){
	qDebug() << "Button 6 pressed";
	this->actionType = PaintArea::ActionType::erase;
}

void PaintArea::loadPaintArea()
{
	std::fstream file;
	file.open("ShapesAndLines.dat",  std::fstream::in | std::fstream::out | std::fstream::binary);

	qint64 var, var2, var3, var4, var5;
	file.read((char*)&var, sizeof(var));
	shapes.resize(var);
	for (int i = 0; i < shapes.size(); i++) {
		file.read((char*)&var, sizeof(var));
		if(var == 1)shapes[i] = new Triangle();else
			if(var == 2)shapes[i] = new Rectangle();else
				if(var == 3)shapes[i] = new Ellipse();
		file.read((char*)&var2, sizeof(var2));
		file.read((char*)&var3, sizeof(var3));
		file.read((char*)&var4, sizeof(var4));
		file.read((char*)&var5, sizeof(var5));
		shapes[i]->setCoords(QPoint(var2, var3), QPoint(var4, var5));
	}

	file.read((char*)&var, sizeof(var));
	lines.clearAll();
	for(int i = 0; i < var; i++){
		file.read((char*)&var2, sizeof(var));
		file.read((char*)&var3, sizeof(var));
		lines.addID(var2, var3);
	}

	file.close();
	update();
}

void PaintArea::savePaintArea()
{
	std::fstream file;
	file.open("ShapesAndLines.dat", std::fstream::trunc | std::fstream::in | std::fstream::out | std::fstream::binary);

	qint64 var;
	var = shapes.size();
	file.write((char*)&var, sizeof(var));
	for (int i = 0; i < shapes.size(); i++) {
		var = shapes[i]->getTypeNumber();
		file.write((char*)&var, sizeof(var));
		var = shapes[i]->getBotLeft().x();
		file.write((char*)&var, sizeof(var));
		var = shapes[i]->getBotLeft().y();
		file.write((char*)&var, sizeof(var));
		var = shapes[i]->getTopRight().x();
		file.write((char*)&var, sizeof(var));
		var = shapes[i]->getTopRight().y();
		file.write((char*)&var, sizeof(var));
	}
	var = lines.getSize();
	file.write((char*)&var, sizeof(var));
	for(int i = 0; i < lines.getSize(); i++){
		var = lines.getID1(i);
		file.write((char*)&var, sizeof(var));
		var = lines.getID2(i);
		file.write((char*)&var, sizeof(var));
	}

	file.close();
}



void PaintArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		startPoint = event->position().toPoint();
		switch(this->actionType){
		case ActionType::rectangle:{
			drawingShape = new Rectangle();
			eventCancelled = false;
			break;
		}
		case ActionType::triangle:{
			drawingShape = new Triangle();
			eventCancelled = false;
			break;
		}
		case ActionType::ellipse:{
			drawingShape = new Ellipse();
			eventCancelled = false;
			break;
		}
		case ActionType::bond:{
			if(!firstPointSet){
				for(int i = 0; i < shapes.size(); i++){
					if(shapes[i]->containsPoint(startPoint)){
						eventCancelled = false;
						firstPointShapeID = i;
						return;
					}
				}
			}else{
				if(!eventCancelled){
					for(int i = 0; i < shapes.size(); i++){ // Новые фигуры перекрываются старыми
						if(shapes[i]->containsPoint(startPoint)){
							secondPointShapeID = i;
							return;
						}
					}
				}
			}
			break;
		}
		case ActionType::move:{
			for(int i = 0; i < shapes.size(); i++){
				if(shapes[i]->containsPoint(startPoint)){
					eventCancelled = false;
					firstPointShapeID = i;

					return;
				}
			}
			firstPointShapeID = -1; // Под курсором нет фигуры
			break;
		}
		case ActionType::erase:{
			for(int i = 0; i < shapes.size(); i++){
				if(shapes[i]->containsPoint(startPoint)){
					eventCancelled = false;
					firstPointShapeID = i;

					return;
				}
			}
			firstPointShapeID = -1; // Под курсором нет фигуры
			break;
		}
		case ActionType::no_action:{}
		}
	}
	if(event->button() == Qt::RightButton){
		eventCancelled = true;
		drawingShape = nullptr;
		firstPointSet = false;
		drawingLine = nullptr;
		this->setMouseTracking(0);
		update();
	}
}

void PaintArea::keyPressEvent(QKeyEvent *event){
	if(event->key() == Qt::Key_Escape){
		eventCancelled = true;
		drawingShape = nullptr;
		firstPointSet = false;
		drawingLine = nullptr;
		this->setMouseTracking(0);
		update();
	}
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
	if (!eventCancelled && ((event->buttons() == Qt::LeftButton) || hasMouseTracking())){
		switch(this->actionType){
		case ActionType::rectangle:
		case ActionType::triangle:
		case ActionType::ellipse:{
			if(drawingShape!=nullptr)
				drawingShape->setCoords(event->position().toPoint(), startPoint);
			update();
			break;
		}
		case ActionType::bond:{
			if((drawingLine!=nullptr) && firstPointSet)
				drawingLine->setP2(event->position().toPoint());
			update();
			break;
		}
		case ActionType::move:{
			if(firstPointShapeID != -1){
				QPoint delta(event->position().toPoint() - startPoint);
				startPoint = event->position().toPoint();
				shapes[firstPointShapeID]->moveCoors(delta);
				update();
			}
			break;
		}
		case ActionType::erase:{
			// Пусто
			break;
		}
		case ActionType::no_action:{}
		}
	}
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
	if (!eventCancelled && (event->buttons() != Qt::LeftButton)){
		switch(this->actionType){
		case ActionType::rectangle:{
			shapes.append(new Rectangle(drawingShape->getBotLeft(), drawingShape->getTopRight()));
			drawingShape = nullptr;
			update();
			break;
		}
		case ActionType::triangle:{
			shapes.append(new Triangle(drawingShape->getBotLeft(), drawingShape->getTopRight()));
			drawingShape = nullptr;
			update();
			break;
		}
		case ActionType::ellipse:{
			shapes.append(new Ellipse(drawingShape->getBotLeft(), drawingShape->getTopRight()));
			drawingShape = nullptr;
			update();
			break;
		}
		case ActionType::bond:{
			if(!firstPointSet){

				if(firstPointShapeID == -1)return;
				if(shapes[firstPointShapeID]->containsPoint(event->position().toPoint())){
					firstPointSet = true;
					drawingLine = new QLine(shapes[firstPointShapeID]->getCenter(), event->position().toPoint());
					this->setMouseTracking(1);	// если указатель мыши не переместился
					update();					// на другую фигуру в процессе клика
					return;
				}else {
					eventCancelled = true;
					drawingShape = nullptr;
					firstPointSet = false; // optimize
					drawingLine = nullptr;
					this->setMouseTracking(0);
					update();
				}
			}else {
				if(secondPointShapeID == -1)return;
				if(shapes[secondPointShapeID]->containsPoint(event->position().toPoint())){
					this->setMouseTracking(0);
					firstPointSet = false;
					lines.addID(firstPointShapeID, secondPointShapeID);
					drawingLine = nullptr;
					update();
					return;
				}else{
					eventCancelled = true;
					drawingShape = nullptr;
					firstPointSet = false;
					drawingLine = nullptr;
					this->setMouseTracking(0);
					update();
				}
			}
			break;
		}
		case ActionType::move:{
			// Пусто
			break;
		}
		case ActionType::erase:{
			for(int i = 0; i < shapes.size(); i++){
				if(shapes[i]->containsPoint(startPoint)){
					if(i == firstPointShapeID){
						shapes.remove(i);
						lines.delID(i);
						update();
						return;
					}
				}
			}
			break;
		}
		case ActionType::no_action:{}
		}
	}
}

void PaintArea::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	if(!painter.isActive())
		painter.begin(this);

	if((drawingLine != nullptr) && firstPointSet)painter.drawLine(*drawingLine);
	if(drawingShape!= nullptr)drawingShape->paint(this, &painter);

	for(int i = 0; i < lines.getSize(); i++){
		QLine line(shapes[lines.getID1(i)]->getCenter(), shapes[lines.getID2(i)]->getCenter());
		painter.drawLine(line);
	}

	for(int i = 0; i < shapes.size(); i++){
		shapes[i]->paint(this, &painter);
	}

	if(painter.isActive())
		painter.end();
}
