#include <iostream>
#include <vector>
#include "Philosopher.hpp"
#include "Fork.hpp"



int main() {
    std::vector<Fork> forks;
    std::vector<Philosopher> philosophers;

    for (int i = 0; i < 5; i++) {
        forks.push_back(Fork(i));
    }

    for (int i = 0; i < 5; i++) {
        philosophers.push_back(Philosopher(i, forks[i], forks[(i + 1) % 5], 10));
    }

    for (auto& philosopher : philosophers) {
        philosopher.join();
    }




    return 0;
}