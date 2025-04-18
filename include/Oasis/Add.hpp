#ifndef OASIS_ADD_HPP
#define OASIS_ADD_HPP

#include "BinaryExpression.hpp"
#include "Expression.hpp"
#include <memory>

namespace Oasis {

// Forward declaration for the generic template
template <IExpression AugendT, IExpression AddendT>
class Add;

/**
 * Specialized Add for Expression,Expression: carries a direction flag for persistent inserts.
 */
template <>
class Add<Expression, Expression> : public BinaryExpression<Add> {
public:
    using Base = BinaryExpression<Add>;

    /**
     * Constructs an Add node, optionally setting the initial direction (false=left, true=right).
     */
    Add(const std::shared_ptr<Expression>& lhs,
        const std::shared_ptr<Expression>& rhs,
        bool dir = false)
      : Base(*lhs, *rhs), dir_(dir)
    {}

    /**
     * Copy constructor preserves both children and direction.
     */
    Add(const Add& other) = default;

    /**
     * Creates a new shared_ptr<Add> with flipped direction.
     */
    auto copy_with_dir(bool newDir) const -> std::shared_ptr<Add> {
        auto ptr = std::make_shared<Add>(*this);
        ptr->dir_ = newDir;
        return ptr;
    }

    /**
     * Returns the current direction flag: false=go left next, true=go right next.
     */
    bool dir() const { return dir_; }

    EXPRESSION_TYPE(Add)
    EXPRESSION_CATEGORY(Associative | Commutative)

private:
    bool dir_{false};
};

/**
 * Generic Add template (for heterogeneous operand types): behavior unchanged.
 */
template <IExpression AugendT, IExpression AddendT>
class Add : public BinaryExpression<Add, AugendT, AddendT> {
public:
    using Base = BinaryExpression<Add, AugendT, AddendT>;
    Add() = default;
    Add(const AugendT& a, const AddendT& b)
      : Base(a, b)
    {}
    Add(const Add& other) = default;
    auto operator=(const Add& other) -> Add& = default;

    EXPRESSION_TYPE(Add)
    EXPRESSION_CATEGORY(Associative | Commutative)
};

} // namespace Oasis

#endif // OASIS_ADD_HPP
