/****************************************************************************
** Meta object code from reading C++ file 'RegisterLogin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RegisterLogin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RegisterLogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RegisterLogin_t {
    const uint offsetsAndSize[56];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_RegisterLogin_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_RegisterLogin_t qt_meta_stringdata_RegisterLogin = {
    {
QT_MOC_LITERAL(0, 13), // "RegisterLogin"
QT_MOC_LITERAL(14, 11), // "querySignal"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 5), // "bool&"
QT_MOC_LITERAL(33, 3), // "ret"
QT_MOC_LITERAL(37, 12), // "tableToQuery"
QT_MOC_LITERAL(50, 5), // "field"
QT_MOC_LITERAL(56, 9), // "queryQstr"
QT_MOC_LITERAL(66, 12), // "insertSignal"
QT_MOC_LITERAL(79, 4), // "name"
QT_MOC_LITERAL(84, 6), // "passwd"
QT_MOC_LITERAL(91, 13), // "isMatchSignal"
QT_MOC_LITERAL(105, 13), // "isValidCookie"
QT_MOC_LITERAL(119, 6), // "cookie"
QT_MOC_LITERAL(126, 17), // "getAPMatrixSignal"
QT_MOC_LITERAL(144, 8), // "QString&"
QT_MOC_LITERAL(153, 8), // "APMatrix"
QT_MOC_LITERAL(162, 12), // "QStringList&"
QT_MOC_LITERAL(175, 6), // "APList"
QT_MOC_LITERAL(182, 4), // "int&"
QT_MOC_LITERAL(187, 7), // "MaxSize"
QT_MOC_LITERAL(195, 13), // "getMUIDSignal"
QT_MOC_LITERAL(209, 4), // "MUID"
QT_MOC_LITERAL(214, 15), // "insertAPMSignal"
QT_MOC_LITERAL(230, 12), // "AccessPolicy"
QT_MOC_LITERAL(243, 16), // "getOrderHxSignal"
QT_MOC_LITERAL(260, 6), // "APQstr"
QT_MOC_LITERAL(267, 5) // "HXNUM"

    },
    "RegisterLogin\0querySignal\0\0bool&\0ret\0"
    "tableToQuery\0field\0queryQstr\0insertSignal\0"
    "name\0passwd\0isMatchSignal\0isValidCookie\0"
    "cookie\0getAPMatrixSignal\0QString&\0"
    "APMatrix\0QStringList&\0APList\0int&\0"
    "MaxSize\0getMUIDSignal\0MUID\0insertAPMSignal\0"
    "AccessPolicy\0getOrderHxSignal\0APQstr\0"
    "HXNUM"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RegisterLogin[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   62,    2, 0x06,    0 /* Public */,
       8,    3,   71,    2, 0x06,    5 /* Public */,
      11,    3,   78,    2, 0x06,    9 /* Public */,
      12,    2,   85,    2, 0x06,   13 /* Public */,
      14,    3,   90,    2, 0x06,   16 /* Public */,
      21,    2,   97,    2, 0x06,   20 /* Public */,
      23,    3,  102,    2, 0x06,   23 /* Public */,
      25,    2,  109,    2, 0x06,   27 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    9,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    9,   10,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,   13,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17, 0x80000000 | 19,   16,   18,   20,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17,   22,   18,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15, 0x80000000 | 15,   24,   16,   22,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   26,   27,

       0        // eod
};

void RegisterLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RegisterLogin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->querySignal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 1: _t->insertSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: _t->isMatchSignal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->isValidCookie((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->getAPMatrixSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->getMUIDSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 6: _t->insertAPMSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->getOrderHxSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RegisterLogin::*)(bool & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::querySignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::insertSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(bool & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::isMatchSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(bool & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::isValidCookie)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(QString & , QStringList & , int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::getAPMatrixSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(QString & , QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::getMUIDSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(QString & , QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::insertAPMSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (RegisterLogin::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegisterLogin::getOrderHxSignal)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject RegisterLogin::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RegisterLogin.offsetsAndSize,
    qt_meta_data_RegisterLogin,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_RegisterLogin_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QStringList &, std::false_type>, QtPrivate::TypeAndForceComplete<int &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QStringList &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>



>,
    nullptr
} };


const QMetaObject *RegisterLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegisterLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RegisterLogin.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RegisterLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RegisterLogin::querySignal(bool & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RegisterLogin::insertSignal(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RegisterLogin::isMatchSignal(bool & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RegisterLogin::isValidCookie(bool & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RegisterLogin::getAPMatrixSignal(QString & _t1, QStringList & _t2, int & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RegisterLogin::getMUIDSignal(QString & _t1, QStringList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void RegisterLogin::insertAPMSignal(QString & _t1, QString & _t2, QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void RegisterLogin::getOrderHxSignal(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
