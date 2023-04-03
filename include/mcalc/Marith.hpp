#pragma once

#include "mcalc/Matrix.hpp"
#include "mcalc/alias.hpp"
#include "mcalc/errors.hpp"

#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace mcalc {
/**
 * @brief Class of matrix constracted by arithmetic elements
 *
 * @tparam T must be arithmetic
 */
template <typename T>
class Marith : virtual public Matrix<T> {
protected:
    /**
     * @brief Class for elementary row operations
     */
    class ElemRowOp {
    private:
        /// Pointer of the parent
        Marith* this_ptr;

    public:
        ElemRowOp(Marith<T>* marith);

        Marith& _interchange(size_t i, size_t j) const;
        Marith& _multiply(size_t i, T s) const;
        Marith& _add(size_t i, size_t j, T s) const;

        inline const Marith& interchange(size_t i, size_t j) const;
        inline const Marith& multiply(size_t i, T s) const;
        inline const Marith& add(size_t i, size_t j, T s) const;
    };

private:
    /// @brief List of elements
    V2<T> data;

    /// @brief Rank of the matrix
    size_t rank;

    /// @brief Size of the row
    const size_t rowsize;

    /// @brief Size of the column
    const size_t colsize;

    /// @brief Elementary row operations
    const ElemRowOp erowop;

public:
    /// @brief Fail to bompile if the elements are not arithmetic
    /// @tparam T
    static_assert(std::is_arithmetic<T>::value, "[error] The type of components must be arithmetic");

    Marith();
    Marith(const Matrix<T>& m);
    Marith(const V2<T> mat, const size_t row_size, const size_t col_size);
    Marith(const V2<T> mat);
    Marith(const size_t row_size, const size_t col_size);

    bool operator==(const Matrix<T>& m) const override;
    inline bool operator!=(const Matrix<T>& m) const override;
    Marith& operator=(const Matrix<T>& m) override;
    Marith& operator+=(const Matrix<T>& m) override;
    Marith& operator-=(const Matrix<T>& m) override;
    Marith& operator*=(const T s) override;
    Marith& operator*=(const Matrix<T>& m) override;

    inline const V2<T>& getData() const override;
    inline const T& at(size_t i, size_t j) const override;
    inline T& at(size_t i, size_t j) override;
    inline const V1<T>& at(size_t i) const override;
    inline V1<T>& at(size_t i) override;
    inline const size_t& getRowsize() const override;
    inline const size_t& getColsize() const override;
    std::string to_string() const override;

    Marith<T> transpose() const;
    inline const ElemRowOp& elemRowOp();
    Marith<T> echelon();
    const size_t& getRank();
};
template <typename T>
inline Marith<T> operator+(const Marith<T>& m1, const Marith<T>& m2);
template <typename T>
inline Marith<T> operator-(const Marith<T>& m1, const Marith<T>& m2);
template <typename T>
inline Marith<T> operator*(const T s, const Marith<T>& m);
template <typename T>
inline Marith<T> operator*(const Marith<T>& m, const T s);
template <typename T>
inline Marith<T> operator*(const Marith<T>& m1, const Marith<T>& m2);
} // namespace mcalc

/**
 * @brief Construct a new mcalc::Marith<T>::Marith object
 *
 * @tparam T
 */
template <typename T>
mcalc::Marith<T>::Marith() : erowop(this) {}
/**
 * @brief Construct a new mcalc::Marith<T>::Marith object
 *
 * @tparam T
 * @param m
 */
template <typename T>
mcalc::Marith<T>::Marith(const Matrix<T>& m) :
    data(m.getData()), rowsize(m.getRowsize()), colsize(m.getColsize()), rank(), erowop(this) {}
/**
 * @brief Construct a new mcalc::Marith<T>::Marith object
 *
 * @tparam T
 * @param mat
 * @param row_size
 * @param col_size
 */
template <typename T>
mcalc::Marith<T>::Marith(const V2<T> mat, const size_t row_size, const size_t col_size) :
    data(mat), rowsize(row_size), colsize(col_size), rank(), erowop(this) {
    size_t rows = getRowsize();
    size_t cols = getColsize();
    size_t drs  = this->data.size();
    if (drs != rows) {
        throw mcalc::bad_cast();
    }
    for (size_t i = 0; i < rows; i++) {
        V1<T>& row   = this->at(i);
        size_t dcs_i = row.size();
        if (dcs_i != cols) {
            throw mcalc::bad_cast();
        }
    }
}
/**
 * @brief Construct a new mcalc::Marith<T>::Marith object
 *
 * @tparam T
 * @param mat
 */
template <typename T>
mcalc::Marith<T>::Marith(const V2<T> mat) : Marith(mat, mat.size(), mat.at(0).size()) {}
/**
 * @brief Construct a new mcalc::Marith<T>::Marith object
 *
 * @tparam T
 * @param row_size
 * @param col_size
 */
template <typename T>
mcalc::Marith<T>::Marith(const size_t row_size, const size_t col_size) :
    Marith(V2<T>(row_size, V1<T>(col_size)), row_size, col_size) {}

/**
 * @brief Construct a new mcalc::Marith<T>::ElemRowOp::ElemRowOp object
 *
 * @tparam T must be arithmetic (will be the same to parent: Marith<T>)
 * @param marith type: Marith<T> Expected to be the pointer of the parent
 */
template <typename T>
mcalc::Marith<T>::ElemRowOp::ElemRowOp(Marith<T>* marith) : this_ptr(marith) {}

/**
 * @brief Return whether the matricies are equivalent
 *
 * @tparam T
 * @param m Operand matrix
 * @return true if all elements are the same.
 * @return false if there is any elements different.
 */
template <typename T>
bool mcalc::Marith<T>::operator==(const mcalc::Matrix<T>& m) const {
    size_t rows  = getRowsize();
    size_t cols  = getColsize();
    size_t mrows = m.getRowsize();
    size_t mcols = m.getColsize();
    if (rows != mrows || cols != mcols) {
        return false;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (at(i, j) != m.at(i, j)) {
                return false;
            }
        }
    }
    return true;
}
/**
 * @brief Call operator== and return the opposite value
 *
 * @tparam T
 * @param m Matrix
 * @return true if there is any elements different.
 * @return false if all elements are the same.
 */
template <typename T>
inline bool mcalc::Marith<T>::operator!=(const mcalc::Matrix<T>& m) const {
    return !operator==(m);
}
/**
 * @brief Substitute a matrix
 *
 * @tparam T
 * @param m Matrix
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::operator=(const mcalc::Matrix<T>& m) {
    Marith(m.getData());
    return *this;
}
/**
 * @brief Add a matrix to *this
 *
 * @tparam T
 * @param m Matrix
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::operator+=(const mcalc::Matrix<T>& m) {
    size_t rows  = getRowsize();
    size_t cols  = getColsize();
    size_t mrows = m.getRowsize();
    size_t mcols = m.getColsize();
    if (rows != mrows || cols != mcols) {
        throw mcalc::range_error("Matricies' size don't match");
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            at(i, j) += m.at(i, j);
        }
    }
    return *this;
}
/**
 * @brief Sabtract a matrix from *this
 *
 * @tparam T
 * @param m Matrix
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::operator-=(const mcalc::Matrix<T>& m) {
    size_t rows  = getRowsize();
    size_t cols  = getColsize();
    size_t mrows = m.getRowsize();
    size_t mcols = m.getColsize();
    if (rows != mrows || cols != mcols) {
        throw mcalc::range_error("Matricies' size don't match");
    }
    for (size_t i = 0; i < getRowsize(); i++) {
        for (size_t j = 0; j < getColsize(); j++) {
            at(i, j) -= m.at(i, j);
        }
    }
    return *this;
}
/**
 * @brief Multiply *this by a scalar
 *
 * @tparam T
 * @param s Scalar value
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::operator*=(const T s) {
    for (size_t i = 0; i < getRowsize(); i++) {
        for (size_t j = 0; j < getColsize(); j++) {
            at(i, j) = s * at(i, j);
        }
    }
    return *this;
}
/**
 * @brief Multiply *this by a matrix
 *
 * @tparam T
 * @param m Matrix
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::operator*=(const Matrix<T>& m) {
    size_t rows  = this->getRowsize();
    size_t cols  = this->getColsize();
    size_t mrows = m.getRowsize();
    size_t mcols = m.getColsize();
    if (rows != mcols) {
        throw mcalc::range_error("Matricies' size don't match");
    }
    V2<T> dresult(rows, V1<T>(cols, 0));
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < mrows; j++) {
            for (size_t k = 0; k < rows; k++) {
                dresult.at(i).at(j) += m.at(i, k) * this->at(k, j);
            }
        }
    }
    this->data = dresult;
    return *this;
}
/**
 * @brief Add two matrices
 *
 * @tparam T
 * @param m1 Matrix 1
 * @param m2 Matrix 2
 * @return mcalc::Marith<T>
 */
template <typename T>
inline mcalc::Marith<T> mcalc::operator+(mcalc::Marith<T>& m1, mcalc::Marith<T>& m2) {
    mcalc::Marith mresult = m1;
    return mresult += m2;
}
/**
 * @brief Subtract a matrix from another matrix
 *
 * @tparam T
 * @param m1 Matrix 1
 * @param m2 Matrix 2
 * @return mcalc::Marith<T>
 */
template <typename T>
inline mcalc::Marith<T> mcalc::operator-(mcalc::Marith<T>& m1, mcalc::Marith<T>& m2) {
    mcalc::Marith mresult = m1;
    return mresult -= m2;
}
/**
 * @brief Get product of a matrix and a scalar
 *
 * @tparam T
 * @param s Scalar value
 * @param m Matrix
 * @return mcalc::Marith<T>
 */
template <typename T>
inline mcalc::Marith<T> mcalc::operator*(const T s, const mcalc::Marith<T>& m) {
    mcalc::Marith<T> mresult = m;
    return mresult *= s;
}
/**
 * @brief Get poduct of a scalar and a matrix
 *
 * @tparam T
 * @param m Matrix
 * @param s Salcar
 * @return mcalc::Marith<T>
 */
template <typename T>
inline mcalc::Marith<T> mcalc::operator*(const mcalc::Marith<T>& m, const T s) {
    return s * m;
}
/**
 * @brief Get product of two matrices
 *
 * @tparam T
 * @param m1 Matrix 1
 * @param m2 Matirx 2
 * @return mcalc::Marith<T>
 */
template <typename T>
inline mcalc::Marith<T> mcalc::operator*(const mcalc::Marith<T>& m1, const mcalc::Marith<T>& m2) {
    mcalc::Marith mresult = m2;
    return mresult *= m1;
}

/**
 * @brief Return list of elements
 *
 * @tparam T
 * @return const mcalc::V2<T>&
 */
template <typename T>
inline const mcalc::V2<T>& mcalc::Marith<T>::getData() const {
    return this->data;
}
/**
 * @brief Return an element on the specified row and column
 *
 * @tparam T
 * @param i Row number
 * @param j Column number
 * @return const T&
 *
 * @details It returns value as const and it doesn't overwrite the member variables.
 */
template <typename T>
inline const T& mcalc::Marith<T>::at(size_t i, size_t j) const {
    if (!(0 < i < getRowsize() && 0 < j < getColsize())) {
        throw mcalc::out_of_range("Index out of range");
    }
    return this->getData().at(i).at(j);
}
/**
 * @brief Return an element on the specified row and column
 *
 * @tparam T
 * @param i Row number
 * @param j Column number
 * @return const T&
 *
 * @details It's return value can be overwrited and It can also overwrite the member variables.
 */
template <typename T>
inline T& mcalc::Marith<T>::at(size_t i, size_t j) {
    if (!(i < getRowsize() && j < getColsize())) {
        throw mcalc::out_of_range("Index out of range");
    }
    return this->data.at(i).at(j);
}
/**
 * @brief Return elements' list on the specified row
 *
 * @tparam T
 * @param i Row number
 * @return const mcalc::V1<T>&
 *
 * @details It returns value as const and it doesn't overwrite the member variables.
 */
template <typename T>
inline const mcalc::V1<T>& mcalc::Marith<T>::at(size_t i) const {
    if (i >= getRowsize()) {
        throw mcalc::out_of_range("Index out of range");
    }
    return this->getData().at(i);
}
/**
 * @brief  Return elements' list on the specified row
 *
 * @tparam T
 * @param i
 * @return mcalc::V1<T>&
 *
 * @details It's return value can be overwrited and It can also overwrite the member variables.
 */
template <typename T>
inline mcalc::V1<T>& mcalc::Marith<T>::at(size_t i) {
    if (i >= getRowsize()) {
        throw mcalc::out_of_range("Index out of range");
    }
    return this->data.at(i);
}

/**
 * @brief Return the row size of *this
 *
 * @tparam T
 * @return const size_t&
 */
template <typename T>
inline const size_t& mcalc::Marith<T>::getRowsize() const {
    return rowsize;
}
/**
 * @brief Return the column size of *this
 *
 * @tparam T
 * @return const size_t&
 */
template <typename T>
inline const size_t& mcalc::Marith<T>::getColsize() const {
    return colsize;
}
/**
 * @brief Return string-expression of *this
 *
 * @tparam T
 * @return std::string
 */
template <typename T>
std::string mcalc::Marith<T>::to_string() const {
    std::ostringstream result;
    result << *this;
    return result.str();
}

/**
 * @brief Return transposed matrix of *this
 *
 * @tparam T
 * @return mcalc::Marith<T>
 */
template <typename T>
mcalc::Marith<T> mcalc::Marith<T>::transpose() const {
    size_t rows = getRowsize();
    size_t cols = getColsize();
    V2<T> dresult(cols, V1<T>(rows));
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++) {
            dresult.at(i).at(j) = at(j, i);
        }
    }
    Marith<T> mresult(dresult);
    return mresult;
}
/**
 * @brief Return the object of elementary-row operations
 *
 * @tparam T
 * @return const mcalc::Marith<T>::ElemRowOp&
 */
template <typename T>
inline const typename mcalc::Marith<T>::ElemRowOp& mcalc::Marith<T>::elemRowOp() {
    return erowop;
}

/**
 * @brief Interchange 2 rows
 *
 * @tparam T
 * @param i Row_index 1
 * @param j Row_index 2
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::_interchange(size_t i, size_t j) const {
    if (i != j) {
        V1<T> data_i    = this_ptr->at(i);
        V1<T> data_j    = this_ptr->at(j);
        this_ptr->at(i) = data_j;
        this_ptr->at(j) = data_i;
    }
    return *this_ptr;
}
/**
 * @brief Multiply each element in a row
 *
 * @tparam T
 * @param i Row_index to be multiplied
 * @param s Scalar value to multiply row
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::_multiply(size_t i, T s) const {
    for (size_t j = 0; j < this_ptr->getColsize(); j++) {
        this_ptr->at(i, j) *= s;
    }
    return *this_ptr;
}
/**
 * @brief Multiply a row and add the result to another row
 *
 * @tparam T
 * @param i Row_index 1 (to be multiplied)
 * @param j Row_index 2
 * @param s Scalar value to multiply row
 * @return mcalc::Marith<T>&
 */
template <typename T>
mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::_add(size_t i, size_t j, T s) const {
    for (size_t k = 0; k < this_ptr->getColsize(); k++) {
        this_ptr->at(j, k) += s * this_ptr->at(i, k);
    }
    return *this_ptr;
}
/**
 * @brief Copy the matrix and call _interchange
 *
 * @tparam T
 * @param i Row_index 1
 * @param j Row_index 2
 * @return const mcalc::Marith<T>&
 */
template <typename T>
inline const mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::interchange(size_t i, size_t j) const {
    mcalc::Marith<T> mresult = *this_ptr;
    return mresult.elemRowOp()._interchange(i, j);
}
/**
 * @brief Copy the matrix and call _multiply
 *
 * @tparam T
 * @param i Row_index to be multiplied
 * @param s Scalar value to multiply row
 * @return const mcalc::Marith<T>&
 */
template <typename T>
inline const mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::multiply(size_t i, T s) const {
    mcalc::Marith<T> mresult = *this_ptr;
    return mresult.elemRowOp()._multiply(i, s);
}
/**
 * @brief Copy the matrix and call _add
 *
 * @tparam T
 * @param i Row_index 1 (to be multiplied by)
 * @param j Row_index 2
 * @param s Scalar value to multiply row
 * @return const mcalc::Marith<T>&
 */
template <typename T>
inline const mcalc::Marith<T>& mcalc::Marith<T>::ElemRowOp::add(size_t i, size_t j, T s) const {
    mcalc::Marith<T> mresult = *this_ptr;
    return mresult.elemRowOp()._add(i, j, s);
}

/**
 * @brief Return the echelon matrix of *this
 *
 * @tparam T
 * @return mcalc::Marith<T>
 */
template <typename T>
mcalc::Marith<T> mcalc::Marith<T>::echelon() {
    static_assert(std::is_floating_point<T>::value, "[error] The type of components must be floating point");

    Marith<T> mresult(this->getData());
    size_t rows = mresult.getRowsize();
    size_t cols = mresult.getColsize();
    size_t r    = 0;
    size_t j    = 0;
    while (r < rows && j < cols) {
        bool skip = false;
        for (size_t i = r; i < rows; i++) {
            if (mresult.at(i, j) != 0) {
                mresult.elemRowOp()._interchange(r, i);
                break;
            } else if (i == rows - 1) {
                skip = true;
            }
        }
        if (!skip) {
            mresult.elemRowOp()._multiply(r, 1 / mresult.at(r, j));
            for (size_t i = 0; i < rows; i++) {
                if (i == j) {
                    continue;
                }
                mresult.elemRowOp()._add(r, i, -mresult.at(i, j));
            }
            r++;
        }
        j++;
    }
    this->rank = r;
    return mresult;
}
/**
 * @brief Return the rank of *this
 *
 * @tparam T
 * @return const size_t&
 */
template <typename T>
const size_t& mcalc::Marith<T>::getRank() {
    static_assert(std::is_floating_point<T>::value, "[error] The type of components must be floating point");
    this->echelon();
    return rank;
}
