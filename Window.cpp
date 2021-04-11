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
#include <QInputDialog>
#include <QLabel>

Window::Window(QWidget *parent)
        :
        QMainWindow(parent) {

    settings = new QSettings("matteobavecchi", "timer");

    if (!settings->contains("timezone")) {
        settings->setValue("timezone", 1);
        settings->setValue("legalHour", true);
        settings->setValue("format", false);
    }
    int timezone = settings->value("timezone").toInt();
    bool legalHour = settings->value("legalHour").toBool();
    bool format = settings->value("format").toBool();
    t = new Data(timezone, legalHour, format);

    t->startClock();

    setFixedSize(400, 200);

    QString date = QString::fromStdString(t->print());

    label = new QLabel(this);
    QFont font = label->font();
    font.setPointSize(26);
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

void Window::refreshConfigurations() {
    int timezone = settings->value("timezone").toInt();
    bool legalHour = settings->value("legalHour").toBool();
    bool format = settings->value("format").toBool();
    t->setTimeZone(timezone);
    t->setLegalHour(legalHour);
    t->setFormat(format);

}

void Window::update() {
    QString date = QString::fromStdString(t->print());
    label->setText(date);
}


void Window::openSettings() {
    settings_window = new QWidget;

    QLabel *timezone_label = new QLabel(settings_window);
    timezone_label->setText("timezone:");
    timezone_label->setGeometry(QRect(QPoint(30, 20), QSize(100, 25)));
    timezone_input = new QLineEdit("", settings_window);
    timezone_input->setPlaceholderText("Enter timezone");
    timezone_input->setText(settings->value("timezone").toString());
    timezone_input->setGeometry(QRect(QPoint(30, 50), QSize(100, 25)));

    legalHour_input = new QCheckBox("Legal hour", settings_window);
    legalHour_input->setChecked(settings->value("legalHour").toBool());
    legalHour_input->setGeometry(QRect(QPoint(170, 20), QSize(100, 25)));

    format_input = new QCheckBox("12h/24h", settings_window);
    format_input->setChecked(settings->value("format").toBool());
    format_input->setGeometry(QRect(QPoint(170, 80), QSize(100, 25)));

    settings_window->setFixedSize(300, 150);
    QPushButton *button = new QPushButton("Save", settings_window);
    connect(button, &QPushButton::released, this, &Window::setConfig);
    button->setGeometry(QRect(QPoint(100, 120), QSize(100, 25)));

    settings_window->show();
    settings_window->setFocus();
}

void Window::setConfig() {
    settings->setValue("timezone", timezone_input->text().toInt());
    settings->setValue("legalHour", legalHour_input->isChecked());
    settings->setValue("format", format_input->isChecked());
    refreshConfigurations();
    settings_window->hide();
}

void Window::openTimer() {

    timer_window = new QWidget;
    timer_window->setFixedSize(300, 200);

    timer = new Data(0, 0, 0);

    QString time = QString::fromStdString(timer->print());

    timer_label = new QLabel(timer_window);
    QFont font = timer_label->font();
    font.setPointSize(26);
    font.setBold(true);
    timer_label->setFont(font);
    timer_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    timer_label->setText(time);
    timer_label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    timer_label->setGeometry(80, 100, 160, 50);


    hour_input = new QLineEdit(0, timer_window);
    hour_input->setPlaceholderText("HH");
    hour_input->setGeometry(QRect(QPoint(70, 30), QSize(50, 25)));

    minute_input = new QLineEdit(0, timer_window);
    minute_input->setPlaceholderText("MM");
    minute_input->setGeometry(QRect(QPoint(125, 30), QSize(50, 25)));

    second_input = new QLineEdit(0, timer_window);
    second_input->setPlaceholderText("SS");
    second_input->setGeometry(QRect(QPoint(180, 30), QSize(50, 25)));


    start_button = new QPushButton("Start", timer_window);
    start_button->setGeometry(80, 150, 80, 30);
    connect(start_button, &QPushButton::released, this, &Window::timerStart);

    stop_button = new QPushButton("Stop", timer_window);
    stop_button->setGeometry(170, 150, 80, 30);
    connect(stop_button, &QPushButton::released, this, &Window::timerStop);

    stop_button->setDisabled(true);

    timer_window->show();
    timer_window->setFocus();
}


void Window::timerStart() {
    start_button->setDisabled(true);
    stop_button->setDisabled(false);
    timer->setHour(hour_input->text().toInt());
    timer->setMinute(minute_input->text().toInt());
    timer->setSecond(second_input->text().toInt());


    QTimer *delay = new QTimer(timer_window);
    connect(delay, &QTimer::timeout, this, QOverload<>::of(&Window::updateTimer));
    delay->start(250);

    timer->startTimer();
}

void Window::timerStop() {
    start_button->setDisabled(false);
    timer->stopTimer();

}

void Window::updateTimer() {
    if (timer->getSecond() == 0 && timer->getMinute() == 0 && timer->getHour() == 0) {
        start_button->setDisabled(false);
        stop_button->setDisabled(true);
        timer_label->setText("TIME OUT");
    } else {

        QString time = QString::fromStdString(timer->print());
        timer_label->setText(time);
    }
}