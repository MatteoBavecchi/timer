//
// Created by Matteo Bavecchi on 02/04/2021.
//
#include "Data.h"
#include <iostream>
#include <chrono>
#include "thread"
#include <unistd.h>
//TODO: fai un tostring che stampa dd/mm/yyyy hh/mm/ss

void Data::goClockWise() {
    std::cout << "Starting Clock...\n";
    while (true) {
        operator++(1);
        sleep(1);
    }
}

void Data::goCounterClockWise() {
    terminated = false;
    pause = false;
    std::cout << "Timer running...\n";
    while (!terminated) {
        if (!pause) {
            sleep(1);
            operator--(1);
            if (hour == 0 && second == 0 && minute == 0) {
                terminated = true;
                std::cout << "\nFinito\n";
            }
        }
    }
}

void Data::stopTimer() {
    terminated = true;
}

void Data::pauseTimer() {
    pause = true;
}

void Data::resumeTimer() {
    pause = false;
}


void Data::startClock() {
    threadCW = new std::thread([this]() { goClockWise(); });
}

void Data::startTimer() {
    threadCCW = new std::thread([this]() { goCounterClockWise(); });
}


void Data::getDataTime() {
    using std::chrono::system_clock;
    system_clock::time_point today = system_clock::now();
    std::time_t timestamp;
    timestamp = system_clock::to_time_t(today);
    unsigned int epoch = (unsigned int) timestamp;
    getDataTimeFromEpoch(epoch);
}

void Data::getDataTimeFromEpoch(int epoch) {
    this->timestamp = epoch;
    int tmp = epoch;
    int years = epoch / (int) (60 * 60 * 24 * 365);
    epoch %= (int) (60 * 60 * 24 * 365);
    this->second = epoch % 60;
    epoch /= 60;
    this->minute = epoch % 60;
    epoch /= 60;
    this->hour = (epoch % 24);

    if (this->hour > 12) {
        setAmPm(false);
    } else {
        setAmPm(true);
    }

    this->year = years + 1970;

    tmp /= 60 * 60 * 24;
    tmp %= 365 * 4 + 1;

    int year;
    for (year = 3; year > 0; year--) {
        if (tmp >= days[year][0])
            break;
    }

    int month;
    for (month = 11; month > 0; month--) {
        if (tmp >= days[year][month])
            break;
    }

    this->month = month + 1;
    this->day = tmp - days[year][month] + 1;
}

int Data::getTimestamp() const {
    return timestamp;
}

void Data::setTimestamp(int timestamp) {
    Data::timestamp = timestamp;
}

int Data::getSecond() const {
    return second;
}

void Data::setSecond(int second) {
    Data::second = second;
}

int Data::getMinute() const {
    return minute;
}

void Data::setMinute(int minute) {
    Data::minute = minute;
}

int Data::getHour() const {
    if (timer)
        return hour;
    int response = isLegalOur() ? hour + timeZone + 1 : hour + timeZone;
    if (format && response > 12)
        response -= 12;

    return response;
}

void Data::setHour(int hour) {
    Data::hour = hour;
}

int Data::getDay() const {
    return day;
}

void Data::setDay(int day) {
    Data::day = day;
}

int Data::getMonth() const {
    return month;
}

void Data::setMonth(int month) {
    Data::month = month;
}

int Data::getYear() const {
    return year;
}

void Data::setYear(int year) {
    Data::year = year;
}


const std::string *Data::getNameOfMonths() const {
    return nameOfMonths;
}

int Data::getTimeZone() const {
    return timeZone;
}

bool Data::isTimer() const {
    return timer;
}

void Data::setTimer(bool timer) {
    Data::timer = timer;
}

void Data::setTimeZone(int timeZone) {
    Data::timeZone = timeZone;
}

bool Data::isLegalOur() const {
    return legalOur;
}

void Data::setLegalOur(bool legalOur) {
    Data::legalOur = legalOur;
}

bool Data::isFormat() const {
    return format;
}

void Data::setFormat(bool format) {
    Data::format = format;
}


Data::Data(int timeZone, bool legalOur, bool format) : timeZone(timeZone), legalOur(legalOur),
                                                       format(format) {
    getDataTime();
    timer = false;
}


Data::Data(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {
    timer = true;
}

bool Data::isAmPm() const {
    return am_pm;
}

void Data::setAmPm(bool amPm) {
    am_pm = amPm;
}


Data Data::operator--(int) {
    if (second == 0) {
        if (minute == 0) {
            if (hour == 0) {
                return *this;
            }
            hour--;
            minute = 59;
            second = 59;
        } else {
            minute--;
            second = 59;
        }
    } else {
        second--;
    }
    return *this;
}

Data Data::operator++(int) {
    if (second == 59) {
        if (minute == 59) {
            if (hour == 59) {
                getDataTime();
            } else {
                hour++;
                minute = 0;
                second = 0;
            }
        } else {
            minute++;
            second = 0;
        }
    } else {
        second++;
    }

    return *this;
}