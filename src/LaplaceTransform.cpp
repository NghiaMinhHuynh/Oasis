// src/LaplaceTransform.cpp

#include "Oasis/LaplaceTransform.hpp"
#include "Oasis/Real.hpp"

namespace Oasis {

LaplaceTransform::LaplaceTransform(std::unique_ptr<Expression> func,
                                   std::unique_ptr<Expression> s,
                                   std::unique_ptr<Expression> roc)
  : _func(std::move(func))
  , _s(std::move(s))
  , _roc(std::move(roc))
{}

auto LaplaceTransform::Copy() const
  -> std::unique_ptr<Expression>
{
  // Copy the ROC only if present
  return std::make_unique<LaplaceTransform>(
    _func->Copy(),
    _s->Copy(),
    _roc ? _roc->Copy() : nullptr
  );
}

auto LaplaceTransform::Simplify() const
  -> std::unique_ptr<Expression>
{
  // Simplify children; leave ROC intact if present
  return std::make_unique<LaplaceTransform>(
    _func->Simplify(),
    _s->Simplify(),
    _roc ? _roc->Simplify() : nullptr
  );
}

auto LaplaceTransform::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // Could apply d/ds L{f}(s) = -L{t f(t)} rule; for now, keep atomic:
  return Copy();
}

auto LaplaceTransform::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // Similarly, leave as-is
  return Copy();
}

auto LaplaceTransform::GetFunction() const -> const Expression* {
  return _func.get();
}

auto LaplaceTransform::GetS() const -> const Expression* {
  return _s.get();
}

auto LaplaceTransform::GetROC() const -> const Expression* {
  return _roc.get();
}

} // namespace Oasis
