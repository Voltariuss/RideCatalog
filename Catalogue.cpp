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
} //----- Fin de Afficher


Collection Catalogue::RechercherParcoursSimple ( char * depart, char * arrivee ) const
// Algorithme :
//
{
  int nbTrajets = collectionTrajets.GetNbTrajets();
  Trajet ** lesTrajets = collectionTrajets.GetLesTrajets();
  Collection lesTrajetsFinaux;

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


Collection Catalogue::RechercherParcoursComplexe ( char * depart, char * arrivee ) const
// Algorithme :
//
{
  int nbTrajets = collectionTrajets.GetNbTrajets(), nbDeparts;
  int iPointe, prochainIDispo, iMax;//, ajout;
  Trajet ** lesTrajets = collectionTrajets.GetLesTrajets();
  Collection * lesTrajetsPossibles, * tmpLesTrajetsPossibles, lesTrajetsFinaux;

  nbDeparts = 0;
  iMax = nbTrajets;
  lesTrajetsPossibles = new Collection[sizeof(Collection)*iMax];
  for(int i=0; i<nbTrajets; i++) {
    if(!strcmp(lesTrajets[0]->GetVilleDepart(), depart)) {
      // lesTrajetsPossibles = new Collection;
      lesTrajetsPossibles[nbDeparts++].AjouterTrajet(lesTrajets[i]);
    }
  }

  iPointe = 0;
  prochainIDispo = nbDeparts;
  while(iPointe != prochainIDispo) {
    for(int i=0; i<nbTrajets; i++) {
      // Si ville arrivée du trajet pointé est différent de l'arrivée voulue
      // et ville arrivée du trajet pointé est égale à ville départ trajet i
      if(strcmp(lesTrajetsPossibles[iPointe].GetLesTrajets()[lesTrajetsPossibles[iPointe].GetNbTrajets()-1]->GetVilleArrivee(), arrivee) &&
         !strcmp(lesTrajetsPossibles[iPointe].GetLesTrajets()[lesTrajetsPossibles[iPointe].GetNbTrajets()-1]->GetVilleArrivee(), lesTrajets[i]->GetVilleDepart())) {
        if(prochainIDispo == iMax) {
          tmpLesTrajetsPossibles = new Collection[sizeof(Collection)*iMax*2];
          for(int j=0; j<iMax; j++)
          { tmpLesTrajetsPossibles[j] = lesTrajetsPossibles[j]; }
          iMax *= 2;
          delete[] lesTrajetsPossibles;
          lesTrajetsPossibles = tmpLesTrajetsPossibles;
        }
        // lesTrajetsPossibles[prochainIDispo] = new Collection;
        lesTrajetsPossibles[prochainIDispo].AjouterTrajet(&lesTrajetsPossibles[iPointe]);
        lesTrajetsPossibles[prochainIDispo].AjouterTrajet(lesTrajets[i]);
        prochainIDispo++;
      }
    }
    iPointe++;
  }

  for(int i=0; i<prochainIDispo; i++) {
    if(!strcmp(lesTrajetsPossibles[i].GetLesTrajets()[lesTrajetsPossibles[iPointe].GetNbTrajets()-1]->GetVilleArrivee(), arrivee))
    { lesTrajetsFinaux.AjouterTrajet(&lesTrajetsPossibles[i]); }
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

    if (strcmp(collection.GetDernierTrajet()->GetVilleArrivee(), trajetSimple->GetVilleDepart()))
    {
      collection.AjouterTrajet(trajetSimple);

      if (collection.GetNbTrajets() >= 2)
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
