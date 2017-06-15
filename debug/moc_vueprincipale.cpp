/****************************************************************************
** Meta object code from reading C++ file 'vueprincipale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vueprincipale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vueprincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreationArticleWindow_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreationArticleWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreationArticleWindow_t qt_meta_stringdata_CreationArticleWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CreationArticleWindow"
QT_MOC_LITERAL(1, 22, 6), // "fermer"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11) // "enregistrer"

    },
    "CreationArticleWindow\0fermer\0\0enregistrer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreationArticleWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CreationArticleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreationArticleWindow *_t = static_cast<CreationArticleWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fermer(); break;
        case 1: _t->enregistrer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreationArticleWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreationArticleWindow::fermer)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CreationArticleWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreationArticleWindow.data,
      qt_meta_data_CreationArticleWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CreationArticleWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreationArticleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreationArticleWindow.stringdata0))
        return static_cast<void*>(const_cast< CreationArticleWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreationArticleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CreationArticleWindow::fermer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_CreationTacheWindow_t {
    QByteArrayData data[4];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreationTacheWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreationTacheWindow_t qt_meta_stringdata_CreationTacheWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CreationTacheWindow"
QT_MOC_LITERAL(1, 20, 6), // "fermer"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11) // "enregistrer"

    },
    "CreationTacheWindow\0fermer\0\0enregistrer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreationTacheWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CreationTacheWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreationTacheWindow *_t = static_cast<CreationTacheWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fermer(); break;
        case 1: _t->enregistrer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreationTacheWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreationTacheWindow::fermer)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CreationTacheWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreationTacheWindow.data,
      qt_meta_data_CreationTacheWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CreationTacheWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreationTacheWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreationTacheWindow.stringdata0))
        return static_cast<void*>(const_cast< CreationTacheWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreationTacheWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CreationTacheWindow::fermer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_CreationMediaWindow_t {
    QByteArrayData data[4];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreationMediaWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreationMediaWindow_t qt_meta_stringdata_CreationMediaWindow = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CreationMediaWindow"
QT_MOC_LITERAL(1, 20, 6), // "fermer"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11) // "enregistrer"

    },
    "CreationMediaWindow\0fermer\0\0enregistrer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreationMediaWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CreationMediaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreationMediaWindow *_t = static_cast<CreationMediaWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fermer(); break;
        case 1: _t->enregistrer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreationMediaWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreationMediaWindow::fermer)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CreationMediaWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreationMediaWindow.data,
      qt_meta_data_CreationMediaWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CreationMediaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreationMediaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreationMediaWindow.stringdata0))
        return static_cast<void*>(const_cast< CreationMediaWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreationMediaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CreationMediaWindow::fermer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_VuePrincipale_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VuePrincipale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VuePrincipale_t qt_meta_stringdata_VuePrincipale = {
    {
QT_MOC_LITERAL(0, 0, 13) // "VuePrincipale"

    },
    "VuePrincipale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VuePrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void VuePrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject VuePrincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VuePrincipale.data,
      qt_meta_data_VuePrincipale,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VuePrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VuePrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VuePrincipale.stringdata0))
        return static_cast<void*>(const_cast< VuePrincipale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VuePrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
