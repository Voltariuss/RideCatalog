/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//--------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h)
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum typeTransport { AUTO, AVION, BATEAU, TRAIN };

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

    typeTransport GetMoyenTransport ( ) const
    { return moyenTransport; }

//------------------------------------------------- Surcharge d'opérateurs
    bool operator == ( TrajetSimple & trajet );

    bool operator != ( TrajetSimple & trajet )
    { return !(*this == trajet); }

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( char *depart, char *arrivee, typeTransport transport );
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
    typeTransport moyenTransport;

};

//----------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H
