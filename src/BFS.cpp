#include "BFS.h"
#include <algorithm>

// implement constructor
BFS::BFS(const std::vector<Edge>& edges) : _edges(edges) {} 

//implement Search
//search the way we can go 
std::vector<Position> BFS::Search(Position start, Position end) {
    std::queue<Position> queue;
    queue.push(start);
    std::unordered_set<Position> visited = {start};
    std::unordered_map<Position, Position> paths;

    while (!queue.empty()) {
        Position currentFrom = queue.front();
        queue.pop();

        if (currentFrom == end) {
            return GetPath(paths, start, end);
        }

        for (const auto& edge : _edges) {
            if (edge.From == currentFrom) {
                Position to = edge.To;

                if (visited.find(to) == visited.end()) {
                    queue.push(to);
                    visited.insert(to);
                    paths[to] = currentFrom;
                }
            }
        }
    }

    return std::vector<Position>();
}

//implement GetNextStep
//find the way (get from Search) we can go next
Position BFS::GetNextStep(Position start, Position end){
    std::vector<Position> path = Search(start, end);
    if(path.size() > 1){
        return path[1];
    }
    return start;
}

//implement GetPath
//get the path we go through
std::vector<Position> BFS::GetPath(std::unordered_map<Position, Position>& paths, Position start, Position end) {
    std::vector<Position> path;
    Position current = end;
    path.push_back(current);

    while (current != start) {
        current = paths[current];
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());
    
    return path;
}