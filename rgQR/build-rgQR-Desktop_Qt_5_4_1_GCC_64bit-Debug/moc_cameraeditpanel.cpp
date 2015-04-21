/****************************************************************************
** Meta object code from reading C++ file 'cameraeditpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rgQR/cameraeditpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraeditpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraEditPanel_t {
    QByteArrayData data[11];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraEditPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraEditPanel_t qt_meta_stringdata_CameraEditPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CameraEditPanel"
QT_MOC_LITERAL(1, 16, 16), // "changeProjection"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 9), // "changeFov"
QT_MOC_LITERAL(5, 50, 9), // "changeFar"
QT_MOC_LITERAL(6, 60, 10), // "changeNear"
QT_MOC_LITERAL(7, 71, 11), // "changeViewX"
QT_MOC_LITERAL(8, 83, 11), // "changeViewY"
QT_MOC_LITERAL(9, 95, 11), // "changeViewW"
QT_MOC_LITERAL(10, 107, 11) // "changeViewH"

    },
    "CameraEditPanel\0changeProjection\0\0"
    "index\0changeFov\0changeFar\0changeNear\0"
    "changeViewX\0changeViewY\0changeViewW\0"
    "changeViewH"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraEditPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CameraEditPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraEditPanel *_t = static_cast<CameraEditPanel *>(_o);
        switch (_id) {
        case 0: _t->changeProjection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeFov(); break;
        case 2: _t->changeFar(); break;
        case 3: _t->changeNear(); break;
        case 4: _t->changeViewX(); break;
        case 5: _t->changeViewY(); break;
        case 6: _t->changeViewW(); break;
        case 7: _t->changeViewH(); break;
        default: ;
        }
    }
}

const QMetaObject CameraEditPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraEditPanel.data,
      qt_meta_data_CameraEditPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraEditPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraEditPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraEditPanel.stringdata))
        return static_cast<void*>(const_cast< CameraEditPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraEditPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
