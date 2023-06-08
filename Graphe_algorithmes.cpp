//
// Created by Pascal Charpentier on 2023-06-01.
//

#include "Graphe_algorithmes.h"


/**
 * Explore un graphe en profondeur à partir d'une sommet donné.
 * @param donneesDFS struct infoDFS contenant le graphe à explorer, une pile qui recevra les noeuds abandonnées et un vecteur
 * de bool indiquant quels noeuds ont été visités.  Voir Graphe_algorithme.h pour une description complète.
 * @param depart Le numéro du sommet de départ à explorer. ATTENTION: Si le numéro de sommet est non-valide, le comportement
 * sera non défini.  La validité du paramètre départ est la responsabilité de l'appeleur!!!
 */
void auxExploreDFS(infoDFS& donneesDFS, size_t depart) {
    if (donneesDFS.visites.at(depart)) return ;

    donneesDFS.visites.at(depart) = true ;
    for (const auto& voisin: donneesDFS.graphe.enumererVoisins(depart))
        if (!donneesDFS.visites.at(voisin.destination)) auxExploreDFS(donneesDFS, voisin.destination) ;

    donneesDFS.abandonnes.push(depart) ;

}

/**
 * Effectue une visite en profondeur d'un objet graphe.
 * @param graphe Le graphe à visiter
 * @return Un pile contenant les noeuds dans l'ordre où ils ont été abandonnés.  Donc le dernier noeud abandonné sera le
 * premier à sortir de la pile.
 */
std::stack<size_t> exploreGrapheDFS(const Graphe &graphe) {
    infoDFS donneesDfs(graphe) ;

    for (size_t depart = 0; depart < graphe.taille(); ++depart)
        auxExploreDFS(donneesDfs, depart) ;

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

std::stack<size_t> exploreDFS(Graphe graphe, size_t depart) {
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
 * Énumère les composantes fortement connexes d'un graphe.
 * @param graphe Objet graphe à analyser
 * @return Un set.  Chaque élément de ce set est lui-même un set contenant les sommets d'une composante fortement connexe.
 */
std::set<std::set<size_t>> kosaraju(const Graphe& graphe) {
    std::set<std::set<size_t>> composantes ;

    // Générer le graphe inverse et l'explorer en profondeur, stocker les sommets dans l'objet pile.
    std::stack<size_t> pile = exploreGrapheDFS(graphe.grapheInverse()) ;

    // Explorer le graphe direct en partant des sommets stockés dans l'objet pile.
    infoDFS data(graphe) ;
    while (!pile.empty()) {
        size_t depart = pile.top() ;
        pile.pop() ;

        // Explorer en profondeur tout noeud non visité
        if (!data.visites.at(depart)) {
            auxExploreDFS(data, depart) ; // La CFC résultante sera stockée dans la pile data.abandonnes
            composantes.insert(transfererPileVersSet<size_t>(data.abandonnes)) ; // La pile est vidée et transférée
        }
    }

    return composantes ;
}
