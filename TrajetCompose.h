/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "TableauTrajets.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
//
//------------------------------------------------------------------------

class TrajetCompose : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    TableauTrajets GetLesTrajets ( ) { return tableauTrajets; };
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    TrajetCompose ( ), tableauTrajets ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
TableauTrajets tableauTrajets;

};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
