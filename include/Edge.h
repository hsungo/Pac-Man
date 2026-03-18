#pragma once
#include "Position.h"

struct Edge {
    Position From;
    Position To;

    Edge(Position from, Position to) : From(from), To(to) {} // Constructor
};