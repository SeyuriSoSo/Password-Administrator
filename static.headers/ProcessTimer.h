#include <iostream>
#include <chrono>

struct ProcessTimer {
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::duration<double> elapsed_seconds;

    std::string name;
    bool destructor_print;

    ProcessTimer(std::string name = "", bool start_clock = true, bool destructor_print = true) {
        if(start_clock)
            start = std::chrono::system_clock::now();
        this->name = name;
        this->destructor_print = destructor_print;
    }

    ~ProcessTimer() {
        this->stop();
        if(destructor_print)
            this->print();
    }

    void stop() {
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
    }

    void reset() {
        start = std::chrono::system_clock::now();
    }

    double get_time(bool stop = true) {
        this->stop();
        return elapsed_seconds.count();
    }

    void print() {
        std::cout << "\nProcess time (" << name << ") : " << elapsed_seconds.count() << " sec" << std::endl;
    }
};