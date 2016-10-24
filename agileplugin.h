#ifndef AGILEPLUGIN_H
#define AGILEPLUGIN_H

#include <QObject>
#include <iostream>
#include "qgisplugin.h" // Plugin interface
#include <qgsmaptool.h>
#include <qgsmaptoolemitpoint.h>

// Forward declarations
class QAction;
class QgisInterface;

// Declaration of the AgilePlugin class
class AgilePlugin: public QObject, public QgisPlugin
{
Q_OBJECT

public:
    // Constructor (interface is passed at construction)
    explicit AgilePlugin(QgisInterface * interface);

    // Called when the plugin is enabled
    void initGui() override;

    // Called when the plugin is disabled
    void unload() override;

public slots:
    // Slot called when the plugin is launched
    void run();
    void run_gpx();
    void run_ajt_pt();
    void run_coord_click();
    void run_dessiner();
    void handleClicked(const QgsPoint &Pt);

private:
    QgisInterface * m_GISInterface; // GIS interface
    QAction * m_action; // Action in the menu bar
    QAction * gpx_action; // Action in the menu bar
    QAction * ajt_pt_action; // Action in the menu bar
    QAction * ajt_coord_click; // Action in the menu bar
    QAction * dessiner_action; // Action in the menu bar
    QgsMapToolEmitPoint * mapTool;
    double X,Y,Xprec=0,Yprec=0;
    QgsVectorLayer * lVectorLayer;
    QgsFeatureList MyFeatureList;
    QList<QgsField> lMyAttribField;
    QgsVectorDataProvider * lDataProvider;
};

#endif
