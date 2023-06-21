#include "marith.hpp"

#include <gtest/gtest.h>

namespace {
constexpr size_t m  = 5;
constexpr size_t n  = 10;
constexpr size_t n2 = 7;
typedef ::testing::Types<int, float> MarithTypes;

// -----------
// Constructor
// -----------
template <typename T>
class MarithConstructorTest : public ::testing::Test {
protected:
    mcalc::Marith<T, m, n> arr_f;
};
TYPED_TEST_CASE(MarithConstructorTest, MarithTypes);
TYPED_TEST(MarithConstructorTest, NoInitializer) {
    try {
        mcalc::Marith<TypeParam, m, n> marith_target;
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TYPED_TEST(MarithConstructorTest, Copy) {
    mcalc::Marith<TypeParam, m, n> marith_original;
    try {
        mcalc::Marith<TypeParam, m, n> marith_target(marith_original);
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TYPED_TEST(MarithConstructorTest, Move) {
    mcalc::Marith<TypeParam, m, n> marith_original;
    try {
        mcalc::Marith<TypeParam, m, n> marith_target(std::move(marith_original));
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}
TYPED_TEST(MarithConstructorTest, FromArray) {
    try {
        mcalc::Marith<TypeParam, m, n> marith_target(std::move(this->arr_f));
    } catch (const std::exception& e) {
        FAIL() << "exception thrown: " << e.what() << std::endl;
    }
}

// --------
// Accessor
// --------
template <typename T>
class MarithAccessorTest : public ::testing::Test {
protected:
    std::array<std::array<T, n>, m> arr_f;
    std::array<std::array<T, n>, m> arr_f2;
    std::array<std::array<T, n>, m> arr_copy_f2;
    mcalc::Marith<T, m, n> mat_target_f;
    virtual void SetUp() {
        for (std::size_t i = 0; i < m; i++) {
            for (std::size_t j = 0; j < n; j++) {
                arr_f.at(i).at(j)       = i * j;
                arr_f2.at(i).at(j)      = i - j;
                arr_copy_f2.at(i).at(j) = arr_f2.at(i).at(j);
                mat_target_f.at(i, j)   = arr_f.at(i).at(j);
            }
        }
    }
};
TYPED_TEST_CASE(MarithAccessorTest, MarithTypes);
TYPED_TEST(MarithAccessorTest, getElems) { ASSERT_EQ(this->arr_f, this->mat_target_f.getElems()); }
TYPED_TEST(MarithAccessorTest, setElems) {
    this->mat_target_f.setElems(std::move(this->arr_f2));
    ASSERT_EQ(this->arr_copy_f2, this->mat_target_f.getElems());
}
TYPED_TEST(MarithAccessorTest, sizeRow) { ASSERT_EQ(this->arr_f.size(), this->mat_target_f.sizeRow()); }
TYPED_TEST(MarithAccessorTest, sizeCol) { ASSERT_EQ(this->arr_f.at(0).size(), this->mat_target_f.sizeCol()); }
TYPED_TEST(MarithAccessorTest, at) {
    for (size_t i = 0; i < m; i++) {
        EXPECT_EQ(this->arr_f.at(i), this->mat_target_f.at(i));
        for (size_t j = 0; j < n; j++) {
            EXPECT_EQ(this->arr_f.at(i).at(j), this->mat_target_f.at(i, j));
        }
    }
}
TYPED_TEST(MarithAccessorTest, at_const) {
    for (size_t i = 0; i < m; i++) {
        EXPECT_EQ(this->arr_f.at(i), this->mat_target_f.at_const(i));
        for (size_t j = 0; j < n; j++) {
            EXPECT_EQ(this->arr_f.at(i).at(j), this->mat_target_f.at_const(i, j));
        }
    }
}

// -------------------
// Comparison Operator
// -------------------
template <typename T>
class MarithComparisonOperatorTest : public ::testing::Test {
protected:
    mcalc::Marith<T, m, n> mat_ltarget_f;
    mcalc::Marith<T, m, n> mat_rtarget_eq_f;
    mcalc::Marith<T, m, n> mat_rtarget_ne_f;
    virtual void SetUp() {
        for (std::size_t i = 0; i < mat_ltarget_f.sizeRow(); i++) {
            for (std::size_t j = 0; j < mat_ltarget_f.sizeCol(); j++) {
                mat_ltarget_f.at(i, j)    = i + j;
                mat_rtarget_eq_f.at(i, j) = mat_ltarget_f.at(i, j);
                mat_rtarget_ne_f.at(i, j) = i / (j + 1);
            }
        }
    }
};
TYPED_TEST_CASE(MarithComparisonOperatorTest, MarithTypes);
TYPED_TEST(MarithComparisonOperatorTest, Equal) {
    ASSERT_TRUE(this->mat_ltarget_f == this->mat_rtarget_eq_f);
    ASSERT_FALSE(this->mat_ltarget_f == this->mat_rtarget_ne_f);
}
TYPED_TEST(MarithComparisonOperatorTest, NotEqual) {
    ASSERT_TRUE(this->mat_ltarget_f != this->mat_rtarget_ne_f);
    ASSERT_FALSE(this->mat_ltarget_f != this->mat_rtarget_eq_f);
}

// -------------------
// Assignment Operator
// -------------------
template <typename T>
class MarithAssignmentOperatorTest : public ::testing::Test {
protected:
    mcalc::Marith<T, m, n> mat_ltarget_f;
    mcalc::Marith<T, m, n> mat_rtarget_f;
    virtual void SetUp() {
        for (std::size_t i = 0; i < m; i++) {
            for (std::size_t j = 0; j < n; j++) {
                mat_ltarget_f.at(i, j) = i + j;
                mat_rtarget_f.at(i, j) = i * j;
            }
        }
    }
};
TYPED_TEST_CASE(MarithAssignmentOperatorTest, MarithTypes);
TYPED_TEST(MarithAssignmentOperatorTest, CopyAssignment) {
    this->mat_ltarget_f = this->mat_rtarget_f;
    EXPECT_EQ(this->mat_rtarget_f, this->mat_ltarget_f);
}
TYPED_TEST(MarithAssignmentOperatorTest, MoveAssignment) {
    this->mat_ltarget_f = std::move(this->mat_rtarget_f);
    EXPECT_EQ(this->mat_rtarget_f, this->mat_ltarget_f);
}
TYPED_TEST(MarithAssignmentOperatorTest, AdditionAssignment) {
    mcalc::Marith<TypeParam, m, n> mat_result;
    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            mat_result.at(i, j) = this->mat_ltarget_f.at_const(i, j) + this->mat_rtarget_f.at_const(i, j);
        }
    }
    this->mat_ltarget_f += this->mat_rtarget_f;
    EXPECT_EQ(mat_result, this->mat_ltarget_f);
}
TYPED_TEST(MarithAssignmentOperatorTest, SubstractionAssignment) {
    mcalc::Marith<TypeParam, m, n> mat_result;
    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            mat_result.at(i, j) = this->mat_ltarget_f.at_const(i, j) - this->mat_rtarget_f.at_const(i, j);
        }
    }
    this->mat_ltarget_f -= this->mat_rtarget_f;
    EXPECT_EQ(mat_result, this->mat_ltarget_f);
}
TYPED_TEST(MarithAssignmentOperatorTest, ScalarProductionAssignment) {
    constexpr TypeParam r_value = 3;
    mcalc::Marith<TypeParam, m, n> mat_result;
    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            mat_result.at(i, j) = this->mat_ltarget_f.at_const(i, j) * r_value;
        }
    }
    this->mat_ltarget_f *= r_value;
    EXPECT_EQ(mat_result, this->mat_ltarget_f);
}
TYPED_TEST(MarithAssignmentOperatorTest, MatrixProductionAssignment) {
    mcalc::Marith<TypeParam, m, m> mat_rtarget_prod_f;
    mcalc::Marith<TypeParam, m, n> mat_result;
    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < m; j++) {
            mat_rtarget_prod_f.at(i, j) = i / (j + 1);
        }
    }
    for (std::size_t i = 0; i < m; i++) {
        for (std::size_t j = 0; j < n; j++) {
            mat_result.at(i, j) = 0;
            for (std::size_t k = 0; k < m; k++) {
                mat_result.at(i, j) += mat_rtarget_prod_f.at_const(i, k) * this->mat_ltarget_f.at_const(k, j);
            }
        }
    }
    this->mat_ltarget_f *= mat_rtarget_prod_f;
    EXPECT_EQ(mat_result, this->mat_ltarget_f);
}
} // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
