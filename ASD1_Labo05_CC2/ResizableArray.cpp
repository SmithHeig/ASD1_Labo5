//
//  ResizableArray.cpp
//  Labos ASD1 2017
//  James Smith, Joel Schär, Guillaume Schranz
//  18.05.2017
//  Copyright © 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <utility>
using namespace std;

/// Forward declaration classe
template < typename T > class ResizableArray;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator << (ostream& os, const ResizableArray<T>& );

/// Classe de tableau redimensionable
template < typename T > class ResizableArray {
public:
    friend ostream& operator << <T>(ostream& os, const ResizableArray<T>& );

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using rvalue_reference = T&&;
    using pointer = T*;
    using const_pointer = const T*;

private:

    // Seuls attributs privés autorisé.
    // La mémoire allouée va de _begin (compris) à _end_cap (non compris).
    // La mémoire utilisée va de _begin (compris) à _end (non compris).

    pointer _begin;
    pointer _end;
    pointer _end_cap;

public:
    /**
     *  @brief Constructeur.
     *
     *  @param size le nombre d'éléments à initialiser par défaut
     */
    ResizableArray(size_t size = 0)
    {
        if(size == 0){
            _begin = nullptr;
            _end_cap = _begin;
        } else {
            _begin = reinterpret_cast<pointer>(::operator new(size * sizeof(value_type)));
            _end_cap = _begin + size;
        }
        try {
            for(_end = _begin; _end != _end_cap; ++_end){
                new(_end) value_type();
            }
        } catch (...) {
            for (pointer p = _begin; p < _end; ++p) {
                p->~value_type();
            }
            ::operator delete(_begin);
            throw;
        }
    }

    /**
     *  @brief Constructeur de copie
     */
    ResizableArray(const ResizableArray& other)
    /* ... */
    {
        if(other._begin == NULL || other.size() == 0){
            ResizableArray();
        }
        else {
            _begin = reinterpret_cast<pointer>(::operator new(other.size() * sizeof(value_type)));
            _end_cap = _begin + other.size();
            _end = _begin;
            try{
                for(size_t i = 0; i < other.size(); ++i){
                    new(_end) value_type(other.at(i));
                    ++_end;
                }
            } catch(...){
                for (pointer p = _begin; p < _end; ++p) {
                    p->~value_type();
                }
                ::operator delete(_begin);
                throw;
            }
        }
    }

    /**
     *  @brief Constructeur de déplacement
     */
    ResizableArray(ResizableArray&& other)
    /* ... */
    {
        _begin = NULL;
        _end = NULL;
        _end_cap = NULL;
        swap(other);
    }

    /**
     *  @brief opérateur d'affectation. Réutilise la mémoire courante si la capacité
     *         est suffisante. Réalloue a la capacité minimal nécessaire sinon.
     *
     *  @param other le ResizableArray à copier
     *
     *  @return *this
     */
    ResizableArray& operator = (const ResizableArray& other) {
        size_t temp_size = size();
        if(capacity() < other.size()){
            ResizableArray temp = ResizableArray(other);
            swap(temp);
        } else {
            _end = _begin + other.size();
            for(size_t i = 0; i < other.size(); ++i){
                if(i < temp_size){
                    this->at(i) = other.at(i);
                } else {
                    new (_begin + i) value_type(other.at(i));
                }
            }
        }
        return *this;
    }

    /**
     *  @brief opérateur de déplacement
     *
     *  @param other le ResizableArray à déplacer. Il sera modifié
     de sorte à être vide après déplacement
     *
     *  @return *this
     */
    ResizableArray& operator = (ResizableArray&& other) {
        swap(other);
        return *this;
    }

    /**
     *  @brief Destructeur
     */
    ~ResizableArray() {
        for(pointer ptr = _begin; ptr < _end; ++ptr){
            ptr->~value_type();
        }
        ::operator delete(_begin);
    }

    /**
     *  @brief Echange le contenu de l'objet avec celui de other
     *
     *  @param other le ResizableArray avec lequel échanger.
     */
    void swap(ResizableArray& other) noexcept {
        std::swap(_begin, other._begin);
        std::swap(_end,other._end);
        std::swap(_end_cap, other._end_cap);
    }

public:
    /**
     *  @brief Taille du tableau
     *
     *  @return le nombre d'éléments stockés
     */
    size_t size() const noexcept {
        return (size_t)(_end - _begin);
    }

    /**
     *  @brief Capacité
     *
     *  @return le nombre d'éléments stockables avec la mémoire actuellement allouée
     */
    size_t capacity() const noexcept {
        return (size_t)(_end_cap - _begin);
    }
    /**
     *  @brief Redimensionne le tableau
     *
     *  @param newSize le nouveau nombre d'éléments du tableau
     *
     *  @remark si la taille augmente, les éléments supplémentaires doivent être créés. si elle diminue, les éléments excédentaires doivent être détruits
     */
    void resize(size_t newSize) {
        if(newSize > size()){
            if(newSize > capacity()){
                reserve(newSize);
            }
            _end += (newSize - size());
        } else if(newSize < size()){
            for(int i = (int)size()-1; i >= (int)newSize; --i){
                pop_back();
            }
        }
    }

    /**
     *  @brief Augmente la capacité du tableau
     *
     *  @param newCapacity la nouvelle capacité, si celle ci est plus grande que la capacité actuelle. sinon c'est une no-op.
     */
    void reserve(size_t newCapacity) {
        if(newCapacity > capacity()){
            pointer temp = reinterpret_cast<pointer>(::operator new (newCapacity * sizeof(value_type)));
            size_t i = 0;
            try{
                size_t tempSize = size();
                for(; i < tempSize; ++i){
                    new(temp + i) value_type(this->at(i));
                }
                this->~ResizableArray();
                _begin = temp;
                _end = temp + tempSize;
                _end_cap = temp + newCapacity;
            } catch(...){
                for(size_t j = 0; j < i; ++j){
                    (temp + j)->~value_type();
                }
                throw;
            }

        }
    }

    /**
     *  @brief Diminue la capacité autant que possible.
     */
    void shrinkToFit() {
        ResizableArray temp = ResizableArray(*this);
        swap(temp);
    }

    /**
     *  @brief ajoute un élément en queue
     *
     *  @param value l'élément à ajouté.
     */
    void push_back(const_reference value) {
        if(size() == capacity()){
            reserve(size() * 2);
        }
        new (_end++) value_type(value);
    }

    /**
     *  @brief supprime l'élément en queue
     *
     *  @exception runtime_error si le tableau est vide
     */
    void pop_back() {
        if(size() == 0){
            throw runtime_error("empty tabular");
        }
        (--_end)->~value_type();
    }

    /**
     *  @brief accède à l'élément en queue
     *
     *  @return une référence (modifiable) à cet élément
     *
     *  @exception runtime_error si le tableau est vide
     */
    reference back() {
        if(size() == 0){
            throw(runtime_error("empty tabular"));
        }
        return (*(_end-1));
    }

    /**
     *  @brief accède à l'élément en queue
     *
     *  @return une référence (constante) à cet élément
     *
     *  @exception runtime_error si le tableau est vide
     */
    const_reference back() const {
        return const_reference(const_cast<ResizableArray*> (this))->back;
    }

    /**
     *  @brief Insère un élément en position quelconque
     *
     *  @param pos   la position d'insertion. 0 signifie insertion en tête
     *  @param value l'élément à insérer
     *
     *  @exception out_of_range si pos non valide
     */
    void insert(size_t pos, const_reference value) {
        if(pos > size()){
            throw out_of_range("pos not valide");
        }
        if(size() == capacity()){
            reserve(size()*2);
        }
        if(pos == size()){
            push_back(value);
        } else {
            pointer i = _end-1;
            push_back(*i);
            for(; i != (_begin + pos); --i){
                *i = *(i - 1);
            }
            *(_begin + pos) = value;
        }

    }

    /**
     *  @brief supprime un élément en position quelconque
     *
     *  @param pos la position de suppression. 0 signifie suppression en tête
     *
     *  @exception out_of_range si pos non valide
     */
    void erase(size_t pos) {
        if(pos >= size()){
            throw out_of_range("pos non valide");
        }
        for(pointer i = _begin + pos; i < _end-1; ++i){
            *(i) = *(i + 1);
        }
        (--_end)->~value_type();
    }

    /**
     *  @brief accède à un élément en position quelconque
     *
     *  @param pos la position de l'élément à accéder
     *
     *  @return une référence (modifiable) à cet élément
     *
     *  @exception out_of_range si pos non valide
     */
    reference at(size_t pos) {
        if(pos >= size()){
            throw(out_of_range("position not valide"));
        }
        return *(_begin + pos);
    }

    /**
     *  @brief accède à un élément en position quelconque
     *
     *  @param pos la position de l'élément à accéder
     *
     *  @return une référence (constante) à cet élément
     *
     *  @exception out_of_range si pos non valide
     */
    const_reference at(size_t pos) const {
        return const_reference(const_cast<ResizableArray*> (this)->at(pos));
    }
};

template <typename T>
ostream& operator << (ostream& os, const ResizableArray<T>& v) {
    os << v.size() << "/" << v.capacity() << ": ";
    for( auto p = v._begin; p < v._end; ++p ) {
        os << *p << " ";
    }
    return os;
}
