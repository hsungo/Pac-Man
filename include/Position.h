#pragma once
#include <functional>

struct Position{
    int Row;
    int Col;

    Position(int r = 0, int c = 0) : Row(r), Col(c) {} // Constructor

    bool operator == (const Position& other) const{ // overload ==
        return Row == other.Row && Col == other.Col;
    }

    bool operator != (const Position& other) const{ // overload !=
        return !(*this == other);
    }
};

namespace std{ //overload hash while using Position in hash
    template <>
    struct hash<Position>{
        size_t operator()(const Position& p) const{
            return hash<int>()(p.Row) ^ (hash<int>()(p.Col) << 1);
        }
    };
}