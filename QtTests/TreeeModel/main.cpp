#include "mainwindow.h"
#include <QApplication>
#include <gl/rgglcamera.h>
#include <gl/rgglobject.h>
#include <gl/rgglcuboid.h>

int main(int argc, char *argv[])
{
    rg::GLObject* Root = new rg::GLObject("ROOT", rg::GLObject::ROOT);
    rg::GLObject* Obj1 = new rg::GLObject("OBJ1", rg::GLObject::CAMERA, Root);
    rg::GLObject* Obj2 = new rg::GLObject("OBJ2", rg::GLObject::LIGHT, Root);
    rg::GLObject* Obj3 = new rg::GLObject("OBJ3", rg::GLObject::OBJECT3D, Obj2);
    rg::GLCamera* cam = new rg::GLCamera("CAM1", Root);
    rg::GLCuboid* cube = new rg::GLCuboid("CUBE1", cam);

    for(auto& e : Root->getChildren()) {
        std::cout << e.second->getName() << std::endl;
        for (auto& se : e.second->getChildren())
            std::cout << "  " << se.second->getName() << std::endl;
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
