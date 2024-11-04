# Jeu en C

Bienvenue dans le projet **Jeu en C** ! Ce projet consiste en un jeu de stratégie en mode texte, avec deux versions : une version de base et une version "historique" qui inclut un système de score. Ce jeu se joue en tour par tour, et les joueurs peuvent personnaliser leurs mouvements de pions pour tenter de gagner.

## Table des matières
- [Fonctionnalités](#fonctionnalités)
- [Prérequis](#prérequis)
- [Installation et exécution](#installation-et-exécution)
  - [Version de base](#version-de-base)
  - [Version historique](#version-historique)
- [Règles du jeu](#règles-du-jeu)
  - [Objectif](#objectif)
  - [Déroulement du jeu](#déroulement-du-jeu)
- [Détails techniques](#détails-techniques)
- [Crédits](#crédits)

---

## Fonctionnalités

- **Deux versions** : une version de base et une version historique avec enregistrement des scores.
- **Déplacements stratégiques** : chaque joueur doit déplacer ses pions en respectant les règles de la version choisie.
- **Mode texte** : jeu entièrement en terminal, sans interface graphique.

## Prérequis

- Compilateur **GCC** (GNU Compiler Collection).

## Installation et exécution

### Version de base

1. Ouvrez un terminal et placez-vous dans le dossier `board`.
2. Compilez et exécutez le jeu de base avec les commandes suivantes :

   ```bash
   gcc -Wall -c board.c
   gcc -Wall board.o affichage.c -o board
   ./board

### Version historique

La version historique du jeu inclut un système de score pour enregistrer les performances des joueurs. En plus des règles de base, les joueurs peuvent accumuler des points en fonction de leurs victoires et défaites, ce qui leur permet de suivre leur classement au fil des parties.

#### Règles de la version historique

- En cas de **victoire**, un joueur gagne **5 points**.
- En cas de **défaite**, un joueur perd **2 points**.
- Le système de score est sauvegardé pour permettre un classement persistant entre les parties.

#### Instructions de compilation et d'exécution

1. Ouvrez un terminal et placez-vous dans le dossier `historic`.
2. Compilez les fichiers nécessaires pour exécuter la version historique avec les commandes suivantes :

   ```bash
   gcc -Wall -c historical.c
   gcc -Wall -c board.c
   gcc -Wall main_historical.c historical.o board.o -o historical
   ./historical
## Règles du jeu

### Objectif
Le but du jeu est de déplacer les pions pour atteindre un certain objectif en suivant les règles de déplacement. Dans la version historique, les joueurs peuvent accumuler des points en fonction de leurs victoires et défaites.

### Déroulement du jeu
1. **Initialisation :**
   - Chaque joueur entre son nom.
   - Les joueurs placent leurs pions sur les deux lignes de leur côté (les deux premières lignes pour le joueur nord, et les deux dernières pour le joueur sud).
   
2. **Déplacements :**
   - Le joueur nord commence le premier déplacement.
   - À chaque tour, le joueur doit déplacer un pion qui se trouve sur le numéro de la case d'arrivée du tour précédent.
   - Si cela est impossible, deux options sont offertes :
     - Réintégrer un pion que le joueur a perdu.
     - Déplacer un autre pion de son choix.

## Détails techniques
- **Langage :** C

## Crédits
- **Créé par :** Cyprien Duroy
