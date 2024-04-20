//
// Created by stasi on 16.04.2024.
//

#include "priority_queue.h"
#include <iostream>
#include <fstream>
#include <sstream>

priority_queue::priority_queue() {

    size = 0;
    capacity = 4;
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

            // If the new key is greater, move up the queue
            while(i > 0 && arr[i - 1].key < new_key) {
                Node temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                i--;
            }

            // If the new key is less, move down the queue
            while(i < size - 1 && arr[i + 1].key >= new_key) {
                Node temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                i++;
            }

            break;
        }
    }
}

int priority_queue::peek() {

    return arr[size - 1].element;
}

int priority_queue::get_size() {

    return size;
}

void priority_queue::print() {

    for(int i = 0; i < size; i++) {
        std::cout << "wartosc: " << arr[i].element << " klucz: " << arr[i].key << std::endl;
    }
}

void priority_queue::load_from_file(std::string file_name, int n)
{
    std::ifstream inputFile(file_name);

    if (!inputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do odczytu.";
        return;
    }

    std::string line;
    for(int i = 0; i < n; i++){

        std::getline(inputFile, line);
        std::istringstream iss(line);
        std::string priority;
        std::string value;
        std::getline(iss, value, ',');
        std::getline(iss, priority, ',');
        insert(std::stoi(value),std::stoi(priority));
    }

    inputFile.close();
}

int priority_queue::get_lowestkey() {
    return arr[size - 1].key;
}

int priority_queue::get_highestkey() {
    return arr[0].key;
}

int priority_queue::get_value(int i) {
    return arr[i].element;
}

void priority_queue::copy(priority_queue &queue) {

    size = queue.size;
    capacity = queue.capacity;
    delete[] arr;
    arr = new Node[capacity];

    for(int i = 0; i < size; i++) {
        arr[i] = queue.arr[i];
    }
}
