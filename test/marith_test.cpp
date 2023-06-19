#include "marith.hpp"

#include <gtest/gtest.h>

constexpr size_t m = 100;
constexpr size_t n = 100;

namespace {
TEST(MarithConstructorTest, no_initializer) {
    try {
        mcalc::Marith<int, m, n> marith_int_target;
        mcalc::Marith<float, m, n> marith_float_target;
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, copy) {
    mcalc::Marith<int, m, n> marith_int;
    mcalc::Marith<float, m, n> marith_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target     = marith_int;
        mcalc::Marith<float, m, n> marith_float_target = marith_float;
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, move) {
    mcalc::Marith<int, m, n> marith_int;
    mcalc::Marith<float, m, n> marith_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target     = std::move(marith_int);
        mcalc::Marith<float, m, n> marith_float_target = std::move(marith_float);
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, from_array) {
    std::array<std::array<int, n>, m> arr_int;
    std::array<std::array<float, n>, m> arr_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target(std::move(arr_int));
        mcalc::Marith<float, m, n> marith_float_target(std::move(arr_float));
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
} // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
