/*************************************************************************
            Trajet  -  Classe abstraite représentant un trajet
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( Trajet_H )
#define Trajet_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//
//
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Afficher ( ) const = 0;

    virtual bool ArriveeEgalDepart ( const Trajet & trajet ) const
    { return !strcmp(GetVilleArrivee(), trajet.GetVilleDepart()); }

    virtual char * GetVilleDepart ( ) const = 0;

    virtual char * GetVilleArrivee ( ) const = 0;

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Trajet ( );

    virtual ~Trajet ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // Trajet_H
