/*************************************************************************
            Trajet  -  Classe abstraite représentant un trajet
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//----------------- Réalisation de la classe <Trajet> (fichier Trajet.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
unsigned int Trajet::GetNbInstance()
{
    return nbInstance;
}

//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet()
{
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de <Trajet> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
} //----- Fin de Trajet

Trajet::~Trajet()
{
    nbInstance--;
#ifdef MAP
    cout << "Appel au destructeur de <Trajet> (total : "
         << GetNbInstance() << " instances restantes)" << endl;
#endif
} //----- Fin de ~Trajet

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Attributs protégés
unsigned int Trajet::nbInstance = 0;