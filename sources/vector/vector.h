//
// Created by Astan on 07.02.2021.
//

#ifndef MYSTD_VECTOR_H
#define MYSTD_VECTOR_H

namespace mystd {
    template<class T>
    class vector {
        size_t _size;
        size_t _capacity;
        char *_data;
        typedef T *iterator;
        typedef const T *const_iterator;
    public:
        vector();

        explicit vector(size_t size);

        vector(size_t size, const T &initial);

        vector(const vector<T> &v);

        vector(std::initializer_list<T>);

        ~vector();

        T &operator[](size_t index);

        vector<T> &operator=(const vector<T> &);

        size_t size() const;

        size_t capacity() const;

        bool empty() const;

        iterator begin();

        const_iterator cbegin();

        iterator end();

        const_iterator cend();

        T &front();

        T &back();

        void push_back(const T &value);

        void pop_back();

        void reserve(size_t capacity);

        void resize(size_t size);

        void clear();

    };

    template<class T>
    vector<T>::vector() : _size(0), _capacity(0), _data(nullptr) {
    }

    template<class T>
    vector<T>::vector(size_t size) : _size(size), _capacity(_size * 2), _data(new char[sizeof(T) * _capacity]) {
    }

    template<class T>
    vector<T>::vector(size_t size, const T &initial) : _size(size), _capacity(_size * 2),
                                                       _data(new char[sizeof(T) * _capacity]) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(initial);
    }

    template<class T>
    vector<T>::vector(const vector<T> &v) : _size(v._size), _capacity(v._capacity),
                                            _data(new char[sizeof(T) * _capacity]) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(v[i]);
    }

    template<class T>
    vector<T>::vector(std::initializer_list<T> l) : _size(l.size()), _capacity(_size * 2),
                                                    _data(new char[sizeof(T) * _capacity]) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(*(l.begin() + i));
    }

    template<class T>
    vector<T>::~vector() {
        delete[] _data;
    }

    template<class T>
    T &vector<T>::operator[](size_t index) {
        return *(reinterpret_cast<T*>(_data + sizeof(T) * index));
    }

    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        return reinterpret_cast<T*>(_data);
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cbegin() {
        return begin();
    }

    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return reinterpret_cast<T*>(_data + sizeof(T) * _size);
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cend() {
        return end();
    }


}

#endif //MYSTD_VECTOR_H
