/*************************************************************************
                           TableauTrajets  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TableauTrajets> (fichier TableauTrajets.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TableauTrajets.h"

//------------------------------------------------------------- Constantes
#define TAILLE_INIT 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int TableauTrajets::AjouterTrajet ( Trajet * trajet )
// Algorithme :
//
{
  bool realloc = false;

  if(nbTrajets >= taille) realloc = reallocaction();

  lesTrajets[nbTrajets++] = trajet;

  return realloc ? -1 : 1;
} //----- Fin de AjouterTrajet


//------------------------------------------------- Surcharge d'opérateurs
TableauTrajets & TableauTrajets::operator = ( const TableauTrajets & unTableauTrajets )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
TableauTrajets::TableauTrajets ( const TableauTrajets & unTableauTrajets )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au constructeur de copie de <TableauTrajets>" << endl;
  #endif
} //----- Fin de TableauTrajets (constructeur de copie)


TableauTrajets::TableauTrajets ( ) :
    nbTrajets ( 0 ),
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


bool TableauTrajets::contient ( Trajet * trajet ) const
// Algorithme :
//
{
  for(int i=0; i<nbTrajets; i++)
    // if(trajet == lesTrajets[i])
      return true;

  return false;
} //----- Fin de contient

//----------------------------------------------------- Méthodes protégées
