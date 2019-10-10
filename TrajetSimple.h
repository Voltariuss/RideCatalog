/*************************************************************************
  TrajetSimple  -  Classe représentant un trajet simple caractérisé par 
    une ville de départ, une ville d'arrivé et un mode de transport
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h)
#if !defined(TRAJETSIMPLE_H)
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "Trajet.h"

//------------------------------------------------------------------ Types
enum TypeTransport
{
    AUTO,
    AVION,
    BATEAU,
    TRAIN
};

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//      Permet la gestion des trajets simples de l'application.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
    //---------------------------------------------------------- -- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    void Afficher(const char *indents) const;
    // Mode d'emploi :
    //      - indents : Indentation de base de l'affichage du trajet
    //
    //      Affiche le trajet simple en prenant en compte l'indentation
    //      actuelle dans l'affichage.
    // Contrat :
    //      La valeur du pointeur est différente de nullptr et la chaîne
    //      de caractères associée doit être composée uniquement
    //      de caractères de tabulation ('\t').
    char *GetVilleDepart() const;
    // Mode d'emploi :
    //      Retourne la ville de départ du trajet simple.
    char *GetVilleArrivee() const;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée du trajet simple.
    TypeTransport GetTypeTransport() const;
    // Mode d'emploi :
    //      Retourne le type de transport du trajet simple.
    Trajet *Clone() const;
    // Mode d'emploi :
    //      Clone le trajet simple.
    static unsigned int GetNbInstance();
    // Mode d'emploi :
    //      Retourne le nombre d'instance de la classe.
    //---------------------------------------- Constructeurs - destructeur
    TrajetSimple(char *depart, char *arrivee, TypeTransport transport);
    TrajetSimple(const TrajetSimple &trajetSimple);
    virtual ~TrajetSimple();

    //---------------------------------------------------------- PROTECTED
protected:
    //------------------------------------------------- Attributs protégés
    char *villeDepart;
    char *villeArrivee;
    TypeTransport typeTransport;
    static const unsigned int TAILLE_CHAINE = 100;
    static unsigned int nbInstance;
};
//----------------------- Autres définitions dépendantes de <TrajetSimple>
#endif // TRAJETSIMPLE_H
