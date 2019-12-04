/*************************************************************************
                    Main  -  Point d'entrée du programme
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
#include <climits>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Persistance.h"
#include "ChatColor.h"

#define TAILLE_CHAINE 100

enum TypeAction {
    IMPORT,
    EXPORT
};

//------------------------------------------------ Signatures de fonctions
static bool verifSaisieAtomique(istream &in);
// Mode d'emploi :
//      Vérification de la validité d'une saisie atomique (sans espace).
//      Envoie un message d'erreur si la saisie est invalide.
//      La fonction nettoie le fichier d'entrée dans tous les cas.
//      (à utiliser pour la vérification de la saisie d'entier, de caractère,
//      d'un mot (string sans espace), etc)

static bool verifSaisieString(istream &in);
// Mode d'emploi :
//      Vérification de la validité de la saisie.
//      Envoie un message d'erreur si la saisie est invalide.
//      La fonction nettoie le fichier uniquement en cas d'erreur.

Trajet *saisirTrajet();
// Mode d'emploi :
//      Demande à l'utilisateur de saisir un trajet et le retourne.

TrajetSimple *saisirTrajetSimple();
// Mode d'emploi :
//      Demande à l'utilisateur de saisir un trajet simple caractérisé par
//      un nom de ville de départ, d'arrivée et un mode de transport.

TrajetCompose *saisirTrajetCompose();
// Mode d'emploi :
//      Demande à l'utilisateur de saisir un trajet composé caractérisé par
//      un ensemble de trajets simples (minimum 2) dont la ville de départ correspond
//      obligatoirement à la ville d'arrivée du trajet précédent s'il existe.

static string *saisirNomFichier(Persistance &persistance, TypeAction typeAction);
// Mode d'emploi :
//      Demande à l'utilisateur la saisie d'un nom de fichier.

static int afficherMenu();
// Mode d'emploi :
//      Affiche le menu de sélection de l'action à entreprendre sur
//      l'application et retourne la réponse de l'utilisateur.

static void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours);
// Mode d'emploi :
//      Affiche la liste de parcours spécifiés en paramètre.

static void afficherMenuExport(Catalogue &catalogue, Persistance &persistance);
// Mode d'emploi :
//      Afficher le menu de sélection pour l'export.

static int afficherMenuExportType();
// Mode d'emploi :
//      Afficher le menu de sélection du type d'exportation.

static void afficherMenuImport(Catalogue &collection, Persistance &persistance);
// Mode d'emploi :
//      Affiche le menu de sélection pour l'import.

static int afficherMenuImportType();
// Mode d'emploi :
//      Affiche le menu de sélection du type d'importation.

//-------------------------------------------------------------- Fonctions
int main() {
    cout << "========== Application - Voyage ==========" << endl
         << endl;

    Catalogue catalogue;
    char *villeDepart;
    char *villeArrivee;
    Collection *parcours;
    Persistance persistance;

    while (1) {
        int reponse = afficherMenu();

        switch (reponse) {
            case 0: {
                return EXIT_SUCCESS;
            }
            case 1: {
                Trajet *trajet = saisirTrajet();

                if (trajet != nullptr) {
                    catalogue.AjouterTrajet(trajet);
                    cout << ChatColor(VERT) << "Le trajet saisi a été ajouté dans le catalogue."
                         << ChatColor(RESET) << endl;
                }
                break;
            }
            case 2: {
                cout << ChatColor(VERT);
                catalogue.Afficher();
                cout << ChatColor(RESET);
                break;
            }
            case 3: {
                villeDepart = new char[TAILLE_CHAINE];
                villeArrivee = new char[TAILLE_CHAINE];
                cout << ChatColor(ROUGE) << "/!\\ Aucune vérification de saisie effectuée ici ! /!\\"
                     << ChatColor(RESET) << endl;
                cout << "Saisie de la ville de départ : ";
                cin >> villeDepart;
                cout << "Saisie de la ville d'arrivée : ";
                cin >> villeArrivee;
                parcours = catalogue.RechercherParcoursSimple(villeDepart, villeArrivee);
                afficherParcours(catalogue, villeDepart, villeArrivee, *parcours);
                delete[] villeDepart;
                delete[] villeArrivee;
                delete parcours;
                break;
            }
            case 4: {
                villeDepart = new char[TAILLE_CHAINE];
                villeArrivee = new char[TAILLE_CHAINE];
                cout << ChatColor(ROUGE) << "/!\\ Aucune vérification de saisie effectuée ici ! /!\\"
                     << ChatColor(RESET) << endl;
                cout << "Saisie de la ville de départ : ";
                cin >> villeDepart;
                cout << "Saisie de la ville d'arrivée : ";
                cin >> villeArrivee;
                parcours = catalogue.RechercherParcoursAvancee(villeDepart, villeArrivee);
                afficherParcours(catalogue, villeDepart, villeArrivee, *parcours);
                delete[] villeDepart;
                delete[] villeArrivee;
                delete parcours;
                break;
            }
            case 5: {
                afficherMenuExport(catalogue, persistance);
                break;
            }
            case 6: {
                afficherMenuImport(catalogue, persistance);
                break;
            }
        }
    }
} //----- fin de main

static bool verifSaisieAtomique(istream &in) {
    bool valid = true;
    if (!in) {
        valid = false;
        cout << ChatColor(ROUGE) << "ERREUR : La saisie est incorrecte." << ChatColor(RESET)
             << endl;
    }
    in.clear();
    in.ignore(INT_MAX, '\n');
    return valid;
} //----- fin de verifSaisieAtomique

static bool verifSaisieString(istream &in) {
    bool valid = true;
    if (!in) {
        valid = false;
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << ChatColor(ROUGE) << "ERREUR : La saisie est incorrecte." << ChatColor(RESET)
             << endl;
    }
    return valid;
} //----- fin de verifSaisieString

Trajet *saisirTrajet()
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
{
    Trajet *trajet = nullptr;
    bool valid;
    int typeTrajet;

    do {
        cout << "Type de trajet (simple = 1, composé = 2, 0 pour annuler) : ";
        cin >> typeTrajet;
        valid = verifSaisieAtomique(cin);

        if (valid && (typeTrajet < 0 || typeTrajet > 2)) {
            valid = false;
            cout << ChatColor(ROUGE) << "Le numéro saisi est incorrect." << ChatColor(RESET) << endl;
        }
    } while (!valid);

    if (typeTrajet == 1) {
        trajet = saisirTrajetSimple();
    } else if (typeTrajet == 2) {
        trajet = saisirTrajetCompose();
    } else {
        cout << ChatColor(VERT) << "Annulation de la saisie d'un trajet." << ChatColor(RESET) << endl;
    }
    return trajet;
} //----- Fin de saisirTrajet

TrajetSimple *saisirTrajetSimple()
// Algorithme :
//      La méthode récupère sur l'entrée standard le nom de la ville de départ
//      et d'arrivée ainsi que l'ID du mode de transport pour construire
//      le trajet simple en conséquent si aucune erreur n'est détectée.
//      Si l'ID du mode de transport ou le type de trajet spécifié est
//      incorrect, la saisie est annulée et le message d'erreur
//      correspondant est affiché.
{
    TrajetSimple *trajetSimple = nullptr;
    bool valid;
    char *villeDepart = new char[TAILLE_CHAINE];
    char *villeArrive = new char[TAILLE_CHAINE];
    int typeTransportId;
    TypeTransport typeTransport;
    cout << "----- Saisie d'un trajet simple -----" << endl;
    do {
        cout << "Ville de départ : ";
        cin.getline(villeDepart, TAILLE_CHAINE);
        valid = verifSaisieString(cin);
    } while (!valid);

    do {
        cout << "Ville d'arrivée : ";
        cin.getline(villeArrive, TAILLE_CHAINE);
        valid = verifSaisieString(cin);
    } while (!valid);

    do {
        cout << "ID du mode de transport (0 : Auto, 1 : Avion, 2 : Bateau, 3 : Train) : ";
        cin >> typeTransportId;
        valid = verifSaisieAtomique(cin);

        if (valid && (typeTransportId < 0 || typeTransportId > 3)) {
            valid = false;
            cout << ChatColor(ROUGE) << "Le numéro saisi est incorrect." << ChatColor(RESET) << endl;
        }
    } while (!valid);

    switch (typeTransportId) {
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
    }
    trajetSimple = new TrajetSimple(villeDepart, villeArrive, typeTransport);
    return trajetSimple;
} //----- Fin de saisirTrajetSimple


TrajetCompose *saisirTrajetCompose()
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
    bool continueSaisie = true;
    cout << "===== Saisie d'un trajet composé =====" << endl;

    do {
        Trajet *trajet = saisirTrajetSimple();

        const Trajet *dernierTrajet = collection->GetDernierTrajet();
        const char *villeDepart = trajet->GetVilleDepart();

        if (dernierTrajet == nullptr || strcmp(dernierTrajet->GetVilleArrivee(), villeDepart) == 0) {
            collection->AjouterTrajet(trajet);

            if (collection->GetNbTrajets() >= 2) {
                bool valid;
                char reponse;

                do {
                    cout << "Continuer la saisie de trajets ? (O/N) : ";
                    cin >> reponse;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponse != 'O' && reponse != 'N') {
                        valid = false;
                        cout << ChatColor(ROUGE) << "ERREUR : La réponse saisie est incorrecte."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponse == 'N') {
                    continueSaisie = false;
                }
            }
        } else {
            cout << ChatColor(ROUGE) << "ERREUR : La ville de départ d'un trajet doit correspondre à la ville "
                 << "d'arrivée du trajet précédent dans un trajet composé." << ChatColor(RESET) << endl;
            cout << ChatColor(ROUGE) << "Le trajet n'est pas pris en compte. Veuillez en saisir un nouveau."
                 << ChatColor(RESET) << endl;
        }
    } while (continueSaisie);

    trajetCompose = new TrajetCompose(collection);
    return trajetCompose;
} //----- Fin de saisirTrajetCompose

static string *saisirNomFichier(Persistance &persistance, TypeAction typeAction) {
    string *nomFichier = new string();
    cout << "Veuillez saisir un nom de fichier : ";
    cin >> *nomFichier;
    bool valid = verifSaisieAtomique(cin);

    if (valid) {
        bool erase = true;

        if (typeAction == EXPORT && persistance.FileExist(*nomFichier)) {
            erase = false;
            char confirmation;

            do {
                cout << "Le fichier \"" << *nomFichier << "\" existe déjà. Souhaitez vous l'écraser ? (O/N) : ";
                cin >> confirmation;
                valid = verifSaisieAtomique(cin);

                if (valid) {
                    if (confirmation != 'O' && confirmation != 'N') {
                        valid = false;
                        cerr << ChatColor(ROUGE) << "ERREUR : Saisie incorrecte. Veuillez réessayer."
                             << ChatColor(RESET) << endl;
                    } else {
                        erase = confirmation == 'O';
                    }
                }
            } while (!valid);
        }

        if (!erase) {
            valid = false;
        }
    }

    if (!valid) {
        cerr << ChatColor(ROUGE) << "ERREUR : Échec de la saisie du nom de fichier." << ChatColor(RESET) << endl;
        nomFichier = nullptr;
    }
    return nomFichier;
} //-----fin de saisirNomFichier

static int afficherMenu() {
    bool valid;
    int reponse;
    do {
        cout << "Choisissez une action à réaliser :" << endl;
        cout << "\t1 - Saisir un trajet dans le catalogue" << endl;
        cout << "\t2 - Afficher les trajets du catalogue" << endl;
        cout << "\t3 - Rechercher un parcours (mode simple)" << endl;
        cout << "\t4 - Rechercher un parcours (mode avancé)" << endl;
        cout << "\t5 - Exporter le catalogue" << endl;
        cout << "\t6 - Importer un catalogue" << endl;
        cout << "\t0 - Quitter le programme" << endl;
        cout << "Votre réponse : ";
        cin >> reponse;
        valid = verifSaisieAtomique(cin);

        if (valid && (reponse < 0 || reponse > 6)) {
            valid = false;
            cerr << ChatColor(ROUGE)
                 << "ERREUR : Le numéro saisie ne correspond pas un numéro d'action valide. Veuillez réessayer."
                 << ChatColor(RESET) << endl;
        }
    } while (!valid);
    return reponse;
} //----- fin de afficherMenu

static void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours) {
    if (parcours.GetNbTrajets() > 0) {
        cout << "Liste des trajets possibles entre " << villeDepart << " et "
             << villeArrivee << " :" << endl;
        catalogue.Afficher(&parcours);
    } else {
        cout << ChatColor(ROUGE) << "Aucun parcours déterminé." << ChatColor(RESET) << endl;
    }
} //----- fin de afficherParcours

static void afficherMenuExport(Catalogue &catalogue, Persistance &persistance) {
    string *nomFichier;
    nomFichier = saisirNomFichier(persistance, EXPORT);

    if (nomFichier) {
        bool valid;
        int choix = afficherMenuExportType();

        switch (choix) {
            case 0: {
                cout << ChatColor(VERT) << "Annulation de l'action d'export de trajet." << ChatColor(RESET) << endl;
            }
            case 1: {
                persistance.Export(*catalogue.GetTrajet(), *nomFichier);
                break;
            }
            case 2: {
                int reponseType;
                TypeTrajet typeTrajet;

                do {
                    cout << "Sélectionnez le type de trajet à conserver (simple = 1, composé = 2) : ";
                    cin >> reponseType;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseType != 1 && reponseType != 2) {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : Le numéro saisie est incorrect. Veuillez réessayer."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseType == 1) {
                    typeTrajet = TypeTrajet::SIMPLE;
                } else {
                    typeTrajet = TypeTrajet::COMPOSE;
                }
                persistance.Export(*catalogue.GetTrajet()->Filtrage(typeTrajet), *nomFichier);
                break;
            }
            case 3: {
                char reponseVD;
                string villeDepart;
                string villeArrivee;

                do {
                    cout << "Souhaitez-vous saisir une ville de départ ? (O/N) : ";
                    cin >> reponseVD;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseVD != 'O' && reponseVD != 'N') {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : La réponse saisie est incorrecte."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseVD == 'O') {
                    do {
                        cout << "Saisie de la ville de départ : ";
                        getline(cin, villeDepart);
                        valid = verifSaisieString(cin);
                    } while (!valid);
                }

                char reponseVA;

                do {
                    cout << "Souhaitez-vous saisir une ville d'arrivée ? (O/N) : ";
                    cin >> reponseVA;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseVA != 'O' && reponseVA != 'N') {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : La réponse saisie est incorrecte."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseVA == 'O') {
                    do {
                        cout << "Saisie de la ville d'arrivée : ";
                        getline(cin, villeArrivee);
                        valid = verifSaisieString(cin);
                    } while (!valid);
                }
                persistance.Export(*catalogue.GetTrajet()->Filtrage(villeDepart.c_str(), villeArrivee.c_str()),
                                                                   *nomFichier);
                break;
            }
            case 4: {
                unsigned int n, m;
                Collection *exportCollection = catalogue.GetTrajet();
                unsigned int size = exportCollection->GetNbTrajets();

                do {
                    cout << "Indice n (indice du premier trajet) : ";
                    cin >> n;
                    valid = verifSaisieAtomique(cin);

                    if (valid && (n < 0 || n >= size)) {
                        valid = false;
                        cerr << ChatColor(ROUGE) << "ERREUR : L'index saisi ne correspond à aucun trajet "
                             << "(index max : " << size - 1 << ")."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                do {
                    cout << "Indice m (indice du dernier trajet) : ";
                    cin >> m;
                    valid = verifSaisieAtomique(cin);

                    if (valid && (m < 0 || m >= size || m < n)) {
                        valid = false;

                        if (m < n) {
                            cerr << ChatColor(ROUGE) << "ERREUR : L'index m du dernier trajet ne peut pas être "
                                 << "inférieur à l'index n du premier trajet." << ChatColor(RESET) << endl;
                        } else {
                            cerr << ChatColor(ROUGE) << "ERREUR : L'index saisi ne correspond à aucun trajet "
                                 << "(index max : " << size - 1 << ")."
                                 << ChatColor(RESET) << endl;
                        }
                    }
                } while (!valid);

                persistance.Export(*exportCollection->Filtrage(n, m), *nomFichier);
                break;
            }
        }
    }
} //----- fin de afficherMenuExport

static int afficherMenuExportType() {
    bool valid;
    int reponse;

    do {
        cout << "Choisissez un type d'exportation :" << endl;
        cout << "\t1 - Tous les trajets du catalogue" << endl;
        cout << "\t2 - Les trajets selon leurs type (Simple/Composé)" << endl;
        cout << "\t3 - Les trajets selon une ville de départ et/ou une ville d'arrivée" << endl;
        cout << "\t4 - Les trajets selon un intervalle" << endl;
        cout << "\t0 - Annuler l'action" << endl;
        cout << "Votre réponse : ";
        cin >> reponse;
        valid = verifSaisieAtomique(cin);

        if (valid && (reponse < 0 || reponse > 4)) {
            valid = false;
            cerr << ChatColor(ROUGE) << "ERREUR : Le numéro saisi est incorrect." << ChatColor(RESET) << endl;
        }
    } while (!valid);
    return reponse;
} //----- fin de afficherMenuExportType

static void afficherMenuImport(Catalogue &catalogue, Persistance &persistance) {
    string *nomFichier;
    nomFichier = saisirNomFichier(persistance, IMPORT);

    if (nomFichier && persistance.FileExist(*nomFichier)) {
        bool valid;
        int reponse;
        Collection *collection = nullptr;

        reponse = afficherMenuImportType();

        switch (reponse) {
            case 0: {
                cout << ChatColor(VERT) << "Annulation de l'action d'import de trajet." << ChatColor(RESET) << endl;
                return;
            }
            case 1: {
                collection = persistance.Import(*nomFichier);
                break;
            }
            case 2: {
                int reponseType;
                TypeTrajet typeTrajet;

                do {
                    cout << "Sélectionnez le type de trajet à conserver (simple = 1, composé = 2) : ";
                    cin >> reponseType;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseType != 1 && reponseType != 2) {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : Le numéro saisie est incorrect. Veuillez réessayer."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseType == 1) {
                    typeTrajet = TypeTrajet::SIMPLE;
                } else {
                    typeTrajet = TypeTrajet::COMPOSE;
                }
                collection = persistance.Import(*nomFichier)->Filtrage(typeTrajet);
                break;
            }
            case 3: {
                char reponseVD;
                string villeDepart;
                string villeArrivee;

                do {
                    cout << "Souhaitez-vous saisir une ville de départ ? (O/N) : ";
                    cin >> reponseVD;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseVD != 'O' && reponseVD != 'N') {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : La réponse saisie est incorrecte."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseVD == 'O') {
                    do {
                        cout << "Saisie de la ville de départ : ";
                        getline(cin, villeDepart);
                        valid = verifSaisieString(cin);
                    } while (!valid);
                }

                char reponseVA;

                do {
                    cout << "Souhaitez-vous saisir une ville d'arrivée ? (O/N) : ";
                    cin >> reponseVA;
                    valid = verifSaisieAtomique(cin);

                    if (valid && reponseVA != 'O' && reponseVA != 'N') {
                        valid = false;
                        cerr << ChatColor(ROUGE)
                             << "ERREUR : La réponse saisie est incorrecte."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                if (reponseVA == 'O') {
                    do {
                        cout << "Saisie de la ville d'arrivée : ";
                        getline(cin, villeArrivee);
                        valid = verifSaisieString(cin);
                    } while (!valid);
                }
                collection = persistance.Import(*nomFichier)->Filtrage(villeDepart.c_str(), villeArrivee.c_str());
                break;
            }
            case 4: {
                unsigned int n, m;
                Collection *importCollection = persistance.Import(*nomFichier);
                unsigned int size = importCollection->GetNbTrajets();

                do {
                    cout << "Indice n (indice du premier trajet) : ";
                    cin >> n;
                    valid = verifSaisieAtomique(cin);

                    if (valid && (n < 0 || n >= size)) {
                        valid = false;
                        cerr << ChatColor(ROUGE) << "ERREUR : L'index saisi ne correspond à aucun trajet "
                             << "(index max : " << size - 1 << ")."
                             << ChatColor(RESET) << endl;
                    }
                } while (!valid);

                do {
                    cout << "Indice m (indice du dernier trajet) : ";
                    cin >> m;
                    valid = verifSaisieAtomique(cin);

                    if (valid && (m < 0 || m >= size || m < n)) {
                        valid = false;

                        if (m < n) {
                            cerr << ChatColor(ROUGE) << "ERREUR : L'index m du dernier trajet ne peut pas être "
                                 << "inférieur à l'index n du premier trajet." << ChatColor(RESET) << endl;
                        } else {
                            cerr << ChatColor(ROUGE) << "ERREUR : L'index saisi ne correspond à aucun trajet "
                                 << "(index max : " << size - 1 << ")."
                                 << ChatColor(RESET) << endl;
                        }
                    }
                } while (!valid);

                collection = importCollection->Filtrage(n, m);
                break;
            }
        }
        catalogue.Fusion(collection);
        cout << ChatColor(VERT) << "Les trajets ont été importés avec succès !"
             << ChatColor(RESET) << endl;
        delete collection;
        delete nomFichier;
    } else {
        cerr << "Impossible d'ouvrir le fichier " << *nomFichier << endl;
    }
} //----- fin de afficherMenuImport

static int afficherMenuImportType() {
    int reponse;
    bool valid;

    do {
        cout << "Choisissez un type d'importation :" << endl;
        cout << "\t1 - Tous les trajets du fichier" << endl;
        cout << "\t2 - Les trajets selon leurs type (Simple/Composé)" << endl;
        cout << "\t3 - Les trajets selon une ville de départ et/ou une ville d'arrivée" << endl;
        cout << "\t4 - Les trajets selon un intervalle" << endl;
        cout << "\t0 - Annuler l'action" << endl;
        cout << "Votre réponse : ";
        cin >> reponse;
        valid = verifSaisieAtomique(cin);

        if (valid && (reponse < 0 || reponse > 4)) {
            valid = false;
            cerr << ChatColor(ROUGE)
                 << "ERREUR : Le numéro saisie ne correspond pas un numéro d'action valide. Veuillez réessayer."
                 << ChatColor(RESET) << endl;
        }
    } while (!valid);
    return reponse;
} // fin de afficherMenuImportType
