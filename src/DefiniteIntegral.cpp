// src/DefiniteIntegral.cpp

#include "Oasis/DefiniteIntegral.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Variable.hpp"

namespace Oasis {

// Simplify by simplifying bounds and integrand
template <IExpression OperandT,
          IExpression VariableT,
          IExpression LowerBoundT,
          IExpression UpperBoundT>
auto DefiniteIntegral<OperandT,VariableT,LowerBoundT,UpperBoundT>::Simplify() const
  -> std::unique_ptr<Expression>
{
  auto lo_s   = this->GetLowerBound().Simplify();
  auto hi_s   = this->GetUpperBound().Simplify();
  auto body_s = this->GetBody().Simplify();

  return std::make_unique<DefiniteIntegral>(
    this->GetVariable(),
    *lo_s,
    *hi_s,
    *body_s
  );
}

// Differentiate: 0 if w.r.t. the integration variable, else push inside
template <IExpression OperandT,
          IExpression VariableT,
          IExpression LowerBoundT,
          IExpression UpperBoundT>
auto DefiniteIntegral<OperandT,VariableT,LowerBoundT,UpperBoundT>::Differentiate(
    const Expression& var) const
  -> std::unique_ptr<Expression>
{
  const auto& idxName = this->GetVariable().GetName();
  if (auto v = dynamic_cast<const Variable*>(&var);
      v && v->GetName() == idxName)
  {
    return std::make_unique<Real>(0.0);
  }

  return std::make_unique<DefiniteIntegral>(
    this->GetVariable(),
    this->GetLowerBound(),
    this->GetUpperBound(),
    *this->GetBody().Differentiate(var)
  )->Simplify();
}

// Integrate: push integration inside the integrand
template <IExpression OperandT,
          IExpression VariableT,
          IExpression LowerBoundT,
          IExpression UpperBoundT>
auto DefiniteIntegral<OperandT,VariableT,LowerBoundT,UpperBoundT>::Integrate(
    const Expression& var) const
  -> std::unique_ptr<Expression>
{
  return std::make_unique<DefiniteIntegral>(
    this->GetVariable(),
    this->GetLowerBound(),
    this->GetUpperBound(),
    *this->GetBody().Integrate(var)
  )->Simplify();
}

// explicit instantiation for the generic Expression type
template class DefiniteIntegral<Expression,Expression,Expression,Expression>;

} // namespace Oasis
