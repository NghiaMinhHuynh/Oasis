//
// Created by Matthew McCall on 4/30/24.
//

#ifndef OASIS_DEFINITEINTEGRAL_HPP
#define OASIS_DEFINITEINTEGRAL_HPP

#include "Oasis/BoundedBinaryExpression.hpp"
#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * A symbolic definite integral:
 *
 *    ∫_{var = lower}^{upper} body
 */
template <
  IExpression OperandT,
  IExpression VariableT,
  IExpression LowerBoundT = Expression,
  IExpression UpperBoundT = LowerBoundT
>
class DefiniteIntegral final
  : public BoundedBinaryExpression<
        DefiniteIntegral,
        OperandT,
        VariableT,
        LowerBoundT,
        UpperBoundT>
{
public:
  using Base = BoundedBinaryExpression<
      DefiniteIntegral,
      OperandT,
      VariableT,
      LowerBoundT,
      UpperBoundT>;

  /**
   * Construct ∫_{var=lower}^{upper} body
   */
  DefiniteIntegral(const VariableT& var,
                   const LowerBoundT& lower,
                   const UpperBoundT& upper,
                   const OperandT& body)
    : Base(body, var)
  {
    this->SetLowerBound(lower);
    this->SetUpperBound(upper);
  }

  /// Simplify by simplifying bounds and body
  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  /// d/dvar ∫ body dvar = 0 if var matches; otherwise push derivative inside
  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// ∫ (∫ body dvar) dvar = nested; otherwise integrate inside
  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// Access the integration variable
  [[nodiscard]] auto GetVariable() const -> const VariableT& {
    return this->GetLeastSigOp();
  }

  /// Access the integrand body
  [[nodiscard]] auto GetBody() const -> const OperandT& {
    return this->GetMostSigOp();
  }
};

} // namespace Oasis

#endif // OASIS_DEFINITEINTEGRAL_HPP
