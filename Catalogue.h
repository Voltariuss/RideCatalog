/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//--------------- Interface de la classe <Catalogue> (fichier Catalogue.h)
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "TableauTrajets.h"

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

    void Afficher ( const TableauTrajets & trajets ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int AjouterTrajet ( Trajet * trajet )
    { return tableauTrajets.AjouterTrajet(trajet); }

    TableauTrajets RechercherParcours ( char *depart, char *arrivee ) const;
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
    TableauTrajets tableauTrajets;

};

//-------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
