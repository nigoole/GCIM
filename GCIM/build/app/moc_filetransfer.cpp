/****************************************************************************
** Meta object code from reading C++ file 'filetransfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GCApp/network/filetransfer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filetransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileTransfer_t {
    QByteArrayData data[11];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileTransfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileTransfer_t qt_meta_stringdata_FileTransfer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FileTransfer"
QT_MOC_LITERAL(1, 13, 14), // "signalNewAudio"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "type"
QT_MOC_LITERAL(4, 34, 11), // "strFileName"
QT_MOC_LITERAL(5, 46, 12), // "sltConnected"
QT_MOC_LITERAL(6, 59, 16), // "sltDisConneceted"
QT_MOC_LITERAL(7, 76, 12), // "displayError"
QT_MOC_LITERAL(8, 89, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 118, 20), // "updateClientProgress"
QT_MOC_LITERAL(10, 139, 20) // "updateServerProgress"

    },
    "FileTransfer\0signalNewAudio\0\0type\0"
    "strFileName\0sltConnected\0sltDisConneceted\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "updateClientProgress\0updateServerProgress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileTransfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       9,    1,   54,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,

       0        // eod
};

void FileTransfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileTransfer *_t = static_cast<FileTransfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalNewAudio((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sltConnected(); break;
        case 2: _t->sltDisConneceted(); break;
        case 3: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->updateClientProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->updateServerProgress(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileTransfer::*_t)(quint8 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileTransfer::signalNewAudio)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FileTransfer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FileTransfer.data,
      qt_meta_data_FileTransfer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileTransfer.stringdata0))
        return static_cast<void*>(const_cast< FileTransfer*>(this));
    return QObject::qt_metacast(_clname);
}

int FileTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FileTransfer::signalNewAudio(quint8 _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
