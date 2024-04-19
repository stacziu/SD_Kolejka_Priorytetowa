//
// Created by stasi on 16.04.2024.
//

#ifndef SD2_PRIORITY_QUEUE_H
#define SD2_PRIORITY_QUEUE_H
#include <iostream>

struct Node {

    int element;
    int key;
};

class priority_queue {

int size;
Node *arr;
int capacity;

public:
    priority_queue();
    ~priority_queue();
    void insert(int element, int key);
    int extract_max();
    int peek();
    int get_size();
    void modify_key(int element, int new_key);
    void print();
    void increase_capacity();
    void decrease_capacity();
    void load_from_file(std::string file_name, int n);
    int get_highestkey();
    int get_lowestkey();
    int get_value(int i);
    void copy(priority_queue &queue);
};


#endif //SD2_PRIORITY_QUEUE_H
