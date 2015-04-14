/****************************************************************************
** Meta object code from reading C++ file 'objectinspector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rgQR/objectinspector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectinspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ObjectInspector_t {
    QByteArrayData data[16];
    char stringdata[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObjectInspector_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObjectInspector_t qt_meta_stringdata_ObjectInspector = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ObjectInspector"
QT_MOC_LITERAL(1, 16, 10), // "changeName"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "changePosX"
QT_MOC_LITERAL(4, 39, 10), // "changePosY"
QT_MOC_LITERAL(5, 50, 10), // "changePosZ"
QT_MOC_LITERAL(6, 61, 10), // "changeRotX"
QT_MOC_LITERAL(7, 72, 10), // "changeRotY"
QT_MOC_LITERAL(8, 83, 10), // "changeRotZ"
QT_MOC_LITERAL(9, 94, 10), // "changeScaX"
QT_MOC_LITERAL(10, 105, 10), // "changeScaY"
QT_MOC_LITERAL(11, 116, 10), // "changeScaZ"
QT_MOC_LITERAL(12, 127, 16), // "treeItemSelected"
QT_MOC_LITERAL(13, 144, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(14, 161, 5), // "QItem"
QT_MOC_LITERAL(15, 167, 6) // "column"

    },
    "ObjectInspector\0changeName\0\0changePosX\0"
    "changePosY\0changePosZ\0changeRotX\0"
    "changeRotY\0changeRotZ\0changeScaX\0"
    "changeScaY\0changeScaZ\0treeItemSelected\0"
    "QTreeWidgetItem*\0QItem\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectInspector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    2,   84,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,   14,   15,
    QMetaType::Void,

       0        // eod
};

void ObjectInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObjectInspector *_t = static_cast<ObjectInspector *>(_o);
        switch (_id) {
        case 0: _t->changeName(); break;
        case 1: _t->changePosX(); break;
        case 2: _t->changePosY(); break;
        case 3: _t->changePosZ(); break;
        case 4: _t->changeRotX(); break;
        case 5: _t->changeRotY(); break;
        case 6: _t->changeRotZ(); break;
        case 7: _t->changeScaX(); break;
        case 8: _t->changeScaY(); break;
        case 9: _t->changeScaZ(); break;
        case 10: _t->treeItemSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->treeItemSelected(); break;
        default: ;
        }
    }
}

const QMetaObject ObjectInspector::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_ObjectInspector.data,
      qt_meta_data_ObjectInspector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ObjectInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectInspector.stringdata))
        return static_cast<void*>(const_cast< ObjectInspector*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int ObjectInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
