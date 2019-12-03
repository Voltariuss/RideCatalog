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
#include "Persistance.h"
#include "ChatColor.h"

#define TAILLE_CHAINE 100

//------------------------------------------------ Signatures de fonctions
int afficherMenu();
// Mode d'emploi :
//      Affiche le menu de sélection de l'action à entreprendre sur
//      l'application et retourne la réponse de l'utilisateur.

void afficherMenuImport(Catalogue &c, Persistance &p);
// Mode d'emploi :
//      Affiche le menu de sélection pour l'import

int afficherMenuExport();
// Mode d'emploi :
//      Afficher le menu de sélection pour l'export

string saisirNomFichier();
// Mode d'emploi :
//      Demande à l'utilisateur la saisie d'un nom de fichier

void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours);
// Mode d'emploi :
//      Affiche la liste de parcours spécifiés en paramètre.

//-------------------------------------------------------------- Fonctions
int main() {
    cout << "========== Application - Voyage ==========" << endl
         << endl;

    Catalogue catalogue;
    char *villeDepart;
    char *villeArrivee;
    Collection *parcours;
    Persistance persistance;
    string nomExport;
    int choix;
    int typeTrajet;
    unsigned int n;
    unsigned int m;
    char answer;

    while (1) {
        int reponse = afficherMenu();

        switch (reponse) {
            case 0:
                return EXIT_SUCCESS;
            case 1:
                catalogue.SaisirTrajet();
                break;
            case 2:
                cout << ChatColor(VERT) << endl;
                catalogue.Afficher();
                cout << ChatColor(RESET);
                break;
            case 3:
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
            case 4:
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
            case 5:
                choix = afficherMenuExport();
                cout << "Veuillez donner un nom au fichier d'export:" << endl;
                cin >> nomExport;

                switch (choix) {
                    case 0:
                        break;
                    case 1:
                        persistance.Export(*catalogue.GetTrajet(), nomExport);
                        break;
                    case 2:

                        do {
                            cout << "Veuillez sélectionner les trajets que vous souhaitez exporter:" << endl;
                            cout << "\t1 - Les trajets simples" << endl;
                            cout << "\t2 - Les trajets composés" << endl;
                            cin >> typeTrajet;

                            if (typeTrajet != 1 && typeTrajet != 2) {
                                cout << "saisie incorrecte. Veuillez recommencer." << endl
                                     << endl;
                            }
                        } while (typeTrajet != 1 && typeTrajet != 2);

                        if (typeTrajet == 1) {
                            persistance.Export(*catalogue.GetTrajet()->Filtrage(SIMPLE), nomExport);
                        } else if (typeTrajet == 2) {
                            persistance.Export(*catalogue.GetTrajet()->Filtrage(COMPOSE), nomExport);
                        }
                        break;

                    case 3:
                        villeDepart = new char[TAILLE_CHAINE];
                        villeArrivee = new char[TAILLE_CHAINE];

                        do {
                            cout << "Souhaitez vous saisir une ville de départ? (O/N) : ";
                            cin >> answer;

                            if (answer == 'O') {
                                cout << "Saisie de la ville de départ : ";
                                cin >> villeDepart;
                            } else if (answer != 'N') {
                                cout << "Saisie incorrect." << endl;
                            }
                        } while (answer != 'N' && answer != 'O');

                        do {
                            cout << "Souhaitez vous saisir une ville d'arrivée'? (O/N) : ";
                            cin >> answer;

                            if (answer == 'O') {
                                cout << "Saisie de la ville d'arrivée : ";
                                cin >> villeArrivee;
                            } else if (answer != 'N') {
                                cout << "Saisie incorrect." << endl;
                            }
                        } while (answer != 'N' && answer != 'O');

                        persistance.Export(*catalogue.GetTrajet()->Filtrage(villeDepart, villeArrivee), nomExport);
                        delete[] villeDepart;
                        delete[] villeArrivee;
                        break;

                    case 4:
                        cout << "Veuillez entrer la valeure inférieure de l'intervalle [n,m] :" << endl;
                        cin >> n;
                        cout << "Veuillez entrer la valeure supérieure de l'intervalle [n,m] : " << endl;
                        cin >> m;
                        persistance.Export(*catalogue.GetTrajet()->Filtrage(n, m), nomExport);
                        break;

                    default:
                        break;
                }
                break;
            case 6:
                afficherMenuImport(catalogue, persistance);
                break;
            default:
                break;
        }
    }
} //----- fin de main

bool verificationSaisie(istream &in) {
    bool valid = true;
    if (!in) {
        valid = false;
        in.clear();
        in.ignore(INT_MAX, '\n');
        cout << ChatColor(ROUGE) << "ERREUR : La saisie est incorrecte." << ChatColor(RESET)
             << endl;
    }
    return valid;
} //----- fin de verificationSaisie

int afficherMenu() {
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
        valid = verificationSaisie(cin);

        if (valid && (reponse < 0 || reponse > 6)) {
            valid = false;
            cout << ChatColor(ROUGE)
                 << "ERREUR : Le numéro saisie ne correspond pas un numéro d'action valide. Veuillez réessayer."
                 << ChatColor(RESET) << endl;
        }
    } while (!valid);
    return reponse;
} //----- fin de afficherMenu

void afficherMenuImport(Catalogue &c, Persistance &persistance) {
    string nomFichier;
    int reponse;
    char answer;
    unsigned int n, m;
    TypeTrajet typeTrajet;
    char *villeDepart = new char[TAILLE_CHAINE];
    char *villeArrivee = new char[TAILLE_CHAINE];

    cout << "Veuillez saisir le chemin du fichier d'import :" << endl;
    cin >> nomFichier;

    if (persistance.FileExist(nomFichier)) {

        cout << "Choisissez un type d'importation :" << endl;
        cout << "\t1 - Importer tous les trajets du fichier" << endl;
        cout << "\t2 - Importer les trajets selon leurs type (Simple/Composé)" << endl;
        cout << "\t3 - Importer les trajets selon la ville de départ et/ou la ville d'arrivée" << endl;
        cout << "\t4 - Importer les trajets selon un intervalle" << endl;
        cin >> reponse;

        switch (reponse) {
            case 1:
                c.Fusion(persistance.Import(nomFichier));
                break;

            case 2:
                cout << "Type de trajet (simple = 1, composé = 2) : ";
                cin >> reponse;

                if (reponse == 1)
                    typeTrajet = TypeTrajet::SIMPLE;
                else if (reponse == 2)
                    typeTrajet = TypeTrajet::COMPOSE;

            c.Fusion(p.Import(nomFichier)->Filtrage(typeTrajet));
            break;
        case 3:
            do
            {
                cout << "Souhaitez vous saisir une ville de départ? (O/N) : ";
                cin >> answer;

                if (answer == 'O')
                {
                    cout << "Saisie de la ville de départ : ";
                    cin >> villeDepart;
                }
                else if (answer != 'N')
                {
                    cout << "Saisie incorrect." << endl;
                }
            } while (answer != 'N' && answer != 'O');

            do
            {
                cout << "Souhaitez vous saisir une ville d'arrivée'? (O/N) : ";
                cin >> answer;

                if (answer == 'O')
                {
                    cout << "Saisie de la ville d'arrivée : ";
                    cin >> villeArrivee;
                }
                else if (answer != 'N')
                {
                    cout << "Saisie incorrect." << endl;
                }
            } while (answer != 'N' && answer != 'O');
           
            c.Fusion(p.Import(nomFichier)->Filtrage(villeDepart, villeArrivee));
            break;
        case 4:
            cout << "Indice n (indice du premier trajet) : ";
            cin >> n;
            cout << "Indice m (indice du dernier trajet) : ";
            cin >> m;

                if (n >= 0 && m >= 0 && m > n)
                    c.Fusion(persistance.Import(nomFichier)->Filtrage(n, m));
                else
                    cout << "Les bornes n et m sont incorrectes. Veuillez recommencer" << endl;
                break;
            default:
                break;
        }

        delete col;
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier " << nomFichier <<endl;
    }

    delete[] villeDepart;
    delete[] villeArrive;
} //----- fin de afficherMenuImport

int afficherMenuExport() {
    cout << "Quel type d'export voulez vous faire?" << endl;
    cout << "\t1 - complet" << endl;
    cout << "\t2 - selon le type des trajets" << endl;
    cout << "\t3 - selon la ville de départ et/ou la ville d'arrivée" << endl;
    cout << "\t4 - selon une sélection de trajet (de n à m)" << endl;
    cout << "\t0 - Revenir au menu précédent" << endl;
    int reponse;
    cin >> reponse;
    return reponse;
} //----- fin de afficherMenu

string *saisirNomFichier(Persistance &persistance) {
    string *nomFichier = new string();
    cout << "Veuillez saisir un nom de fichier : ";
    cin >> *nomFichier;
    cout << endl;
    bool valid = verificationSaisie(cin);

    if (valid && persistance.FileExist(*nomFichier)) {
        char confirmation;
        cout << "Le fichier \"" << *nomFichier << "\" existe déjà. Souhaitez vous l'écraser ? (O/N) : ";
        cin >> confirmation;
        cout << endl;
        valid = verificationSaisie(cin);
    }

    if (!valid) {
        cout << ChatColor(ROUGE) << "ERREUR : Échec de la saisie du nom de fichier." << ChatColor(RESET) << endl;
        nomFichier = nullptr;
    }
    return nomFichier;
} //-----fin de saisirNomFichier

void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours) {
    if (parcours.GetNbTrajets() > 0) {
        cout << "Liste des trajets possibles entre " << villeDepart << " et "
             << villeArrivee << " :" << endl;
        catalogue.Afficher(&parcours);
    } else {
        cout << "Aucun parcours déterminé." << endl;
    }
} //----- fin de afficherParcours
