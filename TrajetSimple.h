/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum typeTransport { AUTO, AVION, BATEAU, TRAIN };

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//
//
//------------------------------------------------------------------------

class TrajetSimple : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    char * GetVilleDepart ( ) { return villeDepart; };
    // Mode d'emploi :
    //
    // Contrat :
    //

    char * GetVilleArrivee ( ) { return villeArrivee; };
    // Mode d'emploi :
    //
    // Contrat :
    //

    char * GetMoyenTransport ( ) { return moyenTransport; };
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    TrajetSimple & operator = ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    TrajetSimple ( char *depart, char *arrivee, typeTransport transport ),
    villeDepart ( depart ), villeArrivee ( arrivee ), moyenTransport ( transport);
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
typeTransport moyenTransport = nullptr;

};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H
