//
// Created by Pascal Charpentier on 2023-06-13.
//

#ifndef FILEPRIORITAIRE_FILEPRIORITAIRE_H
#define FILEPRIORITAIRE_FILEPRIORITAIRE_H

#include <vector>

template <typename T>
class FilePrioritaire {
private:
    using HeapNode = struct HeapNode {
        T cle ;
        size_t numero ;

        HeapNode(const T& data, size_t numero) : cle(data), numero(numero) {}

        bool operator < (const HeapNode& rhs) {return cle < rhs.cle ; }
    };

    using IndexNode = struct IndexNode {
        T data ;
        size_t position ;

        IndexNode(const T& data, size_t position) : data(data), position(position) {}
    };



public:
    explicit FilePrioritaire(const std::vector<T>& donnees) ;
    const T& lireMinimum() const ;
    size_t lireIndexMinimum() const ;
    void extraireMinimum() ;
    size_t taille() const ;
    bool estVide() const ;
    const T& lireClePourIndex(size_t i) const ;
    void reduireCle(size_t numeroIndex, const T& nouvelleCle) ;
    std::vector<T> genererIndex() const ;

private:
    static size_t enfantGauche(size_t i) {return 2 * i + 1 ; }
    static size_t enfantDroite(size_t i) {return 2 * i + 2 ; }
    static size_t parent(size_t i) {return (i - 1)/ 2 ; }

    void construireFilePrioritaire() ;
    void percolerVersLeBas(size_t i) ;

private:
    size_t heapSize ;
    std::vector<HeapNode> heap ;
    std::vector<IndexNode> index ;
};



#include "FilePrioritaireImplantation.h"

#endif //FILEPRIORITAIRE_FILEPRIORITAIRE_H
