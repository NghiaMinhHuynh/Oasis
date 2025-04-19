// include/Oasis/Imaginary.hpp
// Created by Andrew Nazareth on 10/10/23.

#ifndef OASIS_IMAGINARY_HPP
#define OASIS_IMAGINARY_HPP

#include "Oasis/LeafExpression.hpp"
#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * The imaginary unit i (√-1).
 */
class Imaginary : public LeafExpression<Imaginary> {
public:
    Imaginary() = default;
    Imaginary(const Imaginary& other) = default;

    /**
     * Leaf equality: all Imaginary units are identical
     */
    [[nodiscard]] auto Equals(const Expression& other) const -> bool final;

    /**
     * Derivative of i w.r.t. any variable is zero
     */
    [[nodiscard]] auto Differentiate(const Expression& var) const
        -> std::unique_ptr<Expression> override;

    /**
     * Integral of i dx is i*x
     */
    [[nodiscard]] auto Integrate(const Expression& var) const
        -> std::unique_ptr<Expression> override;

    EXPRESSION_TYPE(Imaginary)
    EXPRESSION_CATEGORY(UnExp)
};

} // namespace Oasis

#endif // OASIS_IMAGINARY_HPP
