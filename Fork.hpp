#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


class Fork {
public:
    Fork(int id);
    bool pickUp();
    void putDown();
    void print();
    int id;
private:
    bool inUse;
    std::mutex* mutex;
};
