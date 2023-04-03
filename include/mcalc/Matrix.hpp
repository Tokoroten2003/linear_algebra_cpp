#pragma once

#include "mcalc/alias.hpp"
#include <sstream>
#include <string>
#include <vector>
namespace mcalc {
template <typename T> class Matrix {
public:
    virtual bool operator==(const Matrix<T> &m) const = 0;
    virtual inline bool operator!=(const Matrix &m) const = 0;
    virtual Matrix<T> &operator=(const Matrix &m) = 0;
    virtual Matrix<T> &operator+=(const Matrix &m) = 0;
    virtual Matrix<T> &operator-=(const Matrix &m) = 0;
    virtual Matrix<T> &operator*=(const T s) = 0;
    virtual Matrix<T> &operator*=(const Matrix &m) = 0;

    virtual inline const V2<T> &getData() const = 0;
    virtual inline const T &at(size_t i, size_t j) const = 0;
    virtual inline T &at(size_t i, size_t j) = 0;
    virtual inline const V1<T> &at(size_t i) const = 0;
    virtual inline V1<T> &at(size_t i) = 0;
    virtual inline const size_t &getRowsize() const = 0;
    virtual inline const size_t &getColsize() const = 0;
    virtual std::string to_string() const = 0;
};
template <typename T> std::ostream &operator<<(std::ostream &stream, const Matrix<T> &m);
} // namespace mcalc

template <typename T> std::ostream &mcalc::operator<<(std::ostream &stream, const Matrix<T> &m) {
    size_t rows = m.getRowsize();
    size_t cols = m.getColsize();
    stream << "[";
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            stream << m.at(i, j) << (j < cols - 1 ? " " : "");
        }
        stream << (i < rows - 1 ? "|" : "");
    }
    stream << "]";
    return stream;
}
