#pragma once

#include <initializer_list>
#include <cstddef>

template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    
public:

    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) {
            data[i++] = val;
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& val);   // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void pop_back();                // Vector의 마지막 항목을 제거하는 함수 구현
    size_t size() const;            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](int i) ;          // [] 연산자 구현

    bool operator==(const MyVector& other) const;

    bool operator!=(const MyVector& other) const;

    bool operator<(const MyVector& other) const;

    bool operator>(const MyVector& other) const;

    bool operator<=(const MyVector& other) const;

    bool operator>=(const MyVector& other) const;


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*(); // 역참조 연산자 구현 

        Iterator& operator++();   //전위 증가 연산자 구현
        Iterator& operator--();   //전위 감소 연산자 구현
        Iterator operator+(int n) const ;   // 산술 연산자 구현
        Iterator operator-(int n) const ;   // 산술 연산자 구현

        bool operator==(const Iterator& other) const ;
        bool operator!=(const Iterator& other) const ;

        int operator-(const Iterator& other) const ;
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() ;
    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() ;


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value);

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos);

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() ;

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i); 

    // front/back
    T& front() ;    // 첫번째 항목 리턴 함수 구현
    T& back() ;     // 마지막 항목 리턴 함수 구현

    // capacity
    size_t capacity() const ;   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const ;    // 현재 vector가 empty인지 확인하는 함수 구현

};

#include <stdexcept>

template<typename T>
void MyVector<T>::push_back(const T& val) {
    if(size() == cap) {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];

        for (size_t i = 0; i < size(); ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        cap = newCap;
    }
    data[length++] = val;
}
template<typename T>
void MyVector<T>::pop_back() {
    if(length == 0) throw std::out_of_range("Index out of range");
    length--;
    
}
template<typename T>
size_t MyVector<T>::size() const {
    return length;
}
template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[i];
}

template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}
template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ptr++;
    return *this;
}
template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    ptr--;
    return *this;
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr + n);
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr - n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data+size());
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    long long index = pos - begin();

    if (length == cap) {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        T* newData = new T[newCap];

        for (size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }

        if (data) delete[] data;
        data = newData;
        cap = newCap; 
    }

    for (long long i = length; i > index; i--) {
        data[i] = data[i - 1];
    }

    length++;
    data[index] = value;
    
    return Iterator(data + index);
}
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    long long index = pos - begin();
    
    for (long long i = index; i < length - 1; i++) {
        data[i] = data[i + 1];
    }

    length--;

    return Iterator(data + index);
}


template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) throw std::out_of_range("Index out of range");
    return data[i];
}

template<typename T>
T& MyVector<T>::front() {
    return data[0];
}
template<typename T>
T& MyVector<T>::back() {
    return data[length-1];
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
} 

template<typename T>
bool MyVector<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if(length != other.length) return false;
    for(size_t i = 0; i < length; i++) {
        if(data[i] != other.data[i]) return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t minLen = (length < other.length) ? length : other.length;

    for (size_t i = 0; i < minLen; ++i) {
        if (data[i] < other.data[i]) return true;  
        if (data[i] > other.data[i]) return false; 
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return ptr - other.ptr;
}