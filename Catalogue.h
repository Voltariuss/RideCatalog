/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "TableauTrajets"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ( TableauTrajets trajets, unsigned int nbTrajets );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AjouterTrajet ( TableauTrajets trajets, unsigned int nbTrajets );
    // Mode d'emploi :
    //
    // Contrat :
    //

    int RechercherParcours ( char *depart, char *arrivee, TableauTrajets trajets );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Catalogue & operator = ( const Catalogue & unCatalogue );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( const Catalogue & unCatalogue );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Catalogue ( ), tableauTrajets ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Catalogue ( );
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

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
