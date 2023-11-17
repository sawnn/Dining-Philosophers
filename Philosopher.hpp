#pragma once
#include <atomic>
#include <thread>
#include <mutex>
#include "Fork.hpp"
#include <iostream>
#include <algorithm>

class Philosopher {
public:
    Philosopher(int id, Fork& left, Fork& right, int hungry_limit);
    void start();
    void stop();
    void think();
    void eat();
    void join();
    void print();
    void swapFork();
    bool leftPickUp();
    bool rightPickUp();
private:
    int id;
    Fork& left;
    Fork& right;
    int hungry_limit;
    std::thread* thread;
    bool eating;
    bool thinking;
};