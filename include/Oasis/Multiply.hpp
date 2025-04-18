//
// Created by Matthew McCall on 8/10/23.
// Modified for persistent, O(log N) inserts by adding direction flag and copy_with_dir.

#ifndef OASIS_MULTIPLY_HPP
#define OASIS_MULTIPLY_HPP

#include "BinaryExpression.hpp"
#include "Expression.hpp"
#include "Real.hpp"
#include <memory>

namespace Oasis {

template <IExpression MultiplicandT, IExpression MultiplierT>
class Multiply;

/**
 * Specialized Multiply for Expression,Expression: carries a direction flag for persistent inserts.
 */
template <>
class Multiply<Expression, Expression> : public BinaryExpression<Multiply> {
public:
    using Base = BinaryExpression<Multiply>;

    /**
     * Constructs a Multiply node, optionally setting the initial direction (false=left, true=right).
     */
    Multiply(const std::shared_ptr<Expression>& lhs,
             const std::shared_ptr<Expression>& rhs,
             bool dir = false)
      : Base(*lhs, *rhs), dir_(dir)
    {}

    /**
     * Default copy constructor preserves both children and direction.
     */
    Multiply(const Multiply& other) = default;

    /**
     * Creates a new shared_ptr<Multiply> with flipped direction.
     */
    auto copy_with_dir(bool newDir) const -> std::shared_ptr<Multiply> {
        auto ptr = std::make_shared<Multiply>(*this);
        ptr->dir_ = newDir;
        return ptr;
    }

    /**
     * Returns the current direction flag: false=go left next, true=go right next.
     */
    bool dir() const { return dir_; }

    [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;
    [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;
    [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;

    EXPRESSION_TYPE(Multiply)
    EXPRESSION_CATEGORY(Associative | Commutative | BinExp)

private:
    bool dir_{false};
};

/**
 * Generic Multiply template (for heterogeneous operand types): behavior unchanged.
 */
template <IExpression MultiplicandT, IExpression MultiplierT>
class Multiply : public BinaryExpression<Multiply, MultiplicandT, MultiplierT> {
public:
    using Base = BinaryExpression<Multiply, MultiplicandT, MultiplierT>;
    Multiply() = default;
    Multiply(const Multiply<MultiplicandT, MultiplierT>& other) = default;
    Multiply(const MultiplicandT& a, const MultiplierT& b)
      : Base(a, b)
    {}
    auto operator=(const Multiply& other) -> Multiply& = default;

    EXPRESSION_TYPE(Multiply)
    EXPRESSION_CATEGORY(Associative | Commutative | BinExp)
};

} // namespace Oasis

#endif // OASIS_MULTIPLY_HPP
