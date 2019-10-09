# INSA-CPP-Catalogue-de-trajets
Projet C++ ayant pour but la manipulation des pointeurs, la gestion de la mémoire  et les différentes notions de base de la programmation orientée objet associées au langage C++ (polymorphisme et héritage notamment).

Il s'agit d'une application de gestion d'un catalogue de trajets (qui peut avoir pour but une utilisation dans une agence de voyage par exemple). Un trajet peut soit être un trajet simple caractérisé par une ville de départ, une ville d'arrivée et un type de transport (Avion, Train, etc). Un trajet peut aussi être un trajet composé simplement caractérisé par une liste ordonnée de trajets simples et/ou composés tels que la ville d'arrivée d'un trajet est obligatoire la ville de départ du trajet suivant.

La réalisation de cette application a été soumise à des contraintes de réalisation nous imposant d'utiliser uniquement 2 bibliothèques :
- La bibliothèque de manipulation des flux d'entrées / sorties "iostream" ne devant servir qu'à l'utilisation des objets cin, cout et cerr) ;
- La bibliothèque de manipulation des chaînes de caractères "cstring" pour une utilisation de strlen, strcpy, ...

Pour s'assurer de de l'absence de fuite de mémoire nous avons utilisé l'outil "valgrind".

## Les fonctionnalités de l'application
- Ajout de trajets dans la structure de données créée (un simple tableau dynamique) ;
- Affichage de la liste des trajets sur la sortie standard ;
- Recherche de parcours pour rejoindre deux villes sous deux versions : une recherche simple et une plus avancée :
  - La recherche simple se contente de parcourir l'ensemble des trajets du catalogue (sans parcourir les trajets des trajets composés) et affiche ceux correspondant à la ville de départ et d'arrivée spécifiés -> Un parcours correspond à un trajet ;
  - La recherche avancée consiste à proposer des parcours avec des éventuelles étapes -> Un parcours peut correspondre à un ensemble de trajets.
  
*Note : Un trajet composé doit obligatoirement être pris dans sa totalité (impossible donc de s'arrêter à une escale du trajet).*

## L'application en image
![Image de l'application](https://imgur.com/E5eRTeX.png)

## Diagramme de classe associé
![Diagramme de classe](https://imgur.com/vjrbHkQ.png)
