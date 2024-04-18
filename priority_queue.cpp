//
// Created by stasi on 16.04.2024.
//

#include "priority_queue.h"
#include <iostream>
priority_queue::priority_queue() {

    size = 0;
    capacity = 1;
    arr = new Node[capacity];
}

priority_queue::~priority_queue() {

    delete[] arr;
}

void priority_queue::increase_capacity() {

    if(size == capacity) {

        capacity *= 2;
        Node *new_arr = new Node[capacity];

        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }
}

void priority_queue::decrease_capacity() {

    if(size == capacity / 2) {

        capacity = size;
        Node *new_arr = new Node[capacity];

        for(int i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
    }
}

void priority_queue::insert(int element, int key){

    size++;
    increase_capacity();
    int i = size - 1;
    arr[i].element = element;
    arr[i].key = key;
    while(arr[i - 1].key < key && i - 1 >= 0) {

        Node temp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = temp;
        i--;
    }

}

int priority_queue::extract_max() {

    size--;
    decrease_capacity();
    return arr[size + 1].element;
}

void priority_queue::modify_key(int element, int new_key) {

    for(int i = 0; i < size; i++) {

        if(arr[i].element == element) {

            arr[i].key = new_key;
            while(arr[i - 1].key < new_key && i - 1 >= 0) {

                Node temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                i--;
            }
            break;
        }
    }
}

int priority_queue::peek() {

    return arr[0].element;
}

int priority_queue::get_size() {

    return size;
}

void priority_queue::print() {

    for(int i = 0; i < size; i++) {
        std::cout << "wartosc: " << arr[i].element << " klucz: " << arr[i].key << std::endl;
    }
}

