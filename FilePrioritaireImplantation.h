//
// Created by Pascal Charpentier on 2023-06-13.
//

#ifndef FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H
#define FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H

#include "FilePrioritaire.h"

template<typename T>
FilePrioritaire<T>::FilePrioritaire(const std::vector<T>& donnees) : heapSize(donnees.size()), heap(), index() {
    for (size_t i = 0; i < donnees.size(); ++i) {
        index.emplace_back(donnees.at(i), i) ;
        heap.emplace_back(donnees.at(i), i) ;
    }
    construireFilePrioritaire() ;

}

template<typename T>
void FilePrioritaire<T>::construireFilePrioritaire() {
    for (size_t i = parent(heap.size() - 1) ; i != static_cast<size_t> (-1); --i ) percolerVersLeBas(i) ;
}

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

template<typename T>
const T &FilePrioritaire<T>::lireMinimum() const {
    return index.at(heap.at(0).numero).data ;
}

template<typename T>
void FilePrioritaire<T>::extraireMinimum() {
    std::swap(heap.at(heapSize - 1), heap.at(0)) ;
    index.at(heap.at(heapSize - 1).numero).position = heapSize - 1 ;
    index.at(heap.at(0).numero).position = 0 ;
    -- heapSize ;
    percolerVersLeBas(0) ;

}

template<typename T>
size_t FilePrioritaire<T>::taille() const {
    return heapSize ;
}

template<typename T>
bool FilePrioritaire<T>::estVide() const {
    return taille() == 0 ;
}

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

template<typename T>
size_t FilePrioritaire<T>::lireIndexMinimum() const {
    return heap.at(0).numero ;
}

template<typename T>
std::vector<T> FilePrioritaire<T>::genererIndex() const {
    std::vector<T> resultat ;
    for (size_t i = 0; i < index.size(); ++i) resultat.push_back(index.at(i).data) ;
    return resultat ;
}

template<typename T>
const T &FilePrioritaire<T>::lireClePourIndex(size_t i) const {
    return index.at(i).data ;
}

#endif //FILEPRIORITAIRE_FILEPRIORITAIREIMPLANTATION_H
