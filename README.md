# cub3D

## Introduction
**cub3d** est un projet développé dans le cadre de notre cursus à l'école 42. Il s'agit d'un mini-jeu en 3D utilisant la technique de raycasting, conçu avec la bibliothèque graphique MiniLibX. Ce projet utilise une version améliorée de la MiniLibX, appelée [MiniLibX-Extended](https://github.com/leofarhi/MiniLibX-Extended), qui offre des fonctionnalités supplémentaires.

---

## Fonctionnalités et Objectif
**cub3d** revisite le classique *Pac-Man* en 3D. Voici les principales fonctionnalités :

- **Objectif principal** : Collectez toutes les boules jaunes pour gagner.
- **Fantômes** : Évitez les fantômes ou mangez-les après avoir collecté une boule verte.
- **Minimap** : Représentation 2D de la carte, similaire à l'original *Pac-Man*.
- **Portes** : Ouvrez-les avec un clic gauche ou la touche Espace.
- **Pause** : Appuyez sur Tab pour mettre le jeu en pause.

---

## Installation et Compilation
Pour tester **cub3d**, suivez les étapes ci-dessous :

1. Clonez ce dépôt ainsi que la version originale de la MiniLibX.
2. Compilez le projet en exécutant la commande suivante dans le répertoire du jeu :
   ```bash
   make
   ```
3. Lancez le jeu avec la commande suivante :
   ```bash
   ./cub3D maps/valid/[votre_map].cub
   ```
   > Pour une meilleure expérience, essayez la carte par défaut :
   > ```bash
   > ./cub3D maps/valid/pacman.cub
   > ```

---

## Génération de Cartes
**cub3d** permet de créer vos propres cartes personnalisées grâce à un générateur intégré.

### Étapes :
1. Exécutez le script de génération de cartes :
   ```bash
   python ./map_gen.py
   ```
2. Une fois votre carte générée (générée sous le nom `gen_map.cub`), lancez-la avec :
   ```bash
   ./cub3D maps/gen_map.cub
   ```

---

## Contrôles

| **Action**               | **Touche/Commande**         |
|--------------------------|-----------------------------|
| Déplacement              | W, A, S, D                 |
| Rotation de la caméra    | Souris ou Flèches gauche/droite |
| Ouvrir les portes        | Espace ou Clic gauche       |
| Mettre en pause          | Tab                         |
