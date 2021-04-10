//
// Created by Matteo Bavecchi on 02/04/2021.
//

#ifndef TIMER_DATA_H
#define TIMER_DATA_H

#include <string>
#include "thread"
#include "thread"
#include <iostream>
#include <unistd.h>


class Data {

public:

    Data(int timeZone, bool isLegalOur, bool format);

    Data(int hour, int minute, int second);

    int getTimestamp() const;

    int getSecond() const;

    void setSecond(int second);

    int getMinute() const;

    void setMinute(int minute);

    int getHour() const;

    void setHour(int hour);

    int getDay() const;

    void setDay(int day);

    int getMonth() const;

    void setMonth(int month);

    int getYear() const;

    void setYear(int year);

    void getDataTimeFromEpoch(int epoch);

    int getTimeZone() const;

    void setTimeZone(int timeZone);

    bool isLegalHour() const;

    void setLegalHour(bool legalHour);

    void setTimestamp(int timestamp);

    bool isFormat() const;

    void setFormat(bool format);

    bool isAmPm() const;

    void setAmPm(bool amPm);

    Data operator--(int);

    Data operator++(int);

    void getDataTime();

    void goClockWise();

    void goCounterClockWise();

    void startClock();

    void startTimer();

    void stopTimer();

    void pauseTimer();

    void resumeTimer();


    bool isTimer() const;

    bool isLeap(int year);

    void setTimer(bool timer);

    std::string print();

private:
    static const inline short days[4][12] =
            {
                    {0,    31,   60,   91,   121,  152,  182,  213,  244,  274,  305,  335},
                    {366,  397,  425,  456,  486,  517,  547,  578,  609,  639,  670,  700},
                    {731,  762,  790,  821,  851,  882,  912,  943,  974,  1004, 1035, 1065},
                    {1096, 1127, 1155, 1186, 1216, 1247, 1277, 1308, 1339, 1369, 1400, 1430},
            };

    const int MAX_VALID_YR = 3000;
    const int MIN_VALID_YR = 1971;

    int timestamp;

    int second;
    int minute;
    int hour;

    int day;
    int month;
    int year;

    int timeZone;
    bool legalHour;
    bool format; //format=true -> 12 ore; format=false->24 ore
    bool am_pm; //am_pm =true -> am; am_pm = false -> pm

    std::thread *threadCW;
    std::thread *threadCCW;

    bool timer;
    bool terminated;
    bool pause;


};


#endif //TIMER_DATA_H
