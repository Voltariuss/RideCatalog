/*************************************************************************
    TrajetCompose  -  Classe représentant un trajet composé caractérisé 
      par une collection ordonnée de trajets (simples et/ou composés)
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
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
void TrajetCompose::Afficher() const
// Algorithme :
//
{
  for (int i = 0; i < collection.GetNbTrajets(); i++)
  {
    cout << (i ? " - " : "");
    collection.GetLesTrajets()[i]->Afficher();
  }
  cout << endl;
} //----- Fin de Afficher

//------------------------------------------------- Surcharge d'opérateurs
bool TrajetCompose::operator==(const TrajetCompose &trajet) const
// Algorithme :
//
{
  Trajet *t1, *t2;
  cout << (trajet.GetLesTrajets()->GetLesTrajets()[0]->GetVilleDepart()) << endl;
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
TrajetCompose::TrajetCompose(Trajet *t1, Trajet *t2) : collection()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif

  collection.AjouterTrajet(t1);
  collection.AjouterTrajet(t2);
} //----- Fin de TrajetCompose

TrajetCompose::TrajetCompose(Collection laCollection) : collection(laCollection)
{
#ifdef MAP
  cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
}

TrajetCompose::~TrajetCompose()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
} //----- Fin de ~TrajetCompose

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
