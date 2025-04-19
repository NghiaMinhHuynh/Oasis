// include/Oasis/LaplaceTransform.hpp
#ifndef OASIS_LAPLACETRANSFORM_HPP
#define OASIS_LAPLACETRANSFORM_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * Symbolic Laplace transform:
 *
 *   L{ f(t) }(s) = ∫_{0^-}^{∞} f(t) · e^{-s t} dt
 *
 * Optionally carries a region of convergence (ROC) condition.
 */
class LaplaceTransform : public Expression {
public:
  /**
   * @param func The time-domain function f(t)
   * @param s    The complex frequency variable s
   * @param roc  A condition (Expression) representing the ROC, e.g. Re(s)>a
   */
  LaplaceTransform(std::unique_ptr<Expression> func,
                   std::unique_ptr<Expression> s,
                   std::unique_ptr<Expression> roc);

  [[nodiscard]] auto Copy() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  /// Access the original function f(t)
  [[nodiscard]] auto GetFunction() const -> const Expression*;
  /// Access the frequency variable s
  [[nodiscard]] auto GetS() const -> const Expression*;
  /// Access the region of convergence expression
  [[nodiscard]] auto GetROC() const -> const Expression*;

private:
  std::unique_ptr<Expression> _func;
  std::unique_ptr<Expression> _s;
  std::unique_ptr<Expression> _roc;
};

} // namespace Oasis

#endif // OASIS_LAPLACETRANSFORM_HPP
