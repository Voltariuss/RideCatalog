/*************************************************************************
                    Main  -  Point d'entré du programme
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//------------ Réalisation du module <Main> (fichier Main.cpp)

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables Statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( ) {
  Catalogue c1;
  TrajetSimple t1 ("Poitiers", "Niort", AUTO),
               t2 ("Nantes", "Lyon", BATEAU),
               t3 ("Poitiers", "Nantes", BATEAU),
               t4 ("Orléans", "Poitiers", BATEAU),
               t5 ("Niort", "Nantes", AVION);
  TrajetCompose t6 (&t3, &t2),  // "Poitiers" => "Nantes" => "Lyon"
                t7 (&t1, &t5);  // "Poitiers" => "Niort" => "Nantes"

  c1.AjouterTrajet(&t1);
  c1.AjouterTrajet(&t2);
  c1.AjouterTrajet(&t3);
  c1.AjouterTrajet(&t4);
  c1.AjouterTrajet(&t5);
  // c1.AjouterTrajet(&t6);
  c1.AjouterTrajet(&t7);

  c1.Afficher();
  cout << endl;
  // Recherche "Poitiers" => "Lyon"
  // c1.Afficher(c1.RechercherParcoursComplexe("Poitiers", "Lyon"));

  return 0;
} //----- fin de main
