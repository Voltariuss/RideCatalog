/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//----------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Afficher ( const TableauTrajets & trajets ) const
// Algorithme :
//
{
  for(int i=0; i<trajets.GetNbTrajets(); i++) {
    cout << "- ";
    trajets.GetLesTrajets()[i]->Afficher();
    cout << endl;
  }
  cout << "NbTrajets : " << trajets.GetNbTrajets() << " NbTrajetsMax : " << trajets.GetNbMaxTrajets();
} //----- Fin de Afficher


TableauTrajets Catalogue::RechercherParcours ( char * depart, char * arrivee ) const
// Algorithme :
//
{
  int nbTrajets = tableauTrajets.GetNbTrajets();//, ajout;
  Trajet ** lesTrajets = tableauTrajets.GetLesTrajets();
  TableauTrajets /* * lesTrajetsPossibles, */lesTrajetsFinaux;
  //
  // lesTrajetsPossibles = new TableauTrajets[sizeof(TableauTrajets)*(pow(2, nbTrajets+1)-1)];
  // lesTrajetsPossibles[0] = new TableauTrajets;
  // lesTrajetsPossibles[0].Ajouter(lesTrajets[0]);
  //
  // lesTrajetsFinaux = new TableauTrajets;
  // if(!strcmp(lesTrajets[0].GetVilleDepart(), depart) &&
  //    !strcmp(lesTrajets[0].GetVilleArrivee(), arrivee))
  // { lesTrajetsFinaux.Ajouter(lesTrajets[0]); }
  //
  // for(int i=1; i<nbTrajets; i++) {
  //   for(int j=pow(2, i)-1; j<pow(2, i+1)-1; j++) {
  //     lesTrajetsPossibles[i] = new TableauTrajets;
  //     lesTrajetsPossibles[i].Ajouter(lesTrajetsPossibles[(i-1)/2]);
  //     if(j%2 == 0 &&
  //        lesTrajetsPossibles[(i-1)/2].GetLesTrajets()[lesTrajetsPossibles[(i-1)/2]
  //                                    .GetNbTrajets()-1]
  //                                    .ArriveeEgalDepart(lesTrajets[i]))
  //     {
  //       ajout = lesTrajetsPossibles[i].Ajouter(lesTrajets[i]);
  //       if(ajout && !strcmp(lesTrajetsPossibles[i].GetLesTrajets()[0]
  //                                                 .GetVilleDepart(), depart) &&
  //          !strcmp(lesTrajetsPossibles[i].GetLesTrajets()[lesTrajetsPossibles[i]
  //                                        .GetNbTrajets()-1]
  //                                        .GetVilleArrivee(), arrivee))
  //       { lesTrajetsFinaux.Ajouter(lesTrajetsPossibles[i]); }
  //     }
  //   }
  // }
  //
  // for(i=0; i<pow(2, nbTrajets+1)-1; i++) { delete lesTrajetsPossibles[i]; }
  // delete[] lesTrajetsPossibles;

  for(int i=0; i<nbTrajets; i++) {
    if(!strcmp(lesTrajets[i]->GetVilleDepart(), depart) &&
       !strcmp(lesTrajets[i]->GetVilleArrivee(), arrivee))
    { lesTrajetsFinaux.AjouterTrajet(lesTrajets[i]); }
  }

  return lesTrajetsFinaux;
} //----- Fin de RechercherParcours

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( ) :
    tableauTrajets ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au constructeur de <Catalogue>" << endl;
  #endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
//
{
  #ifdef MAP
      cout << "Appel au destructeur de <Catalogue>" << endl;
  #endif
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
