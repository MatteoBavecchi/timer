//
// Created by Matteo Bavecchi on 05/04/2021.
//

#ifndef TIMER_WINDOW_H
#define TIMER_WINDOW_H

#include <QWidget>
#include "Data.h"
#include <QMainWindow>
#include <QLabel>

class QPushButton;

class Window : public QMainWindow {
public:
    explicit Window(QWidget *parent = nullptr);

    void update();

    void openSettings();
    void openTimer();

private slots:

    void handleButton();

private:
    Data *t;
    QPushButton *settings_button;
    QPushButton *timer_button;
    QLabel *label;
    QWidget *settings_window;
    QWidget *timer_window;
};


#endif //TIMER_WINDOW_H
