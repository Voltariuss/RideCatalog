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
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes
#define TAILLE_CHAINE 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Fusion(Collection *collection)
// Algorithme
//      Fusionne la collection passée en paramètre avec la collection du catalogue.
{
    if (collection != nullptr) {
        this->collectionTrajets->Fusion(collection, 0, collection->GetNbTrajets());
    }
}

void Catalogue::AjouterTrajet(Trajet *trajet)
// Algorithme
//      Ajoute le trajet en paramètre dans la collection du catalogue.
{
    collectionTrajets->AjouterTrajet(trajet);
}

Collection *Catalogue::GetTrajet() const
// Algorithme :
//      Retourne la collection de trajets du catalogue.
{
    return collectionTrajets;
} //----- Fin de GetTrajet

void Catalogue::Afficher(Collection *collection) const
// Algorithme :
//      Affiche individuellement chaque trajet de la collection spécifiée.
{
    if (collection == nullptr) {
        collection = collectionTrajets;
    }
    unsigned int size = collection->GetNbTrajets();

    if (size > 0) {
        cout << endl;

        for (unsigned int i = 0; i < size; i++) {
            char str[] = {0};
            collection->GetTrajets()[i]->Afficher(str);
        }
    } else {
        cout << "Aucun trajet à afficher." << endl;
    }
} //----- Fin de Afficher

Collection *Catalogue::RechercherParcoursSimple(char *depart, char *arrivee) const
// Algorithme :
//      Pour chaque trajet du catalogue la méthode compare le nom de la ville
//      de départ et d'arrivée avec les noms passés en paramètres.
//      Si les noms correspondent, alors le trajet est copié dans la collection
//      qui sera retournée à la fin de la méthode.
{
    unsigned int nbTrajets = collectionTrajets->GetNbTrajets();
    Trajet **trajets = collectionTrajets->GetTrajets();
    Collection *trajetsFinaux = new Collection();

    for (unsigned int i = 0; i < nbTrajets; i++) {
        if (!strcmp(trajets[i]->GetVilleDepart(), depart) &&
            !strcmp(trajets[i]->GetVilleArrivee(), arrivee)) {
            trajetsFinaux->AjouterTrajet(trajets[i]->Clone());
        }
    }
    return trajetsFinaux;
} //----- Fin de RechercherParcours

Collection *Catalogue::RechercherParcoursAvancee(char *depart, char *arrivee) const
// Algorithme :
//      Voir algorithme de rechercherParcoursAvanceeWorker.
{
    TrajetCompose *trajetCompose = new TrajetCompose();
    Collection *trajetsFinaux = new Collection();
    unsigned int *trajetsUtilises = new unsigned int[sizeof(unsigned int)];

    rechercherParcoursAvanceeWorker(depart, arrivee, *trajetCompose, trajetsUtilises, 0,
                                    *trajetsFinaux);
    delete trajetCompose;
    delete[] trajetsUtilises;
    return trajetsFinaux;
} //----- Fin de RechercherParcours

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue() : collectionTrajets(new Collection()) {
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    if (collectionTrajets == nullptr) {
        cerr << "ERREUR FATALE : problème d'allocation de mémoire"
             << ", fin du programme." << endl;
        exit(EXIT_FAILURE);
    }
} //----- Fin de Catalogue

Catalogue::~Catalogue() {
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete collectionTrajets;
} //----- Fin de ~Catalogue

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Méthodes protégées
void Catalogue::rechercherParcoursAvanceeWorker(const char *depart,
                                                const char *arrivee,
                                                const TrajetCompose &trajetCompose,
                                                const unsigned int *trajetsUtilises,
                                                const unsigned int nbTrajetsUtilises,
                                                Collection &trajetsFinaux) const
// Paramètres d'entrée :
//      - Pointeur sur chaîne de caractères depart, correspond à l'arrivée
//          du dernier trajet qui compose l'objet trajetCompose passé en
//          paramètre. Si trajetCompose est vide, alors depart représente le
//          point de départ saisie par l'utilisateur,
//      - Pointeur sur chaîne de caractères arrivee, correspond à l'arrivée
//          saisie par l'utilisateur,
//      - Référence sur TrajetCompose trajetCompose, est composé des trajets
//          qui permettent d'aller du point de départ initial au point de
//          départ actuel (paramètre depart),
//      - Tableau d'entiers trajetsUtilises, contient l'index des trajets
//          utilisés dans l'objet trajetCompose passé en paramètre,
//      - Entier nbTrajetsUtilises, correspond au nombre de trajets utilisés
//          dans trajetCompose passé en paramètre,
//      - Référence sur Collection lesTrajetsFinaux, contient tous les
//          permettant d'aller du point de départ initial au point d'arrivé.
//
//
// Algorithme :
//      Pour chaque trajets du catalogue :
//          Vérifier qu'il n'a pas été utilisé dans la construction du parcours
//          (valeur booléenne + comparer index du trajets aux index présents dans
//          trajetsUtilises)
//
//          Si le départ du trajet est égal à depart :
//          Dupliquer trajetCompose
//          Ajouter le trajet à trajetComposeDuplique
//
//          Si l'arrivée de trajetComposeDuplique est égal à arrivee :
//              Ajouter trajetComposeDuplique à lesTrajetsFinaux
//          Sinon
//              Si nbTrajetsUtilises < nombre de trajets dans catalogue :
//                  Dupliquer trajetsUtilises
//              Ajouter l'index du trajet à trajetsUtilisesDuplique
//              Appel récursif de Catalogue::rechercherParcoursComplexe(...)
//              Destruction de trajetsUtilisesDuplique
{
    unsigned int nbTrajets = collectionTrajets->GetNbTrajets();
    Trajet **trajets = collectionTrajets->GetTrajets();
    bool utilise;

    for (unsigned int i = 0; i < nbTrajets; i++) {
        // Vérifier que le trajet n'a pas déjà été utilisé dans la constrution de ce parcours
        utilise = false;

        for (unsigned int j = 0; j < nbTrajetsUtilises; j++) {
            if (trajetsUtilises[j] == i) {
                utilise = true;
                break;
            }
        }

        // Départ == Arrivée précédente
        if (!utilise && !strcmp(trajets[i]->GetVilleDepart(), depart)) {
            TrajetCompose *trajetComposeDuplique = (TrajetCompose *) trajetCompose.Clone();
            trajetComposeDuplique->GetTrajets()->AjouterTrajet(trajets[i]->Clone());
            // Si arrivée == arrivée finale alors ajouter aux trajets possibles
            // Sinon continuer la construction du trajet
            if (!strcmp(trajetComposeDuplique->GetVilleArrivee(), arrivee)) {
                TrajetCompose *trajetCompose = new TrajetCompose(trajetComposeDuplique->GetTrajets()->Clone());
                trajetsFinaux.AjouterTrajet(trajetCompose);
            } else {
                // Si tous les trajets du catalogue n'ont pas déjà été utilisés
                if (nbTrajetsUtilises < nbTrajets) {
                    unsigned int *trajetsUtilisesDuplique = new unsigned int[sizeof(unsigned int) *
                                                                             (nbTrajetsUtilises + 1)];

                    for (unsigned int j = 0; j < nbTrajetsUtilises; j++) {
                        trajetsUtilisesDuplique[j] = trajetsUtilises[j];
                    }
                    trajetsUtilisesDuplique[nbTrajetsUtilises] = i;

                    rechercherParcoursAvanceeWorker(trajetComposeDuplique->GetVilleArrivee(),
                                                    arrivee,
                                                    *trajetComposeDuplique,
                                                    trajetsUtilisesDuplique,
                                                    nbTrajetsUtilises + 1,
                                                    trajetsFinaux);
                    delete[] trajetsUtilisesDuplique;
                }
            }
            delete trajetComposeDuplique;
        }
    }
} //----- Fin de rechercherParcoursAvanceeWorker
