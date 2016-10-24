#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton> // cette ligne vous permet de créer des objets de type QPushButton
#include <QVBoxLayout>
#include <QLineEdit>
// #include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <string.h> // chaque fois que vous utilisez des fonctions de manipulation de chaînes.
#include <stdlib.h>

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

class windowLatLng : public QWidget{ // On herite de QWidget (IMPORTANT)

        Q_OBJECT // obligatoire pour utiliser les signaux et les slots

    public:
        windowLatLng(QWidget * owner = nullptr);
        virtual ~windowLatLng();

    public slots:
        void onClick();

    private:
        QLabel *tlLat; // enonce lat
        QLineEdit *Lat; // champs d'entree
        QLabel *tlLng; // enonce lng
        QLineEdit *Lng; // champs d'entree
        QPushButton *ajouter; // bouton d'enclenchement
        QLabel *resultat; // sortie
        /* inutile de garder un pointeur sur le layout
        QVBoxLayout *mise_en_forme_V; // mise en forme verticale */

};

#endif // FENETRE_H
