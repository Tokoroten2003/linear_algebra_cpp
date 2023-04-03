/**
 * @file errors.hpp
 * @brief declare error_types in matrix context
 */
#include <string>
namespace mcalc {
/**
 * @brief inherits std::bad_cast. doesn't require error message.
 */
class bad_cast : public std::bad_cast {
public:
    using std::bad_cast::bad_cast;
};

/**
 * @brief inherits std::out_of_range. requires error message.
 */
class out_of_range : public std::out_of_range {
public:
    using std::out_of_range::out_of_range;
};

/**
 * @brief inherits std::range_error. requires error message.
 */
class range_error : public std::range_error {
public:
    using std::range_error::range_error;
};
} // namespace mcalc
