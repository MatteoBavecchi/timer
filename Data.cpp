//
// Created by Matteo Bavecchi on 02/04/2021.
//
#include "Data.h"

void Data::getDatatimeFromEpoch(unsigned int epoch) {
    this->timestamp = epoch;
    unsigned int tmp = epoch;
    unsigned int years = epoch / (unsigned int) (60 * 60 * 24 * 365);
    epoch %= (unsigned int) (60 * 60 * 24 * 365);
    this->second = epoch % 60;
    epoch /= 60;
    this->minute = epoch % 60;
    epoch /= 60;
    this->hour += isLegalOur() ? (epoch % 24) + this->timeZone + 1 : (epoch % 24) + this->timeZone;

    if (this->hour > 12) {
        setAmPm(false);
    } else {
        setAmPm(true);
    }

    this->year = years + 1970;

    tmp /= 60 * 60 * 24;
    tmp %= 365 * 4 + 1;

    unsigned int year;
    for (year = 3; year > 0; year--) {
        if (tmp >= days[year][0])
            break;
    }

    unsigned int month;
    for (month = 11; month > 0; month--) {
        if (tmp >= days[year][month])
            break;
    }

    this->month = month + 1;
    this->day = tmp - days[year][month] + 1;
}

unsigned long Data::getTimestamp() const {
    return timestamp;
}

void Data::setTimestamp(unsigned long timestamp) {
    Data::timestamp = timestamp;
}

unsigned int Data::getSecond() const {
    return second;
}

void Data::setSecond(unsigned int second) {
    Data::second = second;
}

unsigned int Data::getMinute() const {
    return minute;
}

void Data::setMinute(unsigned int minute) {
    Data::minute = minute;
}

unsigned int Data::getHour() const {
    return hour;
}

void Data::setHour(unsigned int hour) {
    Data::hour = hour;
}

unsigned int Data::getDay() const {
    return day;
}

void Data::setDay(unsigned int day) {
    Data::day = day;
}

unsigned int Data::getMonth() const {
    return month;
}

void Data::setMonth(unsigned int month) {
    Data::month = month;
}

unsigned int Data::getYear() const {
    return year;
}

void Data::setYear(unsigned int year) {
    Data::year = year;
}


const std::string *Data::getNameOfMonths() const {
    return nameOfMonths;
}

int Data::getTimeZone() const {
    return timeZone;
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


Data::Data(int timeZone, bool legalOur) : timeZone(timeZone), legalOur(legalOur) {}

bool Data::isAmPm() const {
    return am_pm;
}

void Data::setAmPm(bool amPm) {
    am_pm = amPm;
}
