
#ifndef NODE_H
#define NODE_H

// Node of a doubly Linked list
template <class T>
class Node {

public:
    T data;
    Node<T> *next;
    Node<T> *prev;

    Node(); 
    Node(T data);
    ~Node(); 
};


template <class T>
Node<T>::Node() {
    next = NULL;
    prev = NULL;
}

template <class T>
Node<T>::Node(T data) {
    this->data = data;
    next = NULL;
    prev = NULL;
}

template <class T>
Node<T>::~Node() {
}


#endif