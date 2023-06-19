#include"marith.hpp"
#include<gtest/gtest.h>

TEST(marith_int_test, default_constractor) {
    try {
        mcalc::Marith<int, 1, 1> m;
    } catch(const std::exception& e) {
        ASSERT_TRUE(false);
    }
}
