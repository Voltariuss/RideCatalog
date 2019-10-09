# INSA-CPP-Catalogue-de-trajets
Projet C++ ayant pour but la manipulation des pointeurs, la gestion de la mémoire  et les différentes notions de base de la programmation orientée objet associées au langage C++ (polymorphisme et héritage notamment).

## Les fonctionnalités de l'application
- Ajout de trajets dans la structure de données créée (un simple tableau dynamique) ;
- Affichage de la liste des trajets sur la sortie standard ;
- Recherche de parcours pour rejoindre deux villes sous deux versions : une recherche simple et une plus avancée :
  - La recherche simple se contente de parcourir l'ensemble des trajets du catalogue (sans parcourir les trajets des trajets composés) et affiche ceux correspondant à la ville de départ et d'arrivée spécifiés -> Un parcours correspond à un trajet ;
  - La recherche avancée consiste à proposer des parcours avec des éventuelles étapes -> Un parcours peut correspondre à un ensemble de trajets.

## L'application en image
![Image de l'application](https://imgur.com/E5eRTeX.png)

## Diagramme de classe associé
![Diagramme de classe](https://imgur.com/vjrbHkQ.png)
