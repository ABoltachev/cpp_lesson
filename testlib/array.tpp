#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
CopyArray<T>::CopyArray(size_t size) : m_array(new T[size]), m_size(size) {}

template <typename T>
CopyArray<T>::~CopyArray() {
    delete[] m_array;
}

template <typename T>
CopyArray<T>::CopyArray(const CopyArray &arr) : m_size(arr.m_size) {
    m_array = new T[m_size];
    for (int i = 0; i < m_size; ++i)
        m_array[i] = arr.m_array[i];
}

template <typename T>
CopyArray<T>& CopyArray<T>::operator=(const CopyArray &arr) {
    if (&arr == this)
        return *this;

    delete[] m_array;
    
    m_size = arr.m_size;
    m_array = new T[m_size];

    for (int i = 0; i < m_size; ++i)
        m_array[i] = arr.m_array[i];

    return *this;
}

template <typename T>
int CopyArray<T>::getLength() const { return m_size; }

template <typename T>
T& CopyArray<T>::operator[](int index) { return m_array[index]; }

template <typename T>
const T& CopyArray<T>::operator[](int index) const { return m_array[index]; }

template <typename T>
MoveArray<T>::MoveArray(size_t size) : CopyArray<T>(size) {}

template <typename T>
MoveArray<T>::MoveArray(const MoveArray &arr) : CopyArray<T>(arr) {}

template <typename T>
MoveArray<T>::MoveArray(MoveArray &&arr) {
    CopyArray<T>::m_size = arr.m_size;
    CopyArray<T>::m_array = arr.m_array;
    arr.m_array = nullptr;
    arr.m_size = 0;
}

template <typename T>
MoveArray<T>& MoveArray<T>::operator=(MoveArray &&arr) {
    std::cout << "Move" << std::endl;
    if (&arr == this)
        return *this;

    delete[] CopyArray<T>::m_array;
    
    CopyArray<T>::m_size = arr.m_size;
    CopyArray<T>::m_array = arr.m_array;

    arr.m_array = nullptr;
    arr.m_size = 0;

    return *this;
}

#endif // ARRAY_TPP