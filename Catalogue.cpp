/*************************************************************************
    Catalogue  -  Classe représentant un catalogue contenant l'ensemble 
                        des trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//----------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::SaisirTrajet()
// Algorithme :
//    Récupère sur l'entrée standard le type de trajet, puis ses
//    caractéristiques.
//    Dans le cas d'un trajet composé, le système récupère la liste des
//    trajets simples associés en veillant à ce que pour chacun d'eux
//    la ville de départ corresponde à la ville d'arrivé du trajet
//    précédent s'il existe. De même, le nombre de trajet simple
//    doit être au moins égal à 2.
//    En cas d'erreur, le programme retourne le message d'erreur
//    correspondant.
//    Si la saisie est valide, alors le programme tente d'ajouter
//    le trajet ainsi créée.
//
{
  bool erreur = false;
  int typeTrajet;
  Trajet *trajet;
  cout << "Type de trajet (simple = 1, composé = 2) : ";
  cin >> typeTrajet;
  cout << endl;

  if (typeTrajet == 1)
  {
    trajet = saisirTrajetSimple();
  }
  else if (typeTrajet == 2)
  {
    trajet = saisirTrajetCompose();
  }
  else
  {
    erreur = true;
    cout << "ERREUR : Le type de trajet spécifié est incorrect." << endl;
  }

  if (!erreur && trajet != nullptr)
  {
    collectionTrajets.AjouterTrajet(trajet);
  }
  else
  {
    cout << "Echec de l'ajout du trajet." << endl;
  }
}

void Catalogue::Afficher(const Collection &trajets) const
// Algorithme :
//
{
  for (int i = 0; i < trajets.GetNbTrajets(); i++)
  {
    cout << "- ";
    trajets.GetLesTrajets()[i]->Afficher();
    cout << endl;
  }
  cout << "NbTrajets : " << trajets.GetNbTrajets() << " NbTrajetsMax : " << trajets.GetNbMaxTrajets();
} //----- Fin de Afficher

Collection Catalogue::RechercherParcours(char *depart, char *arrivee) const
// Algorithme :
//
{
  int nbTrajets = collectionTrajets.GetNbTrajets(); //, ajout;
  Trajet **lesTrajets = collectionTrajets.GetLesTrajets();
  Collection /* * lesTrajetsPossibles, */ lesTrajetsFinaux;
  //
  // lesTrajetsPossibles = new Collection[sizeof(Collection)*(pow(2, nbTrajets+1)-1)];
  // lesTrajetsPossibles[0] = new Collection;
  // lesTrajetsPossibles[0].Ajouter(lesTrajets[0]);
  //
  // lesTrajetsFinaux = new Collection;
  // if(!strcmp(lesTrajets[0].GetVilleDepart(), depart) &&
  //    !strcmp(lesTrajets[0].GetVilleArrivee(), arrivee))
  // { lesTrajetsFinaux.Ajouter(lesTrajets[0]); }
  //
  // for(int i=1; i<nbTrajets; i++) {
  //   for(int j=pow(2, i)-1; j<pow(2, i+1)-1; j++) {
  //     lesTrajetsPossibles[i] = new Collection;
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

  for (int i = 0; i < nbTrajets; i++)
  {
    if (!strcmp(lesTrajets[i]->GetVilleDepart(), depart) &&
        !strcmp(lesTrajets[i]->GetVilleArrivee(), arrivee))
    {
      lesTrajetsFinaux.AjouterTrajet(lesTrajets[i]);
    }
  }

  return lesTrajetsFinaux;
} //----- Fin de RechercherParcours

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue() : collectionTrajets()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
TrajetSimple *Catalogue::saisirTrajetSimple()
{
  TrajetSimple *trajetSimple = nullptr;
  bool erreur = false;
  char *villeDepart;
  char *villeArrive;
  int typeTransportId;
  TypeTransport TypeTransport;
  cout << "--- Saisie d'un trajet simple ---" << endl;
  cout << "Ville de départ : ";
  cin >> villeDepart;
  cout << endl;
  cout << "Ville d'arrivé : ";
  cin >> villeArrive;
  cout << endl;
  cout << "ID du mode de transport (0 : Auto, 1 : Avion, 2 : Bateau, 3 : Train) : ";
  cin >> typeTransportId;
  cout << endl;

  switch (typeTransportId)
  {
  case AUTO:
    TypeTransport = AUTO;
    break;
  case AVION:
    TypeTransport = AVION;
    break;
  case BATEAU:
    TypeTransport = BATEAU;
    break;
  case TRAIN:
    TypeTransport = TRAIN;
    break;
  default:
    erreur = true;
    cout << "ERREUR : Le numéro du type de transport spécifié est incorrect." << endl;
    break;
  }

  if (!erreur)
  {
    trajetSimple = new TrajetSimple(villeDepart, villeArrive, TypeTransport);
  }
  return trajetSimple;
}

TrajetCompose *Catalogue::saisirTrajetCompose()
{
  TrajetCompose *trajetCompose = nullptr;
  Collection collection;
  bool erreur = false;
  bool continueSaisie = true;
  TrajetSimple *trajetSimple = nullptr;

  do
  {
    TrajetSimple *trajetSimple = saisirTrajetSimple();

    if (strcmp(collection.GetDernierTrajet()->GetVilleArrivee, trajetSimple->GetVilleDepart))
    {
      collection.AjouterTrajet(trajetSimple);

      if (collection.GetNbTrajets >= 2)
      {
        char reponse;
        cout << "Continuer la saisir ? (O/N) : ";
        cin >> reponse;

        if (reponse == 'N')
        {
          continueSaisie = false;
        }
      }
    }
    else
    {
      erreur = true;
      cout << "ERREUR : La ville de départ d'un trajet doit correspondent à la ville d'arrivé";
      cout << " du trajet précédent dans un trajet composé." << endl;
    }
  } while (continueSaisie && !erreur);

  if (!erreur)
  {
    trajetCompose = new TrajetCompose(collection);
  }
  return trajetCompose;
}
