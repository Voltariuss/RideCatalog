/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//----- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
bool TrajetSimple::operator == ( TrajetSimple & trajet )
{
  return !strcmp(villeDepart, trajet.villeDepart) &&
         !strcmp(villeArrivee, trajet.villeArrivee) &&
         moyenTransport == trajet.moyenTransport;
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( char *depart, char *arrivee, typeTransport transport ):
    moyenTransport ( transport )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au constructeur de <TrajetSimple>" << endl;
  #endif

  villeDepart = depart;
  villeArrivee = arrivee;
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au destructeur de <TrajetSimple>" << endl;
  #endif
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
