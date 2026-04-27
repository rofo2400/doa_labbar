//
// Created by fonse on 4/20/2026.
//

#include "reader.h"
#include "functions.h"

#include <iostream>

int main() {
    adjacency_list_t adj_list = parse_file("edges.txt");
    auto matrix = convertToMatrix(adj_list);
    std::cout << "test1 \n";
    if (dfsConnected(matrix)) {
        std::cout << "The graph is connected" << "\n";
    }
    else {
        std::cout << "The graph is not connected" << "\n";
    }
    std::cout << "test2\n";
    return 0;
}