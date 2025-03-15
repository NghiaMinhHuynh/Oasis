#ifndef OASIS_SUBTRACT_HPP
#define OASIS_SUBTRACT_HPP

#include "BinaryExpression.hpp"
#include "Real.hpp"

namespace Oasis {

template <IExpression MinuendT, IExpression SubtrahendT>
class Subtract;

/// @cond
template <>
class Subtract<Expression, Expression> : public BinaryExpression<Subtract> {
public:
    Subtract() = default;
    Subtract(const Subtract<Expression, Expression>& other) = default;

    Subtract(const Expression& minuend, const Expression& subtrahend)
        : BinaryExpression<Subtract>(minuend, subtrahend)
    {
        // Set the parent pointers
        this->mostSigOp->SetParent(this); // Set parent for minuend
        this->leastSigOp->SetParent(this); // Set parent for subtrahend
    }

    [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

    [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

    [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;

    EXPRESSION_TYPE(Subtract)
    EXPRESSION_CATEGORY(BinExp)
};
/// @endcond

// The Subtract expression subtracts two expressions.
template <IExpression MinuendT = Expression, IExpression SubtrahendT = MinuendT>
class Subtract : public BinaryExpression<Subtract, MinuendT, SubtrahendT> {
public:
    Subtract() = default;
    Subtract(const Subtract<MinuendT, SubtrahendT>& other)
        : BinaryExpression<Subtract, MinuendT, SubtrahendT>(other)
    {
    }

    Subtract(const MinuendT& minuend, const SubtrahendT& subtrahend)
        : BinaryExpression<Subtract, MinuendT, SubtrahendT>(minuend, subtrahend)
    {
        // Set the parent pointers
        this->mostSigOp->SetParent(this); // Set parent for minuend
        this->leastSigOp->SetParent(this); // Set parent for subtrahend
    }

    auto operator=(const Subtract& other) -> Subtract& = default;

    EXPRESSION_TYPE(Subtract)
    EXPRESSION_CATEGORY(BinExp)
};

} // Oasis

#endif // OASIS_SUBTRACT_HPP
