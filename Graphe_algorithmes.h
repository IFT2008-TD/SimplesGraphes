//
// Created by Pascal Charpentier on 2023-06-01.
//

#ifndef SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
#define SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H

#include "Graphe.h"

#include <stack>
#include <set>
#include <queue>

/**
 * @struct infoDFS Type définissant une structure de données auxiliaire pour les visites en profondeur d'un objet graphe.
 * Elle permet d'alléger l'écriture de la fonction auxExploreDFS qui explore en profondeur un graphe à partir d'un sommet
 * donné.  Elle contient les champs suivants:
 *
 * graphe: l'objet graphe que l'on parcourt.
 *
 * abandonnes: une pile contenant les sommets ayant été visités, en ordre d'abandon.  C'est donc le résultat principal d'une
 * exploration en profondeur.
 *
 * visites: un vecteur de bool.  Si visite[x] est true, alors le sommet x a déjà été visité.
 *
 * Initialisation: lors du PREMIER appel à auxExploreDFS sur un objet graphe donné, le struct infoDFS doit être initialisé
 * comme suit:
 *
 * graphe: doit recevoir évidemment une référence à l'objet graphe visité.
 * abandonnes: vide.  Aucun sommet n'a été visité ni abandonné.
 * visites: tous false puisqu'aucun sommet n'a été visité.
 *
 * Lors des appels subséquents à auxExploreDFS, le vecteur visites devrait en général être non touché: on ne veut jamais
 * revisiter des sommets déjà visités.
 *
 * Par-contre, dépendemment de l'algorithme, la pile abandonnes peu ou non être modifiée: si on veut seulement explorer
 * le graphe au complet, comme dans exploreGrapheDFS, on ne touche pas à la pile puisqu'on veut accumuler tous les noeuds
 * du graphe éventuellement.  Si on veut connaître les CFC, comme dans kosaraju, alors il faut vider la pile abandonnes
 * entre chaque appel, puisque après un appel à auxExploreDFS, la pile contient une CFC.
 */
using infoDFS =  struct infoDFS {
    Graphe graphe ;
    std::stack<size_t> abandonnes ;
    std::vector<bool> visites ;

    explicit infoDFS(const Graphe& g) : graphe(g), abandonnes(), visites(g.taille(), false) {}
} ;

// Déclarations des fonctions accessibles

std::stack<size_t> exploreGrapheDFS(const Graphe& graphe) ;

std::vector<size_t> exploreBFS(const Graphe& graphe, size_t depart) ;

std::stack<size_t> exploreDFS(Graphe graphe, size_t depart) ;

std::set<std::set<size_t>> kosaraju(const Graphe& graphe) ;

std::vector<size_t> triTopologique(const Graphe& graphe) ;

template <typename T>
std::set<T> transfererPileVersSet(std::stack<size_t>& pile) ;





#endif //SIMPLESGRAPHES_GRAPHE_ALGORITHMES_H
