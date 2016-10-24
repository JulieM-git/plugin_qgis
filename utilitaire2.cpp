#include "utilitaire2.h"

void plot_line(QgsPoint P1, QgsPoint P2, QgsVectorLayer * lVectorLayer, QgsFeatureList MyFeatureList, QList<QgsField> lMyAttribField, QgsVectorDataProvider * lDataProvider)
{
    // nouveau point
    QgsLine* MyLine;
    // remplissage du point
    MyLine = QgsGeometry::fromLine(P1,P2);
    // nouvelle entity
    QgsFeature MyFeature;
    // ajout du point dans l entity
    MyFeature.setGeometry(MyPoint);
    // ajout de l entity dans la liste d entity
    MyFeatureList.append(MyFeature);
    // ajout de la liste des entities au fourniseur de donnees
    lDataProvider->addFeatures(MyFeatureList);
    // ajout de la couche sur la map
    QgsMapLayerRegistry::instance()->addMapLayer(lVectorLayer, TRUE);
}
