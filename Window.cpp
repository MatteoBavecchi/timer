//
// Created by Matteo Bavecchi on 05/04/2021.
//

#include "Window.h"
#include <QApplication>
#include <QPushButton>
#include "Data.h"
#include <string>

Window::Window(QWidget *parent) :
        QWidget(parent) {

    Data *t = new Data(0, 0, 10);

    // Set size of the window
    setFixedSize(100, 50);

    // Create and position the button
    QString seconds = QString::number(t->getSecond());
    m_button = new QPushButton(seconds, this);
    m_button->setGeometry(10, 10, 80, 30);
    connect(m_button, SIGNAL (clicked()), this, SLOT (start()));
}

void Window::start() {
   std::cout<<"ciaoooo";
}
