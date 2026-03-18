#pragma once
#include "World.h"
#include "Pacman.h"
#include "Ghost.h"
#include <vector>

class Game {
private:
    World _world;
    Pacman _pacman;
    std::vector<Ghost> _ghosts;
    int _loopCount;
    void MoveGhosts();
    bool CheckCollisions();
    bool _isGameOver;
    void GetUserInput();
    
public:
    Game(int ghostCount);
    void Run();
};