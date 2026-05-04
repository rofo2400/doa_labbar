//
// Created by fonse on 4/20/2026.
//

#include "reader.h"
#include "functions.h"

#include <iostream>

int main() {
    system("chcp 65001");
    adjacency_list_t adj_list = parse_file("edges.txt");
    auto matrix = convertToMatrix(adj_list);
    auto meta = adj_list.first;

    node_id_t skyddrum = 0;
    node_id_t nackstavagen = 23;
    node_id_t forradet = 37;
    node_id_t L319 = 46;
    node_id_t D025 = 47;
    node_id_t universitetet = 20;
    node_id_t biteline = 19;

    if (dfsConnected(skyddrum, matrix)) {
        std::cout << "[DFS]The graph is connected" << "\n";
    }
    else {
        std::cout << "[DFS]The graph is not connected" << "\n";
    }
    if (bfsConnected(skyddrum, matrix)) {
        std::cout << "[BFS]The graph is connected" << "\n";
    }
    else {
        std::cout << "[BFS]The graph is not connected" << "\n";
    }
    std::cout << "\n\n";


    //test 1
    auto res1 = dijkstras(nackstavagen, matrix);
    printPath(nackstavagen, forradet, res1, meta);
    std::cout << "\n\n";
    //test 2
    auto res2 = dijkstras(L319, matrix);
    printPath(L319, D025, res2, meta);
    std::cout << "\n\n";

    //test 3
    auto res3 = dijkstras(universitetet, matrix);
    printPath(universitetet, biteline, res3, meta);

    return 0;
}