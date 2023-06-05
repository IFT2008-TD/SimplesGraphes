//
// Created by Pascal Charpentier on 2023-06-01.
//

#ifndef SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
#define SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H

#include "Graphe.h"

#include <stack>
#include <set>
#include <queue>

using infoDFS =  struct infoDFS {
    Graphe graphe ;
    std::stack<size_t> abandonnes ;
    std::vector<bool> visites ;

    explicit infoDFS(const Graphe& g) : graphe(g), abandonnes(), visites(g.taille(), false) {}
} ;

std::stack<size_t> exploreGrapheDFS(const Graphe& graphe) ;

std::vector<size_t> exploreBFS(const Graphe& graphe, size_t depart) ;

std::set<std::set<size_t>> kosaraju(const Graphe& graphe) ;

std::vector<size_t> triTopologique(const Graphe& graphe) ;

template <typename T>
std::set<T> transfererPileVersSet(std::stack<size_t>& pile) ;





#endif //SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
