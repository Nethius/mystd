#ifndef MYSTD_VECTOR_H
#define MYSTD_VECTOR_H

const double expansion_ratio = 2;

namespace mystd {
    template<class T>
    class vector {
        size_t _size;
        size_t _capacity;
        T* _data;
        using iterator = T*;
        using const_iterator = const T*;
        using reference = T&;
        using const_reference = const T&;

        vector(const vector<T>& v, size_t capacity);

        void reallocate(size_t capacity);

        void move_forward(iterator dest, iterator from, size_t count);

        void move_backward(iterator dest, iterator from, size_t count);

    public:
        vector();

        explicit vector(size_t size);

        vector(size_t size, const T& initial);

        vector(const vector<T>& v);

        vector(vector<T>&& v) noexcept;

        vector(std::initializer_list<T> list);

        template<class input_iterator>
        vector(input_iterator first, input_iterator last);

        ~vector();

        T& operator[](size_t pos);

        const T& operator[](size_t pos) const;

        T& at(size_t pos);

        const T& at(size_t pos) const;

        vector<T>& operator=(const vector<T>& v);

        vector<T>& operator=(vector<T>&& v) noexcept;

        void assign(size_t count, const T& value);

        template<class input_iterator>
        void assign(input_iterator first, input_iterator last);

        iterator insert(const_iterator pos, const T& value);

        iterator insert(const_iterator pos, T&& value);

        iterator insert(const_iterator pos, size_t count, const T& value);

        template<class input_iterator>
        iterator insert(const_iterator pos, input_iterator first, input_iterator last);

        iterator insert(const_iterator pos, std::initializer_list<T> list);

        template<typename ... Args>
        iterator emplace(const_iterator pos, Args&& ... args);

        iterator erase(const_iterator pos);

        iterator erase(const_iterator first, const_iterator last);

        size_t size() const;

        size_t max_size() const;

        size_t capacity() const;

        bool empty() const;

        iterator begin();

        const_iterator begin() const;

        const_iterator cbegin() const;

        iterator rbegin();

        const_iterator rbegin() const;

        const_iterator rcbegin() const;

        iterator end();

        const_iterator end() const;

        const_iterator cend() const;

        iterator rend();

        const_iterator rend() const;

        const_iterator rcend() const;

        T& front();

        const T& front() const;

        T& back();

        const T& back() const;

        iterator data();

        const_iterator data() const;

        void push_back(const T& value);

        void push_back(T&& value);

        void pop_back();

        template<typename ... Args>
        void emplace_back(Args&& ... args);

        void reserve(size_t size);

        void resize(size_t count);

        void resize(size_t count, const T& value);

        void shrink_to_fit();

        void clear();

        void swap(vector<T>& other) noexcept;

        friend void swap(vector& left, vector& right) { left.swap(right); }

        bool operator==(const vector<T>& other);

        bool operator!=(const vector<T>& other);

        bool operator<(const vector<T>& other);

        bool operator<=(const vector<T>& other);

        bool operator>(const vector<T>& other);

        bool operator>=(const vector<T>& other);
    };

    template<class T>
    vector<T>::vector() : _size(0), _capacity(0), _data(nullptr) {
    }

    template<class T>
    vector<T>::vector(size_t size) : _size(size), _capacity(_size),
                                     _data(reinterpret_cast<T*>(new std::byte[sizeof(T) * size]())) {
    }

    template<class T>
    vector<T>::vector(size_t size, const T& initial) : vector(size) {
        for (size_t i = 0; i < _size; i++) {
            new(_data + i) T(initial);
        }
    }

    template<class T>
    vector<T>::vector(const vector<T>& v) : vector(v._size) {
        for (size_t i = 0; i < _size; i++) {
            new(_data + i) T(v[i]);
        }
    }

    template<class T>
    vector<T>::vector(vector<T>&& v) noexcept : vector() {
        this->swap(v);
    }

    template<class T>
    vector<T>::vector(std::initializer_list<T> list) : vector(list.size()) {
        for (size_t i = 0; i < _size; i++) {
            new(_data + i) T(*(list.begin() + i));
        }
    }

    template<class T>
    template<class input_iterator>
    vector<T>::vector(input_iterator first, input_iterator last) : vector(std::distance(first, last)) {
        auto it = first;
        for (size_t i = 0; i < _size; i++) {
            new(_data + i) T(*(it));
            it = std::next(it);
        }
    }

    template<class T>
    vector<T>::vector(const vector<T>& v, size_t capacity) : vector(capacity) {
        _size = v._size;
        for (size_t i = 0; i < v._size; i++) {
            new(_data + i) T(v[i]);
        }
    }

    template<class T>
    vector<T>::~vector() {
        for (size_t i = 0; i < _size; i++)
            _data->~T();
    }

    template<class T>
    T& vector<T>::operator[](size_t pos) {
        return *(_data + pos);
    }

    template<class T>
    const T& vector<T>::operator[](size_t pos) const {
        return *(_data + pos);
    }

    template<class T>
    vector<T>& vector<T>::operator=(const vector<T>& v) {
        mystd::vector<T> copy(v);
        this->swap(copy);
        return *this;
    }

    template<class T>
    vector<T>& vector<T>::operator=(vector<T>&& v) noexcept {
        this->swap(v);
        return *this;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        return _data;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::begin() const {
        return _data;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cbegin() const {
        return begin();
    }

    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return _data + _size;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::end() const {
        return _data + _size;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::cend() const {
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
    T& vector<T>::front() {
        return *begin();
    }

    template<class T>
    const T& vector<T>::front() const {
        return *cbegin();
    }

    template<class T>
    T& vector<T>::back() {
        return *(end() - 1);
    }

    template<class T>
    const T& vector<T>::back() const {
        return *(cend() - 1);
    }

    template<class T>
    void vector<T>::push_back(const T& value) {
        if (_size >= _capacity) {
            reallocate(_size * expansion_ratio);
        }
        new(end()) T(value);
        _size++;
    }

    template<class T>
    void vector<T>::push_back(T&& value) {
        if (_size >= _capacity) {
            reallocate(_size * expansion_ratio);
        }
        new(end()) T(std::move(value));
        _size++;
    }

    template<class T>
    void vector<T>::reallocate(size_t capacity) {
        vector<T> newVector(*this, capacity);

        swap(newVector);
    }

    template<class T>
    void vector<T>::move_forward(vector::iterator dest, vector::iterator from, size_t count) {
        if (dest == from) {
            return;
        }
        iterator _dest = dest;
        iterator _from = from;
        for (size_t i = 0; i < count; i++) {
            *_dest++ = std::move(*_from++);
        }
    }

    template<class T>
    void vector<T>::move_backward(vector::iterator dest, vector::iterator from, size_t count) {
        if (dest == from) {
            return;
        }
        iterator _dest = dest + count - 1;
        iterator _from = from + count - 1;
        for (size_t i = count; i > 0; i--) {
            new(_dest--) T(std::move(*_from--));
        }
    }

    template<class T>
    void vector<T>::assign(size_t count, const T& value) {
        vector<T> copy(count, value);
        this->swap(copy);
    }

    template<class T>
    template<class input_iterator>
    void vector<T>::assign(input_iterator first, input_iterator last) {
        vector<T> copy(first, last);
        this->swap(copy);
    }

    template<class T>
    template<typename... Args>
    typename vector<T>::iterator vector<T>::emplace(vector::const_iterator pos, Args&& ... args) {
        size_t index = pos - _data;

        if (_size >= _capacity) {
            reallocate(_size * expansion_ratio);
        }

        iterator it = _data + index;
        move_backward(it + 1, it, _size - index);

        new(it) T(std::forward<Args>(args) ...);
        _size++;
        return it;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector::const_iterator pos, const T& value) {
        return emplace(pos, value);
    }

    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector::const_iterator pos, T&& value) {
        return emplace(pos, std::move(value));
    }

    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector::const_iterator pos, size_t count, const T& value) {
        if (!count) {
            return const_cast<iterator>(pos);
        }
        size_t index = pos - _data;

        if (_size + count >= _capacity) {
            reallocate((_size + count) * expansion_ratio);
        }

        iterator it = _data + index;
        move_backward(it + count, it, _size - index);

        for (size_t i = 0; i < count; i++) {
            new(it + i) T(value);
        }
        _size += count;
        return it;
    }

    template<class T>
    template<class input_iterator>
    typename vector<T>::iterator
    vector<T>::insert(vector::const_iterator pos, input_iterator first, input_iterator last) {
        size_t n = std::distance(first, last);

        if (!n) {
            return const_cast<iterator>(pos);
        }
        size_t index = pos - _data;

        if (_size + n >= _capacity) {
            reallocate((_size + n) * expansion_ratio);
        }

        iterator dest = _data + index;
        move_backward(dest + n, dest, _size - index);

        auto from = first;

        for (size_t i = 0; i < n; i++) {
            new(dest + i) T(*(from));
            from = std::next(from);
        }
        _size += n;
        return dest;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector::const_iterator pos, std::initializer_list<T> list) {
        return insert(pos, list.begin(), list.end());
    }

    template<class T>
    void vector<T>::pop_back() {
        erase(end() - 1);
    }

    template<class T>
    typename vector<T>::iterator vector<T>::erase(vector::const_iterator pos) {
        size_t index = pos - _data;
        iterator it = _data + index;
        it->~T();
        if (pos != end() - 1) {
            move_forward(it, it + 1, _size - index);
        }
        _size--;
        return it;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::erase(vector::const_iterator first, vector::const_iterator last) {
        size_t n = 0;
        for (auto curr = first; curr <= last; ++curr) {
            ++n;
        }

        if (!n) {
            return const_cast<iterator>(last);
        }
        size_t index = first - _data;

        iterator it = _data + index;
        for (size_t i = 0; i < n; i++) {
            (it + i)->~T();
        }

        move_forward(it, it + n, _size - (index + n));

        _size -= n;
        return it;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::data() {
        return _data;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::data() const {
        return data();
    }

    template<class T>
    template<typename... Args>
    void vector<T>::emplace_back(Args&& ... args) {
        emplace(end(), args ...);
    }

    template<class T>
    void vector<T>::reserve(size_t size) {
        if (size > _capacity) {
            reallocate(size);
        }
    }

    template<class T>
    void vector<T>::shrink_to_fit() {
        reallocate(_size);
    }

    template<class T>
    void vector<T>::clear() {
        for (auto it = begin(); it != end(); it++) {
            (it)->~T();
        }
        _size = 0;
    }

    template<class T>
    void vector<T>::resize(size_t count) {
        iterator it = _data;
        if (count > _capacity) {
            reallocate(count * expansion_ratio);
        }
        else {
            for (size_t i = count; i < _size; i++) {
                (it + i)->~T();
            }
        }
        _size = count;
    }

    template<class T>
    void vector<T>::resize(size_t count, const T& value) {
        iterator it = _data;
        if (count > _size) {
            size_t lastElementIndex = _size;
            resize(count);
            it = begin();
            for (size_t i = lastElementIndex; i < count; i++) {
                new(it + i) T(value);
            }
        }
        else {
            for (size_t i = count; i < _size; i++) {
                (it + i)->~T();
            }
        }
        _size = count;
    }

    template<class T>
    bool vector<T>::operator==(const vector<T>& other) {
        if (_size != other._size) {
            return false;
        }
        for (size_t i = 0; i < _size; i++) {
            if (*(_data + i) != *(other._data + i)) {
                return false;
            }
        }
        return true;
    }

    template<class T>
    bool vector<T>::operator!=(const vector<T>& other) {
        return !(*this == other);
    }

    template<class T>
    bool vector<T>::operator<(const vector<T>& other) {
        size_t max_size = size() < other.size() ? size() : other.size();
        for (size_t i = 0; i < max_size; i++) {
            if (*(_data + i) < *(other._data + i)) {
                return true;
            }
        }
        return false;
    }

    template<class T>
    bool vector<T>::operator<=(const vector<T>& other) {
        return !(*this > other);
    }

    template<class T>
    bool vector<T>::operator>(const vector<T>& other) {
        size_t max_size = size() < other.size() ? size() : other.size();
        for (size_t i = 0; i < max_size; i++) {
            if (*(_data + i) > *(other._data + i)) {
                return true;
            }
        }
        return false;
    }

    template<class T>
    bool vector<T>::operator>=(const vector<T>& other) {
        return !(*this < other);
    }

    template<class T>
    void vector<T>::swap(vector<T>& other) noexcept {
        using std::swap; //enable ADL https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
        swap(_size, other._size);
        swap(_capacity, other._capacity);
        swap(_data, other._data);
    }
}

#endif //MYSTD_VECTOR_H
