/*************************************************************************
                           TaleauTrajets  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TaleauTrajets> (fichier TaleauTrajets.h) ----------------
#if ! defined ( TABLEAUTRAJETS_H )
#define TABLEAUTRAJETS_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------- Constantes
#define TAILLE_INIT 100

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TaleauTrajets>
//
//
//------------------------------------------------------------------------

class TaleauTrajets : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AjouterTrajet ( Trajet trajet );
    // Mode d'emploi :
    //
    // Contrat :
    //

    unsigned int GetNbTrajets ( ) { return nbTrajets; };
    // Mode d'emploi :
    //
    // Contrat :
    //

    Trajet * GetLesTrajets ( ) { return lesTrajets; };
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    TaleauTrajets & operator = ( const TaleauTrajets & unTaleauTrajets );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    TaleauTrajets ( const TaleauTrajets & unTaleauTrajets );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    TaleauTrajets ( ),
        nbTrajets ( 0 ),
        taille ( TAILLE_INIT ),
        lesTrajets ( malloc(sizeof(Trajet) * TAILLE_INIT) );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TaleauTrajets ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
unsigned int nbTrajets;
unsigned int taille;
Trajet *lesTrajets;

};

//-------------------------------- Autres définitions dépendantes de <TaleauTrajets>

#endif // TABLEAUTRAJETS_H
