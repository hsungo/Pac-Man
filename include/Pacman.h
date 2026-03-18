#pragma once
#include "Position.h"
#include "Direction.h"
#include "ConsoleColor.h"
#include <vector>
#include <string>
#include <utility>

class World; 
class Pacman {
private:
    World* _world;
    std::vector<std::string> _pacManAnimations;
    int _faceFrame;

public:
    Direction Dir;
    Position Pos;
    int PowerTimes;
    Pacman(World* world);
    void Move();
    std::pair<ConsoleColor, ConsoleColor> GetStateColor();
    char GetFrameFace(Direction direction);
};