#include "utilitaire.h"

/* A METTRE DANS LE RUN DE AGILEPLUGIN.CPP
    // nouvelle couche
    QgsVectorLayer * lVectorLayer = new QgsVectorLayer("Point","Couche de points","memory");
    // la couche devient editable
    lVectorLayer->startEditing();
    // nouvelle liste d entity
    QgsFeatureList MyFeatureList;
    // creation de la table
    QList<QgsField> lMyAttribField;
    // cerate fields
    lMyAttribField << QgsField("X",QVariant::Double) << QgsField("Y",QVariant::Double);
    // creation du fournisseur d acces
    QgsVectorDataProvider * lDataProvider;
    // remplissage du fournisseur d acces
    lDataProvider = lVectorLayer->dataProvider();
    // ajout des champs d attribut
    lDataProvider->addAttributes(lMyAttribField);
    // save attributes
    lVectorLayer->commitChanges();
*/

void plot_point(double PosX, double PosY, QgsVectorLayer * lVectorLayer, QgsFeatureList MyFeatureList, QList<QgsField> lMyAttribField, QgsVectorDataProvider * lDataProvider){ // affiche un point a partir de ces coordonnees
    // nouveau point
    QgsGeometry * MyPoint;
    // remplissage du point
    MyPoint = QgsGeometry::fromPoint(QgsPoint(PosX,PosY));
    // nouvelle entity
    QgsFeature MyFeature;
    // ajout du point dans l entity
    MyFeature.setGeometry(MyPoint);
    // ajout de l entity dans la liste d entity
    MyFeatureList.append(MyFeature);
    // remplissage des champs
    MyFeature.setAttribute("X",PosX);
    MyFeature.setAttribute("Y",PosY);
    // ajout de la liste des entities au fourniseur de donnees
    lDataProvider->addFeatures(MyFeatureList);
    // ajout de la couche sur la map
    QgsMapLayerRegistry::instance()->addMapLayer(lVectorLayer, TRUE);
}
