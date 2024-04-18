#include <iostream>
#include "priority_queue.h"

int main() {

    priority_queue Kolejka;

    Kolejka.insert(100,1);
    Kolejka.insert(100,2);
    Kolejka.insert(100,10);
    Kolejka.insert(100,4);
    Kolejka.insert(100,1);
    Kolejka.insert(101,4);

    Kolejka.print();
    //Kolejka.extract_max();
    std::cout << std::endl;
    Kolejka.modify_key(101,12);
    Kolejka.print();
    return 0;
}
