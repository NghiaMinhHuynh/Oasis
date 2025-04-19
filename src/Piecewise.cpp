// src/Piecewise.cpp
#include "Oasis/Piecewise.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/True.hpp"
#include "Oasis/False.hpp"
#include <stdexcept>

namespace Oasis {

Piecewise::Piecewise(std::vector<Clause> clauses)
  : _clauses(std::move(clauses))
{}

auto Piecewise::Copy() const -> std::unique_ptr<Expression> {
  std::vector<Clause> copied;
  copied.reserve(_clauses.size());
  for (auto const& [cond, expr] : _clauses) {
    copied.emplace_back(cond->Copy(), expr->Copy());
  }
  return std::make_unique<Piecewise>(std::move(copied));
}

auto Piecewise::Simplify() const -> std::unique_ptr<Expression> {
  std::vector<Clause> kept;
  kept.reserve(_clauses.size());

  for (auto const& [cond, expr] : _clauses) {
    auto c_s = cond->Simplify();
    // skip any branch whose condition is definitely false
    if (dynamic_cast<False*>(c_s.get())) 
      continue;

    auto e_s = expr->Simplify();
    // if condition is definitely true, we can short‑circuit
    if (dynamic_cast<True*>(c_s.get())) 
      return e_s;

    kept.emplace_back(std::move(c_s), std::move(e_s));
  }

  if (kept.empty()) {
    // no clause matched → default to zero
    return std::make_unique<Real>(0.0);
  }
  return std::make_unique<Piecewise>(std::move(kept));
}

auto Piecewise::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  std::vector<Clause> dclauses;
  dclauses.reserve(_clauses.size());
  for (auto const& [cond, expr] : _clauses) {
    dclauses.emplace_back(cond->Copy(),
                          expr->Differentiate(var));
  }
  return std::make_unique<Piecewise>(std::move(dclauses))
            ->Simplify();
}

auto Piecewise::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  std::vector<Clause> iclauses;
  iclauses.reserve(_clauses.size());
  for (auto const& [cond, expr] : _clauses) {
    iclauses.emplace_back(cond->Copy(),
                          expr->Integrate(var));
  }
  return std::make_unique<Piecewise>(std::move(iclauses))
            ->Simplify();
}

} // namespace Oasis
