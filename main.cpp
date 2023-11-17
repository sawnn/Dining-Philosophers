#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

std::mutex outputMutex;


class Fork {
public:
    Fork() = default; 

    Fork(int id) : id(id) {}

    int getId() const {
        return id;
    }

    std::mutex& getMutex() {
        return mutex;
    }

private:
    int id;
    std::mutex mutex;
};

class Philosopher {
public:
    Philosopher(int id, Fork& leftFork, Fork& rightFork, int hungryLimit)
        : id(id), leftFork(leftFork), rightFork(rightFork), hungryLimit(hungryLimit), eating(false), thinking(false) {}

    void start() {
        thread = std::unique_ptr<std::thread>(new std::thread(&Philosopher::run, this));
    }

    void stop() {
        if (thread && thread->joinable()) {
            thread->join();
        }
    }

private:
    void run() {
        while (true) {
            eat();
            think();
        }
    }

    void eat() {
        std::lock(leftFork.getMutex(), rightFork.getMutex());
        std::lock_guard<std::mutex> leftLock(leftFork.getMutex(), std::adopt_lock);
        std::lock_guard<std::mutex> rightLock(rightFork.getMutex(), std::adopt_lock);

        eating = true;
        std::cout << "Philosopher " << id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        eating = false;
    }

    void think() {
        std::lock_guard<std::mutex> lock(outputMutex);

        thinking = true;
        std::cout << "Philosopher " << id << " is thinking." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        thinking = false;
    }

    int id;
    Fork& leftFork;
    Fork& rightFork;
    int hungryLimit;
    bool eating;
    bool thinking;
    std::unique_ptr<std::thread> thread;
};

int main() {
    const int NUM_PHILOSOPHERS = 5;
    std::vector<Philosopher> philosophers;
    philosophers.reserve(NUM_PHILOSOPHERS);

    Fork forks[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int leftForkIndex = i;
        int rightForkIndex = (i + 1) % NUM_PHILOSOPHERS;
        philosophers.emplace_back(i, forks[leftForkIndex], forks[rightForkIndex], 3);
    }

    for (auto& philosopher : philosophers) {
        philosopher.start();
    }

    for (auto& philosopher : philosophers) {
        philosopher.stop();
    }

    return 0;
}