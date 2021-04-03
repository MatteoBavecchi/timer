#include <iostream>
#include <chrono>
#include "Data.h"

int main() {
    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t timestamp;
    timestamp = system_clock::to_time_t(today);
    std::cout << "today is: " << timestamp;

    unsigned int epoch = (unsigned int) timestamp;
    Data *x = new Data(1, true);
    x->getDatatimeFromEpoch(epoch);


    std::cout << "\n\nData:\n";
    std::cout << x->getDay() << "-";
    std::cout << x->getMonth() << "-";
    std::cout << x->getYear() << "\n";
    std::cout << x->getHour() << ":";
    std::cout << x->getMinute() << ":";
    std::cout << x->getSecond();

    Data *y = new Data(1, false);
    y->getDatatimeFromEpoch(epoch);


    std::cout << "\n\nData:\n";
    std::cout << y->getDay() << "-";
    std::cout << y->getMonth() << "-";
    std::cout << y->getYear() << "\n";
    std::cout << y->getHour() << ":";
    std::cout << y->getMinute() << ":";
    std::cout << y->getSecond();

    return 0;
}

