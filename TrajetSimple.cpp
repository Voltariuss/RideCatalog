/*************************************************************************
  TrajetSimple  -  Classe représentant un trajet simple caractérisé par 
    une ville de départ, une ville d'arrivé et un mode de transport
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
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
