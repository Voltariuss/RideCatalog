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

Collection Persistance::Import()
{

}

 bool Persistance::Export(Collection & collection, const string nomFichierExport)
{

    int nbTS=0;
    int nbTC=0;
    // TODO: afficher les listes des villes de départs et d'arrivées
    

    bool contains; 

    for (unsigned int i = 0; i < collection.GetNbTrajets(); i++)
    {
        if (typeid(*collection.GetTrajets()[i]) == typeid(TrajetSimple))
        {
            nbTS++;
        }
        else if (typeid(*collection.GetTrajets()[i]) == typeid(TrajetCompose))
        {
            nbTC++;
        }
        
      



    }
    


    ofstream out(nomFichierExport.c_str());

    if(out)    
    {

        out << nbTS << "|" << nbTC << endl;
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
