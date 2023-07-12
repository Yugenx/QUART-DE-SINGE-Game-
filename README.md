# QUART-DE-SINGE-Game-

# 1. Présentation du Projet

Il s'agit d'un jeu de mots nommé "Quart de Singe" qui peut se jouer par deux joueurs ou plus. Durant la partie, plusieurs manches
peuvent se dérouler, une nouvelle manche commence suite à la gratification d'un joueur d'un quart de signe. La partie se termine suite à la première récolte de 4 quarts de singe par l'un des joueurs (qui peut être soit humain soit robot )

**J'ai utilisé des fonctions et des structures autonomes :**

***la structure du joueur :***

-la structure joueur_données contient les informations sur le joueur.
- Le jeu utilise la structure joueur_données pour gérer les joueurs et
effectuer toutes les opérations sur eux en utilisant get_data() et
update_data() garde la structure de joueur dans un tableau, une fois qu'une
infos_joueur est ajouté au jeu, le jeu initialisera une structure de joueur dans
un emplacement de mémoire spécifié,
-toutes les communications se font à travers la structure joueur_données.
- Ainsi, nous pouvons garder la structure de joueur utilisée par le jeu, et la
fonction principale ne passe qu'une structure de type joueur_données .
- le mot struct est un conteneur pour toutes les méthodes dont nous avons
besoin pour manipuler les chaînes de caractères.
- On peut l’utiliser par exemple pour créer un simple cache pour le jeu ou
stocker une chaîne pour un certain temps.
- nous y utilisons aucun conteneur de la bibliothèque standard c++ comme
les chaînes, les pointeurs intelligents, etc.


# 2. Présentation de l’application

Pour des raisons de lisibilité et pour une meilleure structuration de notre
application, il est nécessaire de la découper en plusieurs fichiers.
Fichier entête avec l’extension .h qui comprend les déclarations de variables
de type et la déclaration des fonctions et de structures ainsi que son fichier
source avec l’extension.cpp qui contient l’implémentation des différentes
fonctions déclarées dans le fichier entête.
Notre application est subdivisée en fichiers suivants :
 Main : c’est la fonction principale qui permet de récupérer le nombre de
joueurs ainsi que leurs types.
 Joueur : contient les informations d’un joueur sous forme d’une structure
telles que : nombre, type, caractère saisi(guess), quart de singe (quarts),
ainsi qu’une structure joueur
 Jeu_singe : permet de créer la liste des joueurs avec un tableau
dynamique de type pointeur sur joueur , c’est-à-dire que chaque élément
du tableau est un pointeur vers le joueur.
 Mot : ça peut être le mot recherché ou le mot du dictionnaire ou le mot
saisie.


# Le diagramme suivant montre les dépendances entre les différents fichiers :


![llllll](https://github.com/Yugenx/QUART-DE-SINGE-Game-/assets/128916490/f86a9ce0-38cd-4b15-8159-ca91f9d58c0e)











