#include <iostream>
#include "ConsoleUtils.h"
#include "Game.h"
#include <conio.h> 
#include <thread> 
#include <chrono>
#include <cstdlib>
#include <ctime>

Game::Game(int ghostCount) : _pacman(&_world), _loopCount(0), _isGameOver(false) {
    srand(time(NULL));

    Position startPositions[] = {
        Position(10, 16), 
        Position(10, 24), 
        Position(10, 18), 
        Position(10, 22) 
    };
    ConsoleColor colors[] = {
        ConsoleColor::Red,
        ConsoleColor::Magenta,
        ConsoleColor::Cyan,
        ConsoleColor::Green
    };

    for (int i = 0; i < ghostCount && i < 4; i++) {
        _ghosts.push_back(Ghost(i, startPositions[i], colors[i]));
    }

    _world.InitBFS();
}

//implement GetUserInput
void Game::GetUserInput() {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 224 || ch == 0) {
            ch = _getch();
            switch (ch) {
                case 72: _world.Directions.push(Direction::Up); break;
                case 80: _world.Directions.push(Direction::Down); break;
                case 75: _world.Directions.push(Direction::Left); break;
                case 77: _world.Directions.push(Direction::Right); break;
            }
        } 
        else if (ch == 27) {
            _isGameOver = true;
        }
    }
}

//implement MoveGhosts
void Game::MoveGhosts() {
    for (auto& ghost : _ghosts) {
        _world.ClearGhost(ghost);

        if (ghost.Weak) {
            Direction dirs[] = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
            std::vector<Direction> validDirs;
            for (auto d : dirs) {
                if (_world.IsMovable(ghost.Pos, d)) validDirs.push_back(d);
            }
            if (!validDirs.empty()) {
                Direction rd = validDirs[rand() % validDirs.size()];
                ghost.Pos = _world.GetPosition(ghost.Pos, rd);
            }
        } else {
            int randomChance = ghost.Index * 15; 
            
            if (rand() % 100 < randomChance) {
                Direction dirs[] = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
                std::vector<Direction> validDirs;
                for (auto d : dirs) {
                    if (_world.IsMovable(ghost.Pos, d)) validDirs.push_back(d);
                }
                if (!validDirs.empty()) {
                    Direction rd = validDirs[rand() % validDirs.size()];
                    ghost.Pos = _world.GetPosition(ghost.Pos, rd);
                }
            } else {
                ghost.Pos = _world.BfsAlgo->GetNextStep(ghost.Pos, _pacman.Pos);
            }
        }

        _world.ShowGhost(ghost);
    }
}

//implement CheckCollisions
bool Game::CheckCollisions() {
    for (auto& ghost : _ghosts) {
        if (ghost.Pos == _pacman.Pos) {
            if (ghost.Weak) {
                _world.Score += 10;
                _world.ClearGhost(ghost);
                ghost.Pos = ghost.StartPos;
                ghost.Weak = false;
            } else {
                return true; 
            }
        }
    }
    return false;
}

void Game::Run() {
    _world.ShowWorld();
    _world.ShowDots();
    _world.ShowPacman(_pacman);
    for(auto& ghost : _ghosts) _world.ShowGhost(ghost);
    auto startTime = std::chrono::steady_clock::now();

    while (!_isGameOver) {
        _loopCount++;
        GetUserInput();
        _pacman.Move();

        auto currentTime = std::chrono::steady_clock::now();
        _world.Time = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        _world.UpdateDotsAndScore(_pacman, _ghosts);
        _world.ShowScore();
        _isGameOver = CheckCollisions();

        if (!_isGameOver && _loopCount % 2 == 0) {
            MoveGhosts();
            _isGameOver = CheckCollisions();
        }

        if (!_world.HasDots()) {
            _isGameOver = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150)); 
    }

    ConsoleUtils::SetCursorPosition(0, 25);
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);

    if (!_world.HasDots()) {
        if (World::ShortestTime == 0 || _world.Time < World::ShortestTime) {
            World::ShortestTime = _world.Time;
        }
        std::cout << "Congratulation！\n";
    } 
    else {
        std::cout << "GAME OVER！\n";
    }
}