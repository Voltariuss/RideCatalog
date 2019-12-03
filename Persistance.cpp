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
#include <string>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Persistance.h"
#include "Collection.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"


//------------------------------------------------------------- Constantes

#define META_DONNEE_LENGHT 1
//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//vérifie si l'ouverture d'un fichier ne retourne aucun flag d'erreur
bool Persistance::FileExist(string cheminFichier)
{
    ifstream fichier;

    fichier.open(cheminFichier);
    return fichier.good();
}

//Importer les trajets d'un fichier txt
Collection *Persistance::Import(string cheminFichier)
{
    Collection *col;
    string value = "";

    ifstream fichier;
    fichier.open(cheminFichier, ios::in);
    if (fichier)
    {
        col = CreateCollection(fichier);
    }
    else
    {
        cerr << "Erreur. Impossible d'ouvrir le fichier";
    }

    return col;
}

// Fonction récursive qui permet de créer une collection de trajet (trajet qui peuvent etre des trajets simple ou composé (eux meme composé de trajet simple ou composé))
Collection * Persistance::CreateCollection(ifstream & fichier, int recursivite)
// Algorithme :
//      On parcours chaque ligne du fichier passer en parametre
//      Pour chaque ligne on récupere les informations importantes (typeTrajet, villeDepart, VilleArrivée, ModeTransport) dans un tableau
//      On crée les objets Trajet correspondant a ces données
{
    Collection * col = new Collection();
    string value, array[5];
    TypeTransport typeTransport;
    char * villeDepart, * villeArrivee;

    //on boucle sur chaque ligne afin de créer les objets TrajetSimple et TrajetCompose
    while ((recursivite > 0 || recursivite == -1) && getline(fichier, value))
    {
        Trajet * trajet;
        Split(value, array);
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
            
            //creation d'un trajet avec des const_cast => passage d'un string en char *
            //trajet = new TrajetSimple(const_cast<char *>(array[2].c_str()), const_cast<char *>(array[3].c_str()), typeTransport);
            
            villeDepart = new char[array[2].length() + 1];
            strcpy(villeDepart, array[2].c_str());
            villeArrivee = new char[array[3].length() + 1];
            strcpy(villeArrivee, array[3].c_str());

            trajet = new TrajetSimple(villeDepart, villeArrivee, typeTransport);
            
            col->AjouterTrajet(trajet->Clone());

            delete trajet;

        }
        else
        {
            trajet = new TrajetCompose(CreateCollection(fichier, atoi(array[4].c_str())));
            
            col->AjouterTrajet(trajet->Clone());

            delete trajet;
        }

        if(recursivite > 0 )
            --recursivite;
    }

    return col;
}

bool Persistance::Export(Collection & collection, const string nomFichierExport)
// Algorithme :
// Créer le fichier d'export selon la topologie definie (cf documentation).
{

    ofstream out;
    out.open(nomFichierExport, ios::out);

    
    if(out)    
    {

        for (unsigned int i = 0; i < collection.GetNbTrajets(); i++)
        {
            out  << i <<"|";

            if (typeid(collection.GetTrajets()[i][0])==typeid(TrajetSimple))
            {

                TrajetSimple * ptTs= dynamic_cast <TrajetSimple *> (collection.GetTrajets()[i]);
                out << "S|" << ptTs[0];
            }
            else if (typeid(collection.GetTrajets()[i][0])==typeid(TrajetCompose))
            {
                TrajetCompose * ptTc= dynamic_cast <TrajetCompose *> (collection.GetTrajets()[i]);

                out << "C|" << ptTc[0];

                TrajetSimple * ptTsdeTC;

                for (unsigned int i = 0; i < ptTc[0].GetTrajets()->GetNbTrajets(); i++)
                {
                    ptTsdeTC= dynamic_cast <TrajetSimple *> (ptTc[0].GetTrajets()->GetTrajets()[i]);
                    out << "#|S|" << ptTsdeTC[0];
                }
            }
        }
        
        
        return true;
    }

    else

    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        return false;
    }


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

void Persistance::Split(string data, string array[], char separator)
{

    int i = 0;

    while (data.find(separator) != string::npos)
    {
        array[i] = data.substr(0, data.find(separator));
        data = data.substr(data.find(separator) + 1);

        i++;
    }

    array[i] = data;
}

//----------------------------------------------------- Méthodes protégées
