#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
	T mData;
	Node<T>* mNext;
	Node<T>* mPrev;
	explicit Node(const T& data) : mData(data), mNext(nullptr), mPrev(nullptr) {}
	Node(const Node<T>& other);
	Node(Node<T>&& other) noexcept;

    Node<T>& operator= (const Node<T>& other);
    Node<T>& operator= (Node<T>&& other) noexcept;

};

template<typename T>
inline Node<T>::Node(const Node<T>& other)
    : mData(other.mData), mNext(nullptr), mPrev(nullptr) {
    if (other.mNext) {
        mNext = new Node<T>(*other.mNext);
    }
    if (other.mPrev) {
        mPrev = new Node<T>(*other.mPrev);
    }
}

template<typename T>
inline Node<T>::Node(Node<T>&& other) noexcept
    : mData(std::move(other.mData)), mNext(other.mNext), mPrev(other.mPrev) {
    other.mNext = nullptr;
    other.mPrev = nullptr;
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& other) {
    if (this == &other) {
        return *this;
    }

    delete mNext;
    delete mPrev;

    mData = other.mData;

    if (other.mNext) {
        mNext = new Node<T>(*other.mNext);
    }
    else {
        mNext = nullptr;
    }

    if (other.mPrev) {
        mPrev = new Node<T>(*other.mPrev);
    }
    else {
        mPrev = nullptr;
    }

    return *this;
}


template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete mNext;
    delete mPrev;

    mData = std::move(other.mData);
    mNext = other.mNext;
    mPrev = other.mPrev;


    other.mNext = nullptr;
    other.mPrev = nullptr;

    return *this;
}

