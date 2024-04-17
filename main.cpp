#include <iostream>
#include "priority_queue.h"

int main() {

    priority_queue Kolejka;

    Kolejka.insert(101,1);
    Kolejka.insert(101,2);
    Kolejka.insert(105,10);
    Kolejka.insert(100,4);

    Kolejka.print();
    Kolejka.extract_max();
    Kolejka.print();
    return 0;
}
