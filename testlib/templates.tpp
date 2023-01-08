#ifndef TEMPLATES_TPP
#define TEMPLATES_TPP

namespace TestLib {
    template<class T>
    int Array<T>::getLength() const {
        return m_length;
    }

    template<class T>
    T& Array<T>::operator[](int index) {
        if (index < 0 || index >= m_length) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }
    template<class T>
    const T& Array<T>::operator[](int index) const {
        if (index < 0 || index >= m_length) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }


    template<class T, size_t size>
    int StaticArray<T, size>::getLength() const {
        return size;
    }

    template<class T, size_t size>
    T& StaticArray<T, size>::operator[](size_t index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }
    template<class T, size_t size>
    const T& StaticArray<T, size>::operator[](size_t index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }

    template<size_t size>
    int StaticArray<char, size>::getLength() const {
        return size;
    }

    template<size_t size>
    int StaticArray<char, size>::operator[](size_t index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }
    template<size_t size>
    const int StaticArray<char, size>::operator[](size_t index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index: " + std::to_string(index) + "out of range");
        }
        return m_data[index];
    }
}

#endif // TEMPLATES_TPP
