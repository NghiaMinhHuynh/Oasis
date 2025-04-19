#include "Oasis/FourierSeries.hpp"

#include "Oasis/Summation.hpp"
#include "Oasis/Impulse.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Subtract.hpp"
#include "Oasis/Variable.hpp"
#include "Oasis/Real.hpp"
#include <cmath>

namespace Oasis {

FourierSeries::FourierSeries(std::unique_ptr<Expression> coefFn,
                             std::unique_ptr<Expression> omega0)
  : _coefFn(std::move(coefFn))
  , _omega0(std::move(omega0))
{}

auto FourierSeries::Copy() const
  -> std::unique_ptr<Expression>
{
  return std::make_unique<FourierSeries>(
    _coefFn->Copy(),
    _omega0->Copy()
  );
}

auto FourierSeries::Simplify() const
  -> std::unique_ptr<Expression>
{
  // Just simplify coefficient function and ω₀
  return std::make_unique<FourierSeries>(
    _coefFn->Simplify(),
    _omega0->Simplify()
  );
}

auto FourierSeries::Differentiate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // For now, we do not differentiate the exponential terms symbolically;
  // leave the series intact.
  return Copy();
}

auto FourierSeries::Integrate(const Expression& var) const
  -> std::unique_ptr<Expression>
{
  // Likewise, integration is left structural
  return Copy();
}

auto FourierSeries::ToTransform() const
  -> std::unique_ptr<Expression>
{
  // Build:   F(ω) = 2π · Σ_{n=-∞}^{∞} c(n) · δ(ω − n·ω₀)
  //
  // 1) index variable “n”
  auto nVar = std::make_unique<Variable>("n");

  // 2) build δ(ω − n·ω₀)
  auto deltaArg = std::make_unique<Subtract>(
    std::make_unique<Variable>("ω"),
    std::make_unique<Multiply>(
      nVar->Copy(),
      _omega0->Copy()
    )
  );
  auto impulse = std::make_unique<Impulse>(std::move(deltaArg));

  // 3) term = c(n) * δ(...)
  auto term = std::make_unique<Multiply>(
    _coefFn->Copy(),
    std::move(impulse)
  );

  // 4) Σ_{n=-∞}^{∞} term
  //    Here we use Expression{} placeholders for “-∞” / “∞”;
  //    you can refine with your own Infinity node later.
  auto series = Summation<
    Expression,  // body
    Variable,    // index
    Expression,  // lower bound
    Expression   // upper bound
  >(
    Variable{"n"},
    Expression{},  // -∞ placeholder
    Expression{},  // +∞ placeholder
    *term
  ).Simplify();

  // 5) multiply by 2π
  return std::make_unique<Multiply>(
    std::make_unique<Real>(2.0 * M_PI),
    *series
  );
}

// Optionally register a visitor in Printer.cpp:
//   void Printer::Visit(const FourierSeries& f) { … }

} // namespace Oasis
