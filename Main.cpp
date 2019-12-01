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
int afficherSousMenuExport();
void afficherParcours(Catalogue &catalogue, char *villeDepart, char *villeArrivee, Collection &parcours);
// Mode d'emploi :
//      Affiche la liste de parcours spécifiés en paramètre.

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
    string nomExport;
    int choix;
    int typeTrajet;
    unsigned int n;
    unsigned int m;
    char answer;

    

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
            choix=afficherSousMenuExport();
            cout << "Veuillez donner un nom au fichier d'export:" << endl;
            cin >> nomExport;

            switch (choix)
            {
            case 0:
                break;
            case 1:
                P.Export(*catalogue.GetTrajet(),nomExport);
                break;
            case 2:
                
                do
                    {
                        cout << "Veuillez sélectionner les trajets que vous souhaitez exporter:" << endl;
                        cout << "\t1 - Les trajets simples" << endl;
                        cout << "\t2 - Les trajets composés" << endl;
                        cin >> typeTrajet;

                        if (typeTrajet!=1 && typeTrajet!=2)
                        {
                            cout << "saisie incorrecte. Veuillez recommencer." << endl << endl;
                        }
                    }while (typeTrajet!=1 && typeTrajet!=2);
                    
                if (typeTrajet==1)
                {
                    P.Export(*catalogue.GetTrajet()->Filtrage(SIMPLE),nomExport);
                }
                else if (typeTrajet==2)
                {
                    P.Export(*catalogue.GetTrajet()->Filtrage(COMPOSE),nomExport);
                }              
                break;
            
            case 3:
                villeDepart = new char[TAILLE_CHAINE];
                villeArrivee = new char[TAILLE_CHAINE];

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
                

                P.Export(*catalogue.GetTrajet()->Filtrage(villeDepart,villeArrivee),nomExport);
                delete[] villeDepart;
                delete[] villeArrivee;
                break;
            
            case 4:
                cout << "Veuillez entrer la valeure inférieure de l'intervalle [n,m] :"<<endl;
                cin >> n;
                cout << "Veuillez entrer la valeure supérieure de l'intervalle [n,m] : "<<endl;
                cin >> m;
                P.Export(*catalogue.GetTrajet()->Filtrage(n,m),nomExport);
                break;

            default:
                break;
            }
            break;
                
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
} //----- fin de main

int afficherMenu()
{
    cout << "Choisissez une action à réaliser :" << endl;
    cout << "\t1 - Saisir un trajet dans le catalogue" << endl;
    cout << "\t2 - Afficher les trajets du catalogue" << endl;
    cout << "\t3 - Rechercher un parcours (mode simple)" << endl;
    cout << "\t4 - Rechercher un parcours (mode avancé)" << endl;
    cout << "\t5 - Exporter le catalogue" << endl;
    cout << "\t0 - Quitter le programme" << endl;
    cout << "Votre réponse : ";
    int reponse;
    cin >> reponse;
    return reponse;
} //----- fin de afficherMenu


int afficherSousMenuExport()
{
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
