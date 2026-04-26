//
// Created by fonse on 4/20/2026.
//

#ifndef LABB1_FUNCTIONS_H
#define LABB1_FUNCTIONS_H

#include <vector>

#include "reader.h"

std::vector<std::vector<double>> convertToMatrix(const adjacency_list_t& list);

void dfs(node_id_t startNode, std::vector<std::vector<double>>& matrix, std::vector<bool>& visited);

bool allVisited(const std::vector<bool>& visited);

bool dfsConnected(std::vector<std::vector<double>>& matrix);

void printPath(node_id_t startNode, std::vector<std::vector<double>>& matrix);

void printMatrix(std::vector<std::vector<double>>& matrix);


#endif //LABB1_FUNCTIONS_H
