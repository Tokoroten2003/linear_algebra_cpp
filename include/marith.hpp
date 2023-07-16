#include <array>
#include <iostream>
#include <type_traits>

namespace mcalc {
template <typename T, std::size_t rowN, std::size_t colN>
class Marith {
    static_assert(std::is_arithmetic<T>::value, "The elements' type must be arithmetic!");
    static_assert(colN != 0 && rowN != 0, "The column size and the row size must not be zero!");
    std::array<std::array<T, colN>, rowN> elems;

public:
    Marith();
    Marith(const Marith<T, rowN, colN>& mat);
    Marith(const Marith<T, rowN, colN>&& mat);
    Marith(const std::array<std::array<T, colN>, rowN>&& arr);

    inline const std::array<std::array<T, colN>, rowN>& getElems() const;
    inline void setElems(std::array<std::array<T, colN>, rowN>&& arr);
    inline constexpr std::size_t sizeRow() const;
    inline constexpr std::size_t sizeCol() const;
    inline const T& at_const(std::size_t i, std::size_t j) const;
    inline T& at(std::size_t i, std::size_t j);
    inline const std::array<T, colN>& at_const(std::size_t i) const;
    inline std::array<T, colN>& at(std::size_t i);

    inline bool operator==(const Marith<T, rowN, colN>& r_mat) const;
    inline bool operator!=(const Marith<T, rowN, colN>& r_mat) const;
    inline Marith<T, rowN, colN>& operator=(const Marith<T, rowN, colN>& r_mat);
    inline Marith<T, rowN, colN>& operator=(Marith<T, rowN, colN>&& r_mat);
    inline Marith<T, rowN, colN>& operator+=(const Marith<T, rowN, colN>& r_mat);
    inline Marith<T, rowN, colN>& operator-=(const Marith<T, rowN, colN>& r_mat);
    inline Marith<T, rowN, colN>& operator*=(const T& r_value);
    inline Marith<T, rowN, colN>& operator*=(const Marith<T, rowN, rowN>& r_mat);

private:
    template <typename U, std::size_t rowN2, std::size_t colN2>
    inline Marith<U, rowN2, colN2> conversion() const;
};

template <typename T, std::size_t rowN, std::size_t colN>
inline std::ostream& operator<<(std::ostream& l_stream, const Marith<T, rowN, colN>& r_mat);
template <typename T, std::size_t rowN, std::size_t colN>
inline Marith<T, rowN, colN> operator+(const Marith<T, rowN, colN>& l_mat, const Marith<T, rowN, colN>& r_mat);
template <typename T, std::size_t rowN, std::size_t colN>
inline Marith<T, rowN, colN> operator-(const Marith<T, rowN, colN>& l_mat, const Marith<T, rowN, colN>& r_mat);
template <typename T, std::size_t rowN, std::size_t colN>
inline Marith<T, rowN, colN> operator*(const Marith<T, rowN, colN>& l_mat, const T& r_value);
template <typename T, std::size_t rowN, std::size_t colN>
inline Marith<T, rowN, colN> operator*(const T& l_value, const Marith<T, rowN, colN>& r_mat);
template <typename T, std::size_t rowN, std::size_t colN, std::size_t colN2>
inline Marith<T, rowN, colN2> operator*(const Marith<T, rowN, colN>& l_mat, const Marith<T, colN, colN2>& r_mat);
} // namespace mcalc

// ---------------------------
// Definition of class members
// ---------------------------

template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>::Marith() : elems() {}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>::Marith(const Marith<T, rowN, colN>& mat) : elems(mat.getElems()) {}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>::Marith(const Marith<T, rowN, colN>&& mat) : elems(mat.getElems()) {}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>::Marith(const std::array<std::array<T, colN>, rowN>&& arr) : elems(arr) {}

template <typename T, std::size_t rowN, std::size_t colN>
inline const std::array<std::array<T, colN>, rowN>& mcalc::Marith<T, rowN, colN>::getElems() const {
    return elems;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline void mcalc::Marith<T, rowN, colN>::setElems(std::array<std::array<T, colN>, rowN>&& arr) {
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            at(i, j) = arr.at(i).at(j);
        }
    }
}
template <typename T, std::size_t rowN, std::size_t colN>
inline constexpr std::size_t mcalc::Marith<T, rowN, colN>::sizeRow() const {
    return rowN;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline constexpr std::size_t mcalc::Marith<T, rowN, colN>::sizeCol() const {
    return colN;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline const T& mcalc::Marith<T, rowN, colN>::at_const(std::size_t i, std::size_t j) const {
    return elems.at(i).at(j);
}
template <typename T, std::size_t rowN, std::size_t colN>
inline T& mcalc::Marith<T, rowN, colN>::at(std::size_t i, std::size_t j) {
    return elems.at(i).at(j);
}
template <typename T, std::size_t rowN, std::size_t colN>
inline const std::array<T, colN>& mcalc::Marith<T, rowN, colN>::at_const(std::size_t i) const {
    return elems.at(i);
}
template <typename T, std::size_t rowN, std::size_t colN>
inline std::array<T, colN>& mcalc::Marith<T, rowN, colN>::at(std::size_t i) {
    return elems.at(i);
}

template <typename T, std::size_t rowN, std::size_t colN>
inline bool mcalc::Marith<T, rowN, colN>::operator==(const mcalc::Marith<T, rowN, colN>& r_mat) const {
    return getElems() == r_mat.getElems();
}
template <typename T, std::size_t rowN, std::size_t colN>
inline bool mcalc::Marith<T, rowN, colN>::operator!=(const mcalc::Marith<T, rowN, colN>& r_mat) const {
    return !operator==(r_mat);
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>&
mcalc::Marith<T, rowN, colN>::operator=(const mcalc::Marith<T, rowN, colN>& r_mat) {
    std::array<std::array<T, colN>, rowN> arr = r_mat.getElems();
    setElems(std::move(arr));
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>& mcalc::Marith<T, rowN, colN>::operator=(mcalc::Marith<T, rowN, colN>&& r_mat) {
    setElems(std::move(const_cast<std::array<std::array<T, colN>, rowN>&>(r_mat.getElems())));
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>&
mcalc::Marith<T, rowN, colN>::operator+=(const mcalc::Marith<T, rowN, colN>& r_mat) {
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            at(i, j) += r_mat.at_const(i, j);
        }
    }
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>&
mcalc::Marith<T, rowN, colN>::operator-=(const mcalc::Marith<T, rowN, colN>& r_mat) {
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            at(i, j) -= r_mat.at_const(i, j);
        }
    }
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>& mcalc::Marith<T, rowN, colN>::operator*=(const T& r_value) {
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            at(i, j) *= r_value;
        }
    }
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline mcalc::Marith<T, rowN, colN>&
mcalc::Marith<T, rowN, colN>::operator*=(const mcalc::Marith<T, rowN, rowN>& r_mat) {
    std::array<std::array<T, colN>, rowN> result;
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            result.at(i).at(j) = 0;
            for (std::size_t k = 0; k < rowN; k++) {
                result.at(i).at(j) += r_mat.at_const(i, k) * at_const(k, j);
            }
        }
    }
    setElems(std::move(result));
    return *this;
}
template <typename T, std::size_t rowN, std::size_t colN>
template <typename U, std::size_t rowN2, std::size_t colN2>
mcalc::Marith<U, rowN2, colN2> mcalc::Marith<T, rowN, colN>::conversion() const {
    mcalc::Marith<U, rowN2, colN2> result;
    for (std::size_t i = 0; i < rowN2; i++) {
        if (i >= rowN) {
            break;
        }
        for (std::size_t j = 0; j < colN2; j++) {
            if (j >= colN) {
                break;
            }
            result.at(i, j) = static_cast<U>(at_const(i, j));
        }
    }
    return result;
}

template <typename T, std::size_t rowN, std::size_t colN>
std::ostream& mcalc::operator<<(std::ostream& l_stream, const mcalc::Marith<T, rowN, colN>& r_mat) {
    l_stream << "[ ";
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN; j++) {
            l_stream << r_mat.at_const(i, j) << (j < colN - 1 ? " " : (i < rowN - 1 ? " \\\\ " : " ]"));
        }
    }
    return l_stream;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>
mcalc::operator+(const mcalc::Marith<T, rowN, colN>& l_mat, const mcalc::Marith<T, rowN, colN>& r_mat) {
    mcalc::Marith<T, rowN, colN> result = l_mat;
    result += r_mat;
    return result;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>
mcalc::operator-(const mcalc::Marith<T, rowN, colN>& l_mat, const mcalc::Marith<T, rowN, colN>& r_mat) {
    mcalc::Marith<T, rowN, colN> result = l_mat;
    result -= r_mat;
    return result;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN> mcalc::operator*(const mcalc::Marith<T, rowN, colN>& l_mat, const T& r_value) {
    mcalc::Marith<T, rowN, colN> result = l_mat;
    result *= r_value;
    return result;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN> mcalc::operator*(const T& l_value, const mcalc::Marith<T, rowN, colN>& r_mat) {
    return r_mat * l_value;
}
template <typename T, std::size_t rowN, std::size_t colN, std::size_t colN2>
mcalc::Marith<T, rowN, colN2>
mcalc::operator*(const mcalc::Marith<T, rowN, colN>& l_mat, const mcalc::Marith<T, colN, colN2>& r_mat) {
    mcalc::Marith<T, rowN, colN2> result;
    for (std::size_t i = 0; i < rowN; i++) {
        for (std::size_t j = 0; j < colN2; j++) {
            T elem = 0;
            for (std::size_t k = 0; k < colN; k++) {
                elem += l_mat.at_const(i, k) * r_mat.at_const(k, j);
            }
            result.at(i, j) = elem;
        }
    }
    return result;
}
