/*************************************************************************
    TrajetCompose  -  Classe représentant un trajet composé caractérisé
      par une collection ordonnée de trajets (simples et/ou composés)
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp)

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//----------------------------------------------------------------- PUBLIC

ostream & operator << (ostream & out, const TrajetCompose & t)
{
    
    out << t.GetVilleDepart() << "/"
    << t.GetVilleArrivee() << "/"
    << t.GetTrajets()->GetNbTrajets()
    << endl;

    return out;

}

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Afficher(const char *indents) const
// Algorithme :
//      Affiche la liste des trajets du trajet composé en ajoutant
//      une tabulation supplémentaire à l'indentation actuelle.
{
    cout << indents << "Trajet composé" << endl;
    unsigned int size = strlen(indents) + 2;
    char *incrIndent = new char[size];

    for (unsigned int i = 0; i < size - 1; i++)
    {
        incrIndent[i] = '\t';
    }
    incrIndent[size - 1] = 0;

    for (unsigned int i = 0; i < collection->GetNbTrajets(); i++)
    {
        collection->GetTrajets()[i]->Afficher(incrIndent);
    }
    delete[] incrIndent;
} //----- Fin de Afficher

char *TrajetCompose::GetVilleDepart() const
// Algorithme :
//      Si le nombre de trajets est supérieur à 0, alors la méthode
//      retourne la ville de départ du premier trajet de la collection.
//      Dans le cas contraire, la méthode renvoie nullptr.
{
    if (collection->GetNbTrajets() > 0)
    {   
        return collection->GetTrajets()[0]->GetVilleDepart();
    }
    else
    {
        return nullptr;
    }
} //----- Fin de GetVilleDepart

char *TrajetCompose::GetVilleArrivee() const
// Algorithme :
//      Si le nombre de trajets est supérieur à 0, alors la méthode
//      retourne la ville d'arrivée du dernier trajet de la collection.
//      Dans le cas contraire, la méthode renvoie nullptr.
{
    if (collection->GetNbTrajets() > 0)
    {
        Trajet **trajets = collection->GetTrajets();
        Trajet *trajet = trajets[collection->GetNbTrajets() - 1];
        return trajet->GetVilleArrivee();
    }
    else
    {
        return nullptr;
    }
} //----- Fin de GetVilleArrivee

Collection *TrajetCompose::GetTrajets() const
// Algorithme :
//      Retourne la collection de trajets du trajet composé.
{
    return collection;
} //----- Fin de GetTrajets

Trajet *TrajetCompose::Clone() const
{
    return new TrajetCompose(*this);
}

unsigned int TrajetCompose::GetNbInstance()
{
    return nbInstance;
}

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose() : collection(new Collection())
{
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
} //----- Fin de TrajetCompose

TrajetCompose::TrajetCompose(Collection *laCollection)
    : collection(laCollection)
{
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
} //----- Fin de TrajetCompose

TrajetCompose::TrajetCompose(const TrajetCompose &trajetCompose)
    : collection(trajetCompose.GetTrajets()->Clone())
{
    nbInstance++;
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetCompose> (total : "
         << GetNbInstance() << " instances)" << endl;
#endif
} //----- Fin de TrajetCompose

TrajetCompose::~TrajetCompose()
{
    nbInstance--;
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose> (total : "
         << GetNbInstance() << " instances restantes)" << endl;
#endif
    delete collection;
} //----- Fin de ~TrajetCompose

//-------------------------------------------------------------- PROTECTED

//----------------------------------------------------- Attributs protégés
unsigned int TrajetCompose::nbInstance = 0;
