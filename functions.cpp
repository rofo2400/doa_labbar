//
// Created by fonse on 4/20/2026.
//
#include "functions.h"
#include "reader.h"

#include <iostream>
#include <limits>


//Funktion som konverterar adjacency list från parse_file till adjacency matrix
std::vector<std::vector<double> > convertToMatrix(const adjacency_list_t &list) {
    const int sz = list.first.size();
    //värde för att representera att det inte finns en kant
    const double noEdge = std::numeric_limits<double>::infinity(); //https://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf

    std::vector<std::vector<double> > matrix(sz, std::vector<double>(sz, noEdge)); //fyller en 2d sz*sz matris med värdet ∞

    for (int i = 0; i < sz; i++) {
        matrix[i][i] = 0.0; //fyller matrisens diagonal med 0.0 för att sätta vikten från varje punkt till sig själv till 0.0
    }
    for (const auto& e: list.second) {
        matrix[e.n1][e.n2] = e.weight; //fyller matrisens vikter från varje n1 till n2.
    }
    return matrix;
}

void dfs(node_id_t startNode, std::vector<std::vector<double>> &matrix, std::vector<bool>& visited) {
    const double noEdge = std::numeric_limits<double>::infinity();
    //---Test utskrifter - Ta bort sen
    std::cout << "dfs startNode = " << startNode
              << ", matrix.size = " << matrix.size()
              << ", visited.size = " << visited.size()
              << "\n";

    if (startNode < 0 || startNode >= matrix.size()) {
        std::cout << "ERROR: startNode out of range\n";
        return;
    }
    //--- slut testutskrifter

    visited[startNode] = true; //sätter startnod till besökt
    for (int i = 0; i < matrix.size(); i++) {
        if (!visited[i] && matrix[startNode][i] != noEdge) { //kollar om nod i är besökt och om det finns en kant mellan aktuella noden och nod i
            dfs(i, matrix, visited); //kallar på funktionen rekursivt
        }
    }
}

//itererar genom visited och kollar om någon nod inte är visited -> isf returneras false (ej sammanhängande)
bool allVisited(const std::vector<bool>& visited) {
    for (auto v : visited) {
        if (!v) return false;
    }
    return true;
}

bool dfsConnected(std::vector<std::vector<double>> &matrix) {
    std::vector<bool> visited(matrix.size(), false);
    dfs(0, matrix, visited);
    if (!allVisited(visited)) {
        return false;
    }
    return true;
}

void printPath(node_id_t startNode, std::vector<std::vector<double>> &matrix) {
}

void printMatrix(std::vector<std::vector<double>> &matrix) {
}
