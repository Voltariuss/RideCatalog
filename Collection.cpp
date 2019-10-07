/*************************************************************************
    Collection  -  Structure de données permettant de gérer le stockage
          et les interactions avec les trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//- Réalisation de la classe <Collection> (fichier Collection.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Collection.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes
#define TAILLE_INIT 10

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Collection::AjouterTrajet(Trajet *trajet)
// Algorithme :
//
{
  bool realloc = false;

  // if(Contient(trajet)) return 0;
  if(nbTrajets >= taille) realloc = reallocaction();

  lesTrajets[nbTrajets++] = trajet;

  return realloc ? -1 : 1;
} //----- Fin de AjouterTrajet

int Collection::AjouterTrajet(Collection *trajets)
// Algorithme :
//
{
  bool realloc = false;
  // int nbTrajetsAjoutes = 0;

  for(int i=0; i<trajets->GetNbTrajets(); i++) {
    // if(!Contient(trajets->GetLesTrajets()[i])) {
      if(nbTrajets >= taille) realloc = reallocaction();

      lesTrajets[nbTrajets++] = trajets->GetLesTrajets()[i];
      // nbTrajetsAjoutes++;
    // }
  }

  return realloc ? trajets->GetNbTrajets() * -1 : trajets->GetNbTrajets();
} //----- Fin de AjouterTrajet


// bool Collection::Contient ( Trajet * trajet ) const
// // Algorithme :
// //
// {
//   if(dynamic_cast<TrajetCompose*>(trajet)) cout << "NbTrajets : " << (*dynamic_cast<TrajetCompose*>(trajet)).GetLesTrajets()->GetNbTrajets() << endl;
//
//   for(int i=0; i<nbTrajets; i++) {
//     if(typeid(trajet) == typeid(lesTrajets[i])) {
//       if(dynamic_cast<TrajetSimple*>(trajet) &&
//          *dynamic_cast<TrajetSimple*>(trajet) == *dynamic_cast<TrajetSimple*>(lesTrajets[i]))
//       { return true; }
//       else if(dynamic_cast<TrajetCompose*>(trajet) &&
//               *dynamic_cast<TrajetCompose*>(trajet) == *dynamic_cast<TrajetCompose*>(lesTrajets[i]))
//       { return true; }
//     }
//   }
//
//   return false;
// } //----- Fin de Contient

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Collection::Collection() : nbTrajets(0u),
                           taille(TAILLE_INIT),
                           lesTrajets(new Trajet *[TAILLE_INIT])
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au constructeur de <Collection>" << endl;
#endif
} //----- Fin de Collection

Collection::~Collection()
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au destructeur de <Collection>" << endl;
  #endif

  for(int i=0; i<nbTrajets; i++) { delete lesTrajets[i]; }
  delete[] lesTrajets;
} //----- Fin de ~Collection

//------------------------------------------------------------------ PRIVE
bool Collection::reallocaction()
// Algorithme :
//
{
  Trajet **newTrajets;

  if (nbTrajets == taille - TAILLE_INIT / 2)
    return false;

  taille += TAILLE_INIT / 2;
  newTrajets = new Trajet *[taille];
  for (int i = 0; i < nbTrajets; i++)
    newTrajets[i] = lesTrajets[i];
  delete[] lesTrajets;
  lesTrajets = newTrajets;

  return true;
} //----- Fin de reallocaction

//----------------------------------------------------- Méthodes protégées
