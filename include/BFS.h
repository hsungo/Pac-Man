#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "Position.h"
#include "Edge.h"

class BFS{
private:
    std::vector<Edge> _edges;
    std::vector<Position> GetPath(std::unordered_map<Position, Position>& paths, Position start, Position end);

public:
    BFS(const std::vector<Edge>& edges); // Constructor
    std::vector<Position> Search(Position start, Position end);
    Position GetNextStep(Position start, Position end);
};