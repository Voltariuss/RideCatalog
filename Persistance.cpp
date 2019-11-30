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
#include "Catalogue.h"


//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Persistance::Methode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Methode

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
            out  << i <<":";

            if (typeid(collection.GetTrajets()[i][0])==typeid(TrajetSimple))
            {

                TrajetSimple * ptTs= dynamic_cast <TrajetSimple *> (collection.GetTrajets()[i]);
                out << "\tS|" << ptTs[0];
            }
            else if (typeid(collection.GetTrajets()[i][0])==typeid(TrajetCompose))
            {
                TrajetCompose * ptTc= dynamic_cast <TrajetCompose *> (collection.GetTrajets()[i]);

                out << "\tC|" << ptTc[0];

                TrajetSimple * ptTsdeTC;

                for (unsigned int i = 0; i < ptTc[0].GetTrajets()->GetNbTrajets(); i++)
                {
                    ptTsdeTC= dynamic_cast <TrajetSimple *> (ptTc[0].GetTrajets()->GetTrajets()[i]);
                    out << "\t\tS|" << ptTsdeTC[0];
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
Persistance & Persistance::operator = ( const Persistance & unPersistance )
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Persistance::Persistance ( const Persistance & unPersistance )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Persistance>" << endl;
#endif
} //----- Fin de Persistance (constructeur de copie)

Persistance::Persistance ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Persistance>" << endl;
#endif
} //----- Fin de Persistance


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
