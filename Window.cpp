//
// Created by Matteo Bavecchi on 05/04/2021.
//

#include "Window.h"
#include <QApplication>
#include <QPushButton>
#include "Data.h"
#include <string>
#include <QTimer>
#include <QFont>

//TODO: metti un label con la data
//TODO: metti un pulsante per andare nelle impostazioni
//TODO: metti un pulsante per andare al timer
//TODO: unit test con QT della classe Data
Window::Window(QWidget *parent) :
        QMainWindow(parent) {

    t = new Data(1, true, false);
    t->startClock();
    // Set size of the window
    setFixedSize(400, 200);

    // Create and position the button
    QString date = QString::fromStdString(t->print());

    label = new QLabel(this);
    QFont font = label->font();
    font.setPointSize(30);
    font.setBold(true);
    label->setFont(font);

    settings_button = new QPushButton("Settings", this);
    settings_button->setGeometry(QRect(QPoint(30, 130), QSize(100, 50)));
    connect(settings_button, &QPushButton::released, this, &Window::openSettings);

    timer_button = new QPushButton("Timer", this);
    timer_button->setGeometry(QRect(QPoint(270, 130), QSize(100, 50)));
    connect(timer_button, &QPushButton::released, this, &Window::openTimer);


    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText(date);
    label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    label->setGeometry(QRect(QPoint(30, 50), QSize(340, 50)));
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Window::update));
    timer->start(250);



}

void Window::update() {
    QString date = QString::fromStdString(t->print());
    label->setText(date);
}

void Window::handleButton() {
    // change the text
    //m_button->setText("Example");

    // resize button
    //m_button->resize(100, 100);
}

void Window::openSettings() {
    settings_window = new QWidget;

    settings_window->setFixedSize(300, 50);

    QPushButton *button = new QPushButton("Hello World", settings_window);
    button->setGeometry(100, 20, 100, 30);
    settings_window->show();
    settings_window->setFocus();
}
void Window::openTimer() {
    timer_window = new QWidget;

    timer_window->setFixedSize(300, 50);

    QPushButton *button = new QPushButton("Hello World", timer_window);
    button->setGeometry(100, 20, 100, 30);
    timer_window->show();
    timer_window->setFocus();
}
