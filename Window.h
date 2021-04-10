//
// Created by Matteo Bavecchi on 05/04/2021.
//

#ifndef TIMER_WINDOW_H
#define TIMER_WINDOW_H

#include <QWidget>
#include "Data.h"
#include <QMainWindow>
#include <QLabel>
#include <QSettings>
#include <QLineEdit>
#include <QCheckBox>

class QPushButton;

class Window : public QMainWindow {
public:
    explicit Window(QWidget *parent = nullptr);

    void update();

    void openSettings();
    void openTimer();
    void setConfig();
    void refreshConfigurations();

private slots:

    void handleButton();

private:
    Data *t;
    QPushButton *settings_button;
    QPushButton *timer_button;
    QLabel *label;
    QWidget *settings_window;
    QWidget *timer_window;
    QSettings *settings;

    QLineEdit *timezone_input;
    QCheckBox *legalHour_input;
    QCheckBox *format_input;
};


#endif //TIMER_WINDOW_H
