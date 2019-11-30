/*************************************************************************
                            Persistance  -  description
                              --------------------
   début                : 28/11/2019
   copyright            : (C) 2019 par name
*************************************************************************/

//---------- Interface de la classe <Persistance> (fichier <Persistance.h>) ------

#if ! defined ( PERSISTANCE_H )
#define PERSISTANCE_H
//--------------------------------------------------- Interfaces utilisées
#include "Collection.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Persistance>
//
//------------------------------------------------------------------------
class Persistance
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    //Collection * Import(string nomFichier, const char * villeDepart, const char * villeArrivee);
    //Collection Import(string nomFichier, int type); // enum a faire passer
    Collection * Import(string nomFichier);

//------------------------------------------------- Surcharge d'opérateurs
    Persistance & operator = ( const Persistance & unPersistance );
    // Mode d'emploi :
    // Surchage de l'opérateur d'assignement
    // 
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Persistance ();
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Persistance>
    //
    // Contrat :
    //
    

//------------------------------------------------------------------ PRIVE

    void Split(string data, string array[]);
    Collection * CreateCollection(ifstream & fichier, int recursivite = -1);

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    
};

//--------------------------- Autres définitions dépendantes de <Persistance>

#endif // PERSISTANCE_H