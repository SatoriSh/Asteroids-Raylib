<div align="center">
<table align="center">
<tr>
<td>
<pre>
    _        _                 _     _
   / \   ___| |_ ___ _ __ ___ (_) __| |___
  / _ \ / __| __/ _ | '__/ _ \| |/ _` / __|
 / ___ \\__ | ||  __| | | (_) | | (_| \__ \
/_/   \_|___/\__\___|_|  \___/|_|\__,_|___/
</pre>
</td>
</tr>
</table>
</div>


A high-performance, object-oriented implementation of the classic Asteroids arcade game. Developed using **Modern C++ (C++17)** and the **Raylib** library.

---

## 📸 Video gameplay
https://github.com/user-attachments/assets/bb388f70-a92e-4337-bf06-8e3161145a45

---

## 🛠 Technical Overview
This project serves as a showcase of C++ fundamentals applied to game development:
* **Memory Management:** Utilizes `std::unique_ptr` for automatic and safe lifecycle management of game entities.
* **Entity Component Logic:** Implements a base `GameObject` class with virtual methods for polymorphic behavior.
* **Event Handling:** Features a lambda-based shooting system (`std::function`) to decouple the Player from the Game engine.
* **Optimized Rendering:** Uses `RenderTexture2D` for static starfield generation to minimize draw calls.
* **Collision System:** Implements AABB collision detection with specialized logic for asteroid splitting.

## 🎮 Gameplay Mechanics
* **Movement:** Physics-based thrust and rotation with inertia.
* **Asteroid Logic:** 3-tier destruction system (Large -> Medium -> Small).
* **Difficulty:** Progressive spawn rates and speed scaling based on the current score.

## ⌨️ Controls
| Action | Key / Input |
| :--- | :--- |
| **Thrust** | `W` or `Up Arrow` |
| **Rotate** | `A/D` or `Left/Right Arrows` |
| **Shoot** | `Space` or `Left Mouse Button` |
| **Restart**| `Enter` (when game is over) |

## 🚀 Building and Running
1.  **Requirements:** Visual Studio 2022 and Raylib (installed via NuGet or manually).
2.  **Clone:** `git clone https://github.com/SatoriSh/Asteroids-Raylib.git`
3.  **Build:** Open `.sln` and build the project in **Release** mode for best performance.

---
*Developed as a learning project to master C++ game architecture.*
