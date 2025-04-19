#ifndef OASIS_UTILS_HPP
#define OASIS_UTILS_HPP

#include <string>

namespace Oasis {

/**
 * Parse the input string `expr`, run the
 * Expression::Simplify() pass, then return
 * the simplified expression as a string.
 */
std::string SimplifyString(const std::string& expr);

} // namespace Oasis

#endif // OASIS_UTILS_HPP
