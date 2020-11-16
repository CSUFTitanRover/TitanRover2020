/****************************************************************************
** Meta object code from reading C++ file 'tcplistenerthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../server/tcplistenerthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcplistenerthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TcpListenerThread_t {
    QByteArrayData data[11];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpListenerThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpListenerThread_t qt_meta_stringdata_TcpListenerThread = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TcpListenerThread"
QT_MOC_LITERAL(1, 18, 15), // "deviceConnected"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "cameraId"
QT_MOC_LITERAL(4, 44, 8), // "socketFd"
QT_MOC_LITERAL(5, 53, 18), // "deviceDisconnected"
QT_MOC_LITERAL(6, 72, 17), // "sendConfiguration"
QT_MOC_LITERAL(7, 90, 19), // "ConfigurationPacket"
QT_MOC_LITERAL(8, 110, 8), // "confPack"
QT_MOC_LITERAL(9, 119, 9), // "sendPause"
QT_MOC_LITERAL(10, 129, 13) // "sendHeartbeat"

    },
    "TcpListenerThread\0deviceConnected\0\0"
    "cameraId\0socketFd\0deviceDisconnected\0"
    "sendConfiguration\0ConfigurationPacket\0"
    "confPack\0sendPause\0sendHeartbeat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpListenerThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   49,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    3,    8,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void TcpListenerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpListenerThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceConnected((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->deviceDisconnected((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendConfiguration((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ConfigurationPacket(*)>(_a[2]))); break;
        case 3: _t->sendPause((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sendHeartbeat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpListenerThread::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpListenerThread::deviceConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpListenerThread::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpListenerThread::deviceDisconnected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TcpListenerThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_TcpListenerThread.data,
    qt_meta_data_TcpListenerThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TcpListenerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpListenerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TcpListenerThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TcpListenerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TcpListenerThread::deviceConnected(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpListenerThread::deviceDisconnected(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
