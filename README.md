# cub3D

![cub3d](https://github.com/user-attachments/assets/673b2602-6ab3-4103-a7e2-b4b14441d01b)

## Introduction

**cub3D** is a project developed as part of our curriculum at 42 school. It’s a mini 3D game using the raycasting technique, built with the MiniLibX graphics library. This project uses an enhanced version of MiniLibX called [MiniLibX-Extended](https://github.com/leofarhi/MiniLibX-Extended), which provides additional features.

---

## Features and Goal

**cub3D** is a 3D reinterpretation of the classic *Pac-Man*. Main features include:

* **Main goal**: Collect all the yellow balls to win.
* **Ghosts**: Avoid them, or eat them after grabbing a green ball.
* **Minimap**: 2D view of the map, similar to the original *Pac-Man*.
* **Doors**: Open them with a left click or the Space key.
* **Pause**: Press Tab to pause the game.

---

## Installation and Compilation

To try **cub3D**, follow these steps:

1. Clone this repository along with the original MiniLibX version.
2. Compile the project by running:

   ```bash
   make
   ```
3. Launch the game with:

   ```bash
   ./cub3D maps/valid/[your_map].cub
   ```

   > For the best experience, try the default map:
   >
   > ```bash
   > ./cub3D maps/valid/pacman.cub
   > ```

---

## Map Generation

**cub3D** lets you create your own custom maps with an integrated generator.

### Steps:

1. Run the map generator script:

   ```bash
   python ./map_gen.py
   ```
2. Once your map is generated (as `gen_map.cub`), run it with:

   ```bash
   ./cub3D maps/gen_map.cub
   ```

---

## Controls

| **Action**    | **Key/Command**            |
| ------------- | -------------------------- |
| Move          | W, A, S, D                 |
| Rotate camera | Mouse or Left/Right Arrows |
| Open doors    | Space or Left Click        |
| Pause         | Tab                        |

---

## Team

This project was developed by:

- [leofarhi](https://github.com/leofarhi)
- [pquline](https://github.com/pquline)
