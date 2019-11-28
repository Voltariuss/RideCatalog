/*************************************************************************
    Collection  -  Structure de données permettant de gérer le stockage
          et les interactions avec les trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//------------- Interface de la classe <Collection> (fichier Collection.h)
#if !defined(TABLEAUTRAJETS_H)
#define TABLEAUTRAJETS_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

//------------------------------------------------------------------------
// Rôle de la classe <Collection>
//      Permet la gestion de la structure de données permettant de stocker
//      une liste de trajets correspondant soit à l'ensemble du catalogue,
//      soit à un trajet composé.
//
//------------------------------------------------------------------------

class Collection
{
    //------------------------------------------------------------- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    int AjouterTrajet(Trajet *trajet);
    // Mode d'emploi
    //      - trajet : Pointeur du trajet à ajouter dans la collection
    //
    //      Ajoute un trajet dans la collection.
    // Contrat :
    //      Le pointeur du trajet doit être différent de nullptr.
    int FusionCollection(Collection *collection);
    // Mode d'emploi :
    //      - collection : La collection à inclure dans la collection courante
    //
    //      Ajouter les trajets de la collection spécifiée dans la collection courante.
    // Contrat :
    //      Le pointeur de la collection doit être différent de nullptr.
    Trajet *GetPremierTrajet() const;
    // Mode d'emploi :
    //      Retourne le premier trajet de la collection.
    Trajet *GetDernierTrajet() const;
    // Mode d'emploi :
    //      Retourne le dernier trajet de la collection.
    unsigned int GetNbTrajets() const;
    // Mode d'emploi :
    //      Retourne le nombre de trajets présents dans la collection.
    unsigned int GetTaille() const;
    // Mode d'emploi :
    //      Retourne la taille de la collection.
    Trajet **GetTrajets() const;
    // Mode d'emploi :
    //      Retourne la liste des trajets de la collection.
    Collection *Clone() const;
    // Mode d'emploi :
    //      Clone la collection.
    static unsigned int getNbInstance();
    // Mode d'emploi :
    //      Retourne le nombre d'instance de la classe.
    //---------------------------------------- Constructeurs - destructeur
    Collection();
    Collection(const Collection &collection);
    virtual ~Collection();

    //---------------------------------------------------------- PROTECTED
protected:
    //------------------------------------------------- Méthodes protégées
    bool reallocation();
    //------------------------------------------------- Attributs protégés
    unsigned int nbTrajets;
    unsigned int taille;
    Trajet **trajets;
    static unsigned int nbInstance;
    static const unsigned int TAILLE_INIT = 10;
};
//------------------------- Autres définitions dépendantes de <Collection>
#endif // TABLEAUTRAJETS_H
