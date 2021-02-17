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
        typedef T &reference;
        typedef const T &const_reference;

        void reallocate();
        void move_storage(iterator dest, iterator from, size_t count);

    public:
        vector();

        explicit vector(size_t size);

        vector(size_t size, const T &initial);

        vector(const vector<T> &vector);

        vector(vector<T> &&vector) noexcept;

        vector(std::initializer_list<T> list);

        template<class input_iterator, typename = typename std::enable_if_t<std::_Is_iterator<input_iterator>::value>>
        vector(input_iterator first, input_iterator last);

        ~vector();

        reference operator[](size_t index);

        const_reference operator[](size_t index) const;

        vector<T> &operator=(const vector<T> &);

        vector<T> &operator=(vector<T>);

        vector<T> &operator=(vector<T> &&) noexcept;

        bool operator==(const vector<T> &right);

        void assign(size_t count, const_reference value);

        template<class input_iterator, typename = typename std::enable_if_t<std::_Is_iterator<input_iterator>::value>>
        void assign(input_iterator first, input_iterator last);

        iterator insert(const_iterator pos, const_reference value);
        iterator insert(const_iterator pos, T&& value);
        iterator insert(const_iterator pos, size_t count, const_reference value);
        template<class input_iterator, typename = typename std::enable_if_t<std::_Is_iterator<input_iterator>::value>>
        iterator insert(const_iterator pos, input_iterator first, input_iterator last);
        iterator insert(const_iterator post, std::initializer_list<T> list);

        template <typename ... Args>
        iterator emplace(const_iterator pos, Args&& ... args);

        size_t size() const;

        size_t capacity() const;

        bool empty() const;

        iterator begin();

        const_iterator cbegin();

        iterator end();

        const_iterator cend();

        reference front();

        const_reference front() const;

        reference back();

        const_reference back() const;

        void push_back(const_reference);

        void push_back(T &&value);

        void pop_back();

        void reserve(size_t capacity);

        void resize(size_t size);

        void clear();

        friend void swap(vector<T> &left, vector<T> &right);

    };

    template<class T>
    vector<T>::vector() : _size(0), _capacity(0), _data(nullptr) {
    }

    template<class T>
    vector<T>::vector(size_t size) : _size(size), _capacity(_size), _data(new char[sizeof(T) * size]) {
    }

    template<class T>
    vector<T>::vector(size_t size, const T &initial) : vector(vector._size) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(initial);
    }

    template<class T>
    vector<T>::vector(const vector <T> &vector) : vector(vector._size) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(vector[i]);
    }

    template<class T>
    vector<T>::vector(vector<T> &&vector) noexcept : vector(vector._size) {
        swap(*this, vector);
    }

    template<class T>
    vector<T>::vector(std::initializer_list<T> list) : vector(list.size()) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(*(list.begin() + i));
    }

    template<class T>
    template<class input_iterator, typename>
    vector<T>::vector(input_iterator first, input_iterator last) : vector(last - first) {
        for (size_t i = 0; i < _size; i++)
            new(_data + sizeof(T) * i) T(*(first + i));
    }

    template<class T>
    vector<T>::~vector() {
        delete[] _data;
    }

    template<class T>
    T &vector<T>::operator[](size_t index) {
        return *(reinterpret_cast<iterator>(_data + sizeof(T) * index));
    }

    template<class T>
    const T &vector<T>::operator[](size_t index) const {
        return *(reinterpret_cast<iterator>(_data + sizeof(T) * index));
    }

    template<class T>
    vector<T> &vector<T>::operator=(const vector<T> &vector) {
        if (*this != vector) {
            auto temporaryVector(vector);
            swap(*this, temporaryVector);
        }
        return *this;
    }

    template<class T>
    vector<T> &vector<T>::operator=(vector<T> &&vector) noexcept {
        if (*this != vector) {
            swap(*this, vector);
        }
        return *this;
    }

    template<class T>
    vector<T> &vector<T>::operator=(vector<T> vector) {
        if (*this != vector) {
            swap(*this, vector);
        }
        return *this;
    }

    template<class T>
    bool vector<T>::operator==(const vector <T> &right) {
        if (_size != right._size)
            return false;
        for (size_t i = 0; i < _size; i++)
            if (*(reinterpret_cast<iterator>(_data + sizeof(T) * i)) !=
                *(reinterpret_cast<iterator>(right._data + sizeof(T) * i)))
                return false;
        return true;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        return reinterpret_cast<iterator>(_data);
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cbegin() {
        return begin();
    }

    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return reinterpret_cast<iterator>(_data + sizeof(T) * _size);
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cend() {
        return end();
    }

    template<class T>
    size_t vector<T>::size() const {
        return _size;
    }

    template<class T>
    size_t vector<T>::capacity() const {
        return _capacity;
    }

    template<class T>
    bool vector<T>::empty() const {
        return _size == 0;
    }

    template<class T>
    typename vector<T>::reference vector<T>::front() {
        return *begin();
    }

    template<class T>
    typename vector<T>::const_reference vector<T>::front() const {
        return *cbegin();
    }

    template<class T>
    typename vector<T>::reference vector<T>::back() {
        return *end();
    }

    template<class T>
    typename vector<T>::const_reference vector<T>::back() const {
        return *cend();
    }

    template<class T>
    void swap(vector<T> &left, vector<T> &right) {
        using std::swap; //enable ADL? https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
        swap(left._size, right._size);
        swap(left._capacity, right._capacity);
        swap(left._data, right._data);
    }

    template<class T>
    void vector<T>::push_back(const_reference) {
        if (_size >= _capacity) {
            reallocate();
        }
        new(end()) T(value);
        _size++;
    }

    template<class T>
    void vector<T>::push_back(T &&value) {
        if (_size >= _capacity) {
            reallocate();
        }
        *end() = std::move(value);
        _size++;
    }

    template<class T>
    void vector<T>::reallocate() {
        _capacity = _size * 1.5;

        char *new_data = new char[sizeof(T) * _capacity];
        memcpy(new_data, _data, sizeof(T) * _size);
        delete[] _data;
        _data = new_data;

    }

    template<class T>
    void vector<T>::move_storage(iterator dest, iterator from, size_t count) {
        if (dest < from)
        {
            iterator _dest = dest;
            iterator _from = from;
            for (size_t i = 0; i < count; i++)
                *_dest++ = std::move(*_from++);
        }
        else if (dest > from)
        {
            iterator _dest = dest + count - 1;
            iterator _from = from + count - 1;
            for (size_t i = count; i > 0; i--)
                *_dest-- = std::move(*_from--);
        }
        else
            return;
    }

    template<class T>
    void vector<T>::assign(size_t count, const_reference value) {

    }

    template<class T>
    template<class input_iterator, typename>
    void vector<T>::assign(input_iterator first, input_iterator last) {

    }

    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector::const_iterator pos, const_reference value) {
        return emplace(pos, value);
    }

    template<class T>
    template<typename... Args>
    typename vector<T>::iterator vector<T>::emplace(vector::const_iterator pos, Args &&... args) {
        size_t index = pos - reinterpret_cast<iterator>(_data);

        if (_size >= _capacity) {
            reallocate();
        }

        iterator it = reinterpret_cast<iterator>(_data + sizeof(T) * index);
        move_storage(it + 1, it, _size - index);

        *it = T(std::forward<Args>(args) ...);
        _size++;
        return end();
    }


}

#endif //MYSTD_VECTOR_H
