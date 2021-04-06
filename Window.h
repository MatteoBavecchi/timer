//
// Created by Matteo Bavecchi on 05/04/2021.
//

#ifndef TIMER_WINDOW_H
#define TIMER_WINDOW_H


#include "Data.h"
#include <QMainWindow>

class QPushButton;

class Window : public QMainWindow {
public:
    explicit Window(QWidget *parent = nullptr);
    void update();

private slots:

    void handleButton();

private:
    Data* t;
    QPushButton *m_button;
};


#endif //TIMER_WINDOW_H
