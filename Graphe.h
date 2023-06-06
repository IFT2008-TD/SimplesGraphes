//
// Created by Pascal Charpentier on 2023-06-01.
//

#ifndef SIMPLESGRAPHES_GRAPHE_H
#define SIMPLESGRAPHES_GRAPHE_H

#include <initializer_list>
#include <vector>
#include <list>
#include <algorithm>

/**
 * @class Graphe
 *
 * Cette classe représente un graphe comportant n sommets.  Chaque sommet est identifié par un entier positif consécutif
 * à-partir de 0.
 *
 * Par-exemple, un graphe à 4 sommets contient obligatoirement les sommets: 0, 1 , 2, et 3.  Il ne peut y avoir de saut,
 * le graphe comportant des sommets 0, 1, 2, 4 et 5 ne pourrait pas exister puisque le sommet 3 serait manquant.
 *
 */
class Graphe {
public:

    // Chaque arête du graphe contient un sommet et une pondération.  Cette structure sert à emmagasiner ces données.

    struct Arc {
        size_t destination ;
        double poids ;

        Arc(size_t dest, double poids) : destination(dest), poids(poids) {}
        bool operator == (Arc rhs) const {return destination == rhs.destination && poids == rhs.poids; }
    };

    using Arc = struct Arc ;

public:

    explicit              Graphe(size_t nombre = 0) ;

    size_t                taille()                                     const  ;

    bool                  sommetExiste(size_t numero)                  const ;

    bool                  arcExiste(size_t depart, size_t destination) const ;

    const std::list<Arc>& enumererVoisins(size_t depart)               const ;

    size_t                ariteEntree(size_t sommet)                   const ;

    Graphe                grapheInverse()                              const ;


    void                  ajouterSommet() ;

    void                  retirerSommet(size_t sommet) ;

    void                  ajouterArc(size_t depart, size_t arrivee, double poids = 1.0) ;


private:
    
    std::vector<std::list<Arc>> listes ;


};

#endif //SIMPLESGRAPHES_GRAPHE_H
