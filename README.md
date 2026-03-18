# ᗧ···ᗣ··· PAC-MAN

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

__A classic Pac-Man game implemented in pure C++ for the Windows console environment__

```text
PACMAN/
├── include/                 # Header files
│   ├── BFS.h                # BFS pathfinding algorithm class definition
│   ├── ConsoleColor.h       # Enum for console colors
│   ├── ConsoleUtils.h       # Static utility class encapsulating Windows Console API
│   ├── Direction.h          # Enum for movement directions (Up, Down, Left, Right)
│   ├── Edge.h               # Defines graph edges for building the movable grid
│   ├── Game.h               # Main game controller definition
│   ├── Ghost.h              # Ghost entity structure definition
│   ├── Pacman.h             # Pac-Man entity class definition
│   ├── Position.h           # 2D coordinate (Row, Col) structure and operator overloading
│   └── World.h              # Game world class definition
│
├── src/                     # Source files
│   ├── BFS.cpp              # BFS algorithm for finding shortest paths
│   ├── ConsoleUtils.cpp     # Console cursor movement, visibility, and colors
│   ├── Game.cpp             # Main game loop, user input, and win/loss logic
│   ├── main.cpp             # Application entry point
│   ├── Pacman.cpp           # Pac-Man's movement logic and visual state updates
│   └── World.cpp            # Map rendering, pellet consumption, and real-time score updates
│
├── Makefile                 # Build script
└── README.md                # Project documentation
```
## How to Build & Run

### 🚀 Prerequisites
* Windows Operating System
* any GCC compiler supporting C++
* `make` utility

### Quick start
``` bash
   git clone https://github.com/hsungo/Pac-Man.git
   cd Pac-Man
   make run
```

## 🕹️ Controls

| Key | Function |
| :---: | :--- |
| `↑` `↓` `←` `→` | Move Pac-Man |
| `R` / `r` | Restart the game |
| `ESC` | Exit the game |

| Score | Condition|
| :---: | :--- |
| +1 | Eat normal pellet (.) |
| +5 | Eat Power pellet (+) |
| +10 | Collsion Ghost after eat power pellet |

## 📸 Screenshots
### Menu when game start and restart the game
![alt text](/assets/image.png)

### Screenshot while playing the game
![alt text](/assets/image-1.png)

### Press ESC to exit the game
![alt text](/assets/image-2.png)
