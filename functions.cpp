//
// Created by fonse on 4/20/2026.
//
#include "functions.h"

#include <algorithm>

#include "reader.h"

#include <iostream>
#include <limits>
#include <queue>


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

    visited[startNode] = true; //sätter startnod till besökt
    for (int i = 0; i < matrix.size(); i++) {
        if (!visited[i] && (matrix[startNode][i] != noEdge)) { //kollar om nod i är besökt och om det finns en kant mellan aktuella noden och nod i
            dfs(i, matrix, visited); //kallar på funktionen rekursivt
        }
    }
}

void bfs(node_id_t startNode, std::vector<std::vector<double>>& matrix, std::vector<bool>& visited) {
    const double noEdge = std::numeric_limits<double>::infinity(); //representerar ingen kant med infinity
    std::queue<int> q;
    visited[startNode] = true; //sätter startnoden till besökt
    q.push(startNode); //lägger till startnod i kön
    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        for (int i = 0; i < matrix.size(); i++) {
            if (!visited[i] && (matrix[currentNode][i] != noEdge)) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

dijkstraResult dijkstras(node_id_t startNode, std::vector<std::vector<double>> &matrix) {
    const double noEdge = std::numeric_limits<double>::infinity(); //representerar ingen kant med infinity
    auto undef = -1;
    auto sz = matrix.size();
    using nodeInfo = std::pair<weight_t, node_id_t>; //distans och nod-ID

    std::priority_queue<nodeInfo, std::vector<nodeInfo>, std::greater<nodeInfo>> Q; //skapar en pq med minHeap som innehåller distans och nod-ID. lägst distans/vikt hamnar först
    std::vector<double> dist(sz, noEdge); //fyller vektorn med INF
    std::vector<node_id_t> prev(sz, undef); //fyller vektorn med -1

    dist[startNode] = 0;
    Q.push({0, startNode});
    while (!Q.empty()) {
        auto [currentDist, currentNode] = Q.top(); //hämtar distans och nod-id från kön (lägst vikt)
        Q.pop();

        //kontroll för om det redan finns en kortare väg till currentNode
        if (currentDist > dist[currentNode]) {
            continue;
        }
        for (int i = 0; i < sz; i++) {
            if (matrix[currentNode][i] != noEdge) { //kollar om det finns en kant från currentNode till i
                weight_t alternative = dist[currentNode] + matrix[currentNode][i]; //kostnad av att gå från start till i via currentNode
                if (alternative < dist[i]) { //om kostnaden av att gå via currentNode är lägre än tidigare kortaste väg
                    prev[i] = currentNode; //föregående nod blir currentNode
                    dist[i] = alternative; //kortaste vägen till i blir via currentNode
                    Q.push({alternative,i}); //lägger till den giltiga noden i kön
                }
            }
        }
    }
    return dijkstraResult{dist,prev};
}

//itererar genom visited och kollar om någon nod inte är visited -> isf returneras false (ej sammanhängande)
bool allVisited(const std::vector<bool>& visited) {
    for (auto v : visited) {
        if (!v) return false;
    }
    return true;
}

bool dfsConnected(node_id_t startNode, std::vector<std::vector<double>> &matrix) {
    std::vector<bool> visited(matrix.size(), false);
    dfs(startNode, matrix, visited);
    if (!allVisited(visited)) {
        return false;
    }
    return true;
}

bool bfsConnected(node_id_t startNode, std::vector<std::vector<double>> &matrix) {
    std::vector<bool> visited(matrix.size(), false);
    bfs(startNode, matrix, visited);
    if (!allVisited(visited)) {
        return false;
    }
    return true;
}

std::vector<node_id_t> makePath(node_id_t targetNode, const std::vector<node_id_t> &prev) {
    std::vector<node_id_t> path;
    auto undef = -1;
    node_id_t currentNode = targetNode;

    while (currentNode != undef) {
        path.push_back(currentNode);
        currentNode = prev[currentNode];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void printPath(node_id_t startNode, node_id_t targetNode, const dijkstraResult& result, const meta_t& meta) {

    std::cout << "Shortest path from" << meta.at(startNode) << " to" << meta.at(targetNode) << ": \n";

    if (result.dist[targetNode] == std::numeric_limits<double>::infinity()) {
        std::cout << "There is no path to" << meta.at(targetNode) << ".\n";
        return;
    }
    auto path = makePath(targetNode, result.prev);


    for (int i = 0; i < path.size(); i++) {
        std::cout << meta.at(path[i]);
        if (i + 1 < path.size()) { //skriver endast ut pilen om det inte är sista
            std::cout << " ->" << "\n";
        }
    }

    std::cout << "\n Total distans: " << result.dist[targetNode] << "\n";
}

void printMatrix(std::vector<std::vector<double>> &matrix) {
}
