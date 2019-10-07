/*************************************************************************
    Catalogue  -  Classe représentant un catalogue contenant l'ensemble 
                        des trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------------- Interface de la classe <Catalogue> (fichier Catalogue.h)
#if !defined(CATALOGUE_H)
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Collection.h"

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
    void SaisirTrajet();

    void Afficher() const
    {
        Afficher(collectionTrajets);
    }

    void Afficher(const Collection &trajets) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    int AjouterTrajet(Trajet *trajet)
    {
        return collectionTrajets.AjouterTrajet(trajet);
    }

    Collection RechercherParcours(char *depart, char *arrivee) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur
    Catalogue();

    virtual ~Catalogue();

    //-------------------------------------------------------------- PROTECTED

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    Collection collectionTrajets;

    //------------------------------------------------------------------ PRIVE
private:
    TrajetSimple *saisirTrajetSimple();
    TrajetCompose *saisirTrajetCompose();
};

//-------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
