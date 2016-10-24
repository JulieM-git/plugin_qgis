#include "agileplugin.h"
#include "qgisinterface.h"
#include "qgsmessagelog.h"
#include "qgsmapcanvas.h"
#include "qgsrasterlayer.h"
#include "qgsvectorlayer.h"
#include "qgsmaplayerregistry.h"
#include <QAction>
#include <QList>

#include <QApplication>
#include <QFileDialog>

#include "windowLatLng.h"
#include "utilitaire.h"

// Static variables for plugin description
static const QString sName = QObject::tr("AgilePlugin");
static const QString sDescription = QObject::tr("This is a very agile plugin");
static const QString sCategory = QObject::tr("Agile projects");
static const QString sPluginVersion = QObject::tr("Version 1.0");
static const QgisPlugin::PLUGINTYPE sPluginType = QgisPlugin::UI;
static const QString sPluginIcon = "";


AgilePlugin::AgilePlugin(QgisInterface * interface)
    : QgisPlugin(sName, sDescription, sCategory, sPluginVersion, sPluginType)
    , m_GISInterface(interface)
    , m_action(nullptr)
    , gpx_action(nullptr)
    , ajt_pt_action(nullptr)
    , ajt_coord_click(nullptr)
    , dessiner_action(nullptr)

{
}

void AgilePlugin::initGui()
{
   std::cout << "AgilePlugin::initGui" << std::endl;

    // Bouton "Ajout GeoTIFF" - action si clique
    // Creates the action
    m_action = new QAction(QIcon(""), tr("Ajouter GeoTIFF"), this);
    m_action->setWhatsThis(tr("Lance l'ouverture d'un GeoTIFF"));
    // Connects the triggered signal to the slot
    connect(m_action, SIGNAL(triggered()), this, SLOT(run()));
    // Adds the action to the menu
    m_GISInterface->addRasterToolBarIcon(m_action);
    m_GISInterface->addPluginToMenu(tr("&Plugin scrum"), m_action);

    // Bouton "Ajout GPX" - action si clique
    // Creates the action
    gpx_action = new QAction(QIcon(""), tr("Ajouter GPX"), this);
    gpx_action->setWhatsThis(tr("Lance l'ouverture d'un GPX"));
    // Connects the triggered signal to the slot
    connect(gpx_action, SIGNAL(triggered()), this, SLOT(run_gpx()));
    // Adds the action to the menu
    m_GISInterface->addRasterToolBarIcon(gpx_action);
    m_GISInterface->addPluginToMenu(tr("&Plugin scrum"), gpx_action);

    // Bouton "Ajout points" - action si clique
    // Creates the action
    ajt_pt_action = new QAction(QIcon(""), tr("Ajouter des points"), this);
    ajt_pt_action->setWhatsThis(tr("Fenetre d'ajout des points"));
    // Connects the triggered signal to the slot
    connect(ajt_pt_action, SIGNAL(triggered()), this, SLOT(run_ajt_pt()));
    // Adds the action to the menu
    m_GISInterface->addRasterToolBarIcon(ajt_pt_action);
    m_GISInterface->addPluginToMenu(tr("&Plugin scrum"), ajt_pt_action);

    // Bouton "Clique" - action si clique
    // Creates the action
    ajt_coord_click = new QAction(QIcon(""), tr("Clique"), this);
    ajt_coord_click->setWhatsThis(tr("Fonctionnalités liées aux cliques"));
    // Connects the triggered signal to the slot
    connect(ajt_coord_click, SIGNAL(triggered()), this, SLOT(run_coord_click()));
    // Adds the action to the menu
    m_GISInterface->addRasterToolBarIcon(ajt_coord_click);
    m_GISInterface->addPluginToMenu(tr("&Plugin scrum"), ajt_coord_click);

    // Bouton "Dessiner" - action si clique
    // Creates the action
    dessiner_action = new QAction(QIcon(""), tr("Dessiner"), this);
    dessiner_action->setWhatsThis(tr("Dessiner un trait ou un rectangle"));
    // Connects the triggered signal to the slot
    connect(dessiner_action, SIGNAL(triggered()), this, SLOT(run_dessiner()));
    // Adds the action to the menu
    m_GISInterface->addRasterToolBarIcon(dessiner_action);
    m_GISInterface->addPluginToMenu(tr("&Plugin scrum"), dessiner_action);

    // nouvelle couche
    lVectorLayer = new QgsVectorLayer("Point","Couche de points","memory");
    // la couche devient editable
    lVectorLayer->startEditing();
    // cerate fields
    lMyAttribField << QgsField("X",QVariant::Double) << QgsField("Y",QVariant::Double);
    // remplissage du fournisseur d acces
    lDataProvider = lVectorLayer->dataProvider();
    // ajout des champs d attribut
    lDataProvider->addAttributes(lMyAttribField);
    // save attributes
    lVectorLayer->commitChanges();

}


void AgilePlugin::run()
{

    QString fileName = QFileDialog::getOpenFileName(nullptr,
    tr("Ouvrir un fichier Geotiff"), "/home/", tr("Format Tiff (*.tiff *.TIFF *.tif *.TIF)"));

    QgsMessageLog::instance()->logMessage("Geotiff launched", "AgilePlugin", QgsMessageLog::INFO);

    // Gets the map canvas
    QgsMapCanvas * canvas = m_GISInterface->mapCanvas();

    // Creates a raster layer
    QgsRasterLayer * rasterLayer = new QgsRasterLayer(fileName, "GeoTiff", "tif");
    if (rasterLayer->isValid())
    {
        QgsMessageLog::instance()->logMessage("Chargement de la couche", "AgilePlugin", QgsMessageLog::INFO);
        // Registers the layer
        QgsMapLayerRegistry::instance()->addMapLayer(rasterLayer);

        // Setups the canvas
        canvas->setExtent(rasterLayer->extent());
        canvas->enableAntiAliasing(true);
        canvas->setCanvasColor(QColor(255, 255, 255));
        canvas->freeze(false);

        // Adds the layer in the canvas
        QList <QgsMapCanvasLayer> layerSet;
        layerSet.append(QgsMapCanvasLayer(rasterLayer));
        canvas->setLayerSet(layerSet);
        canvas->setVisible(true);
        canvas->refresh();
    }
    else
    {
        QgsMessageLog::instance()->logMessage("Erreur du chargement de la couche", "AgilePlugin", QgsMessageLog::INFO);
    }
}

void AgilePlugin::run_gpx()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
    tr("Ouvrir un fichier GPX"), "/home/", tr("Image Files (*.gpx *.GPX)"));

    QgsMessageLog::instance()->logMessage("GPX launched", "AgilePlugin", QgsMessageLog::INFO);

    // Gets the map canvas
    QgsMapCanvas * canvas = m_GISInterface->mapCanvas();

    // Creates a raster layer
    QgsVectorLayer * vectorLayer = new QgsVectorLayer(fileName + QString("?type=track"), "GPX", "gpx");
    if (vectorLayer->isValid())
    {
        QgsMessageLog::instance()->logMessage("Chargement de la couche", "AgilePlugin", QgsMessageLog::INFO);
        // Registers the layer
        QgsMapLayerRegistry::instance()->addMapLayer(vectorLayer);

        // Setups the canvas
        canvas->setExtent(vectorLayer->extent());
        canvas->enableAntiAliasing(true);
        canvas->setCanvasColor(QColor(255, 255, 255));
        canvas->freeze(false);

        // Adds the layer in the canvas
        QList <QgsMapCanvasLayer> layerSet;
        layerSet.append(QgsMapCanvasLayer(vectorLayer));
        canvas->setLayerSet(layerSet);
        canvas->setVisible(true);
        canvas->refresh();
    }
    else
    {
        QgsMessageLog::instance()->logMessage("Erreur du chargement de la couche", "AgilePlugin", QgsMessageLog::INFO);
    }
}

void AgilePlugin::run_ajt_pt()
{
    windowLatLng *wdg = new windowLatLng;
    wdg->show();

    QgsMessageLog::instance()->logMessage("Ajout points launched", "AgilePlugin", QgsMessageLog::INFO);
}

void AgilePlugin::run_coord_click()
{
    mapTool = new QgsMapToolEmitPoint(m_GISInterface -> mapCanvas());

    QgsMapCanvas * canvas = m_GISInterface->mapCanvas();
    canvas->setMapTool(mapTool);

    connect(mapTool, SIGNAL(canvasClicked(const QgsPoint&, Qt::MouseButton)), this, SLOT(handleClicked(const QgsPoint&)));

    QgsMessageLog::instance()->logMessage("Click launched", "AgilePlugin", QgsMessageLog::INFO);
}

void AgilePlugin::handleClicked(const QgsPoint &Pt)
{
    X = Pt.x();
    Y = Pt.y();

    if (X == Xprec && Y == Yprec){
        QgsMessageLog::instance()->logMessage("Double", "AgilePlugin", QgsMessageLog::INFO);

        plot_point(X,Y,lVectorLayer,MyFeatureList,lMyAttribField,lDataProvider);
    }else{
        QgsMessageLog::instance()->logMessage(Pt.toString(), "AgilePlugin", QgsMessageLog::INFO);
    }

    Xprec = X;
    Yprec = Y;
}

void AgilePlugin::run_dessiner()
{
    /*mapTool = new QgsMapToolEmitPoint(m_GISInterface -> mapCanvas());

    QgsMapCanvas * canvas = m_GISInterface->mapCanvas();
    canvas->setMapTool(mapTool);

    QgsMessageLog::instance()->logMessage("Erreur du chargement de la couche", "AgilePlugin", QgsMessageLog::INFO);

    connect(mapTool, SIGNAL(canvasClicked(const QgsPoint&, Qt::MouseButton)), this, SLOT(handleClicked(const QgsPoint&)));

    QgsMessageLog::instance()->logMessage("Click launched", "AgilePlugin", QgsMessageLog::INFO);*/
}

void AgilePlugin::unload()
{
    QgsMessageLog::instance()->logMessage("Agile Plugin unloaded", "AgilePlugin", QgsMessageLog::INFO);
}

//////////////////////////////////////////////////////////////////////////
//
//
//  THE FOLLOWING CODE IS AUTOGENERATED BY THE PLUGIN BUILDER SCRIPT
//    YOU WOULD NORMALLY NOT NEED TO MODIFY THIS, AND YOUR PLUGIN
//      MAY NOT WORK PROPERLY IF YOU MODIFY THIS INCORRECTLY
//
//
//////////////////////////////////////////////////////////////////////////

QGISEXTERN QgisPlugin * classFactory(QgisInterface * theQgisInterfacePointer)
{
  return new AgilePlugin(theQgisInterfacePointer);
}

QGISEXTERN QString name()
{
  return sName;
}

QGISEXTERN QString description()
{
  return sDescription;
}

QGISEXTERN QString category()
{
  return sCategory;
}

QGISEXTERN int type()
{
  return sPluginType;
}

QGISEXTERN QString version()
{
  return sPluginVersion;
}

QGISEXTERN QString icon()
{
  return sPluginIcon;
}

QGISEXTERN void unload( QgisPlugin * thePluginPointer )
{
  delete thePluginPointer;
}
