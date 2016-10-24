#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED

#include <iostream>
#include <qgsvectorlayer.h>
#include <qgspoint.h>
#include <qgsgeometry.h>
#include <qgsmaplayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsvectordataprovider.h>
#include <qgsfeature.h>
#include <qgsfield.h>

#include <stdlib.h>

using namespace std;

void plot_point(double x, double y, QgsVectorLayer * lVectorLayer, QgsFeatureList MyFeatureList, QList<QgsField> lMyAttribField, QgsVectorDataProvider * lDataProvider); // affiche un point a partir de ces coordonnees

#endif // UTILITAIRE_H_INCLUDED
