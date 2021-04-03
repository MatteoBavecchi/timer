//
// Created by Matteo Bavecchi on 02/04/2021.
//

#ifndef TIMER_DATA_H
#define TIMER_DATA_H

#include <string>


class Data {

public:

    Data(int timeZone, bool isLegalOur);

    unsigned long getTimestamp() const;

    unsigned int getSecond() const;

    void setSecond(unsigned int second);

    unsigned int getMinute() const;

    void setMinute(unsigned int minute);

    unsigned int getHour() const;

    void setHour(unsigned int hour);

    unsigned int getDay() const;

    void setDay(unsigned int day);

    unsigned int getMonth() const;

    void setMonth(unsigned int month);

    unsigned int getYear() const;

    void setYear(unsigned int year);

    const std::string &getStringDay() const;

    void setStringDay(const std::string &stringDay);

    void getDatatimeFromEpoch(unsigned int epoch);

    const std::string &getStringMonth() const;

    void setStringMonth(const std::string &stringMonth);

    const std::string *getNameOfDays() const;

    const std::string *getNameOfMonths() const;

    int getTimeZone() const;

    void setTimeZone(int timeZone);

    bool isLegalOur() const;

    void setLegalOur(bool legalOur);

    void setTimestamp(unsigned long timestamp);

    bool isFormat() const;

    void setFormat(bool format);

    bool isAmPm() const;

    void setAmPm(bool amPm);

private:
    static const inline unsigned short days[4][12] =
            {
                    {0,    31,   60,   91,   121,  152,  182,  213,  244,  274,  305,  335},
                    {366,  397,  425,  456,  486,  517,  547,  578,  609,  639,  670,  700},
                    {731,  762,  790,  821,  851,  882,  912,  943,  974,  1004, 1035, 1065},
                    {1096, 1127, 1155, 1186, 1216, 1247, 1277, 1308, 1339, 1369, 1400, 1430},
            };

    unsigned int timestamp;
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    unsigned int year;
    std::string nameOfMonths[12] = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno", "luglio",
                                    "agosto", "settembre", "ottobre", "novembre", "dicembre"};
    int timeZone;
    bool legalOur;
    bool format; //format=true -> 12 ore; format=false->24 ore
    bool am_pm; //am_pm =true -> am; am_pm = false -> pm


};


#endif //TIMER_DATA_H
