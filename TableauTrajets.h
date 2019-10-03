/*************************************************************************
                           TableauTrajets  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TableauTrajets> (fichier TableauTrajets.h) ----------------
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

    unsigned int GetNbTrajets ( ) { return nbTrajets; };
    // Mode d'emploi :
    //
    // Contrat :
    //

    Trajet ** GetLesTrajets ( ) { return lesTrajets; };
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    TableauTrajets & operator = ( const TableauTrajets & unTableauTrajets );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    TableauTrajets ( const TableauTrajets & unTableauTrajets );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    TableauTrajets ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TableauTrajets ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    bool reallocaction ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool contient ( Trajet * trajet ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    unsigned int nbTrajets;
    unsigned int taille;
    Trajet **lesTrajets;

};

//-------------------------------- Autres définitions dépendantes de <TableauTrajets>

#endif // TABLEAUTRAJETS_H
