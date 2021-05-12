/****************************************************************************
** Meta object code from reading C++ file 'ServerSetup.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ServerSetup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerSetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerSetup_t {
    const uint offsetsAndSize[30];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ServerSetup_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ServerSetup_t qt_meta_stringdata_ServerSetup = {
    {
QT_MOC_LITERAL(0, 11), // "ServerSetup"
QT_MOC_LITERAL(12, 11), // "loginSignal"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 4), // "name"
QT_MOC_LITERAL(30, 6), // "logOut"
QT_MOC_LITERAL(37, 6), // "cookie"
QT_MOC_LITERAL(44, 17), // "isAbleDecrySignal"
QT_MOC_LITERAL(62, 4), // "MUID"
QT_MOC_LITERAL(67, 18), // "readAndProcessData"
QT_MOC_LITERAL(86, 8), // "readData"
QT_MOC_LITERAL(95, 13), // "detectConnect"
QT_MOC_LITERAL(109, 12), // "displayError"
QT_MOC_LITERAL(122, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(151, 11), // "socketError"
QT_MOC_LITERAL(163, 16) // "serverDisconnect"

    },
    "ServerSetup\0loginSignal\0\0name\0logOut\0"
    "cookie\0isAbleDecrySignal\0MUID\0"
    "readAndProcessData\0readData\0detectConnect\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "socketError\0serverDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerSetup[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    0 /* Public */,
       4,    2,   65,    2, 0x06,    2 /* Public */,
       6,    2,   70,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   75,    2, 0x08,    8 /* Private */,
       9,    0,   76,    2, 0x08,    9 /* Private */,
      10,    0,   77,    2, 0x08,   10 /* Private */,
      11,    1,   78,    2, 0x08,   11 /* Private */,
      14,    0,   81,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QStringList,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

       0        // eod
};

void ServerSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerSetup *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loginSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->logOut((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->isAbleDecrySignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->readAndProcessData(); break;
        case 4: { QStringList _r = _t->readData();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->detectConnect(); break;
        case 6: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: _t->serverDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerSetup::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSetup::loginSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerSetup::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSetup::logOut)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerSetup::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerSetup::isAbleDecrySignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ServerSetup::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ServerSetup.offsetsAndSize,
    qt_meta_data_ServerSetup,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ServerSetup_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QStringList, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ServerSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerSetup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ServerSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ServerSetup::loginSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerSetup::logOut(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerSetup::isAbleDecrySignal(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
