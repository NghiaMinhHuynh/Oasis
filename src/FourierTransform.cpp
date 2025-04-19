// src/FourierTransform.cpp

#include "Oasis/FourierTransform.hpp"

namespace Oasis {

FourierTransform::FourierTransform(std::unique_ptr<Expression> f,
                                   std::unique_ptr<Expression> omega)
  : _func(std::move(f))
  , _omega(std::move(omega))
{}

auto FourierTransform::Copy() const
  -> std::unique_ptr<Expression>
{
  return std::make_unique<FourierTransform>(
    _func->Copy(),
    _omega->Copy()
  );
}

auto FourierTransform::Simplify() const
  -> std::unique_ptr<Expression>
{
  // Just simplify children; transform remains atomic
  return std::make_unique<FourierTransform>(
    _func->Simplify(),
    _omega->Simplify()
  );
}

auto FourierTransform::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // For now we do not apply the “d/dω ℱ{f}(ω) = -i ℱ{t f}(ω)” rule,
  // so leave node intact.
  return Copy();
}

auto FourierTransform::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // Likewise, we do not apply frequency‐integration rules yet.
  return Copy();
}

// *If* you later want to expand this into the defining integral,
// you could add a member like:
//
// auto ToDefinition() const -> std::unique_ptr<Expression> {
//   // build DefiniteIntegral<Multiply< f, Exp{ -i*ω*t } > >
// }

} // namespace Oasis
