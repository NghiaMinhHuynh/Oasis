#ifndef OASIS_ADD_HPP
#define OASIS_ADD_HPP

#include "BinaryExpression.hpp"
#include "Real.hpp"
#include <memory>  // For std::shared_ptr

namespace Oasis {

template <IExpression AugendT, IExpression AddendT>
class Add;

template <>
class Add<Expression, Expression> : public BinaryExpression<Add> {
public:
    using BinaryExpression::BinaryExpression;

    // Constructor with parent pointer initialization
    Add(const AugendT& addend1, const AddendT& addend2, std::shared_ptr<Expression> parent = nullptr)
        : BinaryExpression<Add, AugendT, AddendT>(addend1, addend2), parent_(parent)
    {}

    [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;

    [[nodiscard]] auto Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression> final;
    [[nodiscard]] auto Differentiate(const Expression& differentiationVariable) const -> std::unique_ptr<Expression> final;

    EXPRESSION_TYPE(Add)
    EXPRESSION_CATEGORY(Associative | Commutative | BinExp)

    // Getter and Setter for parent pointer
    void SetParent(std::shared_ptr<Expression> parent) { parent_ = parent; }
    std::shared_ptr<Expression> GetParent() const { return parent_; }

private:
    mutable std::shared_ptr<Expression> parent_; // Parent pointer
};

template <IExpression AugendT = Expression, IExpression AddendT = AugendT>
class Add : public BinaryExpression<Add, AugendT, AddendT> {
public:
    Add() = default;
    Add(const Add<AugendT, AddendT>& other)
        : BinaryExpression<Add, AugendT, AddendT>(other), parent_(other.parent_)
    {
    }

    Add(const AugendT& addend1, const AddendT& addend2, std::shared_ptr<Expression> parent = nullptr)
        : BinaryExpression<Add, AugendT, AddendT>(addend1, addend2), parent_(parent)
    {
        if (addend1.GetParent() == nullptr) {
            addend1.SetParent(shared_from_this());
        }
        if (addend2.GetParent() == nullptr) {
            addend2.SetParent(shared_from_this());
        }
    }

    auto operator=(const Add& other) -> Add& = default;

    EXPRESSION_TYPE(Add)
    EXPRESSION_CATEGORY(Associative | Commutative)

    void SetParent(std::shared_ptr<Expression> parent) { parent_ = parent; }
    std::shared_ptr<Expression> GetParent() const { return parent_; }

private:
    std::shared_ptr<Expression> parent_;
};

} // namespace Oasis

#endif // OASIS_ADD_HPP
