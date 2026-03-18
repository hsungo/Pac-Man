#include "Pacman.h"
#include "World.h"

Pacman::Pacman(World* world) : _world(world), _faceFrame(0), Dir(Direction::None), PowerTimes(0) {
    _pacManAnimations = {
        "\"' '\"", 
        "n. .n",   
        ")>- ->",  
        "(<- -<"  
    };
    Pos = Position(17, 20);
}

std::pair<ConsoleColor, ConsoleColor> Pacman::GetStateColor() {
    if (PowerTimes <= 0) return {ConsoleColor::Black, ConsoleColor::Yellow};
    if (PowerTimes < 30) return {ConsoleColor::Black, ConsoleColor::Magenta};
    return {ConsoleColor::Black, ConsoleColor::Cyan};
}

char Pacman::GetFrameFace(Direction direction) {
    int faceRow = static_cast<int>(direction);
    if (faceRow < 0 || faceRow >= static_cast<int>(_pacManAnimations.size())) faceRow = 0;
    
    if (Dir == direction) {
        _faceFrame = (_faceFrame + 1) % _pacManAnimations[faceRow].length();
    } else {
        _faceFrame = 0;
    }
    return _pacManAnimations[faceRow][_faceFrame];
}

//implement Move
void Pacman::Move() {
    Direction newDir = Dir;
    
    if (!_world->Directions.empty()) {
        newDir = _world->Directions.front();
        _world->Directions.pop();
    }

    if (_world->IsMovable(Pos, newDir)) {
        Dir = newDir;
        _world->ClearPacman(Pos);
        Pos = _world->GetPosition(Pos, newDir);
        _world->ShowPacman(*this);
    } 
    else if (_world->IsMovable(Pos, Dir)) {
        _world->ClearPacman(Pos);
        Pos = _world->GetPosition(Pos, Dir);
        _world->ShowPacman(*this);
    }
}