//
// Created by Pascal Charpentier on 2023-06-01.
//

#include "Graphe_algorithmes.h"

/**
 * @namespace anonyme: comprend un type et des fonctions privées à ce fichier.  Ce sont des fonctions auxiliaires servant
 * à faciliter l'écriture des algorithmes standards des graphes.
 */

namespace {

/**
 * @struct InfoDFS Type définissant une structure de données auxiliaire pour les visites en profondeur d'un objet graphe.
 * Elle permet d'alléger l'écriture de la fonction auxExploreRecursifDFS qui explore en profondeur un graphe à partir d'un sommet
 * donné.  Elle contient les champs suivants:
 *
 * graphe: l'objet graphe que l'on parcourt.
 *
 * abandonnes: une pile contenant les sommets ayant été visités, en ordre d'abandon.  C'est donc le résultat principal d'une
 * exploration en profondeur.
 *
 * visites: un vecteur de bool.  Si visite[x] est true, alors le sommet x a déjà été visité.
 *
 * Initialisation: lors du PREMIER appel à auxExploreRecursifDFS sur un objet graphe donné, le struct InfoDFS doit être initialisé
 * comme suit:
 *
 * graphe: doit recevoir évidemment une référence à l'objet graphe visité.
 * abandonnes: vide.  Aucun sommet n'a été visité ni abandonné.
 * visites: tous false puisqu'aucun sommet n'a été visité.
 *
 * Lors des appels subséquents à auxExploreRecursifDFS, le vecteur visites devrait en général être non touché: on ne veut jamais
 * revisiter des sommets déjà visités.
 *
 * Par-contre, dépendemment de l'algorithme, la pile abandonnes peu ou non être modifiée: si on veut seulement explorer
 * le graphe au complet, comme dans exploreRecursifGrapheDFS, on ne touche pas à la pile puisqu'on veut accumuler tous les noeuds
 * du graphe éventuellement.  Si on veut connaître les CFC, comme dans kosaraju, alors il faut vider la pile abandonnes
 * entre chaque appel, puisque après un appel à auxExploreRecursifDFS, la pile contient une CFC.
 */

    using InfoDFS =  struct infoDFS {
        Graphe graphe ;
        std::stack<size_t> abandonnes ;
        std::vector<bool> visites ;

        explicit infoDFS(const Graphe& g) : graphe(g), abandonnes(), visites(g.taille(), false) {}
    } ;

    /**
     * Fonction auxiliaire utilisée dans Dijkstra.  Elle balaye les noeuds non-résolus à la recherche de celui qui a une
     * distance minimale.  Ce noeud est retiré des non-résolus: il sera le prochain noeud résolu.
     * @param nonResolus std::set comprenant la liste des sommets non-résolus.
     * @param distances Vecteur comprenant les distances mises à jour.
     * @return Le numéro du prochain sommet résolu.
     */
    size_t localiserSommetMinimal(std::set<size_t> nonResolus, std::vector<double> distances) {
        auto temp = std::numeric_limits<double>::infinity() ;
        size_t indexMin = *nonResolus.begin();

        for (auto cle: nonResolus)
            if (distances.at(cle) < temp) indexMin = cle ;
        return indexMin ;
    }

    /**
     * Relaxe le noeud voisin à partir du noeud courant.
     * @param voisin struct Arc un noeud adjacent au noeud courant
     * @param courant le numéro du sommet courant
     * @param res struct ResultatDijkstra comprenant les distances et les prédécesseurs. Mis à jour lors de la relaxation.
     */
    void relaxer(const Graphe::Arc& voisin, size_t courant, ResultatsDijkstra& res) {
        double temp = res.distances.at(courant) + voisin.poids ;
        if (temp < res.distances.at(voisin.destination)) {
            res.distances.at(voisin.destination) = temp ;
            res.predecesseurs.at(voisin.destination) = courant ;
        }
    }

    /**
     * Relaxe le noeud voisin à partir du noeud courant, utilisant une file prioritaire pour les distances
     * @param voisin struct Arc, noeud voisin
     * @param courant Numéro du noeud courant
     * @param resultat Dans cette structure, les prédécesseurs seront mis à jour
     * @param nonResolus dans cette structure les distances seront mises à jour
     */
    void relaxerFilePrioritaire(Graphe::Arc voisin, size_t courant, ResultatsDijkstra& resultat, FilePrioritaire<double>& nonResolus) {
        double temp = nonResolus.lireClePourIndex(courant) + voisin.poids ;
        if (temp < nonResolus.lireClePourIndex(voisin.destination)) {
            nonResolus.reduireCle(voisin.destination, temp) ;
            resultat.predecesseurs.at(voisin.destination) = courant ;
        }
    }

    /**
     * Transfère le contenu d'une pile dans un set, en vidant la pile.
     * @tparam T Type d'éléments de la pile
     * @param pile
     * @return Un set contenant tous les éléments de la pile.
     * @post La pile est VIDE à la fin
     */
    template<typename T>
    std::set<T> transfererPileVersSet(std::stack<size_t> &pile) {
        std::set<T> valeurRetour ;

        while (!pile.empty()) {
            valeurRetour.insert(pile.top()) ;
            pile.pop() ;
        }

        return valeurRetour ;
    }

    /**
     * Explore un graphe en profondeur à partir d'une sommet donné.
     * @param donneesDFS struct InfoDFS contenant le graphe à explorer, une pile qui recevra les noeuds abandonnées et un vecteur
     * de bool indiquant quels noeuds ont été visités.  Voir Graphe_algorithme.h pour une description complète.
     * @param depart Le numéro du sommet de départ à explorer.
     * @pre ATTENTION: Si le numéro de sommet est non-valide, le comportement
     * sera non défini.  La validité du paramètre départ est la responsabilité de l'appeleur!!!
     */
    void auxExploreRecursifDFS(InfoDFS& donneesDFS, size_t depart) {
        if (donneesDFS.visites.at(depart)) return ;

        donneesDFS.visites.at(depart) = true ;
        for (const auto& voisin: donneesDFS.graphe.enumererVoisins(depart))
            if (!donneesDFS.visites.at(voisin.destination)) auxExploreRecursifDFS(donneesDFS, voisin.destination) ;

        donneesDFS.abandonnes.push(depart) ;

    }


}



/**
 * Effectue une visite en profondeur d'un objet graphe.
 * @param graphe Le graphe à visiter
 * @return Un pile contenant les noeuds dans l'ordre où ils ont été abandonnés.  Donc le dernier noeud abandonné sera le
 * premier à sortir de la pile.
 */
std::stack<size_t> exploreRecursifGrapheDFS(const Graphe &graphe) {
    InfoDFS donneesDfs(graphe) ;

    for (size_t depart = 0; depart < graphe.taille(); ++depart)
        auxExploreRecursifDFS(donneesDfs, depart) ;

    return donneesDfs.abandonnes ;
}

/**
 * Effectue une visite en largeur d'un graphe à partir d'un noeud.
 * @param graphe Le graphe à explorer
 * @param depart Le numéro du sommet de départ.
 * @return Un vecteur contenant les prédécesseur de chacun des sommets accessibles durant cette visite.  Par définition,
 * le noeud de départ n'a jamais de prédécesseur.  Les autres noeuds sans prédécesseurs ne sont pas accessibles à partir
 * du départ.  L'absence de prédécesseur est indiquée par la valeur graphe.taille() qui ne correspond à aucun sommet.
 * @except std::invalid_argument si le numéro de départ n'est pas dans le graphe, ou si le graphe est vide
 */
std::vector<size_t> exploreBFS(const Graphe &graphe, size_t depart) {
    if (!graphe.sommetExiste(depart)) throw std::invalid_argument("exploreBFS: sommet invalide ou graphe vide") ;

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

/**
 * Explore un objet graphe en profondeur à partir d'un sommet de départ.
 * @param graphe Objet graphe à visiter
 * @param depart Entier positif ou nul désignant le sommet de départ
 * @return La piles des sommets abandonnés.
 */
std::stack<size_t> exploreIteratifDFS(const Graphe& graphe, size_t depart) {
    std::stack<size_t> abandonnes ;
    std::stack<size_t> encours ;
    std::vector<bool> visites(graphe.taille(), false) ;

    encours.push(depart) ;
    visites.at(depart) = true ;

    while (!encours.empty()) {
        auto courant = encours.top() ;
        encours.pop() ;
        auto liste = graphe.enumererVoisins(courant) ;
        auto it = std::find_if(liste.begin(), liste.end(), [&visites](Graphe::Arc e){return !visites[e.destination];}) ;
        while ( it != liste.end()) {
            encours.push(courant) ;
            courant = it->destination ;
            visites.at(courant) = true ;
            liste = graphe.enumererVoisins(courant) ;
            it = std::find_if(liste.begin(), liste.end(), [&visites](Graphe::Arc e){return !visites[e.destination];}) ;
        }
        abandonnes.push(courant) ;
    }
    return abandonnes ;
}



/**
 * Énumère les composantes fortement connexes d'un graphe.
 * @param graphe Objet graphe à analyser
 * @return Un set.  Chaque élément de ce set est lui-même un set contenant les sommets d'une composante fortement connexe.
 */
std::set<std::set<size_t>> kosaraju(const Graphe& graphe) {
    std::set<std::set<size_t>> composantes ;

    std::stack<size_t> pile = exploreRecursifGrapheDFS(graphe.grapheInverse()) ;

    InfoDFS data(graphe) ;
    while (!pile.empty()) {
        size_t depart = pile.top() ;
        pile.pop() ;

        if (!data.visites.at(depart)) {
            auxExploreRecursifDFS(data, depart) ; // La CFC résultante sera stockée dans la pile data.abandonnes
            composantes.insert(transfererPileVersSet<size_t>(data.abandonnes)) ; // La pile est vidée et transférée
        }
    }

    return composantes ;
}

/**
 * Effectue le tri topologique de l'objet graphe.  Cette implantation utilise l'algorithme vu dans le cours où l'on
 * localise successivement les sommets puits et on les retire du graphe.  Attention, il y a ici une petite subtilité...
 * Lorsqu'on retire un sommet du graphe, les autres sont automatiquement renumérotés de manière à préserver la numérotation
 * successive des sommets.  Il faut donc une structure de données supplémentaire, un index afin de stocker dans le vecteur
 * des résultats le numéro original du sommet!!!
 * @param graphe Objet graphe à trier
 * @return Un vecteur comprenant les numéros de sommet dans l'ordre topologique
 * @except std::invalid_argument si le graphe est cyclique
 */
std::vector<size_t> triTopologique(Graphe graphe) {

    std::vector<size_t> tri(graphe.taille(), graphe.taille()) ;
    std::vector<size_t> index(graphe.taille()) ;
    std::iota(index.begin(), index.end(), 0) ;
    size_t restants = graphe.taille() ;

    while (restants > 0) {
        size_t i = 0 ;

        while (i < graphe.taille() && graphe.ariteSortie(i) != 0) ++i ;
        if (i == graphe.taille())
            throw std::invalid_argument("Tri topologique: tentative de trier un graphe cyclique") ;

        graphe.retirerSommet(i) ;
        tri.at(-- restants) = index.at(i) ;
        index.erase(index.begin() + static_cast<std::vector<size_t>::difference_type> (i)) ;
    }
    return tri ;
}

/**
 * Utilise l'algorithme de Dijkstra pour trouver les trajets les plus courts partant d'un sommet départ vers tous les
 * autres sommets, dans un graphe orienté et pondéré.
 * @param graphe Objet graphe à analyser, utilisant des listes d'adjacences.
 * @param depart Numéro du sommet de départ.
 * @return Un struct contenant un vecteur de prédécesseurs, permettant de reconstituer les chemins, et un vecteur des
 * distances.
 * @pre Le sommet départ doit se trouver dans le graphe, sinon le comportement est non défini.
 */
ResultatsDijkstra dijkstra(const Graphe& graphe, size_t depart) {
    ResultatsDijkstra resultats(graphe.taille(), depart) ;

    std::set<size_t> nonResolus ;
    for (size_t i = 0; i < graphe.taille(); ++i) nonResolus.insert(i) ;

    while (!nonResolus.empty()) {
        auto courant = localiserSommetMinimal(nonResolus, resultats.distances) ;
        nonResolus.erase(courant) ;
        for (auto voisin: graphe.enumererVoisins(courant)) relaxer(voisin, courant, resultats) ;
    }
    return resultats ;
}


/**
 * Même algorithme que la fonction précédente, mais version plus efficace utilisant une file prioritaire.
 * @param graphe Objet graphe à analyser
 * @param depart Numéro du sommet de départ
 * @return Un struct contenant un vecteur de prédécesseurs et un vecteur de distances
 * @pre Le sommet de départ doit se trouver dans le graphe, sinon le comportement est non-défini
 */
ResultatsDijkstra dijkstraFilePrioritaire(const Graphe& graphe, size_t depart) {
    ResultatsDijkstra resultats(graphe.taille(), depart) ;

    FilePrioritaire<double> nonResolus(resultats.distances) ;
    while (!nonResolus.estVide()) {
        auto courant = nonResolus.lireIndexMinimum() ;
        nonResolus.extraireMinimum() ;
        for (auto voisin: graphe.enumererVoisins(courant)) relaxerFilePrioritaire(voisin, courant, resultats, nonResolus) ;
    }
    resultats.distances = nonResolus.genererIndex() ;
    return resultats ;
}
