#pragma once
#include "Position.h"
#include "ConsoleColor.h"

struct Ghost {
    int Index;
    Position Pos;
    Position StartPos;
    ConsoleColor Color;
    bool Weak;

    Ghost(int index, Position pos, ConsoleColor color) 
        : Index(index), Pos(pos), StartPos(pos), Color(color), Weak(false) {}
};