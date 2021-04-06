#include <iostream>
#include "Data.h"
#include <unistd.h>
#include <QApplication>
#include "Window.h"

int main(int argc, char **argv) {
    /*QApplication app(argc, argv);
    QWidget window;
    window.setFixedSize(300, 50);

    QPushButton *button = new QPushButton("Hello World", &window);
    button->setGeometry(100, 20, 100, 30);
    window.show();
    return app.exec();*/
    QApplication app(argc, argv);

    Window window;
    window.show();

    return app.exec();




/*
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
    */
}

