/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//--- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Afficher ( ) const
// Algorithme :
//
{
  for(int i=0; i<tableauTrajets.GetNbTrajets(); i++) {
    cout << (i ? " - " : "");
    tableauTrajets.GetLesTrajets()[i]->Afficher();
  }
  cout << endl;
} //----- Fin de Afficher


//------------------------------------------------- Surcharge d'opérateurs
bool TrajetCompose::operator == ( const TrajetCompose & trajet ) const
// Algorithme :
//
{
  Trajet *t1, *t2;
cout << (trajet.tableauTrajets.GetNbTrajets());
  // if(trajet.tableauTrajets.GetNbTrajets() != tableauTrajets.GetNbTrajets())
  //   return false;
  //
  // for(int i=0; i<tableauTrajets.GetNbTrajets(); i++) {
  //   t1 = trajet.tableauTrajets.GetLesTrajets()[i];
  //   t2 = tableauTrajets.GetLesTrajets()[i];
  //
  //   // Faire le second test (avec dynamic_cast) selon le type de t1 et t2
  //   // pour faciliter le tp, les trajets d'un trajet composé seront forcement
  //   // des trajets simple.
  //   if(typeid(&t1) != typeid(t2) &&
  //      *dynamic_cast<TrajetSimple*>(t1) != *dynamic_cast<TrajetSimple*>(t2))
  //     return false;
  // }

  return true;
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( Trajet * t1, Trajet * t2 ) :
    tableauTrajets ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au constructeur de <TrajetCompose>" << endl;
  #endif

  tableauTrajets.AjouterTrajet(t1);
  tableauTrajets.AjouterTrajet(t2);
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au destructeur de <TrajetCompose>" << endl;
  #endif
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
