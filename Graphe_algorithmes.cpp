//
// Created by Pascal Charpentier on 2023-06-01.
//

#include "Graphe_algorithmes.h"



void auxExploreDFS(infoDFS& data, size_t depart) {
    if (data.visites.at(depart)) return ;
    data.visites.at(depart) = true ;

    for (const auto& voisin: data.graphe.enumererVoisins(depart))
        if (!data.visites.at(voisin.destination)) auxExploreDFS(data, voisin.destination) ;

    data.abandonnes.push(depart) ;

}

std::stack<size_t> exploreGrapheDFS(const Graphe &graphe) {
    infoDFS data(graphe) ;
    for (size_t depart = 0; depart < graphe.taille(); ++depart)
        auxExploreDFS(data, depart) ;
    return data.abandonnes ;
}

std::vector<size_t> exploreBFS(const Graphe &graphe, size_t depart) {
    std::vector<size_t> predecesseurs(graphe.taille(), graphe.taille()) ;
    std::queue<size_t> attente ;
    std::vector<bool> visites(graphe.taille(), false) ;
    visites.at(depart) = true ;

    attente.push(depart) ;
    while (!attente.empty()) {
        auto courant = attente.front() ;
        attente.pop() ;
        for (auto voisin: graphe.enumererVoisins(courant)) {
            if (!visites.at(voisin.destination)) {
                attente.push(voisin.destination) ;
                visites.at(voisin.destination) = true ;
                predecesseurs.at(voisin.destination) = courant ;
            }
        }
    }
    return predecesseurs ;
}

std::set<std::set<size_t>> kosaraju(const Graphe& graphe) {
    std::set<std::set<size_t>> composantes ;

    Graphe inv = graphe.grapheInverse() ;
    std::stack<size_t> pile = exploreGrapheDFS(inv) ;
    infoDFS data(graphe) ;
    while (!pile.empty()) {
        size_t depart = pile.top() ;
        pile.pop() ;
        if (!data.visites.at(depart)) {
            auxExploreDFS(data, depart) ;
            composantes.insert(std::set<size_t>(data.visites.begin(), data.visites.end())) ;
        }
    }
}
