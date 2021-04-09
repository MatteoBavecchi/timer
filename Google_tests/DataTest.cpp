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
    try {
        clock.setSecond(61);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Secondi non validi", err.what());
    }
}

TEST(test, minuti) {
    Data clock(1, true, true);
    try {
        clock.setMinute(61);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Minuti non validi", err.what());
    }
}


TEST(test, ore) {
    Data clock(1, true, true);
    try {
        clock.setHour(12);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Ora non valida", err.what());
    }
}

TEST(test, giorni) {
    Data clock(1, true, true);
    try {
        clock.setDay(32);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Giorno non valido", err.what());
    }
}

TEST(test, mesi) {
    Data clock(1, true, true);
    try {
        clock.setMonth(13);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Mese non valido", err.what());
    }
}

TEST(test, anni) {
    Data clock(1, true, true);
    try {
        clock.setYear(3001);
        FAIL();
    }
    catch (std::invalid_argument &err) {
        // check exception
        ASSERT_STREQ("Anno non valido", err.what());
    }
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