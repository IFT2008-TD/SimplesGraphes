//
// Created by Pascal Charpentier on 2023-06-01.
//

#ifndef SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
#define SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H

#include "Graphe.h"
#include "FilePrioritaire.h"

#include <stack>
#include <set>
#include <queue>
#include <numeric>
#include <limits>


using ResultatsDijkstra = struct resultatsDijkstra {
    std::vector<size_t> predecesseurs ;
    std::vector<double> distances ;

    explicit resultatsDijkstra(size_t n, size_t d) : predecesseurs(n, n), distances(n, std::numeric_limits<double>::infinity()) {
        distances.at(d) = 0 ;
    } ;
};

// Déclarations des fonctions accessibles

std::stack<size_t> exploreRecursifGrapheDFS(const Graphe& graphe) ;

std::vector<size_t> exploreBFS(const Graphe& graphe, size_t depart) ;

std::stack<size_t> exploreIteratifDFS(const Graphe& graphe, size_t depart) ;

std::set<std::set<size_t>> kosaraju(const Graphe& graphe) ;

std::vector<size_t> triTopologique(const Graphe& graphe) ;

ResultatsDijkstra dijkstra(const Graphe& graphe, size_t depart) ;

ResultatsDijkstra dijkstraFilePrioritaire(const Graphe& graphe, size_t depart) ;







#endif //SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
