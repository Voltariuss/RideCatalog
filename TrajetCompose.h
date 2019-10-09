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

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//      Permet la gestion des trajets composés de l'application.
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
    //------------------------------------------------------------- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    void Afficher(const char *indents) const;
    // Mode d'emploi :
    //      Affiche le trajet composé en prenant en compte l'indentation
    //      actuelle dans l'affichage.
    // Contrat :
    //      La valeur du pointeur est différente de nullptr et la chaîne
    //      de caractères associée doit être composée uniquement
    //      de caractères de tabulation ('\t').
    char *GetVilleDepart() const;
    // Mode d'emploi :
    //      Retourne la ville de départ du trajet composé.
    char *GetVilleArrivee() const;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée du trajet composé.
    Collection *GetTrajets() const;
    // Mode d'emploi :
    //      Retourne la collection de trajets du trajet composé.
    Trajet *Clone() const;
    // Mode d'emploi :
    //      Clone le trajet composé.
    static unsigned int GetNbInstance();
    // Mode d'emploi :
    //      Retourne le nombre d'instance de la classe.
    //---------------------------------------- Constructeurs - destructeur
    TrajetCompose();
    TrajetCompose(Collection *laCollection);
    // Contrat :
    //      La collection doit être différente de nullptr.
    TrajetCompose(const TrajetCompose &trajetCompose);
    virtual ~TrajetCompose();

    //---------------------------------------------------------- PROTECTED
protected:
    //------------------------------------------------- Attributs protégés
    Collection *collection;
    static unsigned int nbInstance;
};
//---------------------- Autres définitions dépendantes de <TrajetCompose>
#endif // TRAJETCOMPOSE_H
