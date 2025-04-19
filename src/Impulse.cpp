#include "Oasis/Impulse.hpp"
#include "Oasis/Piecewise.hpp"
#include "Oasis/Equal.hpp"
#include "Oasis/True.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Step.hpp"    // for Integrate()
#include <vector>
#include <memory>

namespace Oasis {

Impulse::Impulse(std::unique_ptr<Expression> arg)
  : _arg(std::move(arg))
{}

auto Impulse::Copy() const -> std::unique_ptr<Expression> {
  return std::make_unique<Impulse>(_arg->Copy());
}

auto Impulse::Simplify() const -> std::unique_ptr<Expression> {
  // δ(x) → piecewise { x==0:1, true:0 }
  using Clause = Piecewise::Clause;
  std::vector<Clause> clauses;
  clauses.emplace_back(
    std::make_unique<Equal>(_arg->Copy(), std::make_unique<Real>(0.0)),
    std::make_unique<Real>(1.0)
  );
  clauses.emplace_back(
    std::make_unique<True>(),
    std::make_unique<Real>(0.0)
  );
  return std::make_unique<Piecewise>(std::move(clauses))->Simplify();
}

auto Impulse::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // d/dx δ(x) is the distributional derivative;
  // for now just differentiate the piecewise form
  return Simplify()->Differentiate(var);
}

auto Impulse::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // ∫ δ(x) dx = Step(x)
  return std::make_unique<Step>(_arg->Copy());
}

} // namespace Oasis
