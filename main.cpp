#include <iostream>
#include <chrono>
#include "Data.h"
#include <unistd.h>
#include <thread>

int main() {
    Data *x = new Data(1, true, false);
    x->getDataTime();

    Data *t = new Data(0, 0, 10);

    t->startTimer();
    while (true) {

        std::cout << "\n\nData:\n";
        std::cout << t->getHour() << ":";
        std::cout << t->getMinute() << ":";
        std::cout << t->getSecond();
        sleep(1);

    }
    return 0;
}

