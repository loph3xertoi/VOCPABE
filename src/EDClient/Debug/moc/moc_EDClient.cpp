/****************************************************************************
** Meta object code from reading C++ file 'EDClient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../EDClient.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EDClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EDClient_t {
    const uint offsetsAndSize[26];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_EDClient_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_EDClient_t qt_meta_stringdata_EDClient = {
    {
QT_MOC_LITERAL(0, 8), // "EDClient"
QT_MOC_LITERAL(9, 9), // "recvLogin"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 10), // "getMsgInfo"
QT_MOC_LITERAL(31, 14), // "processMsgFile"
QT_MOC_LITERAL(46, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(68, 7), // "downMsg"
QT_MOC_LITERAL(76, 10), // "enableDown"
QT_MOC_LITERAL(87, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(111, 18), // "showLoggedUserInfo"
QT_MOC_LITERAL(130, 8), // "QString&"
QT_MOC_LITERAL(139, 14), // "loggedUserInfo"
QT_MOC_LITERAL(154, 16) // "showSSMsgCatalog"

    },
    "EDClient\0recvLogin\0\0getMsgInfo\0"
    "processMsgFile\0on_pushButton_clicked\0"
    "downMsg\0enableDown\0on_pushButton_2_clicked\0"
    "showLoggedUserInfo\0QString&\0loggedUserInfo\0"
    "showSSMsgCatalog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EDClient[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    0 /* Private */,
       3,    0,   69,    2, 0x08,    1 /* Private */,
       4,    0,   70,    2, 0x08,    2 /* Private */,
       5,    0,   71,    2, 0x08,    3 /* Private */,
       6,    0,   72,    2, 0x08,    4 /* Private */,
       7,    0,   73,    2, 0x08,    5 /* Private */,
       8,    0,   74,    2, 0x08,    6 /* Private */,
       9,    1,   75,    2, 0x0a,    7 /* Public */,
      12,    0,   78,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void EDClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EDClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recvLogin(); break;
        case 1: _t->getMsgInfo(); break;
        case 2: _t->processMsgFile(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->downMsg(); break;
        case 5: _t->enableDown(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->showLoggedUserInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->showSSMsgCatalog(); break;
        default: ;
        }
    }
}

const QMetaObject EDClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EDClient.offsetsAndSize,
    qt_meta_data_EDClient,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_EDClient_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *EDClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EDClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EDClient.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EDClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
