/*************************************************************************
                           TableauTrajets  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//----- Interface de la classe <TableauTrajets> (fichier TableauTrajets.h)
#if ! defined ( TABLEAUTRAJETS_H )
#define TABLEAUTRAJETS_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TableauTrajets>
//
//
//------------------------------------------------------------------------

class TableauTrajets
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int AjouterTrajet ( Trajet * trajet );
    // Mode d'emploi :
    //
    // Contrat :
    //

    int AjouterTrajet ( TableauTrajets * trajets );
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
    TableauTrajets ( );

    virtual ~TableauTrajets ( );

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

//--------------------- Autres définitions dépendantes de <TableauTrajets>

#endif // TABLEAUTRAJETS_H
