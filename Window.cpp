//
// Created by Matteo Bavecchi on 05/04/2021.
//

#include "Window.h"
#include <QApplication>
#include <QPushButton>
#include "Data.h"
#include <string>
#include <QTimer>

//TODO: metti un label con la data
//TODO: metti un pulsante per andare nelle impostazioni
//TODO: metti un pulsante per andare al timer
//TODO: unit test con QT della classe Data
Window::Window(QWidget *parent) :
        QMainWindow(parent) {

    t = new Data(1, true, false);
    t->startClock();
    // Set size of the window
    setFixedSize(900, 500);

    // Create and position the button

    QString date = QString::fromStdString(t->print());
    m_button = new QPushButton(date, this);
    m_button->setGeometry(QRect(QPoint(0, 0), QSize(200, 50)));
    //connect(m_button, &QPushButton::released, this, &Window::handleButton);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Window::update));
    timer->start(250);
}

void Window::update() {
    QString date = QString::fromStdString(t->print());
    m_button->setText(date);
}

void Window::handleButton() {
    // change the text
    //m_button->setText("Example");

    // resize button
    //m_button->resize(100, 100);
}
