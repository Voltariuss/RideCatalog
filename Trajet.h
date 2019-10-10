/*************************************************************************
            Trajet  -  Classe abstraite représentant un trajet
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------------------- Interface de la classe <Trajet> (fichier Trajet.h)
#if !defined(Trajet_H)
#define Trajet_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//      Permet la gestion des trajets de l'application.
//------------------------------------------------------------------------

class Trajet
{
    //------------------------------------------------------------- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    virtual void Afficher(const char *indents) const = 0;
    // Mode d'emploi :
    //      - indents : Tabulation de base de l'affichage du trajet
    //
    //      Affiche le trajet en prenant en compte l'indentation actuelle
    //      dans l'affichage.
    // Contrat :
    //      La valeur du pointeur est différente de nullptr et la chaîne
    //      de caractères associée doit être composée uniquement
    //      de caractères de tabulation ('\t').
    virtual char *GetVilleDepart() const = 0;
    // Mode d'emploi :
    //      Retourne la ville de départ du trajet.
    virtual char *GetVilleArrivee() const = 0;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée du trajet.
    virtual Trajet *Clone() const = 0;
    // Mode d'emploi :
    //      Clone le trajet.
    static unsigned int GetNbInstance();
    // Mode d'emploi :
    //      Retourne le nombre d'instance de la classe.
    //---------------------------------------- Constructeurs - destructeur
    Trajet();
    virtual ~Trajet();

    //---------------------------------------------------------- PROTECTED

    //------------------------------------------------- Attributs protégés
    static unsigned int nbInstance;
};
//----------------------------- Autres définitions dépendantes de <Trajet>
#endif // Trajet_H
