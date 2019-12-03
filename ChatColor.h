/*************************************************************************
       ChatColor - Classe de gestion des couleurs dans la console
                             -------------------
    début                : 3/10/2019
    copyright            : (C) 2019 par Nel BOUVIER & Loïc DUBOIS-TERMOZ
    e-mail               : nel.bouvier@insa-lyon.fr
                           loic.dubois-termoz@insa-lyon.fr
*************************************************************************/

//--------------- Interface de la classe <ChatColor> (fichier ChatColor.h)
#ifndef INSA_CPP_CATALOGUE_DE_TRAJETS_CHATCOLOR_H
#define INSA_CPP_CATALOGUE_DE_TRAJETS_CHATCOLOR_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>

//------------------------------------------------------------------ Types
enum IndexCouleur {
    NOIR, ROUGE, VERT, JAUNE, BLEU, MAGENTA, CYAN, BLANC, RESET
};
static const char *const COULEUR[] = {
        "\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m", "\033[m\017"
};

class ChatColor {
    //------------------------------------------------------------- PUBLIC
public:
    //------------------------------------------------- Méthodes publiques
    explicit ChatColor(IndexCouleur i): index(i) {}
    inline friend ostream & operator <<(ostream & os, const ChatColor & color) {
        const char * const strColor = COULEUR[color.index];
        os.write(strColor, strlen(strColor));
        return os.flush();
    }

    //------------------------------------------------------------ PRIVATE
private:
    IndexCouleur index;
};

#endif //INSA_CPP_CATALOGUE_DE_TRAJETS_CHATCOLOR_H
