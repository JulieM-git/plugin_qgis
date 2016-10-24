#ifndef UTILITAIRE2_H_INCLUDED
#define UTILITAIRE2_H_INCLUDED

#include <iostream>
#include <qgsvectorlayer.h>
#include <qgspoint.h>
#include <qgsgeometry.h>
#include <qgsmaplayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsvectordataprovider.h>
#include <qgsfeature.h>
#include <qgsfield.h>
#include <qgsline.h>

#include <stdlib.h>

using namespace std;

void plot_line(QgsPoint P1, QgsPoint P2, QgsVectorLayer * lVectorLayer, QgsFeatureList MyFeatureList, QList<QgsField> lMyAttribField, QgsVectorDataProvider * lDataProvider);


#endif // UTILITAIRE2_H_INCLUDED
