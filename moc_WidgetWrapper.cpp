/****************************************************************************
** Meta object code from reading C++ file 'WidgetWrapper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "common/WidgetWrapper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetWrapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QComboBoxWithSignal_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QComboBoxWithSignal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QComboBoxWithSignal_t qt_meta_stringdata_QComboBoxWithSignal = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QComboBoxWithSignal"
QT_MOC_LITERAL(1, 20, 10), // "popupShown"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11) // "popupHidden"

    },
    "QComboBoxWithSignal\0popupShown\0\0"
    "popupHidden"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QComboBoxWithSignal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QComboBoxWithSignal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QComboBoxWithSignal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->popupShown(); break;
        case 1: _t->popupHidden(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QComboBoxWithSignal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QComboBoxWithSignal::popupShown)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QComboBoxWithSignal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QComboBoxWithSignal::popupHidden)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QComboBoxWithSignal::staticMetaObject = { {
    &QComboBox::staticMetaObject,
    qt_meta_stringdata_QComboBoxWithSignal.data,
    qt_meta_data_QComboBoxWithSignal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QComboBoxWithSignal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QComboBoxWithSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QComboBoxWithSignal.stringdata0))
        return static_cast<void*>(this);
    return QComboBox::qt_metacast(_clname);
}

int QComboBoxWithSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
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
void QComboBoxWithSignal::popupShown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QComboBoxWithSignal::popupHidden()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_QSpinBoxWithSignal_t {
    QByteArrayData data[4];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSpinBoxWithSignal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSpinBoxWithSignal_t qt_meta_stringdata_QSpinBoxWithSignal = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QSpinBoxWithSignal"
QT_MOC_LITERAL(1, 19, 7), // "focusIn"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8) // "focusOut"

    },
    "QSpinBoxWithSignal\0focusIn\0\0focusOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSpinBoxWithSignal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QSpinBoxWithSignal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QSpinBoxWithSignal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->focusIn(); break;
        case 1: _t->focusOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QSpinBoxWithSignal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSpinBoxWithSignal::focusIn)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QSpinBoxWithSignal::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSpinBoxWithSignal::focusOut)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QSpinBoxWithSignal::staticMetaObject = { {
    &QSpinBox::staticMetaObject,
    qt_meta_stringdata_QSpinBoxWithSignal.data,
    qt_meta_data_QSpinBoxWithSignal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QSpinBoxWithSignal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSpinBoxWithSignal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSpinBoxWithSignal.stringdata0))
        return static_cast<void*>(this);
    return QSpinBox::qt_metacast(_clname);
}

int QSpinBoxWithSignal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSpinBox::qt_metacall(_c, _id, _a);
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
void QSpinBoxWithSignal::focusIn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QSpinBoxWithSignal::focusOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ScreenLabelWindow_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenLabelWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenLabelWindow_t qt_meta_stringdata_ScreenLabelWindow = {
    {
QT_MOC_LITERAL(0, 0, 17) // "ScreenLabelWindow"

    },
    "ScreenLabelWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenLabelWindow[] = {

 // content:
       8,       // revision
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

void ScreenLabelWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ScreenLabelWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ScreenLabelWindow.data,
    qt_meta_data_ScreenLabelWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScreenLabelWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenLabelWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenLabelWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ScreenLabelWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_RecordingFrameWindow_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordingFrameWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordingFrameWindow_t qt_meta_stringdata_RecordingFrameWindow = {
    {
QT_MOC_LITERAL(0, 0, 20) // "RecordingFrameWindow"

    },
    "RecordingFrameWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordingFrameWindow[] = {

 // content:
       8,       // revision
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

void RecordingFrameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RecordingFrameWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RecordingFrameWindow.data,
    qt_meta_data_RecordingFrameWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordingFrameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordingFrameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordingFrameWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RecordingFrameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
