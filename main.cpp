#include <iostream>
#include <chrono>
#include "Data.h"
#include <unistd.h>
#include <thread>

int main() {
    Data *x = new Data(1, true, false);
    x->getDataTime();

    x->startTimer();
    while (true) {
        sleep(1);
        std::cout << "\n\nData:\n";
        std::cout << x->getHour() << ":";
        std::cout << x->getMinute() << ":";
        std::cout << x->getSecond();

    }
    return 0;
}

