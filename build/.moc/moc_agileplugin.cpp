/****************************************************************************
** Meta object code from reading C++ file 'agileplugin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../agileplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agileplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AgilePlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      19,   12,   12,   12, 0x0a,
      29,   12,   12,   12, 0x0a,
      42,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,
      78,   75,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AgilePlugin[] = {
    "AgilePlugin\0\0run()\0run_gpx()\0run_ajt_pt()\0"
    "run_coord_click()\0run_dessiner()\0Pt\0"
    "handleClicked(QgsPoint)\0"
};

void AgilePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AgilePlugin *_t = static_cast<AgilePlugin *>(_o);
        switch (_id) {
        case 0: _t->run(); break;
        case 1: _t->run_gpx(); break;
        case 2: _t->run_ajt_pt(); break;
        case 3: _t->run_coord_click(); break;
        case 4: _t->run_dessiner(); break;
        case 5: _t->handleClicked((*reinterpret_cast< const QgsPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AgilePlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AgilePlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AgilePlugin,
      qt_meta_data_AgilePlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AgilePlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AgilePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AgilePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AgilePlugin))
        return static_cast<void*>(const_cast< AgilePlugin*>(this));
    if (!strcmp(_clname, "QgisPlugin"))
        return static_cast< QgisPlugin*>(const_cast< AgilePlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int AgilePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
