#ifndef OASIS_SIN_HPP
#define OASIS_SIN_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * Symbolic sine function: sin(arg)
 */
class Sin : public Expression {
public:
  /** 
   * @param arg The argument to sine (e.g. θ, t, etc.)
   */
  explicit Sin(std::unique_ptr<Expression> arg);

  [[nodiscard]] auto Copy() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

private:
  std::unique_ptr<Expression> _arg;
};

} // namespace Oasis

#endif // OASIS_SIN_HPP
