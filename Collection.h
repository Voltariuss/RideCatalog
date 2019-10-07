/*************************************************************************
    Collection  -  Structure de données permettant de gérer le stockage 
          et les interactions avec les trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//----- Interface de la classe <Collection> (fichier Collection.h)
#if ! defined ( TABLEAUTRAJETS_H )
#define TABLEAUTRAJETS_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Collection>
//
//
//------------------------------------------------------------------------

class Collection
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int AjouterTrajet ( Trajet * trajet );
    // Mode d'emploi :
    //
    // Contrat :
    //

    int AjouterTrajet ( Collection * trajets );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool Contient ( Trajet * trajet ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    unsigned int GetNbTrajets ( ) const
    { return nbTrajets; };

    unsigned int GetNbMaxTrajets ( ) const
    { return taille; };

    Trajet ** GetLesTrajets ( ) const
    { return lesTrajets; };

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Collection ( );

    virtual ~Collection ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    bool reallocaction ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    unsigned int nbTrajets;
    unsigned int taille;
    Trajet ** lesTrajets;

};

//--------------------- Autres définitions dépendantes de <Collection>

#endif // TABLEAUTRAJETS_H
