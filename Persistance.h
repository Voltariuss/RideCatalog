/*************************************************************************
                            Persistance  -  description
                              --------------------
   début                : 28/11/2019
   copyright            : (C) 2019 par name
*************************************************************************/

//---------- Interface de la classe <Persistance> (fichier <Persistance.h>) ------

#if ! defined ( PERSISTANCE_H )
#define PERSISTANCE_H
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Persistance>
//
//------------------------------------------------------------------------
class Persistance
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
    Persistance & operator = ( const Persistance & unPersistance );
    // Mode d'emploi :
    // Surchage de l'opérateur d'assignement
    // 
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Persistance ();
    // Mode d'emploi :
    // Constructeur par défaut de la classe <Persistance>
    //
    // Contrat :
    //

    bool Import();
    bool Export(Catalogue & _catalogue);
    bool CritereSelection();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    
};

//--------------------------- Autres définitions dépendantes de <Persistance>

#endif // PERSISTANCE_H