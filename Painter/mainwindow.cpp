#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->paintArea->setBackgroundRole(QPalette::Base);

	connect(ui->b1_rectangle, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionRectangle);
	connect(ui->b2_triangle, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionTriangle);
	connect(ui->b3_ellipse, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionEllipse);
	connect(ui->b4_bond, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionBond);
	connect(ui->b5_move, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionMove);
	connect(ui->b6_erase, &QAbstractButton::clicked, ui->paintArea, &PaintArea::setActionErase);
	connect(ui->b7_load, &QAbstractButton::clicked, ui->paintArea, &PaintArea::loadPaintArea);
	connect(ui->b8_save, &QAbstractButton::clicked, ui->paintArea, &PaintArea::savePaintArea);

// B7, B8
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){ // Отпраляем Esc доске для рисования
	if(event->key() == Qt::Key_Escape){
		QCoreApplication::sendEvent(ui->paintArea, event);
	}
}

