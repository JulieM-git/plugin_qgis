#include "windowLatLng.h"
#include "utilitaire.h"
#include "qgsmessagelog.h"

windowLatLng::~windowLatLng()
{
    //dtor
}

// Constructor :
windowLatLng::windowLatLng(QWidget *owner)
    :QWidget{owner},
    tlLat{new QLabel{"",this}}, // enonce lat
    Lat{new QLineEdit{"",this}}, // champs d'entree
    tlLng{new QLabel{"",this}}, // enonce lng
    Lng{new QLineEdit{"",this}}, // champs d'entree
    ajouter{new QPushButton{"run_project",this}}, // construction du bouton
    resultat{new QLabel{"",this}} // construction de la sortie
    {

    // Personnalisation de la fenetre :
    setFixedSize(400,175);
    setWindowTitle("Ajout de points");

    // Texte lat:
    tlLat->setText("Latitude :");
    tlLat->setFont(QFont("Helvetica", 11));
    tlLat->setAlignment(Qt::AlignCenter);

    // Champs lat :
    Lat->setAlignment(Qt::AlignCenter);
    Lat->setFont(QFont("Helvetica", 11));

    // Texte lng :
    tlLng->setText("Longitude :");
    tlLng->setFont(QFont("Helvetica", 11));
    tlLng->setAlignment(Qt::AlignCenter);

    // Champs lng :
    Lng->setAlignment(Qt::AlignCenter);
    Lng->setFont(QFont("Helvetica", 11));

    // Bouton ajouter :
    ajouter->setText("Ajouter"); // que nous appelons tout simplement "Conversion"
    ajouter->setFont(QFont("Helvetica", 11));
    ajouter->setToolTip("Ajoute le point de coordonnées Lat,Lng à la carte");

    // personalisation du resultat :
    resultat->setAlignment(Qt::AlignCenter);
    resultat->setFont(QFont("Helvetica", 13));

    // construction du layout vertical :
    auto mise_en_forme_V = new QVBoxLayout{};

    // ajout des widgets
    mise_en_forme_V->addWidget(tlLat);
    mise_en_forme_V->addWidget(Lat);
    mise_en_forme_V->addWidget(tlLng);
    mise_en_forme_V->addWidget(Lng);
    mise_en_forme_V->addWidget(ajouter);
    mise_en_forme_V->addWidget(resultat);

    setLayout(mise_en_forme_V);

    // On connecte le click sur le bouton a notre slot onClick
    connect(ajouter, SIGNAL(&QPushButton::clicked), this, SLOT(&windowGLatLng::onClick()));
}


// fonction principale activee par le bouton
void windowLatLng::onClick(){

    QgsMessageLog::instance()->logMessage("Ajout points launched", "AgilePlugin", QgsMessageLog::INFO);

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

    plot_point(
        Lat->text().toDouble(),
        Lng->text().toDouble(),
        lVectorLayer,
        MyFeatureList,
        lMyAttribField,
        lDataProvider
    );


/*
    // si la chaine contient un reel   positif a virgule                ou                                negatif a virgule                 ou                                positif sans virgule ou                            negatif sans virgule ET on accepte que le point !!!
    if((reel->text().contains(QRegExp("^[\\d]{1,10}\\.{1}[\\d]{1,6}$")) || reel->text().contains(QRegExp("^-[\\d]{1,10}\\.{1}[\\d]{1,6}$")) || reel->text().contains(QRegExp("^[\\d]{1,10}$")) || reel->text().contains(QRegExp("^-[\\d]{1,10}$"))) && !reel->text().contains(QRegExp(","))){
        if(reel->text().size() <= 85){ // si la taille du reel rentre n est pas trop grande
            char binaire_ieee_754[32]; // chaine de caractere qui contiendra le binaire final
            norme_ieee_754(reel->text().toStdString().c_str(),binaire_ieee_754); // fonction principale dans norme_ieee_754.cpp
            resultat->setText(binaire_ieee_754); // rajout du binaire final dans le text de resultat
        }else{ // sinon // en fait on ne rentre jamais dans cette boucle else car la taille est deja verifiee par les QRegExp
            resultat->setText(""); // rajout rien du tout
            QMessageBox *msgBox2 = new QMessageBox(QMessageBox::Critical, "Erreur d'entrée", ""); // construction d une info-bulle
            msgBox2->setText("<p align='center'>Le réel rentré est trop long !</p>"); // HTML !
            msgBox2->setFont(QFont("Helvetica", 9));
            msgBox2->exec(); // execution de l info bulle
        }
    }else if(!reel->text().isEmpty()){ // sinon
        resultat->setText(""); // rajout rien du tout
        QMessageBox *msgBox1 = new QMessageBox(QMessageBox::Critical, "Erreur d'entrée", ""); // construction d une info-bulle
        msgBox1->setText("<p align='center'>Le réel doit correspondre aux patrons suivants :</p>\n<p align='center'>xxxxxxxxxx</p>\n<p align='center'>-xxxxxxxxxx</p>\n<p align='center'>xxxxxxxxxx.xxxxxx</p>\n<p align='center'>-xxxxxxxxxx.xxxxxx</p>"); // HTML !
        msgBox1->setFont(QFont("Helvetica", 9));
        msgBox1->exec(); // execution de l info bulle
    }
    */
}
