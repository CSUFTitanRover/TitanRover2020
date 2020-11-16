/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../server/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "configurationReady"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "cameraId"
QT_MOC_LITERAL(4, 40, 19), // "ConfigurationPacket"
QT_MOC_LITERAL(5, 60, 8), // "confPack"
QT_MOC_LITERAL(6, 69, 9), // "addDevice"
QT_MOC_LITERAL(7, 79, 2), // "fd"
QT_MOC_LITERAL(8, 82, 12), // "removeDevice"
QT_MOC_LITERAL(9, 95, 9), // "setCamera"
QT_MOC_LITERAL(10, 105, 16), // "setConfiguration"
QT_MOC_LITERAL(11, 122, 15), // "configurationId"
QT_MOC_LITERAL(12, 138, 17), // "createPopupWindow"
QT_MOC_LITERAL(13, 156, 18), // "videoListenerIndex"
QT_MOC_LITERAL(14, 175, 16), // "getConfiguration"
QT_MOC_LITERAL(15, 192, 9), // "viewIndex"
QT_MOC_LITERAL(16, 202, 7), // "quality"
QT_MOC_LITERAL(17, 210, 11), // "handlePause"
QT_MOC_LITERAL(18, 222, 13) // "viewportIndex"

    },
    "MainWindow\0configurationReady\0\0cameraId\0"
    "ConfigurationPacket\0confPack\0addDevice\0"
    "fd\0removeDevice\0setCamera\0setConfiguration\0"
    "configurationId\0createPopupWindow\0"
    "videoListenerIndex\0getConfiguration\0"
    "viewIndex\0quality\0handlePause\0"
    "viewportIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   59,    2, 0x0a /* Public */,
       8,    2,   64,    2, 0x0a /* Public */,
       9,    1,   69,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,
      14,    3,   78,    2, 0x0a /* Public */,
      17,    1,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    7,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   15,    3,   16,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->configurationReady((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ConfigurationPacket(*)>(_a[2]))); break;
        case 1: _t->addDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->removeDevice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setCamera((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setConfiguration((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->createPopupWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->getConfiguration((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->handlePause((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString , ConfigurationPacket );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::configurationReady)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MainWindow::configurationReady(const QString _t1, ConfigurationPacket _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
