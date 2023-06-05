//
// Created by Pascal Charpentier on 2023-06-02.
//

#include "Graphe.h"
#include "GrapheTest.h"
#include "Graphe_algorithmes.h"
#include "gtest/gtest.h"

TEST_F(GrapheTest, exploreGrapheDFS_1){
    std::stack<size_t> attendu ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreGrapheDFS(g1)) ;
}

TEST_F(GrapheTest, exploreGrapheDFS_3) {
    std::stack<size_t> attendu ;
    attendu.push(2) ;
    attendu.push(1) ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreGrapheDFS(g3)) ;
}

TEST_F(GrapheTest, exploreBFS_graphe3_depart0) {
    std::vector<size_t> attendu {3, 0, 1} ;
    EXPECT_EQ(attendu, exploreBFS(g3, 0)) ;
}

TEST_F(GrapheTest, kosaraju_graphe_6) {
    std::set<std::set<size_t>> attendu {{0, 1, 2}, {3, 4, 5}} ;
    EXPECT_EQ(attendu, kosaraju(g6)) ;
}
