
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <iostream>
#include "Node.h"

using namespace std;

// Doubly Linked List class
template <class T>
class DoublyLinkedList {
    private:
        Node<T> *head;      // pointer to the head
        Node<T> *tail;      // pointer to the tail
        int size;           // size of the list

    public: 
        DoublyLinkedList(); 
        ~DoublyLinkedList(); 

        // insert data at the given position
        void insert(T data, int position);
        // insert data at the beginning
        void insert_beginning(T data);
        // insert data at the end
        void insert_end(T data);

        // removes and returns the data present at the head
        T remove_beginning();
        // removes and returns the data present at the tail 
        T remove_end();

        // returns the data present at the head
        T get_head_data();
        // returns the data present at the tail
        T get_tail_data();
        // returns the data present at the given position
        T get_data(int position);

        // displays the linked list to stdout
        void display();
        
        // returns true if the linked list is empty
        bool isEmpty();

        // returns the number of elements in the list
        int get_size();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node<T> *current = head;
    // deallocated  each node
    while (current != NULL) {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }
}

// insert data at the given position
template <class T>
void DoublyLinkedList<T>::insert(T d, int position) {
    // if the given position is invalid
    if (position < 0 || position > size) {
        cout << "Error: Cannot insert data, invalid position!";
        return;
    }

    Node<T> *node = new Node<T>(d);
    
    // insert at head
    if (position == 0)
        insert_beginning(d);
    // insert at tail
    else if (position == size-1)
        insert_end(d);
    // insert in the middle
    else {
        int index = 0;
        Node<T> *current = head;
        while (index != position) {
            index++;
            current = current->next;
        }

        node->next = current->next;
        node->prev = current;

        current->next = node;
        node->next->prev = node;

        size++;
    }
}


// inserts data at the beginning
template <class T>
void DoublyLinkedList<T>::insert_beginning(T d) {
    Node<T> *node = new Node<T>(d);
    
    // if list is empty
    if (head == NULL) {
        head = node;
        tail = node;
        size++;
    }
    else {
        node->next = head;
        head->prev = node;
        head = node;
        size++;
    }
    
}

// inserts data at the end of the list
template <class T>
void DoublyLinkedList<T>::insert_end(T d) {
    Node<T> *node = new Node<T>(d);
    
    // if list is empty
    if (head == NULL) {
        head = node;
        tail = node;
        size++;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        size++;
    }
    
}


// removes and returns data present at the head 
template <class T>
T DoublyLinkedList<T>::remove_beginning() {

    // if list is empty
    if (head == NULL)
        return T();

    // if only 1 node in the list
    if (head->next == NULL) {
        T data = head->data;
        delete head;
        head = NULL;
        tail = NULL;
        size--;
        return data;
    }

    // more than 1 node in the list
    T data = head->data;
    Node<T> *temp = head;
    head = head->next;
    head->prev = NULL;
    delete temp;
    size--;
    return data;
}


// removes and returns data present at the tail 
template <class T>
T DoublyLinkedList<T>::remove_end() {

    // if list is empty
    if (head == NULL)
        return T();

    // if only 1 node in the list
    if (head->next == NULL) {
        T data = head->data;
        delete head;
        head = NULL;
        tail = NULL;
        size--;
        return data;
    }

    // more than 1 node in the list
    T data = tail->data;
    Node<T> *temp = tail;
    tail = tail->prev;
    tail->next = NULL;
    delete temp;
    size--;
    return data;
}


// returns the data present at the head
template <class T>
T DoublyLinkedList<T>::get_head_data() {
    if (size == 0) {
        cout << "Error: Cannot get data, list is empty!";
        return T();
    }

    return head->data;
}


// returns the data present at the tail
template <class T>
T DoublyLinkedList<T>::get_tail_data() {
    if (size == 0) {
        cout << "Error: Cannot get data, list is empty!";
        return T();
    }

    return tail->data;
}


// returns the data present at the given position
template <class T>
T DoublyLinkedList<T>::get_data(int position) {

    // if posoition is invalid
    if (position < 0 || position >= size) {
        cout << "Error: Cannot get data, invalid position!";
        return T();
    }

    int index = 0;
    Node<T> *current = head;
    while (index != position) {
        index++;
        current = current->next;
    }

    return current->data;
}


// prints the list to stdout
template <class T>
void DoublyLinkedList<T>::display() {
    cout << "Size: " << size << endl;
    Node<T> *current = head;
    while(current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// returns true if the list is empty
template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return(size == 0);
}


template <class T>
int DoublyLinkedList<T>::get_size() {
    return size;
}



#endif