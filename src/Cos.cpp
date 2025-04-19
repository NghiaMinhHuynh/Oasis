#include "Oasis/Cos.hpp"
#include "Oasis/Sin.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Negative.hpp"

namespace Oasis {
  
Cos::Cos(std::unique_ptr<Expression> arg) : _arg(std::move(arg)) {}
auto Cos::Copy() const -> std::unique_ptr<Expression> { return std::make_unique<Cos>(_arg->Copy()); }
auto Cos::Simplify() const -> std::unique_ptr<Expression> {
  return std::make_unique<Cos>(_arg->Simplify());
}
auto Cos::Differentiate(const Expression& var) const -> std::unique_ptr<Expression> {
  // d/dx cos(u) = -sin(u)·u'
  auto du = _arg->Differentiate(var);
  auto s  = std::make_unique<Sin>(_arg->Copy());
  auto neg= std::make_unique<Negative>(std::move(s));
  return std::make_unique<Multiply>(std::move(neg), *du)->Simplify();
}
auto Cos::Integrate(const Expression& var) const -> std::unique_ptr<Expression> {
  // ∫ cos(u) du = sin(u) / u'
  // for now, just wrap sin
  return std::make_unique<Sin>(_arg->Copy());
}
