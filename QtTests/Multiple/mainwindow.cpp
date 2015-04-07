#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <toolitem.h>

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QListWidget *list = new QListWidget;
  list->addItem("One");
  list->addItem("Two");
  list->addItem("Three");

  ToolBox *toolBox = new ToolBox;
  toolBox->addItem(new ToolItem("Title 1", new QLabel("Some text here")));
  toolBox->addItem(new ToolItem("Title 2", list));
  toolBox->addItem(new ToolItem("Title 3", new QLabel("Lorem Ipsum..")));
  //toolBox->hideItem(1);

  ToolItem* item = toolBox->itemAt(2);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(toolBox);
  ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow() { delete ui; }

