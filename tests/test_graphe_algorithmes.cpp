//
// Created by Pascal Charpentier on 2023-06-02.
//

#include "Graphe.h"
#include "GrapheTest.h"
#include "Graphe_algorithmes.h"
#include "gtest/gtest.h"

TEST_F(GrapheTest, exploreGrapheDFS_0) {
    std::stack<size_t> attendu ;
    EXPECT_EQ(attendu, exploreRecursifGrapheDFS(g0)) ;
}

TEST_F(GrapheTest, exploreGrapheDFS_1){
    std::stack<size_t> attendu ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreRecursifGrapheDFS(g1)) ;
}

TEST_F(GrapheTest, exploreGrapheDFS_2) {
    std::stack<size_t> attendu ;
    attendu.push(1) ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreRecursifGrapheDFS(g2)) ;
}

TEST_F(GrapheTest, exploreGrapheDFS_3) {
    std::stack<size_t> attendu ;
    attendu.push(2) ;
    attendu.push(1) ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreRecursifGrapheDFS(g3)) ;
}

TEST_F(GrapheTest, exploreBFS_g1_depart_0) {
    std::vector<size_t> attendu {1} ;
    EXPECT_EQ(attendu, exploreBFS(g1, 0)) ;
}

TEST_F(GrapheTest, exploreBFS_g3_depart_invalide) {
    EXPECT_THROW(exploreBFS(g3, 10), std::invalid_argument) ;
}

TEST_F(GrapheTest, exploreBFS_g3_depart_1) {
    std::vector<size_t> attendu {3, 3, 1} ;
    EXPECT_EQ(attendu, exploreBFS(g3, 1)) ;
}

TEST_F(GrapheTest, exploreBFS_g3_depart_2) {
    std::vector<size_t> attendu {3, 3, 3} ;
    EXPECT_EQ(attendu, exploreBFS(g3, 2)) ;
}

TEST_F(GrapheTest, exploreBFS_graphe3_depart_0) {
    std::vector<size_t> attendu {3, 0, 1} ;
    EXPECT_EQ(attendu, exploreBFS(g3, 0)) ;
}

TEST_F(GrapheTest, exploreBFS_graphe6_depart_0) {
    std::vector<size_t> attendu {6, 0, 1, 2, 3, 4} ;
    EXPECT_EQ(attendu, exploreBFS(g6, 0)) ;
}

TEST_F(GrapheTest, exploreBFS_graphe6_depart_2) {
    std::vector<size_t> attendu {2, 0, 6, 2, 3, 4} ;
    EXPECT_EQ(attendu, exploreBFS(g6, 2)) ;
}

TEST_F(GrapheTest, exploreBFS_graphe6_depart_3) {
    std::vector<size_t> attendu {6, 6, 6, 6, 3, 4} ;
    EXPECT_EQ(attendu, exploreBFS(g6, 3)) ;
}

TEST_F(GrapheTest, exploreDFS_1) {
    std::stack<size_t> attendu ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreIteratifDFS(g1, 0)) ;
}

TEST_F(GrapheTest, exploreDFS_2) {
    std::stack<size_t> attendu ;
    attendu.push(1) ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreIteratifDFS(g2, 0)) ;
}

TEST_F(GrapheTest, exploreDFS_3) {
    std::stack<size_t> attendu ;
    attendu.push(2) ;
    attendu.push(1) ;
    attendu.push(0) ;
    EXPECT_EQ(attendu, exploreIteratifDFS(g3, 0)) ;
}

TEST_F(GrapheTest, kosaraju) {
    std::set<std::set<size_t>>
        attendu6 {{0, 1, 2}, {3, 4, 5}},
        attendu3{{0}, {1}, {2}},
        attendu2{{0}, {1}},
        attendu1{{0}},
        attenduvide {};

    EXPECT_EQ(attenduvide, kosaraju(g0)) ;
    EXPECT_EQ(attendu1, kosaraju(g1)) ;
    EXPECT_EQ(attendu2, kosaraju(g2)) ;
    EXPECT_EQ(attendu3, kosaraju(g3)) ;
    EXPECT_EQ(attendu6, kosaraju(g6)) ;
}

TEST_F(GrapheTest, triTopologique_0) {
    EXPECT_EQ(std::vector<size_t>{}, triTopologique(g0)) ;
}

TEST_F(GrapheTest, triTopologique_1) {
    EXPECT_EQ(std::vector<size_t>{0}, triTopologique(g1)) ;
}

TEST_F(GrapheTest, triTopologique_3) {
    std::vector<size_t> attendu {0, 1, 2} ;
    EXPECT_EQ(attendu, triTopologique(g3)) ;
}

TEST_F(GrapheTest, triTopologique_6) {
    EXPECT_THROW(triTopologique(g6), std::invalid_argument) ;
}

TEST_F(GrapheTest, dijkstra_6_depart_0) {
    std::vector<size_t> pred {6, 0, 1, 2, 3, 4} ;
    std::vector<double> dist {0, 1, 2, 3, 4, 5} ;
    auto resultat = dijkstra(g6, 0) ;
    EXPECT_EQ(pred, resultat.predecesseurs) ;
    EXPECT_EQ(dist, resultat.distances) ;
}
