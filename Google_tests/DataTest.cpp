//
// Created by Matteo Bavecchi on 09/04/2021.
//


#include <gtest/gtest.h>
#include "../Data.h"


TEST(test, secondi) {
    std::string c = "ciao";
    Data x(1, true, true);
    ASSERT_EQ(c, "ciao");

}

// Google Test can be run manually from the main() function
// or, it can be linked to the gtest_main library for an already
// set-up main() function primed to accept Google Test test cases.
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}