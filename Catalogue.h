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
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Collection.h"

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//      Gestion du catalogue comportant la liste des trajets simples
//      et composés de l'application avec la possibilité d'en saisir,
//      d'afficher la liste actuelle ou de faire une recherche de
//      parcours pour aller d'un point A à un point B.
//------------------------------------------------------------------------

class Catalogue
{
    //------------------------------------------------------------- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    void Fusion(Collection * col);
    // Mode d'emploi :
    //      Fusionne la collection courante avec celle passée en parametre
    Collection * GetTrajet() const;
    // Mode d'emploi :
    //      Retourne la collection de trajets du catalogue.
    void SaisirTrajet();
    // Mode d'emploi :
    //      Demande à l'utilisateur de saisir un trajet pour l'ajouter
    //      ensuite dans le catalogue.
    void Afficher(Collection *collection = nullptr) const;
    // Mode d'emploi :
    //      - collection : pointeur sur la collection à afficher, nullptr
    //          par défaut.
    //
    //      Affiche la liste des trajets de la collection spécifiée. Si la
    //      la collection est égale à nullptr, alors la méthode affichera
    //      la collection du catalogue.
    Collection *RechercherParcoursSimple(char *depart, char *arrivee) const;
    // Mode d'emploi :
    //      - depart : nom de la ville de la ville de départ du parcours
    //      - arrivee : nom de la ville d'arrivée du parcours
    //
    //      Effectue une recherche simple de parcours et retourne la
    //      collection de trajets correspondant au résultat de la
    //      recherche.
    // Contrat :
    //      depart et arrivee doivent être différents de nullptr.
    Collection *RechercherParcoursAvancee(char *depart, char *arrivee) const;
    // Mode d'emploi :
    //      - depart : nom de la ville de la ville de départ du parcours
    //      - arrivee : nom de la ville d'arrivée du parcours
    //
    //      Effectue une recherche avancée de parcours et retourne la
    //      collection de trajets correspondant au résultat de la
    //      recherche.
    // Contrat :
    //      depart et arrivee doivent être différents de nullptr.
    //---------------------------------------- Constructeurs - destructeur
    Catalogue();
    virtual ~Catalogue();

    //---------------------------------------------------------- PROTECTED
protected:
    //------------------------------------------------- Méthodes protégées
    TrajetSimple *saisirTrajetSimple();
    TrajetCompose *saisirTrajetCompose();
    void rechercherParcoursAvanceeWorker(const char *depart,
                                         const char *arrivee,
                                         const TrajetCompose &trajetCompose,
                                         const unsigned int *trajetsUtilises,
                                         const unsigned int nbTrajetsUtilises,
                                         Collection &trajetsFinaux) const;
    //------------------------------------------------- Attributs protégés
    Collection *collectionTrajets;
};
//-------------------------- Autres définitions dépendantes de <Catalogue>
#endif // CATALOGUE_H
