#include "Oasis/Summation.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Variable.hpp"
#include <cmath>

namespace Oasis {

template <IExpression OpT, IExpression VarT, IExpression LoT, IExpression HiT>
auto Summation<OpT,VarT,LoT,HiT>::Simplify() const
  -> std::unique_ptr<Expression>
{
  // first simplify bounds and body
  auto lo = this->GetLowerBound().Simplify();
  auto hi = this->GetUpperBound().Simplify();
  auto body = this->GetBody().Simplify();

  // if bounds are integer literals and small range, unroll
  if (auto loR = dynamic_cast<Real*>(lo.get());
      loR && loR->IsInteger() &&
      dynamic_cast<Real*>(hi.get()) &&
      (hiR = static_cast<Real*>(hi.get())) &&
      hiR->IsInteger())
  {
    long L = static_cast<long>(std::round(loR->GetValue()));
    long H = static_cast<long>(std::round(hiR->GetValue()));
    if (H - L <= 100) {
      auto sum = std::make_unique<Real>(0.0);
      for (long i = L; i <= H; ++i) {
        // substitute idx→i
        auto term = body->Substitute(
          this->GetIndex(), Real{double(i)});
        sum = std::make_unique<Add<Expression,Expression>>(
          *sum, *term)->Simplify();
      }
      return sum;
    }
  }

  // otherwise, return a (possibly simplified) Σ(...) node
  return std::make_unique<Summation>(
    this->GetIndex(), *lo, *hi, *body);
}

template <IExpression OpT, IExpression VarT, IExpression LoT, IExpression HiT>
auto Summation<OpT,VarT,LoT,HiT>::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // if differentiating w.r.t. the index, it's zero
  if (auto v = dynamic_cast<const Variable*>(&var);
      v && v->GetName() == this->GetIndex().GetName())
  {
    return std::make_unique<Real>(0.0);
  }

  // else push derivative into the body
  return std::make_unique<Summation>(
    this->GetIndex(),
    this->GetLowerBound(),
    this->GetUpperBound(),
    *this->GetBody().Differentiate(var)
  )->Simplify();
}

template <IExpression OpT, IExpression VarT, IExpression LoT, IExpression HiT>
auto Summation<OpT,VarT,LoT,HiT>::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // integrate inside the body
  return std::make_unique<Summation>(
    this->GetIndex(),
    this->GetLowerBound(),
    this->GetUpperBound(),
    *this->GetBody().Integrate(var)
  )->Simplify();
}

// Explicit instantiation for the common case:
template class Summation<Expression,Expression,Expression,Expression>;

} // namespace Oasis
