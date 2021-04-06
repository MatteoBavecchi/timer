//
// Created by Matteo Bavecchi on 05/04/2021.
//

#ifndef TIMER_WINDOW_H
#define TIMER_WINDOW_H


#include <QWidget>
#include "Data.h"

class QPushButton;
class Window : public QWidget
{
public:
    explicit Window(QWidget *parent = 0);
private slots:
    void start();
private:
    QPushButton *m_button;
};


#endif //TIMER_WINDOW_H
