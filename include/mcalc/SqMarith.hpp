#pragma once

#include "mcalc/Marith.hpp"
#include "mcalc/alias.hpp"
#include <string>

namespace mcalc {
template <typename T> class SqMarith : public Marith<T> {
private:
    bool isregular;

public:
    using Marith<T>::Marith;

    // constractors
    SqMarith();
    SqMarith(const Matrix<T> &m);
    SqMarith(const V2<T> mat, const size_t size_of_matrix);
    SqMarith(const V2<T> mat);
    SqMarith(const size_t size_of_matrix);

    // return the size of this matrix
    inline const size_t getSize() const;
    // return the determinant of this matrix
    T determinant();
    // return boolian: if this matrix is regular or not
    bool isRegular();
    // return an identity matrix
    static SqMarith<T> identity(size_t size_of_matrix);
    // return an elementary matrix for interchange
    static SqMarith<T> elementary_ic(size_t size_of_matrix, size_t i, size_t j);
    // return an elementary matrix for multilication
    static SqMarith<T> elementary_mtpl(size_t size_of_matrix, size_t i, T s);
    // return an elementary matrix for addition
    static SqMarith<T> elementary_add(size_t size_of_matrix, size_t i, size_t j, T s);
};
} // namespace mcalc

template <typename T> mcalc::SqMarith<T>::SqMarith() : Marith<T>::Marith(), isregular() {}
template <typename T>
mcalc::SqMarith<T>::SqMarith(const Matrix<T> &m) : Marith<T>::Marith(m), isregular() {
    size_t mrows = m.getRowsize();
    size_t mcols = m.getColsize();
    if (mrows != mcols) {
        throw mcalc::bad_cast();
    }
}
template <typename T>
mcalc::SqMarith<T>::SqMarith(const V2<T> mat, const size_t size_of_matrix)
    : Marith<T>::Marith(mat, size_of_matrix, size_of_matrix), isregular() {}
template <typename T> mcalc::SqMarith<T>::SqMarith(const V2<T> mat) : SqMarith<T>::SqMarith(mat, mat.at(0).size()) {
    if (mat.size() != mat.at(0).size()) {
        throw mcalc::bad_cast();
    }
}
template <typename T>
mcalc::SqMarith<T>::SqMarith(const size_t size_of_matrix)
    : Marith<T>::Marith(size_of_matrix, size_of_matrix), isregular() {}

template <typename T> inline const size_t mcalc::SqMarith<T>::getSize() const { return this->getRowsize(); }
template <typename T> T mcalc::SqMarith<T>::determinant() {
    SqMarith<T> m(this->getData());
    size_t msize = m.getSize();
    T result = 1;
    for (size_t j = 0; j < msize; j++) {
        for (size_t i = j; i < msize; i++) {
            if (m.at(i, j) != 0) {
                m.elemRowOp()._interchange(i, j);
                break;
            }
            if (j == msize - 1) {
                return 0;
            }
        }
        for (size_t i = j + 1; i < msize; i++) {
            T s = m.at(i, j) / m.at(j, j);
            m.elemRowOp()._add(j, i, -s);
        }
        result *= m.at(j, j);
    }
    this->isregular = (result != 0) ? true : false;
    return result;
}
template <typename T> bool mcalc::SqMarith<T>::isRegular() {
    this->determinant();
    return isregular;
}

template <typename T> mcalc::SqMarith<T> mcalc::SqMarith<T>::identity(size_t size_of_matrix) {
    SqMarith<T> mresult(size_of_matrix);
    for (size_t i = 0; i < mresult.getSize(); i++) {
        mresult.at(i, i) = 1;
    }
    return mresult;
}
template <typename T> mcalc::SqMarith<T> mcalc::SqMarith<T>::elementary_ic(size_t size_of_matrix, size_t i, size_t j) {
    SqMarith<T> mresult = identity(size_of_matrix);
    mresult.at(i, i) = 0;
    mresult.at(j, j) = 0;
    mresult.at(i, j) = 1;
    mresult.at(j, i) = 1;
    return mresult;
}
template <typename T> mcalc::SqMarith<T> mcalc::SqMarith<T>::elementary_mtpl(size_t size_of_matrix, size_t i, T s) {
    SqMarith<T> mresult = identity(size_of_matrix);
    mresult.at(i, i) = s;
    return mresult;
}
template <typename T>
mcalc::SqMarith<T> mcalc::SqMarith<T>::elementary_add(size_t size_of_matrix, size_t i, size_t j, T s) {
    SqMarith<T> mresult = identity(size_of_matrix);
    mresult.at(j, i) = s;
    return mresult;
}
