//
// Created by Pascal Charpentier on 2023-06-01.
//

#include "Graphe.h"


/**
 * Construit un graphe comportant un nombre donné de sommets.  Par défaut, un graphe vide sera construit.
 * @param nombre Nombre entier positif ou nul.  Le nombre de sommets voulus.
 */
Graphe::Graphe(size_t nombre) : listes(nombre) {
}

/**
 * Ajouter un sommet au graphe.  Si le graphe a n sommets, il en aura ensuite n+1.
 */
void Graphe::ajouterSommet() {
    listes.emplace_back() ;
}

/**
 * Vérifie si le graphe comporte une arête entre le sommet départ, et le sommet arrivée.
 * Remarquez, ligne 35 l'utilisation de std::any_of avec une lambda expression.
 * @param depart Numéro du sommet de départ, un entier positif ou nul.
 * @param arrivee Numéro du sommet d'arrivée, un entier positif ou nul.
 * @return true si une arête existe entre les deux sommets.
 * @except invalid_argument si un des deux arguments n'est pas un sommet présent dans le graphe.
 */
bool Graphe::arcExiste(size_t depart, size_t arrivee) const {
    if (!sommetExiste(depart)) throw std::invalid_argument("arcExiste: depart invalide") ;
    if (!sommetExiste(arrivee)) throw std::invalid_argument("arcExiste: arrivée invalide") ;

    auto liste = listes.at(depart) ;
    return std::any_of(liste.begin(), liste.end(), [&arrivee](Arc e) {return e.destination == arrivee ; }) ;
}

/**
 * Vérifie si un sommet est bien présent dans le graphe.
 * @param numero Nombre entier positif désignant un éventuel sommet.
 * @return true si le paramètre numero désigne bien un sommet présent dans le graphe.
 */
bool Graphe::sommetExiste(size_t numero) const {
    return numero < listes.size() ;
}

/**
 * Ajoute une arête d'un poids donné, entre un sommet de départ et un sommet d'arrivée.
 * @param depart Entier positif désignant le sommet de départ
 * @param arrivee Entier positif désignant le sommet d'arrivée
 * @param poids Un double représentant la pondération de l'arête.
 * @except invalid_argument si un des numéros de sommet ne représente pas un des sommets du graphe.
 * @except invalid_argument si on veut ajouter un arc déjà présent entre deux sommets.
 */
void Graphe::ajouterArc(size_t depart, size_t arrivee, double poids) {
    if (arcExiste(depart, arrivee)) throw std::invalid_argument("ajouterArc: l'arc existe déjà.") ;

    listes.at(depart).emplace_back(arrivee, poids) ;
}

/**
 * Énumère les arêtes partant d'un sommet de départ.  Chaque arête comportant un sommet de destination et une pondération.
 * @param depart Numéro du sommet de départ.
 * @return Un std::list dont chaque élément est un struct Arc comportant un champ destination et un champ pondération.
 * @except invalid_argument si le paramètre départ ne représente pas un sommet du graphe.
 */
const std::list<Graphe::Arc>& Graphe::enumererVoisins(size_t depart) const {
    if (!sommetExiste(depart)) throw std::invalid_argument("enumererVoisins: sommet inexistant") ;
    return listes.at(depart) ;
}

/**
 * Calcule le nombre d'arêtes aboutissant à un sommet donné.
 * @param sommet Entier positif dénotant le sommet dont on veut connaître l'arité d'entrée.
 * @return Un entier positif représentant l'arité d'entrée du sommet.
 */
size_t Graphe::ariteEntree(size_t sommet) const {
    if (!sommetExiste(sommet)) throw std::invalid_argument("ariteEntree: sommet invalide.") ;
    auto arite = 0 ;

    for (const auto& liste: listes)
        for (auto elem: liste) if (elem.destination == sommet) ++ arite ;

    return arite ;
}

/**
 * Génère le graphe inverse de l'objet graphe courant.  C'est donc un graphe identique, sauf que le sens de toutes les
 * arêtes a été inversé.
 * @return Un objet graphe représentant l'inverse du graphe courant.
 */
Graphe Graphe::grapheInverse() const {

    Graphe inverse(listes.size()) ;

    for (size_t depart = 0; depart < listes.size(); ++depart) {
        auto liste = listes.at(depart) ;
        for (auto arc: liste) {
            inverse.ajouterArc(arc.destination, depart, arc.poids) ;
        }
    }

    return inverse ;
}

/**
 * Donne le nombre de sommets dans le graphe.
 * @return Entier positif ou nul représentant le nombre de sommets.
 */
size_t Graphe::taille() const {
    return listes.size() ;
}

/**
 * Retire un sommet du graphe.  Toutes les arêtes partant du sommet et allant vers ce sommet sont aussi donc supprimées
 * et les noeuds sont renumérotés de manière à demeurer consécutifs.
 * Exemple: J'ai le graphe 0-->1-->2 et je retire le sommet 1.  Le graphe résultant sera: 0-->1 car l'ancien sommet
 * numéro 2 a été renuméroté à 1.
 * @param sommet Entier positif. Le numéro du sommet à éliminer.
 * @except std::invalid_argument si le sommet n'est pas dans le graphe
 */
void Graphe::retirerSommet(size_t sommet) {
    if (!sommetExiste(sommet)) throw std::invalid_argument("retirerSommet: sommet inexistant") ;

    listes.erase(listes.begin() + static_cast<std::vector<size_t>::difference_type> (sommet)) ;

    for (auto& liste: listes) {
        auto it = std::find_if(liste.begin(), liste.end(), [sommet](Arc element) {return element.destination == sommet; }) ;
        if (it != liste.end()) liste.erase(it) ;
    }

    for (auto& liste: listes) {
        for (auto& voisin: liste) if (voisin.destination > sommet) --voisin.destination ;
    }

}

/**
 * Retourne le nombre d'arêtes partant d'un sommet donné
 * @param sommet Entier positif ou nul représentant le numéro du sommet
 * @return Un entier positif ou nul représentant le nombre d'arcs partants de ce sommet
 * @except std::invalid_argument si le numéro de sommet demandé n'est pas dans le graphe
 */
size_t Graphe::ariteSortie(size_t sommet) const {
    if (!sommetExiste(sommet)) throw std::invalid_argument("ariteSortie: sommet inexistant") ;
    return listes.at(sommet).size() ;
}

/**
 * Retire une arête du graphe.
 * NB: Si une arête va de 1 vers 2, retirerArc(2, 1) ne fonctionnera pas, il faut absolument respecter le sens
 * de l'arête.
 * @param depart Entier positif ou nul, sommet de départ de l'arête
 * @param arrivee Entier positif ou nul, sommet d'arrivée de l'arête
 */
void Graphe::retirerArc(size_t depart, size_t arrivee) {
    auto& liste = listes.at(depart) ;
    auto it = std::find_if(liste.begin(), liste.end(), [&arrivee](Arc e) {return e.destination == arrivee ; }) ;
    if (it != liste.end()) liste.erase(it) ;
    else throw std::invalid_argument("retirerArc: arc inexistant") ;
}




