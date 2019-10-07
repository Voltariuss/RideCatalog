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
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum TypeTransport { AUTO, AVION, BATEAU, TRAIN };

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Afficher ( ) const
    {
      cout << "Départ : " << villeDepart
           << " Arrivée : " << villeArrivee
           << " Moyen de Transport : " << moyenTransport;
    }

    virtual char * GetVilleDepart ( ) const
    { return villeDepart; }

    virtual char * GetVilleArrivee ( ) const
    { return villeArrivee; }

    TypeTransport GetMoyenTransport ( ) const
    { return moyenTransport; }

//------------------------------------------------- Surcharge d'opérateurs
    bool operator == ( TrajetSimple & trajet );

    bool operator != ( TrajetSimple & trajet )
    { return !(*this == trajet); }

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( char *depart, char *arrivee, TypeTransport transport );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char *villeDepart;
    char *villeArrivee;
    TypeTransport moyenTransport;

};

//----------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H
