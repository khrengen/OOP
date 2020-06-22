#ifndef VECTOR_H
#define VECTOR_H


#include <iterator>
#include <iostream>
#include <memory>
#include <algorithm>

template <class T> class vec_iterator;


// TODO: use preprocessor to not compile error checks
const int VECTOR_SPEED_UP = 0;

//===== INTERFACE =======//

template <class T>
class TVector {
    unsigned capacity;
    unsigned size;
    T* data;

    public:
        using iterator = vec_iterator<T>;

        TVector();
        TVector(unsigned capacity);
        TVector(unsigned capacity, T initial);
        TVector(TVector<T>& vec);

        ~TVector();

        T& Front() const;
        T& Back() const;

        iterator Begin() const;
        iterator End() const;

        unsigned Size() const;
        bool Empty() const;
        void Print(char del=' ', char end='\n') const;

        void PopBack();
        void Insert(T val, unsigned ind);
        void PushBack(T val);

        void Resize();
        void Clear();
        void Swap(TVector<T>& lhs, TVector<T>& rhs);

        iterator begin() {
            return iterator(data, capacity);
        }
        vec_iterator<T> end() {
            return iterator(data + size, capacity);
        }

        T& operator [] (unsigned ind) const;
        TVector<T>& operator = (TVector<T> vec);
};



template<class T>
TVector<T>::TVector(): 
    capacity(0), size(0), data(NULL) 
    {
    }

template<class T>
TVector<T>::TVector(unsigned cap): TVector<T>::TVector(){
    capacity = cap;
    size = 0;
    data = new T[capacity];
}

template<class T>
TVector<T>::TVector(unsigned cap, T init): TVector<T>() {
    capacity = cap;
    size = cap;
    data = new T[capacity];
    std::fill(data, data + size, init);
}

template<class T>
TVector<T>::TVector(TVector<T>& vec):TVector<T>() {
    TVector<T> vOut(vec.capacity);
    vOut.size = vec.size;

    if (vec.data) 
        std::copy(vec.data, vec.data + vec.size, vOut.data); 
    Swap(*this, vOut); 
}

template<class T>
TVector<T>::~TVector() {
    delete[] data;

    size = 0;
    capacity = 0;
    data = NULL;
}


template<class T>
unsigned TVector<T>::Size() const {
    return size;
}

template<class T>
void TVector<T>::Print(char del, char end) const {
    for (unsigned i = 0; i < size; ++i) {
        std::cout << data[i] << del;
    }
    std::cout << end;
}

template<class T>
void TVector<T>::PushBack(T val) {
    if (size == capacity) 
        Resize();
    data[size] = val;
    size++;
}

template<class T>
void TVector<T>::Resize () {
    if (!capacity) 
        capacity = 1;

    using std::copy;
    T* buf = new T[capacity *= 2];
    copy(data, data + size, buf);
    delete[] data;
    data = buf;
}

template<class T>
typename TVector<T>::iterator TVector<T>::Begin() const {
    return data;
}

template<class T>
typename TVector<T>::iterator TVector<T>::End() const {
    return data + size;
}

template<class T>
bool TVector<T>::Empty() const {
    return size;
}

template<class T>
T& TVector<T>::operator [] (unsigned ind) const {
    return data[ind];
}

template<class T>
void TVector<T>::Swap(TVector<T>& lhs, TVector<T>& rhs) {
    using std::swap;

    swap(lhs.size, rhs.size);
    swap(lhs.capacity, rhs.capacity);
    swap(lhs.data, rhs.data);
}

template<class T>
TVector<T>& TVector<T>::operator = (TVector<T> vec) {
    Swap(*this, vec);
    return *this;
}

template<class T>
T& TVector<T>::Front() const {
    return data[0];
}

template<class T>
T& TVector<T>::Back() const {
    return data[size - 1];
}

template<class T>
void TVector<T>::Insert(T val, unsigned ind) {
    if (size == capacity) 
        Resize();

    using std::copy;
    T* buf = new T[capacity];
    if (ind)
        copy(data, data + ind, buf);
    buf[ind] = val;
    copy(data + ind, data + size, buf + ind + 1);

    delete[] data;
    data = buf;
    size++;
}

template<class T>
void TVector<T>::Clear() {
    size = 0;
}

template<class T>
void TVector<T>::PopBack() {
    size--;
}

template<class T>
std::istream& operator >> (std::istream& in, TVector<T>& vec) {
    for (unsigned i = 0; i < vec.size(); ++i) in >> vec[i];
    return in;
}

template<class T>
std::ostream& operator << (std::ostream& out, const TVector<T>& vec) {
    for (unsigned i = 0; i < vec.size(); ++i) out << vec[i] << " ";
    return out;
}

template <class T>
class vec_iterator {
public:
    T* data;
    int cap;

    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = size_t;
    using pointer = T*;
    using reference = T&;

    vec_iterator()
    {    
    }

    vec_iterator(pointer _data, int capacity) : data(_data), cap(capacity) 
    {   
    }

    void next() { 
        data += 1; 
    }

    reference operator*() {
        return *data; 
    }
    bool operator!=(const vec_iterator& other) {
        return data != other.data;
    }
    vec_iterator<T>& operator++() {
        data += 1;
        return *this;
    }
    vec_iterator<T> operator++(int) {
        return vec_iterator<T>(data + 1);
    }

    void insert(T to_ins) {
        *data = to_ins;
    }
    void erase() {
        data = data + 1;
    }
    reference operator[](std::size_t idx) {
        return *(data + idx);
    }
};

#endif