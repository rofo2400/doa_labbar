//
// Created by fonse on 4/20/2026.
//

#ifndef LABB1_FUNCTIONS_H
#define LABB1_FUNCTIONS_H

#include <vector>

#include "reader.h"

std::vector<std::vector<double>> convertToMatrix(const adjacency_list_t& list);

void dfs(node_id_t startNode, std::vector<std::vector<double>>& matrix, std::vector<bool>& visited);

void bfs(node_id_t startNode, std::vector<std::vector<double>>& matrix, std::vector<bool>& visited);

struct dijkstraResult {
    std::vector<double> dist;
    std::vector<node_id_t> prev;
};

dijkstraResult dijkstras(node_id_t startNode, std::vector<std::vector<double>>& matrix);

bool allVisited(const std::vector<bool>& visited);

bool dfsConnected(std::vector<std::vector<double>>& matrix);

bool bfsConnected(std::vector<std::vector<double>>& matrix);

std::vector<node_id_t> makePath(node_id_t target, const std::vector<node_id_t>& prev);

void printPath(node_id_t startNode, node_id_t targetNode, const dijkstraResult& result, const meta_t& meta);

void printMatrix(std::vector<std::vector<double>>& matrix);


#endif //LABB1_FUNCTIONS_H
