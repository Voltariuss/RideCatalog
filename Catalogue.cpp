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
#define TAILLE_CHAINE 100

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
//    Si la saisie est valide, alors le programme ajoute
//    le trajet ainsi créée dans le catalogue.
//
{
    bool erreur = false;
    int typeTrajet;
    Trajet *trajet;
    cout << "Type de trajet (simple = 1, composé = 2, 0 pour annuler) : ";
    cin >> typeTrajet;

    if (typeTrajet == 0)
    {
        cout << "Fin de la saisie de trajets." << endl;
        return;
    }
    else if (typeTrajet == 1)
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
        collectionTrajets->AjouterTrajet(trajet);
    }
    else
    {
        cout << "Échec de l'ajout du trajet dans le catalogue." << endl;
    }
} //----- Fin de SaisirTrajet

void Catalogue::Afficher(Collection *collection) const
// Algorithme :
//      Affiche individuellement chaque trajet de la collection spécifiée.
{
    if (collection == nullptr)
    {
        collection = collectionTrajets;
    }

    for (unsigned int i = 0; i < collection->GetNbTrajets(); i++)
    {
        char str[] = {0};
        collection->GetTrajets()[i]->Afficher(str);
    }
} //----- Fin de Afficher

Collection *Catalogue::RechercherParcoursSimple(char *depart, char *arrivee) const
// Algorithme :
//
{
    unsigned int nbTrajets = collectionTrajets->GetNbTrajets();
    Trajet **trajets = collectionTrajets->GetTrajets();
    Collection *trajetsFinaux = new Collection();

    for (unsigned int i = 0; i < nbTrajets; i++)
    {
        if (!strcmp(trajets[i]->GetVilleDepart(), depart) &&
            !strcmp(trajets[i]->GetVilleArrivee(), arrivee))
        {
            trajetsFinaux->AjouterTrajet(trajets[i]->Clone());
        }
    }
    return trajetsFinaux;
} //----- Fin de RechercherParcours

Collection *Catalogue::RechercherParcoursAvancee(char *depart, char *arrivee) const
// Algorithme :
//
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
Catalogue::Catalogue() : collectionTrajets(new Collection())
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
    if (collectionTrajets == nullptr)
    {
        cerr << "ERREUR FATALE : problème d'allocation de mémoire"
             << ", fin du programme." << endl;
        exit(EXIT_FAILURE);
    }
} //----- Fin de Catalogue

Catalogue::~Catalogue()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    delete collectionTrajets;
} //----- Fin de ~Catalogue

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Méthodes protégées
TrajetSimple *Catalogue::saisirTrajetSimple()
// Mode d'emploi :
//      Permet la saisie d'un trajet simple par l'utilisateur et le retourne.
//
// Algorithme :
//      La méthode récupère sur l'entrée standard le nom de la ville de départ
//      et d'arrivée ainsi que l'ID du mode de transport pour construire
//      le trajet simple en conséquent si aucune erreur n'est détectée.
//      Si l'ID du mode de transport ou le type de trajet spécifié est
//      incorrect, la saisie est annulée et le message d'erreur
//      correspondant est affiché.
{
    TrajetSimple *trajetSimple = nullptr;
    bool erreur = false;
    char *villeDepart = new char[TAILLE_CHAINE];
    char *villeArrive = new char[TAILLE_CHAINE];
    int typeTransportId;
    TypeTransport typeTransport;
    cout << "----- Saisie d'un trajet simple -----" << endl;
    cout << "Ville de départ : ";
    cin >> villeDepart;
    cout << "Ville d'arrivé : ";
    cin >> villeArrive;
    cout << "ID du mode de transport (0 : Auto, 1 : Avion, 2 : Bateau, 3 : Train) : ";
    cin >> typeTransportId;

    switch (typeTransportId)
    {
    case AUTO:
        typeTransport = AUTO;
        break;
    case AVION:
        typeTransport = AVION;
        break;
    case BATEAU:
        typeTransport = BATEAU;
        break;
    case TRAIN:
        typeTransport = TRAIN;
        break;
    default:
        erreur = true;
        cout << "ERREUR : Le numéro du type de trajet spécifié est incorrect." << endl;
        break;
    }

    if (!erreur)
    {
        trajetSimple = new TrajetSimple(villeDepart, villeArrive, typeTransport);
    }
    else
    {
        delete[] villeDepart;
        delete[] villeArrive;
    }
    return trajetSimple;
} //----- Fin de saisirTrajetSimple

TrajetCompose *Catalogue::saisirTrajetCompose()
// Mode d'emploi :
//      Permet la saisie d'un trajet composé par l'utilisateur et le retourne.
//
// Algorithme :
//      Pour chaque ajout de trajet dans le trajet composé en cours de saisie,
//      la méthode récupère en premier sur l'entrée standard le type de trajet
//      à saisir puis lance la demande saisie du trajet correspondant.
//      Si le type de trajet spécifié est incorrect, un message d'erreur
//      est affiché et la saisie est annulée.
//      Une fois un trajet saisie, le système vérifie le bon ordonnancement
//      des trajets dans la collection. Si la ville de départ d'un trajet ne
//      correspond pas à la ville d'arrivée du trajet précédent (si ce dernier
//      existe), alors la saisie est annulée et le message d'erreur associé
//      est affiché sur la sortie standard.
//      Les deux premières saisies de trajets d'un trajet composé sont
//      obligatoires. Au delà, l'utilisateur peut faire le choix de
//      poursuivre ou non la saisie de trajets supplémentaires.
{
    TrajetCompose *trajetCompose = nullptr;
    Collection *collection = new Collection();
    bool erreur = false;
    bool continueSaisie = true;
    cout << "===== Saisie d'un trajet composé =====" << endl;

    do
    {
        Trajet *trajet = saisirTrajetSimple();

        if (!erreur && trajet != nullptr)
        {
            Trajet *dernierTrajet = collection->GetDernierTrajet();
            char *villeDepart = trajet->GetVilleDepart();

            if (dernierTrajet == nullptr ||
                strcmp(dernierTrajet->GetVilleArrivee(), villeDepart) == 0)
            {
                collection->AjouterTrajet(trajet);

                if (collection->GetNbTrajets() >= 2)
                {
                    char reponse;

                    do
                    {
                        cout << "Continuer la saisie de trajets ? (O/N) : ";
                        cin >> reponse;

                        if (reponse == 'N')
                        {
                            continueSaisie = false;
                        }
                        else if (reponse != 'O')
                        {
                            cout << "Saisie incorrect." << endl;
                        }
                    } while (reponse != 'N' && reponse != 'O');
                }
            }
            else
            {
                erreur = true;
                cout << "ERREUR : La ville de départ d'un trajet doit";
                cout << " correspondre à la ville d'arrivé du trajet";
                cout << " précédent dans un trajet composé." << endl;
            }
        }
        else if (trajet == nullptr)
        {
            erreur = true;
            cout << "Échec de l'ajout du trajet dans le trajet composé." << endl;
        }
    } while (continueSaisie && !erreur);

    if (!erreur)
    {
        trajetCompose = new TrajetCompose(collection);
    }
    else
    {
        delete collection;
    }
    return trajetCompose;
} //----- Fin de saisirTrajetCompose

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

    for (unsigned int i = 0; i < nbTrajets; i++)
    {
        // Vérifier que le trajet n'a pas déjà été utilisé dans la constrution de ce parcours
        utilise = false;

        for (unsigned int j = 0; j < nbTrajetsUtilises; j++)
        {
            if (trajetsUtilises[j] == i)
            {
                utilise = true;
                break;
            }
        }

        // Départ == Arrivée précédente
        if (!utilise && !strcmp(trajets[i]->GetVilleDepart(), depart))
        {
            TrajetCompose *trajetComposeDuplique = (TrajetCompose *)trajetCompose.Clone();
            trajetComposeDuplique->GetTrajets()->AjouterTrajet(trajets[i]->Clone());
            // Si arrivée == arrivée finale alors ajouter aux trajets possibles
            // Sinon continuer la construction du trajet
            if (!strcmp(trajetComposeDuplique->GetVilleArrivee(), arrivee))
            {
                TrajetCompose * trajetCompose = new TrajetCompose(trajetComposeDuplique->GetTrajets()->Clone());
                trajetsFinaux.AjouterTrajet(trajetCompose);
            }
            else
            {
                // Si tous les trajets du catalogue n'ont pas déjà été utilisés
                if (nbTrajetsUtilises < nbTrajets)
                {
                    unsigned int *trajetsUtilisesDuplique = new unsigned int[sizeof(unsigned int) * (nbTrajetsUtilises + 1)];

                    for (unsigned int j = 0; j < nbTrajetsUtilises; j++)
                    {
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
