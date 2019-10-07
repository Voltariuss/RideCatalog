/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h)
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TableauTrajets.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int AjouterTrajet ( Trajet * trajet )
    { return tableauTrajets.AjouterTrajet(trajet); }

    virtual void Afficher ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual char * GetVilleDepart ( ) const
    { return tableauTrajets.GetLesTrajets()[0]->GetVilleDepart(); }

    virtual char * GetVilleArrivee ( ) const
    { return tableauTrajets.GetLesTrajets()[tableauTrajets.GetNbTrajets()-1]->GetVilleArrivee(); }

    TableauTrajets * GetLesTrajets ( )
    { return &tableauTrajets; }

//------------------------------------------------- Surcharge d'opérateurs
    bool operator == ( const TrajetCompose & trajet ) const;

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( Trajet * t1, Trajet * t2 );

    virtual ~TrajetCompose ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    TableauTrajets tableauTrajets;

};

//---------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
