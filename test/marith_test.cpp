#include "marith.hpp"

#include <gtest/gtest.h>

constexpr size_t m = 100;
constexpr size_t n = 100;

namespace {
TEST(MarithIntConstractorTest, def) {
    try {
        mcalc::Marith<int, m, n> mat_target;
    } catch (const std::exception& e) {
        FAIL();
    }
}
TEST(MarithIntConstractorTest, copy) {
    mcalc::Marith<int, m, n> mat;
    try {
        mcalc::Marith<int, m, n> mat_target = mat;
        ASSERT_NE(&mat, &mat_target);
        ASSERT_EQ(mat.getElems(), mat_target.getElems());
    } catch(const std::exception& e) {
        FAIL();
    }
}
TEST(MarithIntConstractorTest, from_array) {
    std::array<std::array<int, n>, m> arr;
    try {
        mcalc::Marith<int, m, n> mat_target(arr);
        ASSERT_EQ(arr, mat_target.getElems());
    } catch(const std::exception& e) {
        FAIL();
    }
}
} // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
