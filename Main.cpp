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

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Persistance.h"

#define TAILLE_CHAINE 100

//------------------------------------------------ Signatures de fonctions
int afficherMenu();
// Mode d'emploi :
//      Affiche le menu de sélection de l'action à entreprendre sur
//      l'application et retourne la réponse de l'utilisateur.
void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours);
// Mode d'emploi :
//      Affiche la liste de parcours spécifiés en paramètre.

void import(Catalogue & c, Persistance & p);
// Mode d'emploi :
//      Affiche le menu de sélection de l'import

//-------------------------------------------------------------- Fonctions
int main()
{
    cout << "========== Application - Voyage ==========" << endl
         << endl;

    Catalogue catalogue;
    char *villeDepart;
    char *villeArrivee;
    Collection *parcours;
    Persistance P;

    while (1)
    {
        int reponse = afficherMenu();

        switch (reponse)
        {
        case 0:
            return EXIT_SUCCESS;
        case 1:
            catalogue.SaisirTrajet();
            break;
        case 2:
            catalogue.Afficher();
            break;
        case 3:
            villeDepart = new char[TAILLE_CHAINE];
            villeArrivee = new char[TAILLE_CHAINE];
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
            P.Export(*catalogue.GetTrajet(),"exportCatalogue");
            break;
        case 6:
            import(catalogue, P);
            break;
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
} //----- fin de main

void import(Catalogue & c, Persistance & p)
{
    string nomFichier;
    int reponse;
    int n,m;


    cout << "Veuillez insérer le nom du fichier d'import :" << endl;
    cin >> nomFichier;
    cout << "Choisissez un type d'importation :" << endl;
    cout << "\t1 - Importer tous les trajets du fichier" << endl;
    cout << "\t2 - Importer les trajets selon leurs type (Simple/Composé)" << endl;
    cout << "\t3 - Importer les trajets selon la ville de départ et/ou la ville d'arrivée" << endl;
    cout << "\t4 - Importer les trajets selon un intervalle" << endl;
    cin >> reponse;

    switch (reponse)
    {
    case 1:
        c.Fusion(p.Import(nomFichier));
        break;

    case 2:
        cout << "Type de trajet (simple = 1, composé = 2) : "; 
        cin >> reponse;

        if(reponse==1)
            c.Fusion(p.Import(nomFichier));
        else if(reponse==2)
            c.Fusion(p.Import(nomFichier));

        break;
    case 3:
        c.Fusion(p.Import(nomFichier));
        break;
    case 4:
        cout << "Indice n (indice du premier trajet) : "; 
        cin >> n;
        cout << "Indice m (indice du dernier trajet) : "; 
        cin >> m;
        c.Fusion(p.Import(nomFichier));
        break;
    default:
        break;
    }
}

int afficherMenu()
{
    cout << "Choisissez une action à réaliser :" << endl;
    cout << "\t1 - Saisir un trajet dans le catalogue" << endl;
    cout << "\t2 - Afficher les trajets du catalogue" << endl;
    cout << "\t3 - Rechercher un parcours (mode simple)" << endl;
    cout << "\t4 - Rechercher un parcours (mode avancé)" << endl;
    cout << "\t5 - Exporter le catalogue" << endl;
    cout << "\t6 - Importer un catalogue" << endl;
    cout << "\t0 - Quitter le programme" << endl;
    cout << "Votre réponse : ";
    int reponse;
    cin >> reponse;
    return reponse;
} //----- fin de afficherMenu

void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours)
{
    if (parcours.GetNbTrajets() > 0)
    {
        cout << "Liste des trajets possibles entre " << villeDepart << " et "
             << villeArrivee << " :" << endl;
        catalogue.Afficher(&parcours);
    }
    else
    {
        cout << "Aucun parcours déterminé." << endl;
    }
}
