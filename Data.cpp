//
// Created by Matteo Bavecchi on 02/04/2021.
//
#include "Data.h"
#include <iostream>
#include <chrono>
#include "thread"
#include <unistd.h>

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
    hour = 0;
    minute = 0;
    second = 0;
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
    if (timestamp >= (unsigned int) 32503680000 || timestamp <= (unsigned int) 31536000)
        throw std::invalid_argument("timestamp non valido");
    Data::timestamp = timestamp;
}

int Data::getSecond() const {
    return second;
}

void Data::setSecond(int second) {

    if (second < 0 || second > 59)
        throw std::invalid_argument("Secondi non validi");
    Data::second = second;
}

int Data::getMinute() const {
    return minute;
}

void Data::setMinute(int minute) {
    if (minute < 0 || minute > 59)
        throw std::invalid_argument("Minuti non validi");
    Data::minute = minute;
}

int Data::getHour() const {
    if (timer)
        return hour;
    int response = isLegalHour() ? hour + timeZone + 1 : hour + timeZone;
    if (format && response > 12)
        response -= 12;

    return response;
}

void Data::setHour(int hour) {
    if (hour < 0)
        throw std::invalid_argument("Ora non valida");

    if (!timer && isFormat()) {
        //12 ore
        if (hour > 11)
            throw std::invalid_argument("Ora non valida");
        Data::hour = hour + 12;
    } else {
        //24 ore
        if (hour > 23)
            throw std::invalid_argument("Ora non valida");

        Data::hour = hour;
    }
}

int Data::getDay() const {
    return day;
}

void Data::setDay(int day) {
    if (day < 1 || day > 31)
        throw std::invalid_argument("Giorno non valido");

    if (month == 2) {
        if (isLeap(year)) {
            if (day > 29)
                throw std::invalid_argument("Giorno non valido");
        } else {
            if (day > 28)
                throw std::invalid_argument("Giorno non valido");
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            throw std::invalid_argument("Giorno non valido");
    }

    Data::day = day;
}

int Data::getMonth() const {
    return month;
}

void Data::setMonth(int month) {
    if (month < 1 || month > 12)
        throw std::invalid_argument("Mese non valido");
    Data::month = month;
}

int Data::getYear() const {
    return year;
}

void Data::setYear(int year) {
    if (year > MAX_VALID_YR || year < MIN_VALID_YR)
        throw std::invalid_argument("Anno non valido");
    Data::year = year;
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

bool Data::isLegalHour() const {
    return legalHour;
}

void Data::setLegalHour(bool legalHour) {
    Data::legalHour = legalHour;
}

bool Data::isFormat() const {
    return format;
}

void Data::setFormat(bool format) {
    Data::format = format;
}


Data::Data(int timeZone, bool legalOur, bool format) : timeZone(timeZone), legalHour(legalOur),
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
    if (hour > 12)
        setAmPm(false);
    else
        setAmPm(true);

    return *this;
}

bool Data::isLeap(int year) {
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}


std::string Data::print() {
    std::string hh;
    std::string mm;
    std::string ss;

    std::string DD;
    std::string MM;
    std::string YYYY;

    if (timer) {
        hour < 10 ? hh = "0" + std::to_string(hour) : hh = std::to_string(hour);
        minute < 10 ? mm = "0" + std::to_string(minute) : mm = std::to_string(minute);
        second < 10 ? ss = "0" + std::to_string(second) : ss = std::to_string(second);
        return hh + ":" + mm + ":" + ss;
    } else {

        int effectiveHour = isLegalHour() ? hour + timeZone + 1 : hour + timeZone;
        if (isFormat() && effectiveHour > 12)
            effectiveHour -= 12;

        effectiveHour < 10 ? hh = "0" + std::to_string(effectiveHour) : hh = std::to_string(effectiveHour);
        minute < 10 ? mm = "0" + std::to_string(minute) : mm = std::to_string(minute);
        second < 10 ? ss = "0" + std::to_string(second) : ss = std::to_string(second);
        day < 10 ? DD = "0" + std::to_string(day) : DD = std::to_string(day);
        month < 10 ? MM = "0" + std::to_string(month) : MM = std::to_string(month);
        YYYY = std::to_string(year);

        if (isFormat())
            return DD + "/" + MM + "/" + YYYY + "  " + hh + ":" + mm + ":" + ss + (isAmPm() ? " AM" : " PM");
        else
            return DD + "/" + MM + "/" + YYYY + "  " + hh + ":" + mm + ":" + ss;
    }
}