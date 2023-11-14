#include "Fork.hpp"

Fork::Fork(int id) : id(id), inUse(false) {}


bool Fork::pickUp() {
    std::unique_lock<std::mutex> lock(mutex);
    if (inUse) {
        return false;
    }
    else {
        inUse = true;
        return true;
    }
}

void Fork::putDown() {
    std::unique_lock<std::mutex> lock(mutex);
    inUse = false;
}