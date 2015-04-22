/****************************************************************************
** Meta object code from reading C++ file 'lighteditpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../rgQR/lighteditpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lighteditpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LightEditPanel_t {
    QByteArrayData data[13];
    char stringdata[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LightEditPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LightEditPanel_t qt_meta_stringdata_LightEditPanel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "LightEditPanel"
QT_MOC_LITERAL(1, 15, 11), // "pickLaColor"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "pickLdColor"
QT_MOC_LITERAL(4, 40, 11), // "pickLsColor"
QT_MOC_LITERAL(5, 52, 15), // "changeLightType"
QT_MOC_LITERAL(6, 68, 5), // "index"
QT_MOC_LITERAL(7, 74, 8), // "changeAa"
QT_MOC_LITERAL(8, 83, 8), // "changeAb"
QT_MOC_LITERAL(9, 92, 8), // "changeAc"
QT_MOC_LITERAL(10, 101, 15), // "changeSpotAngle"
QT_MOC_LITERAL(11, 117, 19), // "changeSpotCosCutoff"
QT_MOC_LITERAL(12, 137, 18) // "changeSpotExponent"

    },
    "LightEditPanel\0pickLaColor\0\0pickLdColor\0"
    "pickLsColor\0changeLightType\0index\0"
    "changeAa\0changeAb\0changeAc\0changeSpotAngle\0"
    "changeSpotCosCutoff\0changeSpotExponent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LightEditPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    1,   67,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LightEditPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LightEditPanel *_t = static_cast<LightEditPanel *>(_o);
        switch (_id) {
        case 0: _t->pickLaColor(); break;
        case 1: _t->pickLdColor(); break;
        case 2: _t->pickLsColor(); break;
        case 3: _t->changeLightType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeAa(); break;
        case 5: _t->changeAb(); break;
        case 6: _t->changeAc(); break;
        case 7: _t->changeSpotAngle(); break;
        case 8: _t->changeSpotCosCutoff(); break;
        case 9: _t->changeSpotExponent(); break;
        default: ;
        }
    }
}

const QMetaObject LightEditPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LightEditPanel.data,
      qt_meta_data_LightEditPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LightEditPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LightEditPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LightEditPanel.stringdata))
        return static_cast<void*>(const_cast< LightEditPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int LightEditPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
