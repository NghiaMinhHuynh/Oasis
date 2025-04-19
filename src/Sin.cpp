#include "Oasis/Sin.hpp"
#include "Oasis/Cos.hpp"
#include "Oasis/Negative.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Real.hpp"

namespace Oasis {

Sin::Sin(std::unique_ptr<Expression> arg)
  : _arg(std::move(arg))
{}

auto Sin::Copy() const
  -> std::unique_ptr<Expression>
{
  return std::make_unique<Sin>(_arg->Copy());
}

auto Sin::Simplify() const
  -> std::unique_ptr<Expression>
{
  // Just simplify the inner argument
  return std::make_unique<Sin>(_arg->Simplify());
}

auto Sin::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // d/dx sin(u) = cos(u) * u'
  auto du = _arg->Differentiate(var);
  auto cos_u = std::make_unique<Cos>(_arg->Copy());
  return std::make_unique<Multiply>(std::move(cos_u), *du)
             ->Simplify();
}

auto Sin::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // ∫ sin(u) du = -cos(u)
  auto cos_u = std::make_unique<Cos>(_arg->Copy());
  auto neg_cos_u = std::make_unique<Negative>(std::move(cos_u));
  return neg_cos_u->Simplify();
}

} // namespace Oasis
