//
// Created by fonse on 4/20/2026.
//

#include "reader.h"
#include "functions.h"

#include <iostream>

int main() {
    adjacency_list_t adj_list = parse_file("edges.txt");
    auto matrix = convertToMatrix(adj_list);

    if (dfsConnected(matrix)) {
        std::cout << "[DFS]The graph is connected" << "\n";
    }
    else {
        std::cout << "[DFS]The graph is not connected" << "\n";
    }
    if (bfsConnected(matrix)) {
        std::cout << "[BFS]The graph is connected" << "\n";
    }
    else {
        std::cout << "[BFS]The graph is not connected" << "\n";
    }
    return 0;
}