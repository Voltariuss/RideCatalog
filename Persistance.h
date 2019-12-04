/*************************************************************************
                            Persistance  -  description
                              --------------------
   début                : 28/11/2019
   copyright            : (C) 2019 par name
*************************************************************************/

//---------- Interface de la classe <Persistance> (fichier <Persistance.h>) ------

#if !defined ( PERSISTANCE_H )
#define PERSISTANCE_H
//--------------------------------------------------- Interfaces utilisées
#include "Collection.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Persistance>
//
//------------------------------------------------------------------------
class Persistance {
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    bool FileExist(string nomFichier);
    // Mode d'emploi :
    // - nomFichier : nom du fichier txt sur lequel effectuer un test d'ouverture

    Collection *Import(string nomFichier);
    // Mode d'emploi :
    // - nomFichier : nom du fichier txt a partir duquelle l'import va s'effectuer
    //
    // Récupere tous les trajets d'un fichier et les stock dans une collection
    // Contrat :
    // l'utilisateur rentre un fichier au format .txt

    bool Export(Collection &collection, const string nomFichierExport);
    // Mode d'emploi :
    // Permet d'exporter une collection de trajet dans un fichier dont le nom est passé en paramètre.
    //
    // Contrat :
    // Le dossier Data doit déjà être créé. Les exports seront placés dans ce répertoire.
    // Si un fichier du même nom existait déjà, il sera supprimé.

//------------------------------------------------- Surcharge d'opérateurs
    Persistance &operator=(const Persistance &unPersistance);
    // Mode d'emploi :
    // Surchage de l'opérateur d'assignement
    // 
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Persistance(const Persistance &unPersistance);

    Persistance();
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Persistance>
    //
    // Contrat :
    //





//------------------------------------------------------------------ PRIVE

    void Split(string data, string array[], char separator = '|');

    //
    Collection *CreateCollection(ifstream &fichier, int recursivite = -1);

protected:
//----------------------------------------------------- Méthodes protégées


//----------------------------------------------------- Attributs protégés

};

//--------------------------- Autres définitions dépendantes de <Persistance>

#endif // PERSISTANCE_H