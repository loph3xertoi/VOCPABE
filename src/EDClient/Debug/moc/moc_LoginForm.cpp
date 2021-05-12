/****************************************************************************
** Meta object code from reading C++ file 'LoginForm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../LoginForm.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginForm_t {
    const uint offsetsAndSize[18];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LoginForm_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LoginForm_t qt_meta_stringdata_LoginForm = {
    {
QT_MOC_LITERAL(0, 9), // "LoginForm"
QT_MOC_LITERAL(10, 8), // "showMain"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 10), // "showLogged"
QT_MOC_LITERAL(31, 8), // "QString&"
QT_MOC_LITERAL(40, 14), // "loggedUserInfo"
QT_MOC_LITERAL(55, 18), // "SSMsgCatalogSignal"
QT_MOC_LITERAL(74, 30), // "on_pushButton_register_clicked"
QT_MOC_LITERAL(105, 27) // "on_pushButton_login_clicked"

    },
    "LoginForm\0showMain\0\0showLogged\0QString&\0"
    "loggedUserInfo\0SSMsgCatalogSignal\0"
    "on_pushButton_register_clicked\0"
    "on_pushButton_login_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginForm[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    0 /* Public */,
       3,    1,   45,    2, 0x06,    1 /* Public */,
       6,    0,   48,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   49,    2, 0x08,    4 /* Private */,
       8,    0,   50,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LoginForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showMain(); break;
        case 1: _t->showLogged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SSMsgCatalogSignal(); break;
        case 3: _t->on_pushButton_register_clicked(); break;
        case 4: _t->on_pushButton_login_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginForm::showMain)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginForm::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginForm::showLogged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginForm::SSMsgCatalogSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject LoginForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LoginForm.offsetsAndSize,
    qt_meta_data_LoginForm,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LoginForm_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *LoginForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LoginForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void LoginForm::showMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginForm::showLogged(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LoginForm::SSMsgCatalogSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
