#pragma once
#include <vector>
#include <string>
#include <queue>
#include "Pacman.h"
#include "Ghost.h"
#include "BFS.h"

class World {
private:
    std::vector<std::string> WallsString;
    std::vector<std::string> DotsString;
    std::vector<std::string> _dots; 
    std::vector<std::string> LogicMap;

public:
    int Score = 0;       
    int Time = 0;
    static int HighScore;
    static int ShortestTime;
    BFS* BfsAlgo = nullptr;
    World();
    ~World();
    std::queue<Direction> Directions;
    void ShowWorld();
    void ShowDots();
    void ShowPacman(Pacman& pacman);
    void ShowGhost(Ghost& ghost);
    void InitBFS();
    bool IsMovable(Position pos, Direction dir);
    Position GetPosition(Position pos, Direction dir);
    void ClearPacman(Position pos);
    void ClearGhost(Ghost& ghost);
    void UpdateDotsAndScore(Pacman& pacman, std::vector<Ghost>& ghosts);
    void ShowScore();
    bool HasDots();
};