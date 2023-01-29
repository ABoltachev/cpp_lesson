#ifndef SMART_POINTER_TPP
#define SMART_POINTER_TPP

// AutoPtr

template<typename T>
AutoPtr<T>::AutoPtr(T *ptr) : m_ptr(ptr) {}

template<typename T>
AutoPtr<T>::~AutoPtr() {
    delete m_ptr;
}

template<typename T>
AutoPtr<T>::AutoPtr(AutoPtr &a) {
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
}

template<typename T>
AutoPtr<T>& AutoPtr<T>::operator=(AutoPtr &a) {
    if (&a == this) {
        return *this;
    }

    delete m_ptr;
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    return *this;
}

template<typename T>
T& AutoPtr<T>::operator*() const {
    return *m_ptr;
}

template<typename T>
T* AutoPtr<T>::operator->() const {
    return m_ptr;
}

template<typename T>
bool AutoPtr<T>::isNull() const {
    return m_ptr == nullptr;
}

// SmartPtr

template<typename T>
SmartPtr<T>::SmartPtr(T *ptr) : m_ptr(ptr) {}

template<typename T>
SmartPtr<T>::~SmartPtr() {
    delete m_ptr;
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr &a) {
    m_ptr = new T;
    *m_ptr = *a.m_ptr;
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr &a) {
    if (&a == this) {
        return *this;
    }

    delete m_ptr;
    m_ptr = new T;
    *m_ptr = *a.m_ptr;
    return *this;
}

template<typename T>
T& SmartPtr<T>::operator*() const {
    return *m_ptr;
}

template<typename T>
T* SmartPtr<T>::operator->() const {
    return m_ptr;
}

template<typename T>
bool SmartPtr<T>::isNull() const {
    return m_ptr == nullptr;
}

// SmarterPtr

template<typename T>
SmarterPtr<T>::SmarterPtr(T *ptr) : SmartPtr<T>(ptr) {}

template<typename T>
SmarterPtr<T>::SmarterPtr(const SmarterPtr &a) {
    SmartPtr<T>::m_ptr = new T;
    *SmartPtr<T>::m_ptr = *a.m_ptr;
}

template<typename T>
SmarterPtr<T>::SmarterPtr(SmarterPtr &&a) {
    SmartPtr<T>::m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
}

template<typename T>
SmarterPtr<T>& SmarterPtr<T>::operator=(SmarterPtr &&a) {
    std::cout << "test" << std::endl;
    if (&a == this) {
        return *this;
    }

    delete SmartPtr<T>::m_ptr;
    SmartPtr<T>::m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    return *this;
}

template<typename T>
T& SmarterPtr<T>::operator*() const {
    return *SmartPtr<T>::m_ptr;
}

template<typename T>
T* SmarterPtr<T>::operator->() const {
    return SmartPtr<T>::m_ptr;
}

template<typename T>
bool SmarterPtr<T>::isNull() const {
    return SmartPtr<T>::m_ptr == nullptr;
}

#endif // SMART_POINTER_TPP
