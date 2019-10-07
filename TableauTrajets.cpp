/*************************************************************************
                           TableauTrajets  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//- Réalisation de la classe <TableauTrajets> (fichier TableauTrajets.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TableauTrajets.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes
#define TAILLE_INIT 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int TableauTrajets::AjouterTrajet ( Trajet * trajet )
// Algorithme :
//
{
  bool realloc = false;

  if(Contient(trajet)) return 0;
  if(nbTrajets >= taille) realloc = reallocaction();

  lesTrajets[nbTrajets++] = trajet;

  return realloc ? -1 : 1;
} //----- Fin de AjouterTrajet


int TableauTrajets::AjouterTrajet ( TableauTrajets * trajets )
// Algorithme :
//
{
  bool realloc = false;
  int nbTrajetsAjoutes = 0;

  for(int i=0; i<trajets->GetNbTrajets(); i++) {
    if(!Contient(trajets->GetLesTrajets()[i])) {
      if(nbTrajets >= taille) realloc = reallocaction();

      lesTrajets[nbTrajets++] = trajets->GetLesTrajets()[i];
      nbTrajetsAjoutes++;
    }
  }

  return realloc ? nbTrajetsAjoutes * -1 : nbTrajetsAjoutes;
} //----- Fin de AjouterTrajet


bool TableauTrajets::Contient ( Trajet * trajet ) const
// Algorithme :
//
{
  if(dynamic_cast<TrajetCompose*>(trajet)) cout << dynamic_cast<TrajetCompose*>(trajet)->GetLesTrajets()->GetNbTrajets();

  for(int i=0; i<nbTrajets; i++) {
    if(typeid(trajet) == typeid(lesTrajets[i])) {
      if(dynamic_cast<TrajetSimple*>(trajet) &&
         *dynamic_cast<TrajetSimple*>(trajet) == *dynamic_cast<TrajetSimple*>(lesTrajets[i]))
      { return true; }
      else if(dynamic_cast<TrajetCompose*>(trajet))// &&
              //*dynamic_cast<TrajetCompose*>(trajet) == *dynamic_cast<TrajetCompose*>(lesTrajets[i]))
      { return true; }
    }
  }

  return false;
} //----- Fin de Contient


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TableauTrajets::TableauTrajets ( ) :
    nbTrajets ( 0u ),
    taille ( TAILLE_INIT ),
    lesTrajets ( new Trajet * [TAILLE_INIT] )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au constructeur de <TableauTrajets>" << endl;
  #endif
} //----- Fin de TableauTrajets


TableauTrajets::~TableauTrajets ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au destructeur de <TableauTrajets>" << endl;
  #endif
} //----- Fin de ~TableauTrajets


//------------------------------------------------------------------ PRIVE
bool TableauTrajets::reallocaction ( )
// Algorithme :
//
{
  Trajet ** newTrajets;

  if(nbTrajets == taille - TAILLE_INIT / 2) return false;

  taille += TAILLE_INIT / 2;
  newTrajets = new Trajet * [taille];
  for(int i=0; i<nbTrajets; i++)
    newTrajets[i] = lesTrajets[i];
  delete[] lesTrajets;
  lesTrajets = newTrajets;

  return true;
} //----- Fin de reallocaction

//----------------------------------------------------- Méthodes protégées
