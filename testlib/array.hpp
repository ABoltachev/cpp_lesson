#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T>
class CopyArray {
protected:
    T* m_array;
    size_t m_size;
public:
    CopyArray(size_t size);

    CopyArray() = default;

    ~CopyArray();

    CopyArray(const CopyArray &arr);

    CopyArray& operator=(const CopyArray &arr);

    int getLength() const;
    T& operator[](int index);
    const T& operator[](int index) const;
};

template <typename T>
class MoveArray : public CopyArray<T> {
public:
    MoveArray(size_t size);

    MoveArray(const MoveArray &arr);

    MoveArray(MoveArray &&arr);

    MoveArray& operator=(MoveArray &&arr);

};

CopyArray<int> cloneArrayAndDouble(const CopyArray<int> &arr) {
    CopyArray<int> dbl(arr.getLength());
    for (int i = 0; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;
    return dbl;
}

MoveArray<int> cloneArrayAndDouble(const MoveArray<int> &arr) {
    MoveArray<int> dbl(arr.getLength());
    for (int i = 0; i < arr.getLength(); ++i)
        dbl[i] = arr[i] * 2;
    return dbl;
}

#include "array.tpp"

#endif // ARRAY_HPP
