#include "ConsoleUtils.h"
#include <windows.h>
#include <iostream>

//implement SetCursorPosition
//change the cursor position in terminal
void ConsoleUtils::SetCursorPosition(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);
}

//implement SetColor
//8bits for color, 4 bits for foreground, 4 bits for background
void ConsoleUtils::SetColor(ConsoleColor foreground, ConsoleColor background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = static_cast<int>(foreground) | (static_cast<int>(background) << 4);
    SetConsoleTextAttribute(hConsole, colorAttribute);
}

//implement HideCursor
void ConsoleUtils::HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//implement ClearScreen
void ConsoleUtils::ClearScreen() {
    system("cls"); 
}