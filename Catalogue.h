/*************************************************************************
    Catalogue  -  Classe représentant un catalogue contenant l'ensemble 
                        des trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------------- Interface de la classe <Catalogue> (fichier Catalogue.h)
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Collection.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ( ) const
    { Afficher(tableauTrajets); }

    void Afficher ( const Collection & trajets ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int AjouterTrajet ( Trajet * trajet )
    { return tableauTrajets.AjouterTrajet(trajet); }

    Collection RechercherParcours ( char *depart, char *arrivee ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );

    virtual ~Catalogue ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    Collection tableauTrajets;

};

//-------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
