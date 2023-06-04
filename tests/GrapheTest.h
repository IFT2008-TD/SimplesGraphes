//
// Created by Pascal Charpentier on 2023-06-02.
//

#ifndef SIMPLESGRAPHES_GRAPHETEST_H
#define SIMPLESGRAPHES_GRAPHETEST_H

#include "Graphe.h"
#include "gtest/gtest.h"

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
