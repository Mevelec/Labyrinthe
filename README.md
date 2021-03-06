# Labyrinthe
## Infos
Projet developpé et testé sous visual studio 2019 et sous windows 10 x86

## Objectif
L'objectif de ce projet est de réaliser un programme qui charge un fichier, affiche un labyrinthe, essai de le résoudre et affichage le nombre de coups nécessaire à la résolution du labyrinthe.
[lien vers la vidéo](https://youtu.be/WjgM7qOo06I)
![Video de démonstration](https://github.com/Mevelec/Labyrinthe/blob/main/screenshots/screen_1.PNG)
## Algorithmes de résolution
- déplacement en ligne droite et tourne à droite quand bloqué
- déplacement en ligne droite et tourne à gauche quand bloqué
- déplacement en ligne droite et tourne aléatoirement à chaque embranchement
- déplacement le plus en ligne droite vers la sortie
- déplacement en ligne droite et tourne à droite quand bloqué mais retiens la case vistées

## Structure du projet
- ConsolRenderer : librairie permettant le rendu d'objet dans la console windows ainsi que la gstion des evenements clavier et de la gameloop
- GameLib : librairie contenant les classes principales, la logique du jeu (grid, player, grid Manager ...)
- GameTest : tests unitaires de GameLib 
- Game : projet executable, implementation du jeu en utilisant ConsolRenderer et GameLib
 
## credits
merci a @Javidx9, pour le code de la game loop et le system de keyevent

