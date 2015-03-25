#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <io/jsoncons/json.hpp>



#define GLEW_STATIC
#include <GL/glew.h>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QWindow>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSurfaceFormat requestedFormat;
    requestedFormat.setVersion( 3, 3 );

    QOpenGLContext * context = new QOpenGLContext(ui->openGLWidget);
    context->setFormat( requestedFormat );
    context->create();

    GLenum err = glewInit();
    if (err != GLEW_NO_ERROR) {
      printf("GLew Error = %s\n",glewGetErrorString(err));
      exit(-1);
    }


    Scene.loadFromJsonFile("");
    Scene.dumpTree();
}





MainWindow::~MainWindow()
{
    delete ui;
}
