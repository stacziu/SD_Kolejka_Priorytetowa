#include <iostream>
#include <chrono>
#include <fstream>
#include <random>

#include "priority_queue.h"

int generuj_x_liczb_do_pliku(int x, std::string nazwa_pliku)
{
    // Otwórz plik do zapisu
    std::ofstream outputFile(nazwa_pliku);

    // Sprawdź, czy plik został poprawnie otwarty
    if (!outputFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu.";
        return 1;
    }
    // Pobierz minimalną i maksymalną wartość dla typu int
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    // Inicjalizuj generator liczb pseudolosowych
    std::random_device rd;
    std::mt19937 gen(rd());
    // Utwórz rozkład równomierny na przedziale [min_int, max_int]
    std::uniform_int_distribution<int> distribution(min_int, max_int);
    // Wygeneruj x losowych liczb i zapisz je do pliku CSV
    for (int i = 0; i < x; ++i) {
        // Wylosuj liczbę z przedziału [min_int, max_int]
        int random_number = distribution(gen);

        // Zapisz wylosowaną liczbę do pliku CSV
        outputFile << random_number << ",";
        random_number = distribution(gen);
        outputFile<< random_number << ",";

        // Dodaj znak nowej lini, z wyjątkiem ostatniej liczby w wierszu
        if (i < x - 1)
            outputFile << "\n";
    }
    outputFile.close();
    return 0;
}

void priority_queue_test_modifyKey(int numOfArrays, std::string plik, int size){
    std::ofstream results(plik);

    generuj_x_liczb_do_pliku(size, "dane.txt");
    auto time = 0;
    for(int l = 0; l < 100; l++) {
        priority_queue *queues = new priority_queue[numOfArrays];

        queues[0].load_from_file("dane.txt", size);
        for (int i = 1; i < numOfArrays; i++) {

            queues[i].copy(queues[0]);
        }

        int min_int = std::numeric_limits<int>::min();
        int max_int = std::numeric_limits<int>::max();
        std::random_device rd_key;
        std::mt19937 gen_key(rd_key());
        std::uniform_int_distribution<int> distribution_key(min_int, max_int);

        int rand_key = distribution_key(gen_key);

        std::random_device rd_index;
        std::mt19937 gen_index(rd_index());
        std::uniform_int_distribution<int> distribution_index(0, size - 1);

        int rand_index = distribution_index(gen_index);
        int rand_element = queues[0].get_value(rand_index);
        auto begin = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numOfArrays; i++) {

            queues[i].modify_key(rand_element, rand_key);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        time += elapsed.count() / numOfArrays;
        delete[] queues;
    }
    results << time / 100 << std::endl;
}

void priority_queue_test_insertFront(int numOfArrays, std::string plik, int size){
    std::ofstream results(plik);

    generuj_x_liczb_do_pliku(size, "dane.txt");

    priority_queue* queues = new priority_queue[numOfArrays];

    queues[0].load_from_file("dane.txt", size);
    for (int i = 1; i < numOfArrays; i++) {

        queues[i].copy(queues[0]);
    }

    int highest_prio = queues[0].get_lowestkey();
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numOfArrays; i++) {

        queues[i].insert(1,highest_prio);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    results << elapsed.count() / numOfArrays << std::endl;

    delete[] queues;
}

void priority_queue_test_extract(int numOfArrays, std::string plik, int size){
    std::ofstream results(plik);

    generuj_x_liczb_do_pliku(size, "dane.txt");

    priority_queue* queues = new priority_queue[numOfArrays];

    queues[0].load_from_file("dane.txt", size);
    for (int i = 1; i < numOfArrays; i++) {

        queues[i].copy(queues[0]);
    }

    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numOfArrays; i++) {

        queues[i].extract_max();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    results << elapsed.count() / numOfArrays << std::endl;

    delete[] queues;
}

void priority_queue_test_insertBack(int numOfArrays, std::string plik, int size){
    std::ofstream results(plik);

    generuj_x_liczb_do_pliku(size, "dane.txt");

    priority_queue* queues = new priority_queue[numOfArrays];

    queues[0].load_from_file("dane.txt", size);
    for (int i = 1; i < numOfArrays; i++) {

        queues[i].copy(queues[0]);
    }

    int lowest_prio = queues[0].get_highestkey();
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numOfArrays; i++) {

        queues[i].insert(1,lowest_prio);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    results << elapsed.count() / numOfArrays << std::endl;

    delete[] queues;
}

void priority_queue_test_peek(int numOfArrays, std::string plik, int size){
    std::ofstream results(plik);

    generuj_x_liczb_do_pliku(size, "dane.txt");

    priority_queue* queues = new priority_queue[numOfArrays];

    queues[0].load_from_file("dane.txt", size);
    for (int i = 1; i < numOfArrays; i++) {

        queues[i].copy(queues[0]);
    }

    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numOfArrays; i++) {

        queues[i].peek();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    results << elapsed.count() / numOfArrays << std::endl;

    delete[] queues;
}

int main() {

    priority_queue_test_insertFront(100, "insert100Front.txt", 100);
    priority_queue_test_insertFront(100, "insert1000Front.txt", 1000);
    priority_queue_test_insertFront(100, "insert2000Front.txt", 2001);
    priority_queue_test_insertFront(100, "insert4000Front.txt", 4000);
    priority_queue_test_insertFront(100, "insert8000Front.txt", 8000);
    priority_queue_test_insertFront(100, "insert16000Front.txt", 16000);
    priority_queue_test_insertFront(100, "insert320000Front.txt", 32000);
    priority_queue_test_insertFront(100, "insert640000Front.txt", 64000);
    priority_queue_test_insertFront(100, "insert128000Front.txt", 128000);

    priority_queue_test_insertBack(100, "results100Back.txt", 100);
    priority_queue_test_insertBack(100, "results1000Back.txt", 1000);
    priority_queue_test_insertBack(100, "results2000Back.txt", 2000);
    priority_queue_test_insertBack(100, "results4000Back.txt", 4000);
    priority_queue_test_insertBack(100, "results8000Back.txt", 8000);
    priority_queue_test_insertBack(100, "results16000Back.txt", 16000);
    priority_queue_test_insertBack(100, "results320000Back.txt", 32000);
    priority_queue_test_insertBack(100, "results640000Back.txt", 64000);
    priority_queue_test_insertBack(100, "results128000Back.txt", 128000);

    priority_queue_test_modifyKey(10, "results100modify.txt", 100);
    priority_queue_test_modifyKey(10, "results1000modify.txt", 1000);
    priority_queue_test_modifyKey(10, "results2000modify.txt", 2000);
    priority_queue_test_modifyKey(10, "results4000modify.txt", 4000);
    priority_queue_test_modifyKey(10, "results8000modify.txt", 8000);
    priority_queue_test_modifyKey(10, "results16000modify.txt", 16000);
    priority_queue_test_modifyKey(10, "results320000modify.txt", 32000);
    priority_queue_test_modifyKey(10, "results640000modify.txt", 64000);
    priority_queue_test_modifyKey(10, "results128000modify.txt", 128000);

    priority_queue_test_extract(100, "results100extract.txt", 100);
    priority_queue_test_extract(100, "results1000extract.txt", 1000);
    priority_queue_test_extract(100, "results2000extract.txt", 2000);
    priority_queue_test_extract(100, "results4000extract.txt", 4000);
    priority_queue_test_extract(100, "results8000extract.txt", 8000);
    priority_queue_test_extract(100, "results16000extract.txt", 16000);
    priority_queue_test_extract(100, "results320000extract.txt", 32000);
    priority_queue_test_extract(100, "results640000extract.txt", 64000);
    priority_queue_test_extract(100, "results128000extract.txt", 128000);

    priority_queue_test_peek(100, "results100peek.txt", 100);
    priority_queue_test_peek(100, "results1000peek.txt", 1000);
    priority_queue_test_peek(100, "results2000peek.txt", 2000);
    priority_queue_test_peek(100, "results4000peek.txt", 4000);
    priority_queue_test_peek(100, "results8000peek.txt", 8000);
    priority_queue_test_peek(100, "results16000peek.txt", 16000);
    priority_queue_test_peek(100, "results320000peek.txt", 32000);
    priority_queue_test_peek(100, "results640000peek.txt", 64000);
    priority_queue_test_peek(100, "results128000peek.txt", 128000);


    return 0;
}
