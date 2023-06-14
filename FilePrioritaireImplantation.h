//
// Created by Pascal Charpentier on 2023-06-13.
//

#ifndef FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H
#define FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H

#include "FilePrioritaire.h"

/**
 * Construit une file prioritaire à l'aide d'un vecteur contenant les clés.  Chaque clé correspondra à un numéro.
 * @tparam T
 * @param donnees std::vector<T> contenant une clé pour chaque index du vector.
 */
template<typename T>
FilePrioritaire<T>::FilePrioritaire(const std::vector<T>& donnees) : heapSize(donnees.size()), heap(), index() {
    for (size_t i = 0; i < donnees.size(); ++i) {
        index.emplace_back(donnees.at(i), i) ;
        heap.emplace_back(donnees.at(i), i) ;
    }
    construireFilePrioritaire() ;

}

/**
 * transforme un vector en heap binaire, en place.  Le vector est donc modifié.
 * @tparam T
 */
template<typename T>
void FilePrioritaire<T>::construireFilePrioritaire() {
    for (size_t i = parent(heap.size() - 1) ; i != static_cast<size_t> (-1); --i ) percolerVersLeBas(i) ;
}

/**
 * Rétablit la propriété des heaps par percolation d'un noeud vers le bas.  Doit aussi mettre à jour l'index du heap
 * afin de garantir l'intégrité.
 * @tparam T
 * @param i Position du noeud à percoler DANS LE HEAP: ce n'est pas le numéro d'index de la clé
 */
template<typename T>
void FilePrioritaire<T>::percolerVersLeBas(size_t i) {
    size_t g = enfantGauche(i) ;
    size_t d = enfantDroite(i) ;
    size_t minimum = i ;

    if ((g < heapSize) && (heap.at(g) < heap.at(minimum))) minimum = g ;

    if ((d < heapSize) && (heap.at(d) < heap.at(minimum))) minimum = d ;

    if (i != minimum) {
        std::swap(heap.at(i), heap.at(minimum)) ;
        index.at(heap.at(i).numero).position = i ;
        index.at(heap.at(minimum).numero).position = minimum ;
        percolerVersLeBas(minimum) ;
    }
}

/**
 * Retourne la clé en tête de file
 * @tparam T
 * @return La clé minimale de la file
 */
template<typename T>
const T &FilePrioritaire<T>::lireMinimum() const {
    return index.at(heap.at(0).numero).data ;
}

/**
 * Élimine la clé en tête de file.
 * @tparam T
 */
template<typename T>
void FilePrioritaire<T>::extraireMinimum() {
    std::swap(heap.at(heapSize - 1), heap.at(0)) ;
    index.at(heap.at(heapSize - 1).numero).position = heapSize - 1 ;
    index.at(heap.at(0).numero).position = 0 ;
    -- heapSize ;
    percolerVersLeBas(0) ;

}

/**
 * Retourne le nombre d'éléments restants dans la file
 * @tparam T
 * @return Entier positif ou nul
 */
template<typename T>
size_t FilePrioritaire<T>::taille() const {
    return heapSize ;
}

/**
 * Indique si la file est vide
 * @tparam T
 * @return true si la file est vide
 */
template<typename T>
bool FilePrioritaire<T>::estVide() const {
    return taille() == 0 ;
}

/**
 * Change la valeur de la clé d'un élément de la file.  La nouvelle valeur doit être plus petite que l'ancienne sinon
 * la file ne sera plus valide.
 * @tparam T
 * @param numeroIndex Numéro d'index de l'élément à modifier
 * @param nouvelleCle Nouvelle valeur de la clé
 * @pre La nouvelle clé est plus petite que l'ancienne
 */
template<typename T>
void FilePrioritaire<T>::reduireCle(size_t numeroIndex, const T &nouvelleCle) {
    size_t i = index.at(numeroIndex).position ;
    heap.at(i).cle = nouvelleCle ;
    index.at(heap.at(i).numero).data = nouvelleCle ;
    while ( (i > 0) && (heap.at(i) < heap.at(parent(i)) ) ) {
        std::swap(heap.at(i), heap.at(parent(i))) ;
        index.at(heap.at(i).numero).position = i ;
        index.at(heap.at(parent(i)).numero).position = parent(i) ;
        i = parent(i) ;
    }
}

/**
 * Retourne le numéro d'index de l'élément en tête de file
 * @tparam T
 * @return Un entier positif ou nul
 */
template<typename T>
size_t FilePrioritaire<T>::lireIndexMinimum() const {
    return heap.at(0).numero ;
}

/**
 * Retourne un vector contenant l'index numéro-clé de la file
 * @tparam T
 * @return
 */
template<typename T>
std::vector<T> FilePrioritaire<T>::genererIndex() const {
    std::vector<T> resultat ;
    for (size_t i = 0; i < index.size(); ++i) resultat.push_back(index.at(i).data) ;
    return resultat ;
}

/**
 * Retourne la clé associée à un numéro d'index
 * @tparam T
 * @param i Entier positif ou nul: le numéro d'index
 * @return La clé
 * @pre La clé i doit être présente dans l'index sinon le comportement sera non défini
 */
template<typename T>
const T &FilePrioritaire<T>::lireClePourIndex(size_t i) const {
    return index.at(i).data ;
}

#endif //FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H
