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

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void AjouterTrajet ( const Trajet & trajet )
// Algorithme :
//
{
  if(nbTrajets >= taille)
  {
    // Réaloc
  }

  lesTrajets[nbTrajets++] = trajet;
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


TableauTrajets::TableauTrajets ( )
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

//----------------------------------------------------- Méthodes protégées
