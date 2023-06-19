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
};
} // namespace mcalc

template <typename T, std::size_t colN, std::size_t rowN>
mcalc::Marith<T, colN, rowN>::Marith() : elems() {}
