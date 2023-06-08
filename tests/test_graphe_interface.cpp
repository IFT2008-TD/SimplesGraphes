//
// Created by Pascal Charpentier on 2023-06-01.
//

#include "Graphe.h"
#include "GrapheTest.h"
#include "gtest/gtest.h"

TEST(Graphe, constructeur) {
    EXPECT_NO_THROW(Graphe g) ;
}

TEST(Graphe, graphe_vide) {
    Graphe g ;
    EXPECT_FALSE(g.sommetExiste(1)) ;
}

TEST(Graphe, graphe_un_sommet_sommet_existe) {
    Graphe g(1) ;
    EXPECT_TRUE(g.sommetExiste(0)) ;
    EXPECT_FALSE(g.sommetExiste(1)) ;
}

TEST(Graphe, graphe_deux_sommets_sans_arc) {
    Graphe g(2) ;
    EXPECT_TRUE(g.sommetExiste(0)) ;
    EXPECT_TRUE(g.sommetExiste(1)) ;
    EXPECT_FALSE(g.arcExiste(0, 1)) ;
    EXPECT_FALSE(g.arcExiste(1, 0)) ;
}




TEST_F(GrapheTest, graphe_trois_sommets_ajouter_arc) {

    EXPECT_TRUE(g3.arcExiste(0, 1)) ;
    EXPECT_TRUE(g3.arcExiste(1, 2)) ;
    EXPECT_FALSE(g3.arcExiste(1, 0)) ;
    EXPECT_FALSE(g3.arcExiste(2, 1)) ;
    EXPECT_FALSE(g3.arcExiste(0, 2)) ;
    EXPECT_FALSE(g3.arcExiste(2, 0)) ;
}

TEST_F(GrapheTest, liste_adjacence) {
    std::list<Graphe::Arc> attendu {{1, 1.0}} ;
    std::list<Graphe::Arc> vide {} ;
    EXPECT_EQ(attendu, g3.enumererVoisins(0)) ;
    EXPECT_EQ(vide, g3.enumererVoisins(2)) ;
}

TEST_F(GrapheTest, arite_entree) {
    EXPECT_EQ(0, g3.ariteEntree(0)) ;
    EXPECT_EQ(1, g3.ariteEntree(1)) ;
    EXPECT_EQ(1, g3.ariteEntree(2)) ;
}

TEST_F(GrapheTest, arite_sortie) {
    EXPECT_EQ(0, g1.ariteSortie(0)) ;
    EXPECT_EQ(1, g2.ariteSortie(0)) ;
    EXPECT_EQ(0, g2.ariteSortie(1)) ;

}

TEST_F(GrapheTest, inverse) {
    Graphe inv = g3.grapheInverse() ;
    EXPECT_TRUE(inv.arcExiste(2, 1)) ;
    EXPECT_TRUE(inv.arcExiste(1, 0)) ;
    EXPECT_FALSE(inv.arcExiste(2, 0)) ;
}

TEST_F(GrapheTest, retirerSommet_g1) {
    g1.retirerSommet(0) ;
    EXPECT_EQ(0, g1.taille()) ;
    EXPECT_FALSE(g1.sommetExiste(0)) ;
}

TEST_F(GrapheTest, retirerSommet_g2) {
    g2.retirerSommet(1) ;
    EXPECT_EQ(1, g2.taille()) ;
    EXPECT_TRUE(g2.sommetExiste(0)) ;
    EXPECT_FALSE(g2.sommetExiste(1)) ;
}

TEST_F(GrapheTest, retirerSommet_g3_sommet1) {
    g3.retirerSommet(1) ;
    EXPECT_EQ(2, g3.taille()) ;
    EXPECT_TRUE(g3.sommetExiste(0)) ;
    EXPECT_TRUE(g3.sommetExiste(1)) ;
    EXPECT_FALSE(g3.arcExiste(0, 1)) ;
    EXPECT_FALSE(g3.arcExiste(1, 0)) ;
}

TEST_F(GrapheTest, retirerSommet_g3_sommet0) {
    g3.retirerSommet(0) ;
    EXPECT_EQ(2, g3.taille()) ;
    EXPECT_TRUE(g3.sommetExiste(0)) ;
    EXPECT_TRUE(g3.sommetExiste(1)) ;
    EXPECT_TRUE(g3.arcExiste(0, 1)) ;
}

TEST_F(GrapheTest, retirerArc_g2_01) {
    g2.retirerArc(0, 1) ;
    EXPECT_EQ(0, g2.ariteSortie(0)) ;
    EXPECT_EQ(0, g2.ariteEntree(1)) ;
    EXPECT_FALSE(g2.arcExiste(0, 1)) ;
    EXPECT_EQ(2, g2.taille()) ;
}
