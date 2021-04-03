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
    Data *x = new Data(1, true, false);
    x->getDatatimeFromEpoch(epoch);


    std::cout << "\n\nData:\n";
    std::cout << x->getHour() << ":";
    std::cout << x->getMinute() << ":";
    std::cout << x->getSecond();

    x->operator--(1);

    std::cout << "\n\nData:\n";
    std::cout << x->getHour() << ":";
    std::cout << x->getMinute() << ":";
    std::cout << x->getSecond();




    return 0;
}

