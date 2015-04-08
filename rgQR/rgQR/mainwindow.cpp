#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <objectinspector.h>
#include <QLabel>
#include <QDockWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    objectInspector(new ObjectInspector("build Information", this))
{
    ui->setupUi(this);
    addDockWidget(Qt::LeftDockWidgetArea, objectInspector);
}

MainWindow::~MainWindow()
{
    delete ui;
}
