#pragma once  
#include <iostream>  
#include "Two way node.h"  
using namespace std;  
template <typename T>
class TwoWayList;

template <typename T>
TwoWayList<T> operator+(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs);

template<typename T>
TwoWayList<T> operator*(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs);

/*  
Задание 1  
Реализовать шаблонный класс "Очередь" на основе двусвязного списка.  

Задание 2  
В существующий класс двусвязного списка добавить: операцию клонирования списка (функция должна возвращать адрес головы клонированного списка), перегрузить оператор + (оператор должен возвращать адрес головы нового списка, содержащего элементы обоих списков для которых вызывался оператор), перегрузить оператор * (оператор должен возвращать адрес головы нового списка, содержащего только общие элементы обоих списков для которых вызывался оператор).  
*/ //
template <typename T>  
class TwoWayList {
private:
    Node<T>* mHead = nullptr; // Указатель на голову списка  
    Node<T>* mTail = nullptr; // Указатель на хвост списка  
    size_t mSize = 0;         // Размер списка  

   static bool isCommonElement(const T& data, const TwoWayList<T>& list);
   static bool isAlreadyInResult(const T& data, const TwoWayList<T>& list);

public:

    TwoWayList() = default;
    ~TwoWayList();

    void clear();
    void enqueue(const T& data);
    void enqueue(Node<T>* node);
    T dequeue();
    bool isEmpty() const { return mHead == nullptr; }
    size_t getSize() const { return mSize; }
    T front() const;
    void output() const;
    Node<T>* clone() const;

    friend TwoWayList<T> operator+ <>(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs);
    friend TwoWayList<T> operator* <>(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs);
};

template<typename T>
inline TwoWayList<T> operator+(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs)
{
    TwoWayList<T> result;

    Node<T>* current = lhs.mHead;
    while (current) {
        result.enqueue(current->mData);
        current = current->mNext;
    }

    current = rhs.mHead;
    while (current) {
        result.enqueue(current->mData);
        current = current->mNext;
    }

    return result;
}

template<typename T>
inline TwoWayList<T> operator*(const TwoWayList<T>& lhs, const TwoWayList<T>& rhs)
{
    TwoWayList<T> result;

    Node<T>* currentLhs = lhs.mHead;
    while (currentLhs) {
        if (TwoWayList<T>::isCommonElement(currentLhs->mData, rhs) && 
            !TwoWayList<T>::isAlreadyInResult(currentLhs->mData, result)) {
            result.enqueue(currentLhs->mData);
        }
        currentLhs = currentLhs->mNext;
    }

    return result;
}

template<typename T>
inline bool TwoWayList<T>::isCommonElement(const T& data, const TwoWayList<T>& list)
{
    Node<T>* currentRhs = list.mHead;
    while (currentRhs) {
        if (currentRhs->mData == data) {
            return true;
        }
        currentRhs = currentRhs->mNext;
    }
    return false;
}

template<typename T>
inline bool TwoWayList<T>::isAlreadyInResult(const T& data, const TwoWayList<T>& result)
{
    Node<T>* check = result.mHead;
    while (check) {
        if (check->mData == data) {
            return true;
        }
        check = check->mNext;
    }
    return false;
}

template<typename T>
inline TwoWayList<T>::~TwoWayList()
{
    clear();
}

template<typename T>
inline void TwoWayList<T>::clear() {
    while (mHead) {
        Node<T>* temp = mHead;
        mHead = mHead->mNext;
        delete temp;
    }
    mTail = nullptr;
    mSize = 0;
}

template<typename T>
inline void TwoWayList<T>::enqueue(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (!mTail) {
        mHead = mTail = newNode;
    }
    else {
        mTail->mNext = newNode;
        newNode->mPrev = mTail;
        mTail = newNode;
    }
    ++mSize;
}

template<typename T>
inline void TwoWayList<T>::enqueue(Node<T>* node) {
    if (!node) return; 
    if (!mTail) {
        mHead = mTail = node;
    }
    else {
        mTail->mNext = node;
        node->mPrev = mTail;
        mTail = node;
    }
    ++mSize;
}

template<typename T>
inline T TwoWayList<T>::dequeue()
{
    if (!mHead) {
    return T();
}
    Node<T>* temp = mHead;
    T data = temp->mData;
    mHead = mHead->mNext;
    if (mHead) {
        mHead->mPrev = nullptr;
    }
    else {
        mTail = nullptr;
    }
    delete temp;
    --mSize;
    return data;
}

template<typename T>
inline T TwoWayList<T>::front() const
{
    if (!mHead) {
        cout << "Queue is empty" << endl;
        return T();
    }

    return mHead->mData;
}

template<typename T>
inline void TwoWayList<T>::output() const
{
    cout << "Currently in queue:" << endl;
    Node<T>* current = mHead; 
    while (current) {
        cout << current->mData << " "; 
        current = current->mNext;     
    }
    cout << endl << string(15, '-') << endl;
}

template <typename T>
Node<T>* TwoWayList<T>::clone() const {
    if (!mHead) {
        return nullptr;
    }

    Node<T>* newHead = new Node<T>(mHead->mData);
    Node<T>* currentOld = mHead->mNext;
    Node<T>* currentNew = newHead;   

    while (currentOld) {
        Node<T>* newNode = new Node<T>(currentOld->mData);
        currentNew->mNext = newNode;   
        newNode->mPrev = currentNew; 
        currentNew = newNode;      
        currentOld = currentOld->mNext; 
    }

    return newHead; 
}

