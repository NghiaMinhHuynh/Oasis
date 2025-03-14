//
// Created by Matthew McCall on 7/2/23.
//

#ifndef OASIS_REAL_HPP
#define OASIS_REAL_HPP

#include "LeafExpression.hpp"
#include <type_traits>

namespace Oasis {

/**
 * A real number that supports different numeric types.
 */
template <typename T = float, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Real : public LeafExpression<Real<T>> {
public:
    Real() = default;
    Real(const Real& other) = default;

    explicit Real(T value) : value(value) {}

    [[nodiscard]] auto Equals(const Expression& other) const -> bool final;

    EXPRESSION_TYPE(Real)
    EXPRESSION_CATEGORY(UnExp)

    /**
     * Gets the value of the real number.
     * @return The value of the real number.
     */
    [[nodiscard]] auto GetValue() const -> T { return value; }

    [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;

    [[nodiscard]] auto Differentiate(const Expression&) const -> std::unique_ptr<Expression> final;

    auto operator=(const Real& other) -> Real& = default;

private:
    T value {};
};

} // namespace Oasis

#endif // OASIS_REAL_HPP
