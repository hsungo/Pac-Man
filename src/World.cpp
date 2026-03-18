#include "World.h"
#include "ConsoleUtils.h"
#include <iostream>

int World::HighScore = 0;
int World::ShortestTime = 0;

//initial game map
World::World() {
    WallsString = {
        "╔═══════════════════╦═══════════════════╗",
        "║                   ║                   ║",
        "║   ╔═╗   ╔═════╗   ║   ╔═════╗   ╔═╗   ║",
        "║   ╚═╝   ╚═════╝   ╨   ╚═════╝   ╚═╝   ║",
        "║                                       ║",
        "║   ═══   ╥   ══════╦══════   ╥   ═══   ║",
        "║         ║         ║         ║         ║",
        "╚═════╗   ╠══════   ╨   ══════╣   ╔═════╝",
        "      ║   ║                   ║   ║      ",
        "══════╝   ╨   ╔════   ════╗   ╨   ╚══════",
        "              ║           ║              ",
        "══════╗   ╥   ║           ║   ╥   ╔══════",
        "      ║   ║   ╚═══════════╝   ║   ║      ",
        "      ║   ║                   ║   ║      ",
        "╔═════╝   ╨   ══════╦══════   ╨   ╚═════╗",
        "║                   ║                   ║",
        "║   ══╗   ═══════   ╨   ═══════   ╔══   ║",
        "║     ║                           ║     ║",
        "╠══   ╨   ╥   ══════╦══════   ╥   ╨   ══╣",
        "║         ║         ║         ║         ║",
        "║   ══════╩══════   ╨   ══════╩══════   ║",
        "║                                       ║",
        "╚═══════════════════════════════════════╝"
    };

    DotsString = {
        "                                         ",
        "  . . . . . . . . .   . . . . . . . . .  ",
        "  .     .         .   .         .     .  ",
        "  +     .         .   .         .     +  ",
        "  . . . . . . . . . . . . . . . . . . .  ",
        "  .     .   .               .   .     .  ",
        "  . . . .   . . . .   . . . .   . . . .  ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "        .                       .        ",
        "  . . . . . . . . .   . . . . . . . . .  ",
        "  .     .         .   .         .     .  ",
        "  + .   . . . . . .   . . . . . .   . +  ",
        "    .   .   .               .   .   .    ",
        "  . . . .   . . . .   . . . .   . . . .  ",
        "  .               .   .               .  ",
        "  . . . . . . . . . . . . . . . . . . .  ",
        "                                         "
    };

    LogicMap = {
        "WWWWWWWWWWWWWWWWWWW W WWWWWWWWWWWWWWWWWWW",
        "W                   W                   W",
        "W   WWW   WWWWWWW   W   WWWWWWW   WWW   W",
        "W   WWW   WWWWWWW   W   WWWWWWW   WWW   W",
        "W                                       W",
        "W   WWW   W   WWWWWWWWWWWWW   W   WWW   W",
        "W         W         W         W         W",
        "WWWWWWW   WWWWWWW   W   WWWWWWW   WWWWWWW",
        "      W   W                   W   W      ",
        "WWWWWWW   W   WWWW     WWWW   W   WWWWWWW",
        "              W           W              ",
        "WWWWWWW   W   W           W   W   WWWWWWW",
        "      W   W   WWWWWWWWWWWWW   W   W      ",
        "      W   W                   W   W      ",
        "WWWWWWW   W   WWWWWWWWWWWWW   W   WWWWWWW",
        "W                   W                   W",
        "W   WWW   WWWWWWW   W   WWWWWWW   WWW   W",
        "W     W                           W     W",
        "WWW   W   W   WWWWWWWWWWWWW   W   W   WWW",
        "W         W         W         W         W",
        "W   WWWWWWWWWWWWW   W   WWWWWWWWWWWWW   W",
        "W                                       W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    _dots = DotsString;
}

World::~World() {
    if (BfsAlgo != nullptr) delete BfsAlgo;
}

//implement ShowWorld
void World::ShowWorld() {
    ConsoleUtils::SetColor(ConsoleColor::Blue, ConsoleColor::Black);
    for (size_t row = 0; row < WallsString.size(); row++) {
        ConsoleUtils::SetCursorPosition(0, row); 
        std::cout << WallsString[row];
    }
}

//implement ShowDots
void World::ShowDots() {
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
    for (size_t row = 0; row < _dots.size(); row++) {
        for (size_t col = 0; col < _dots[row].length(); col++) {
            if (_dots[row][col] == '.' || _dots[row][col] == '+') {
                ConsoleUtils::SetCursorPosition(col, row);
                std::cout << _dots[row][col];
            }
        }
    }
}


//implement ShowPacman
void World::ShowPacman(Pacman& pacman) {
    auto colors = pacman.GetStateColor();
    ConsoleUtils::SetColor(colors.first, colors.second);
    ConsoleUtils::SetCursorPosition(pacman.Pos.Col, pacman.Pos.Row);
    std::cout << pacman.GetFrameFace(pacman.Dir);
}

//implement ShowGhost
void World::ShowGhost(Ghost& ghost) {
    ConsoleUtils::SetColor(ConsoleColor::Black, ghost.Color);
    ConsoleUtils::SetCursorPosition(ghost.Pos.Col, ghost.Pos.Row);
    std::cout << 'G';
}

//implement GetPosition
Position World::GetPosition(Position pos, Direction dir) {
    Position newPos = pos;
    if (dir == Direction::Up) newPos.Row--;
    else if (dir == Direction::Down) newPos.Row++;
    else if (dir == Direction::Left) newPos.Col--;
    else if (dir == Direction::Right) newPos.Col++;

    int colBound = LogicMap[0].length();
    if (newPos.Col < 0) newPos.Col = colBound - 1;
    if (newPos.Col >= colBound) newPos.Col = 0;

    return newPos;
}

//implement IsMovable
bool World::IsMovable(Position pos, Direction dir) {
    Position newPos = GetPosition(pos, dir);
    if (newPos.Row < 0 || newPos.Row >= (int)LogicMap.size()) return false;
    return LogicMap[newPos.Row][newPos.Col] == ' ';
}

//implement CleaerPacman
void World::ClearPacman(Position pos) {
    ConsoleUtils::SetCursorPosition(pos.Col, pos.Row);
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
    std::cout << " ";
}

//implement InitBFS
void World::InitBFS() {
    std::vector<Edge> edges;
    Direction dirs[] = {Direction::Up, Direction::Down, Direction::Left, Direction::Right};
    for (int row = 0; row < (int)LogicMap.size(); row++) {
        for (int col = 0; col < (int)LogicMap[0].length(); col++) {
            if (LogicMap[row][col] == ' ') {
                Position from(row, col);
                for (Direction d : dirs) {
                    if (IsMovable(from, d)) {
                        edges.push_back(Edge(from, GetPosition(from, d)));
                    }
                }
            }
        }
    }
    BfsAlgo = new BFS(edges);
}

//ClearGhost
void World::ClearGhost(Ghost& ghost) {
    ConsoleUtils::SetCursorPosition(ghost.Pos.Col, ghost.Pos.Row);
    char c = _dots[ghost.Pos.Row][ghost.Pos.Col];
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
    if (c == '.' || c == '+') {
        std::cout << c;
    } 
    else {
        std::cout << ' ';
    }
}

//implement UpdateDotsAndScore
void World::UpdateDotsAndScore(Pacman& pacman, std::vector<Ghost>& ghosts) {
    int row = pacman.Pos.Row;
    int col = pacman.Pos.Col;
    char c = _dots[row][col];
    
    if (pacman.PowerTimes > 0) {
        pacman.PowerTimes--;
        if (pacman.PowerTimes == 0) {
            for (auto& g : ghosts) g.Weak = false;
        }
    }

    if (c == '.') { 
        _dots[row][col] = ' ';
        Score += 1;
    } 
    else if (c == '+') { 
        _dots[row][col] = ' ';
        Score += 5;
        pacman.PowerTimes = 40;
        for (auto& g : ghosts) g.Weak = true;
    }

    if (Score > HighScore) {
        HighScore = Score;
    }
}

//implement HasDots
bool World::HasDots() {
    for (const auto& row : _dots) {
        for (char c : row) {
            if (c == '.' || c == '+') return true;
        }
    }
    return false;
}


//implement ShowScore
void World::ShowScore() {
    ConsoleUtils::SetCursorPosition(0, 23);
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
    std::cout << "Score: " << Score << "    High Score: " << HighScore << std::endl;

    ConsoleUtils::SetCursorPosition(0, 24);
    std::cout << "Time: " << Time << " s    ";
    if (ShortestTime == 0) {
        std::cout << "Best: -- s       ";
    } 
    else {
        std::cout << "Best: " << ShortestTime << " s       ";
    }
}