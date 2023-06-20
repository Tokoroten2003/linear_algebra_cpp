#include "marith.hpp"

#include <gtest/gtest.h>

constexpr size_t m = 5;
constexpr size_t n = 10;

namespace {
// -------------------
// test of constructor
// -------------------
TEST(MarithConstructorTest, NoInitializer) {
    try {
        mcalc::Marith<int, m, n> marith_int_target;
        mcalc::Marith<float, m, n> marith_float_target;
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, Copy) {
    mcalc::Marith<int, m, n> marith_int;
    mcalc::Marith<float, m, n> marith_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target     = marith_int;
        mcalc::Marith<float, m, n> marith_float_target = marith_float;
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, Move) {
    mcalc::Marith<int, m, n> marith_int;
    mcalc::Marith<float, m, n> marith_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target     = std::move(marith_int);
        mcalc::Marith<float, m, n> marith_float_target = std::move(marith_float);
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TEST(MarithConstructorTest, FromArray) {
    std::array<std::array<int, n>, m> arr_int;
    std::array<std::array<float, n>, m> arr_float;
    try {
        mcalc::Marith<int, m, n> marith_int_target(std::move(arr_int));
        mcalc::Marith<float, m, n> marith_float_target(std::move(arr_float));
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}

// -----------------
// test of accessors
// -----------------
class MarithAccessTest : public ::testing::Test {
protected:
    std::array<std::array<int, n>, m> arr_int_f;
    std::array<std::array<float, n>, m> arr_float_f;

    virtual void SetUp() {
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                arr_int_f.at(i).at(j)   = i + j;
                arr_float_f.at(i).at(j) = i + j * 0.1;
            }
        }
    }
};

TEST_F(MarithAccessTest, getElems) {
    mcalc::Marith<int, m, n> mat_int_target(std::move(arr_int_f));
    mcalc::Marith<float, m, n> mat_float_target(std::move(arr_float_f));
    ASSERT_EQ(arr_int_f, mat_int_target.getElems());
    ASSERT_EQ(arr_float_f, mat_float_target.getElems());
}
TEST_F(MarithAccessTest, sizeRow) {
    mcalc::Marith<int, m, n> mat_int_target(std::move(arr_int_f));
    mcalc::Marith<float, m, n> mat_float_target(std::move(arr_float_f));
    ASSERT_EQ(arr_int_f.size(), mat_int_target.sizeRow());
    ASSERT_EQ(arr_float_f.size(), mat_float_target.sizeRow());
}
TEST_F(MarithAccessTest, sizeCol) {
    mcalc::Marith<int, m, n> mat_int_target(std::move(arr_int_f));
    mcalc::Marith<float, m, n> mat_float_target(std::move(arr_float_f));
    ASSERT_EQ(arr_int_f.at(0).size(), mat_int_target.sizeCol());
    ASSERT_EQ(arr_float_f.at(0).size(), mat_float_target.sizeCol());
}
TEST_F(MarithAccessTest, at) {
    mcalc::Marith<int, m, n> mat_int_target(std::move(arr_int_f));
    mcalc::Marith<float, m, n> mat_float_target(std::move(arr_float_f));
    for (size_t i = 0; i < m; i++) {
        EXPECT_EQ(arr_int_f.at(i), mat_int_target.at(i));
        EXPECT_EQ(arr_float_f.at(i), mat_float_target.at(i));
        for (size_t j = 0; j < n; j++) {
            EXPECT_EQ(arr_int_f.at(i).at(j), mat_int_target.at(i, j));
            EXPECT_EQ(arr_float_f.at(i).at(j), mat_float_target.at(i, j));
        }
    }
}
TEST_F(MarithAccessTest, at_const) {
    mcalc::Marith<int, m, n> mat_int_target(std::move(arr_int_f));
    mcalc::Marith<float, m, n> mat_float_target(std::move(arr_float_f));
    for (size_t i = 0; i < m; i++) {
        EXPECT_EQ(arr_int_f.at(i), mat_int_target.at_const(i));
        EXPECT_EQ(arr_float_f.at(i), mat_float_target.at_const(i));
        for (size_t j = 0; j < n; j++) {
            EXPECT_EQ(arr_int_f.at(i).at(j), mat_int_target.at_const(i, j));
            EXPECT_EQ(arr_float_f.at(i).at(j), mat_float_target.at_const(i, j));
        }
    }
}
} // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
