

#ifndef OASIS_FOURIERSERIES_HPP
#define OASIS_FOURIERSERIES_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * Represents the complex‐exponential Fourier series of a periodic
 * function f(t):
 *
 *     f(t) = Σ_{n=-∞}^{∞} c(n) · e^{i·n·ω₀·t}
 *
 * Internally we store:
 *   – _coefFn : an expression c(n) giving the nth coefficient
 *   – _omega0 : the fundamental frequency ω₀
 */
class FourierSeries : public Expression {
public:
  FourierSeries(std::unique_ptr<Expression> coefFn,
                std::unique_ptr<Expression> omega0);

  [[nodiscard]] auto Copy() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /**
   * Convert this Fourier‐series node into the frequency‐domain
   * transform
   *
   *     F(ω) = 2π · Σ_{n=-∞}^{∞} c(n) · δ(ω − n·ω₀)
   */
  [[nodiscard]] auto ToTransform() const
    -> std::unique_ptr<Expression>;

private:
  std::unique_ptr<Expression> _coefFn;
  std::unique_ptr<Expression> _omega0;
};

} // namespace Oasis

#endif // OASIS_FOURIERSERIES_HPP
