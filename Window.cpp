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
Window::Window(QWidget *parent) :
        QMainWindow(parent) {

    t = new Data(1, true, false);
    t->startClock();
    // Set size of the window
    setFixedSize(900, 500);

    // Create and position the button

    m_button = new QPushButton("", this);
    m_button->setGeometry(QRect(QPoint(0, 0), QSize(200, 50)));
    //connect(m_button, &QPushButton::released, this, &Window::handleButton);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Window::update));
    timer->start(1000);
}

void Window::update() {
    QString seconds = QString::number(t->getSecond());
    QString minute = QString::number(t->getMinute());
    QString hour = QString::number(t->getHour());
    QString day = QString::number(t->getDay());
    QString month = QString::number(t->getMonth());
    QString year = QString::number(t->getYear());
    QString date = day + "/" + month + "/" + year + "  " + hour + ":" + minute + ":" + seconds;
    m_button->setText(date);
}

void Window::handleButton() {
    // change the text
    //m_button->setText("Example");

    // resize button
    //m_button->resize(100, 100);
}
