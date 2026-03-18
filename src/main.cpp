#include <iostream>
#include <windows.h>
#include <conio.h>
#include "ConsoleUtils.h"
#include "Game.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    ConsoleUtils::HideCursor();

    while (true) {
        ConsoleUtils::ClearScreen();
        ConsoleUtils::SetColor(ConsoleColor::Blue, ConsoleColor::Black);
        ConsoleUtils::SetCursorPosition(10, 8);
        std::cout << "=== PACMAN GAME===";
        ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
        ConsoleUtils::SetCursorPosition(10, 10);
        std::cout << "Choose Difficulty:";
        ConsoleUtils::SetColor(ConsoleColor::Green, ConsoleColor::Black);
        ConsoleUtils::SetCursorPosition(10, 12);
        std::cout << "1. Easy   (2 Ghosts)";
        ConsoleUtils::SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
        ConsoleUtils::SetCursorPosition(10, 13);
        std::cout << "2. Medium (3 Ghosts)";
        ConsoleUtils::SetColor(ConsoleColor::Red, ConsoleColor::Black);
        ConsoleUtils::SetCursorPosition(10, 14);
        std::cout << "3. Hard   (4 Ghosts)";
        ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
        
        int ghostCount = 2;
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == '1') { ghostCount = 2; break; }
                if (ch == '2') { ghostCount = 3; break; }
                if (ch == '3') { ghostCount = 4; break; }
            }
        }

        ConsoleUtils::ClearScreen();
        Game game(ghostCount);
        game.Run();

        ConsoleUtils::SetCursorPosition(0, 26);
        ConsoleUtils::SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
        std::cout << "Press R/r to replay the game or Press ESC to finish the game...\n";

        bool restart = false;
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'r' || ch == 'R') {
                    restart = true;
                    break;
                }
                if (ch == 27) { 
                    restart = false; 
                    break;
                }
            }
        }

        if (!restart) {
            break; 
        }
    }

    ConsoleUtils::ClearScreen();
    ConsoleUtils::SetCursorPosition(0, 0);
    ConsoleUtils::SetColor(ConsoleColor::White, ConsoleColor::Black);
    std::cout << "Game is finish! Have fun next time!!！\n";
    std::cout << "Your best score is "<< World::HighScore << " in this series of games\n";
    std::cout << "Your best time is "<< World::ShortestTime << " in this series of games\n";
    std::cout << "Press any key to exit...";
    _getch();
    ConsoleUtils::ClearScreen();

    return 0;
}