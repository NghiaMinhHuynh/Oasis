//
// Created by Matthew McCall on 5/2/24.
//

#ifndef OASIS_SUMMATION_HPP
#define OASIS_SUMMATION_HPP

#include "Oasis/BoundedBinaryExpression.hpp"
#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * Symbolic summation:
 *
 *   Σ_{index = lower}^{upper} body(index)
 *
 * Template parameters:
 *   OperandT         — the “body” expression type
 *   IncrementingVarT — the bound index variable type
 *   LowerBoundT      — type of the lower‐bound expression
 *   UpperBoundT      — type of the upper‐bound expression
 */
template <
    IExpression OperandT,
    IExpression IncrementingVarT,
    IExpression LowerBoundT = Expression,
    IExpression UpperBoundT = LowerBoundT>
class Summation final
  : public BoundedBinaryExpression<
        Summation,
        OperandT,
        IncrementingVarT,
        LowerBoundT,
        UpperBoundT>
{
public:
  using Base = BoundedBinaryExpression<
      Summation,
      OperandT,
      IncrementingVarT,
      LowerBoundT,
      UpperBoundT>;

  /// Build Σ_{idx=lower}^{upper} body
  Summation(const IncrementingVarT& idx,
            const LowerBoundT& lower,
            const UpperBoundT& upper,
            const OperandT& body)
    : Base(body, idx)
  {
    this->SetLowerBound(lower);
    this->SetUpperBound(upper);
  }

  /// Fully simplify: try to evaluate when bounds & body are constants
  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  /// d/dvar Σ f(idx,var) = Σ d/dvar f(idx,var) (and 0 if var==idx)
  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// ∫ Σ f(idx,t) dt = Σ ∫ f(idx,t) dt
  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// Accessors for clarity
  [[nodiscard]] auto GetIndex() const -> const IncrementingVarT&
  { return this->GetLeastSigOp(); }

  [[nodiscard]] auto GetBody() const -> const OperandT&
  { return this->GetMostSigOp(); }

  // Note: use Base::GetLowerBound() and Base::GetUpperBound()
  // to fetch the bounds themselves.
};

} // namespace Oasis

#endif // OASIS_SUMMATION_HPP
