#ifndef QUEUE_H
#define QUEUE_H

#include "DoublyLinkedList.h"

// Queue class, derived from linked list class
template <class T>
class Queue : public DoublyLinkedList<T> {

public:
    Queue() {
        DoublyLinkedList<T>();
    }

    // push the data into the queue
    void enqueue(T data) {
        DoublyLinkedList<T>::insert_beginning(data);
    }


    // removes and returns the data from the queue
    T dequeue() {
        return DoublyLinkedList<T>::remove_end();
    }

    // reutrns the top element of the queue
    T peek() {
        return DoublyLinkedList<T>::get_tail_data();
    }

    // returns true if the queue is empty
    bool is_empty() {
        return DoublyLinkedList<T>::isEmpty();
    }

};
    


#endif