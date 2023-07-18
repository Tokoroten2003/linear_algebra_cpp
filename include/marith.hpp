#include <array>
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
    inline const std::size_t sizeRow() const;
    inline const std::size_t sizeCol() const;
    inline const T& at_const(std::size_t i, std::size_t j) const;
    inline T& at(std::size_t i, std::size_t j);
    inline const std::array<T, colN>& at_const(std::size_t i) const;
    inline std::array<T, colN>& at(std::size_t i);
};

namespace impl {
    namespace elemRowXform {
        template <typename T, std::size_t rowN, std::size_t colN>
        Marith<T, rowN, colN>& interchange_(Marith<T, rowN, colN>& mat, std::size_t i, std::size_t j);
        template <typename T, std::size_t rowN, std::size_t colN>
        Marith<T, rowN, colN>& multiplyAndAdd_(Marith<T, rowN, colN>& mat, T s, std::size_t i, std::size_t j);
        template <typename T, std::size_t rowN, std::size_t colN>
        Marith<T, rowN, colN>& multiply_(Marith<T, rowN, colN>& mat, T s, std::size_t i);
    } // namespace elemRowXform

} // namespace impl

} // namespace mcalc

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
inline const std::size_t mcalc::Marith<T, rowN, colN>::sizeRow() const {
    return rowN;
}
template <typename T, std::size_t rowN, std::size_t colN>
inline const std::size_t mcalc::Marith<T, rowN, colN>::sizeCol() const {
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

// impl
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>& mcalc::impl::elemRowXform::interchange_(mcalc::Marith<T, rowN, colN>& mat, std::size_t i, std::size_t j) {
    const std::array<T, colN> mat_at_i = mat.at_const(i);
    mat.at(i) = mat.at_const(j);
    mat.at(j) = mat_at_i;
    return mat;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>& mcalc::impl::elemRowXform::multiplyAndAdd_(mcalc::Marith<T, rowN, colN>& mat, T s, std::size_t i, std::size_t j) {
    for (std::size_t k = 0; k < colN; k++) {
        mat.at(j, k) += mat.at_const(i, k) * s;
    }
    return mat;
}
template <typename T, std::size_t rowN, std::size_t colN>
mcalc::Marith<T, rowN, colN>& mcalc::impl::elemRowXform::multiply_(mcalc::Marith<T, rowN, colN>& mat, T s, std::size_t i) {
    for (std::size_t j = 0; j < colN; j++) {
        mat.at(i, j) *= s;
    }
    return mat;
}