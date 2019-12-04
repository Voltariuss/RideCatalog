/*************************************************************************
    Collection  -  Structure de données permettant de gérer le stockage
          et les interactions avec les trajets de l'application
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------- Réalisation de la classe <Collection> (fichier Collection.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Collection.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Collection::AjouterTrajet(Trajet *trajet)
// Algorithme :
//      Ajoute le trajet passé en paramètre en vérifiant avant s'il
//      est nécessaire de réallouer la collection ou non.
//      Si l'ajout s'est effectué sans réallocation de mémoire, alors
//      la méthode retourne 1, sinon elle renvoie -1.
{
    bool realloc = false;

    if (nbTrajets >= taille) {
        realloc = reallocation();
    }
    trajets[nbTrajets++] = trajet;
    return realloc ? -1 : 1;
} //----- Fin de AjouterTrajet

int Collection::Fusion(Collection *collection, unsigned int first, unsigned int last)
// Algorithme :
//      Ajoute les trajets clonés de la collection passée en paramètre en vérifiant avant s'il
//      est nécessaire de réallouer la collection courante ou non.
//      Si l'ajout s'est effectué sans réallocation de mémoire, alors
//      la méthode retourne 1, sinon elle renvoie -1.
{
    bool realloc = false;

    for (unsigned int i = 0; i < collection->GetNbTrajets(); i++) {
        if (i >= first && i <= last) {
            Trajet *trajet = collection->GetTrajets()[i]->Clone();
            realloc = AjouterTrajet(trajet) || realloc;
        }
    }
    return realloc;
} //----- Fin de FusionCollection

Collection *Collection::Filtrage(unsigned int first, unsigned int last)
// Algorithme :
//      Vérifie la validité des indexes spécifiés (interval et nombre d'éléments).
//      Si les arguments sont valides, alors on fusionne la nouvelle collection vide avec la collection courante.
//      Sinon on retourne nullptr.
{
    int nbElements = last - first + 1;
    Collection *collection = nullptr;
    bool isFirstValid = first >= 0 && first < GetNbTrajets();
    bool isLastValid = last >= 0 && last < GetNbTrajets();
    bool isNbElementsValid = nbElements >= 1;
    bool isValid = isFirstValid && isLastValid && isNbElementsValid;

    if (isValid) {
        collection = new Collection();
        collection->Fusion(this, first, last);
    }
    return collection;
} //----- Fin de Filtrage(int, int)

Collection *Collection::Filtrage(const char *depart, const char *arrivee)
// Algorithme :
//      On vérifie la validité d'au moins un des noms de ville passés en arguments.
//      Si la validité est vérifiée, alors on créer une nouvelle collection avec les trajets clonés ayant comme
//      ville de départ et/ou ville d'arrivée celle(s) spécifiée(s) en arguments de la méthode.
{
    Collection *collection = nullptr;

    //QUESTION : Si il ne selectionne ni une ville de depart, ni une ville d'arrivée => on retourne tous les trajets du fichier ??? ou rien ?

    //REMARQUE : j'ai modifié cette methode et j'aurais peut etre pas du => si l'export l'utilise alors elle risque de ne plus fonctionner correctement. comportement a verifier
    //              => la methode utilisais avant le taille des chaines depart et arrivee. si les parametres etaient vident alors le filtre n'était pas appliqué. Mais je ne sais pas comment l'utilisateur peut saisir une chaine vide avec cin >> villedepart

    if (strcmp(depart, "") != 0) {
        collection = filtrageDepart(depart);
    }

    if (strcmp(arrivee, "") != 0) {
        if (collection == nullptr) {
            collection = filtrageArrivee(arrivee);
        } else {
            Collection *collectionArrivee = collection->filtrageArrivee(arrivee);
            delete collection;
            collection = collectionArrivee;
        }
    }
    return collection;
} //----- Fin de Filtrage(char *, char *)

Collection *Collection::Filtrage(TypeTrajet typeTrajet)
// Algorithme :
//      On parcours l'ensemble des trajets de la collection courante en clonant dans la nouvelle collection ensuite
//      retournée les trajets du même type que celui spécifié en argument de la méthode.
{
    Collection *collection = new Collection();

    for (unsigned int i = 0; i < GetNbTrajets(); i++) {
        const Trajet *trajet = GetTrajets()[i];
        TypeTrajet type = (dynamic_cast<TrajetCompose *>(trajet->Clone()) == nullptr) ? SIMPLE : COMPOSE;

        if (type == typeTrajet) {
            collection->AjouterTrajet(trajet->Clone());
        }
    }
    return collection;
} //----- Fin de Filtrage(TypeTrajet)

const Trajet *Collection::GetPremierTrajet() const
// Algorithme :
//      Retourne le premier trajet si le nombre de trajets est
//      supérieur à 0, nullptr sinon.
{
    if (nbTrajets > 0) {
        return trajets[0];
    } else {
        return nullptr;
    }
}

const Trajet *Collection::GetDernierTrajet() const
// Algorithme :
//      Retourne le dernier trajet si le nombre de trajets est
//      supérieur à 0, nullptr sinon.
{
    if (nbTrajets > 0) {
        return trajets[nbTrajets - 1];
    } else {
        return nullptr;
    }
}

unsigned int Collection::GetNbTrajets() const {
    return nbTrajets;
}

unsigned int Collection::GetTaille() const {
    return taille;
}

Trajet **Collection::GetTrajets() const {
    return trajets;
}

Collection *Collection::Clone() const {
    return new Collection(*this);
}

unsigned int Collection::getNbInstance() {
    return nbInstance;
}

//-------------------------------------------- Constructeurs - destructeur
Collection::Collection() : nbTrajets(0u),
                           taille(TAILLE_INIT),
                           trajets(new Trajet *[taille])
// Algorithme :
//      Initialise les attributs de la classe et vérifie que l'allocation
//      de l'espace mémoire pour la liste des trajets a été effectué avec
//      succès. Dans le cas contraire le constructeur stop le programme
//      en renvoyant un message d'erreur.
{
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de <Collection> (total : "
         << getNbInstance() << " instances)" << endl;
#endif
    if (trajets == nullptr) {
        cerr << "ERREUR FATALE : problème d'allocation de mémoire"
             << ", fin du programme." << endl;
        exit(EXIT_FAILURE);
    }
} //----- Fin de Collection

Collection::Collection(const Collection &collection)
        : nbTrajets(collection.GetNbTrajets()),
          taille(collection.GetTaille()),
          trajets(new Trajet *[taille]) {
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Collection> (total : "
         << getNbInstance() << " instances)" << endl;
#endif
    for (unsigned int i = 0; i < collection.GetNbTrajets(); i++) {
        trajets[i] = collection.GetTrajets()[i]->Clone();
    }
} //----- Fin de Collection

Collection::~Collection() {
    nbInstance--;
#ifdef MAP
    cout << "Appel au destructeur de <Collection> (total : "
         << getNbInstance() << " instances restantes)" << endl;
#endif

    for (unsigned int i = 0; i < nbTrajets; i++) {
        delete trajets[i];
    }
    delete[] trajets;
} //----- Fin de ~Collection

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Attributs protégés
unsigned int Collection::nbInstance = 0;

//----------------------------------------------------- Méthodes protégées
bool Collection::reallocation()
// Mode d'emploi :
//      Tente de réalloue la collection afin d'aggrandir sa taille.
//      La méthode renvoie "vrai" si la réallocation a été effectuée avec
//      succès, "faux" sinon.
// Algorithme :
//      La méthode vérifie si le nombre de trajets est suffisament élevé
//      pour nécessité une réallocation. Si la vérification passe
//      avec succès, alors une demande est faite au système pour obtenir
//      une nouvelle zone mémoire. Si cela réussi, l'ensemble des trajets
//      présents dans l'ancien espace mémoire sont transférés vers la
//      nouvelle zone, la première étant libérée ensuite et la méthode
//      retourne "vrai".
//      Dans les autres cas la méthode renvoie "faux" pour signifier
//      qu'aucune réallocation n'a été effectuée.
{
    bool estRealloue = false;
    Trajet **newTrajets;
    unsigned int incrementation = TAILLE_INIT / 2;

    if (nbTrajets > taille - incrementation) {
        taille += incrementation;
        newTrajets = new Trajet *[taille];

        if (newTrajets != nullptr) {
            for (unsigned int i = 0; i < nbTrajets; i++) {
                newTrajets[i] = trajets[i];
            }
            delete[] trajets;
            trajets = newTrajets;
            estRealloue = true;
#ifdef MAP
            cout << "Réallocation de la mémoire" << endl;
#endif
        }
    }
    return estRealloue;
} //----- Fin de reallocation

Collection *Collection::filtrageDepart(const char *depart)
// Mode d'emploi :
//      Filtre les trajets par rapport à la ville de départ spécifiée.
// Contrat :
//      depart doit être différent de nullptr et son nombre d'élément supérieur à 0
// Algorithme :
//      Parcours l'ensemble des trajets de la collection courante en clonant dans la nouvelle collection créée
//      uniquement les trajets ayant comme ville de départ celle spécifiée en argument de la méthode.
{
    Collection *collection = new Collection();

    for (unsigned int i = 0; i < GetNbTrajets(); i++) {
        const Trajet *trajet = GetTrajets()[i];

        if (strcmp(trajet->GetVilleDepart(), depart) == 0) {
            collection->AjouterTrajet(trajet->Clone());
        }
    }
    return collection;
} //----- Fin de filtrageDepart

Collection *Collection::filtrageArrivee(const char *arrivee)
// Mode d'emploi :
//      Filtre les trajets par rapport à la ville d'arrivée spécifiée.
// Contrat :
//      arrivee doit être différent de nullptr et son nombre d'élément supérieur à 0
// Algorithme :
//      Parcours l'ensemble des trajets de la collection courante en clonant dans la nouvelle collection créée
//      uniquement les trajets ayant comme ville d'arrivée celle spécifiée en argument de la méthode.
{
    Collection *collection = new Collection();

    for (unsigned int i = 0; i < GetNbTrajets(); i++) {
        const Trajet *trajet = GetTrajets()[i];

        if (strcmp(trajet->GetVilleArrivee(), arrivee) == 0) {
            collection->AjouterTrajet(trajet->Clone());
        }
    }
    return collection;
} //----- Fin de filtrageArrivee