//
// Created by Matteo Bavecchi on 09/04/2021.
//


#include <gtest/gtest.h>
#include "../Data.h"
#include <unistd.h>


TEST(test, timestamp) {
    Data clock(1, true, true);
    try {
        clock.setTimestamp(31536000);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("timestamp non valido", err.what());
    }
}

TEST(test, secondi) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setSecond(61), std::invalid_argument);
}

TEST(test, minuti) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setMinute(61), std::invalid_argument);
}


TEST(test, ore) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setHour(12), std::invalid_argument);
}

TEST(test, giorni) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setDay(32), std::invalid_argument);
}

TEST(test, mesi) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setMonth(13), std::invalid_argument);
}

TEST(test, anni) {
    Data clock(1, true, true);
    ASSERT_THROW(clock.setYear(3001), std::invalid_argument);
}

TEST(test, inc) {
    Data clock(1, true, true);
    int oldSeconds = clock.getSecond();
    clock.operator++(1);
    ASSERT_EQ(oldSeconds + 1, clock.getSecond());
}

TEST(test, dec) {
    Data clock(1, true, true);
    int oldSeconds = clock.getSecond();
    clock.operator--(1);
    ASSERT_EQ(oldSeconds - 1, clock.getSecond());
}

TEST(test, timer) {
    Data timer(0, 0, 5);
    timer.startTimer();

    sleep(6);

    ASSERT_EQ(0, timer.getSecond());

}

TEST(test, epochConverter) {
    Data clock(1, true, false);
    clock.getDataTimeFromEpoch(1618005365);
    ASSERT_EQ(clock.print(), "09/04/2021  23:56:05");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}