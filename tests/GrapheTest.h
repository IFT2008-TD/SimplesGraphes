//
// Created by Pascal Charpentier on 2023-06-02.
//

#ifndef SIMPLESGRAPHES_GRAPHETEST_H
#define SIMPLESGRAPHES_GRAPHETEST_H

#include "Graphe.h"
#include "gtest/gtest.h"

/**
 * @class GrapheTest
 *
 * Dispositif de test servant à mettre à l'épreuve nos algorithmes de graphe.  Il contient quelques graphes
 * préconstruits:
 *
 * g0 graphe vide
 * g1 graphe à un seul sommet
 * g2 graphe à deux sommets: 0 ---> 1
 * g3 graphe à trois sommets: 0 ---> 1 ---> 2
 * g6 graphe comportant 6 sommets.  Il y a un cycle 0->1->2->0, et un cycle 3->4->5->3 reliés par une arête 2->3.
 * Ce graphe a donc
 * deux composantes fortement connexes: {0, 1, 2} et {3, 4, 5}.
 */

class GrapheTest : public ::testing::Test {
protected:
    GrapheTest() : g0(0), g1(1), g2(2), g3(3), g6(6) {}

    void SetUp() override {
        g2.ajouterArc(0, 1) ;

        g3.ajouterArc(0, 1) ;
        g3.ajouterArc(1, 2) ;

        g6.ajouterArc(0, 1) ;
        g6.ajouterArc(1, 2) ;
        g6.ajouterArc(2, 0) ;
        g6.ajouterArc(3, 4) ;
        g6.ajouterArc(4, 5) ;
        g6.ajouterArc(5, 3) ;
        g6.ajouterArc(2, 3) ;
    }

    Graphe g0, g1, g2, g3, g6 ;

};




#endif //SIMPLESGRAPHES_GRAPHETEST_H
