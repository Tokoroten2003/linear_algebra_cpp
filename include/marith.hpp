#include <array>
#include <type_traits>

namespace mcalc {
template <typename T, std::size_t colN, std::size_t rowN>
class Marith {
    static_assert(std::is_arithmetic<T>::value, "The elements' type of \"Marith\" must be arithmetic!");
    std::array<std::array<T, rowN>, colN> elems;

public:
    Marith();
    Marith(const Marith<T, colN, rowN>& mat);
    Marith(const std::array<std::array<T, rowN>, colN>& arr);

    inline const std::array<std::array<T, rowN>, colN>& getElems() const;
    inline const std::size_t sizeRow() const;
    inline const std::size_t sizeCol() const;
    inline const T& at(std::size_t i, std::size_t j) const;
    inline T& at(std::size_t i, std::size_t j);
};
} // namespace mcalc

template <typename T, std::size_t colN, std::size_t rowN>
mcalc::Marith<T, colN, rowN>::Marith() : elems() {}
template <typename T, std::size_t colN, std::size_t rowN>
mcalc::Marith<T, colN, rowN>::Marith(const Marith<T, colN, rowN>& mat) : elems(mat.getElems()) {}
template <typename T, std::size_t colN, std::size_t rowN>
mcalc::Marith<T, colN, rowN>::Marith(const std::array<std::array<T, rowN>, colN>& arr) : elems(arr) {}

template <typename T, std::size_t colN, std::size_t rowN>
inline const std::array<std::array<T, rowN>, colN>& mcalc::Marith<T, colN, rowN>::getElems() const {
    return elems;
}
template <typename T, std::size_t colN, std::size_t rowN>
inline const std::size_t mcalc::Marith<T, colN, rowN>::sizeRow() const {
    return rowN;
}
template <typename T, std::size_t colN, std::size_t rowN>
inline const std::size_t mcalc::Marith<T, colN, rowN>::sizeCol() const {
    return colN;
}
template <typename T, std::size_t colN, std::size_t rowN>
inline const T& mcalc::Marith<T, colN, rowN>::at(std::size_t i, std::size_t j) const {
    return elems.at(i).at(j);
}
template <typename T, std::size_t colN, std::size_t rowN>
inline T& mcalc::Marith<T, colN, rowN>::at(std::size_t i, std::size_t j) {
    return elems.at(i).at(j);
}
