/****************************************************************************
** Meta object code from reading C++ file 'ssrtools.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ssrtools.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ssrtools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ssrtools_t {
    QByteArrayData data[8];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ssrtools_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ssrtools_t qt_meta_stringdata_ssrtools = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ssrtools"
QT_MOC_LITERAL(1, 9, 31), // "on_m_toolButton_options_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 29), // "on_m_pushButton_start_clicked"
QT_MOC_LITERAL(4, 72, 46), // "on_m_pushbutton_video_select_..."
QT_MOC_LITERAL(5, 119, 43), // "on_m_pushbutton_video_select_..."
QT_MOC_LITERAL(6, 163, 23), // "OnUpdateVideoAreaFields"
QT_MOC_LITERAL(7, 187, 22) // "OnUpdateRecordingFrame"

    },
    "ssrtools\0on_m_toolButton_options_clicked\0"
    "\0on_m_pushButton_start_clicked\0"
    "on_m_pushbutton_video_select_rectangle_clicked\0"
    "on_m_pushbutton_video_select_window_clicked\0"
    "OnUpdateVideoAreaFields\0OnUpdateRecordingFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ssrtools[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ssrtools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ssrtools *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_m_toolButton_options_clicked(); break;
        case 1: _t->on_m_pushButton_start_clicked(); break;
        case 2: _t->on_m_pushbutton_video_select_rectangle_clicked(); break;
        case 3: _t->on_m_pushbutton_video_select_window_clicked(); break;
        case 4: _t->OnUpdateVideoAreaFields(); break;
        case 5: _t->OnUpdateRecordingFrame(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ssrtools::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ssrtools.data,
    qt_meta_data_ssrtools,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ssrtools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ssrtools::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ssrtools.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ssrtools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
