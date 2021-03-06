/*************************************************************************
  TrajetSimple  -  Classe représentant un trajet simple caractérisé par 
    une ville de départ, une ville d'arrivé et un mode de transport
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//----- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes
static const unsigned int TAILLE_CHAINE = 100;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
ostream &operator<<(ostream &out, const TrajetSimple &t) {
    out << t.GetVilleDepart() << "|"
        << t.GetVilleArrivee() << "|"
        << t.GetTypeTransport()
        << endl;
    return out;
}

void TrajetSimple::Afficher(const char *indents) const
// Algorithme :
//      Affiche le trajet simple en prenant en compte l'indentation
//      spécifiée et en convertissant le type de transport en
//      chaîne de caractères.
{
    cout << indents << "Trajet simple" << endl;
    cout << indents << "\tVille de départ : " << villeDepart << endl;
    cout << indents << "\tVille d'arrivée : " << villeArrivee << endl;
    cout << indents << "\tMoyen de transport : "
         << typeTransportStr[typeTransport] << endl;
    cout << endl;
} //----- Fin de Afficher

const char *TrajetSimple::GetVilleDepart() const
// Algorithme :
//      Retourne le nom de la ville de départ du trajet simple.
{
    return villeDepart;
} //----- Fin de GetVilleDepart

const char *TrajetSimple::GetVilleArrivee() const
// Algorithme :
//      Retourne le nom de la ville d'arrivée du trajet simple.
{
    return villeArrivee;
} //----- Fin de GetVilleArrivee

TypeTransport TrajetSimple::GetTypeTransport() const
// Algorithme :
//      Retourne le moyen de transport du trajet simple.
{
    return typeTransport;
} //----- Fin de GetMoyenTransport

Trajet *TrajetSimple::Clone() const {
    return new TrajetSimple(*this);
}

unsigned int TrajetSimple::GetNbInstance() {
    return nbInstance;
}

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple(char *depart, char *arrivee, TypeTransport transport) {
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
    villeDepart = depart;
    villeArrivee = arrivee;
    typeTransport = transport;
} //----- Fin de TrajetSimple

TrajetSimple::TrajetSimple(const TrajetSimple &trajetSimple) {
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetSimple> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
    int tailleVD = strlen(trajetSimple.GetVilleDepart());
    int tailleVA = strlen(trajetSimple.GetVilleArrivee());
    villeDepart = new char[tailleVD + 1];
    villeArrivee = new char[tailleVA + 1];
    const char *depart = trajetSimple.GetVilleDepart();
    strncpy(villeDepart, depart, tailleVD + 1);
    const char *arrivee = trajetSimple.GetVilleArrivee();
    strncpy(villeArrivee, arrivee, tailleVA + 1);
}

TrajetSimple::~TrajetSimple() {
    nbInstance--;
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple> (total : "
         << GetNbInstance() << " instances restantes)" << endl;
#endif
    delete[] villeDepart;
    delete[] villeArrivee;
} //----- Fin de ~TrajetSimple

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Attributs protégés
unsigned int TrajetSimple::nbInstance = 0;