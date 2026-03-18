#pragma once
#include "ConsoleColor.h"

class ConsoleUtils {
public:
    static void SetCursorPosition(int x, int y);
    static void SetColor(ConsoleColor foreground, ConsoleColor background);
    static void HideCursor();
    static void ClearScreen();
};