/*************************************************************************
                            Persistance  -  description
                              --------------------
   début                : 28/11/2019
   copyright            : (C) 2019 par name
*************************************************************************/

//---------- Réalisation de la classe <Persistance> (fichier Persistance.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Persistance.h"
#include "Catalogue.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables statiques

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Persistance::Methode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Methode

//------------------------------------------------- Surcharge d'opérateurs
Persistance & Persistance::operator = ( const Persistance & unPersistance )
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Persistance::Persistance ( const Persistance & unPersistance )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Persistance>" << endl;
#endif
} //----- Fin de Persistance (constructeur de copie)

Persistance::Persistance ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Persistance>" << endl;
#endif
} //----- Fin de Persistance

bool Persistance::Import()
{

}

bool Persistance::Export(Catalogue & _catalogue)
{

}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
