/*************************************************************************
                           Main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
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
  char *str1 = new char[8+1], *str2 = new char[5+1];
  char *str3 = new char[6+1], *str4 = new char[4+1];
  char *str5 = new char[8+1], *str6 = new char[6+1];
  char *str7 = new char[7+1], *str8 = new char[8+1];
  char *str9 = new char[4+1], *str10 = new char[7+1];
  strcpy(str1, "Poitiers"); strcpy(str2, "Niort");
  strcpy(str3, "Nantes"); strcpy(str4, "Lyon");
  strcpy(str5, "Poitiers"); strcpy(str6, "Nantes");
  strcpy(str7, "Orléans"); strcpy(str8, "Poitiers");
  strcpy(str9, "Lyon"); strcpy(str10, "Orléans");
  TrajetSimple t1 (str1, str2, AUTO),
               t2 (str3, str4, BATEAU),
               t3 (str5, str6, BATEAU),
               t4 (str7, str8, BATEAU),
               t5 (str9, str10, AVION);
  TrajetCompose t6 (&t3, &t2), t7 (&t3, &t2);

  t7.AjouterTrajet(&t5);

  c1.AjouterTrajet(&t1);
  c1.AjouterTrajet(&t2);
  c1.AjouterTrajet(&t3);
  c1.AjouterTrajet(&t4);
  c1.AjouterTrajet(&t6);
  t6.Afficher();
  // c1.AjouterTrajet(&t6);
  // cout << t7.GetVilleDepart();
  // c1.AjouterTrajet(&t7);
  //
  // c1.Afficher();
  // c1.Afficher(c1.RechercherParcours(str1, str4));

  return 0;
} //----- fin de main
