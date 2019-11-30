/*************************************************************************
                            Persistance  -  description
                              --------------------
   début                : 28/11/2019
   copyright            : (C) 2019 par name
*************************************************************************/

//---------- Réalisation de la classe <Persistance> (fichier Persistance.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <string.h>

//------------------------------------------------------ Include personnel
#include "Persistance.h"
#include "Collection.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

#define META_DONNEE_LENGHT 3
//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Collection *Persistance::Import(string nomFichier)
{
    Collection *col = new Collection();
    string value = "";
    int i;

    ifstream fichier;
    fichier.open("Data/" + nomFichier, ios::in);
    if (fichier)
    {
        //on saute les 3 premieres lignes du fichier
        for (i = 0; i < META_DONNEE_LENGHT; i++)
            getline(fichier, value);

        col = CreateCollection(fichier);
    }
    else
    {
        cerr << "Erreur. Impossible d'ouvrir le fichier";
    }

    //AFFICHAGE RESULTAT COLLECTION
    /*char str[] = {0};
    cout << col->GetNbTrajets() << endl;
    Trajet ** t = col->GetTrajets();
    for(i=0; i<col->GetNbTrajets(); i++)
    {
        t[i]->Afficher(str);
    }*/

    return col;
}

Collection * Persistance::CreateCollection(ifstream & fichier, int recursivite)
{
    Collection * col = new Collection();
    string value;
    string array[5];
    TypeTransport typeTransport;
    Trajet * trajet;

    //on boucle sur chaque ligne afin de créer les objets TrajetSimple et TrajetCompose
    while ((recursivite > 0 || recursivite == -1) && getline(fichier, value))
    {
        Split(value, array);
        //if(atoi(array[4].c_str()) == n)
        if (array[1] == "S")
        {
            //if()
            switch (atoi(array[4].c_str()))
            {
            case 0:
                typeTransport = AUTO;
                break;
            case 1:
                typeTransport = AVION;
                break;
            case 2:
                typeTransport = BATEAU;
                break;
            default:
                typeTransport = TRAIN;
                break;
            }

            trajet = new TrajetSimple(const_cast<char *>(array[2].c_str()), const_cast<char *>(array[3].c_str()), typeTransport);
            col->AjouterTrajet(trajet->Clone());
        }
        else
        {
            trajet = new TrajetCompose(CreateCollection(fichier, atoi(array[4].c_str())));
            
            col->AjouterTrajet(trajet->Clone());
        }

        if(recursivite > 0 )
            --recursivite;
    }

    return col;
}

//------------------------------------------------- Surcharge d'opérateurs
/*Persistance & Persistance::operator = ( const Persistance & unPersistance )
// Algorithme :
//
{
} //----- Fin de operator =*/

//-------------------------------------------- Constructeurs - destructeur

Persistance::Persistance()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Persistance>" << endl;
#endif
} //----- Fin de Persistance

//------------------------------------------------------------------ PRIVE

void Persistance::Split(string data, string array[])
{

    int i = 0;

    while (data.find('|') != string::npos)
    {
        array[i] = data.substr(0, data.find('|'));
        data = data.substr(data.find('|') + 1);

        i++;
    }

    array[i] = data;
}

//----------------------------------------------------- Méthodes protégées
