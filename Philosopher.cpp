#include "Philosopher.hpp"

Philosopher::Philosopher(int id, Fork& left, Fork& right, int hungry_limit) : id(id), left(left), right(right), hungry_limit(hungry_limit), eating(false), thinking(false) {
    thread = new std::thread(&Philosopher::start, this);
}



void Philosopher::start() {
    while (true) {
        eat();
        think();
    }
}

void Philosopher::stop() {
    
    if (thread) {
        thread->join();
        delete thread;
        thread = nullptr;
    }
}


void Philosopher::think() {

    thinking = true;
    print();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    thinking = false;

    
}

void Philosopher::eat() {
    if (leftPickUp()) {
        if (rightPickUp()) {
            eating = true;
            print();
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            right.putDown();
            left.putDown();
            eating = false;
        }
    }
}

bool Philosopher::leftPickUp() {
    if (left.id > right.id) {
        return right.pickUp();
    }
    else {

        return left.pickUp();
    }
}

bool Philosopher::rightPickUp() {
    if (left.id > right.id) {
        return left.pickUp();
    }
    else {
        return right.pickUp();
    }
}

void Philosopher::join() {
    thread->join();
}

void Philosopher::print() {
    std::cout << "Philosopher " << id << " is ";
    if (eating) {
        std::cout << "eating" << std::endl;
    }
    else if (thinking) {
        std::cout << "thinking" << std::endl;
    }
}

