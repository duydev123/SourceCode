#include <gtest/gtest.h>
#include "utils.h"

TEST(IsPrimeTest, HandlesPrimes) {
    EXPECT_TRUE(isPrime(2));
    EXPECT_TRUE(isPrime(3));
    EXPECT_TRUE(isPrime(13));
}

TEST(IsPrimeTest, HandlesNonPrimes) {
    EXPECT_FALSE(isPrime(1));
    EXPECT_FALSE(isPrime(4));
    EXPECT_FALSE(isPrime(100));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
