#ifndef OASIS_FOURIERTRANSFORM_HPP
#define OASIS_FOURIERTRANSFORM_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * Symbolic Fourier transform:
 *
 *   ℱ{ f(t) }(ω) = ∫_{-∞}^{∞} f(t) · e^{ -i · ω · t } dt
 *
 * For now this node is kept atomic; you can call
 * Simplify() to simplify its children, or expand it
 * yourself into a DefiniteIntegral if you add an Exp().
 */
class FourierTransform : public Expression {
public:
  /// f: time‐domain function; omega: frequency variable
  FourierTransform(std::unique_ptr<Expression> f,
                   std::unique_ptr<Expression> omega);

  [[nodiscard]] auto Copy() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// Access the time‐domain function f(t)
  [[nodiscard]] auto GetFunction()   const -> const Expression* { return _func.get(); }
  /// Access the frequency‐domain var ω
  [[nodiscard]] auto GetFreqVar()    const -> const Expression* { return _omega.get(); }

private:
  std::unique_ptr<Expression> _func;
  std::unique_ptr<Expression> _omega;
};

} // namespace Oasis

#endif // OASIS_FOURIERTRANSFORM_HPP
