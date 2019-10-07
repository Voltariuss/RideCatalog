/*************************************************************************
    TrajetCompose  -  Classe représentant un trajet composé caractérisé
      par une collection ordonnée de trajets (simples et/ou composés)
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h)
#if !defined(TRAJETCOMPOSE_H)
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "Collection.h"

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
    int AjouterTrajet(Trajet *trajet)
    {
        return collection.AjouterTrajet(trajet);
    }

    virtual void Afficher() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual char *GetVilleDepart() const
    {
        return collection.GetLesTrajets()[0]->GetVilleDepart();
    }

    virtual char *GetVilleArrivee() const
    {
        return collection.GetLesTrajets()[collection.GetNbTrajets() - 1]->GetVilleArrivee();
    }

    Collection *GetLesTrajets()
    {
        return &collection;
    }

    //------------------------------------------------- Surcharge d'opérateurs
    // bool operator == ( const TrajetCompose & trajet ) const;

    //-------------------------------------------- Constructeurs - destructeur
    TrajetCompose(Trajet *t1, Trajet *t2);

    TrajetCompose(Collection laCollection);

    virtual ~TrajetCompose();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    Collection collection;
};

//---------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
