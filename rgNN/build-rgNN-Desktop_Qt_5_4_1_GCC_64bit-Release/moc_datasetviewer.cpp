/****************************************************************************
** Meta object code from reading C++ file 'datasetviewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../common/datasetviewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datasetviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DatasetViewer_t {
    QByteArrayData data[9];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatasetViewer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatasetViewer_t qt_meta_stringdata_DatasetViewer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DatasetViewer"
QT_MOC_LITERAL(1, 14, 9), // "prevImage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "nextImage"
QT_MOC_LITERAL(4, 35, 10), // "firstImage"
QT_MOC_LITERAL(5, 46, 9), // "lastImage"
QT_MOC_LITERAL(6, 56, 11), // "applyFilter"
QT_MOC_LITERAL(7, 68, 11), // "clearFilter"
QT_MOC_LITERAL(8, 80, 11) // "updateStats"

    },
    "DatasetViewer\0prevImage\0\0nextImage\0"
    "firstImage\0lastImage\0applyFilter\0"
    "clearFilter\0updateStats"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatasetViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DatasetViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DatasetViewer *_t = static_cast<DatasetViewer *>(_o);
        switch (_id) {
        case 0: _t->prevImage(); break;
        case 1: _t->nextImage(); break;
        case 2: _t->firstImage(); break;
        case 3: _t->lastImage(); break;
        case 4: _t->applyFilter(); break;
        case 5: _t->clearFilter(); break;
        case 6: _t->updateStats(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DatasetViewer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DatasetViewer.data,
      qt_meta_data_DatasetViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DatasetViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatasetViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DatasetViewer.stringdata))
        return static_cast<void*>(const_cast< DatasetViewer*>(this));
    return QDialog::qt_metacast(_clname);
}

int DatasetViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
