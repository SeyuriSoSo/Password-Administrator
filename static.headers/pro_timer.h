#include <iostream>
#include <chrono>

namespace aes {

struct pro_timer {
    std::string context_print;
    clock_t start, end;

    pro_timer(std::string context_print = "") {
        start = clock();
        this->context_print = context_print;
    }

    ~pro_timer() {
        this->stop_timer();
        std::cout << "Process time (" << this->context_print << "): " << double(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;
    }

    void stop_timer() {
        end = clock();
    }
};

}