#include "Oasis/Step.hpp"
#include "Oasis/Piecewise.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Less.hpp"
#include "Oasis/GreaterEqual.hpp"

namespace Oasis {

Step::Step(std::unique_ptr<Expression> arg)
  : _arg(std::move(arg))
{}

auto Step::Copy() const -> std::unique_ptr<Expression> {
  return std::make_unique<Step>(_arg->Copy());
}

auto Step::Simplify() const -> std::unique_ptr<Expression> {
  // piecewise { t<0:0, t>=0:1 }
  using Clause = Piecewise::Clause;
  std::vector<Clause> clauses;
  clauses.emplace_back(
    std::make_unique<Less>(_arg->Copy(), std::make_unique<Real>(0.0)),
    std::make_unique<Real>(0.0)
  );
  clauses.emplace_back(
    std::make_unique<GreaterEqual>(_arg->Copy(), std::make_unique<Real>(0.0)),
    std::make_unique<Real>(1.0)
  );
  return std::make_unique<Piecewise>(std::move(clauses))->Simplify();
}

auto Step::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // derivative of a step is zero everywhere except impulse at 0,
  // but for now just differentiate the piecewise
  return Simplify()->Differentiate(var);
}

auto Step::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // ∫u(t) dt = piecewise { t<0: 0, t>=0: t }
  return Simplify()->Integrate(var);
}

} // namespace Oasis
