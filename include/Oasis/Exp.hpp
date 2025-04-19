#ifndef OASIS_EXP_HPP
#define OASIS_EXP_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 * The exponential function e^{arg}.
 *  - Implements Euler‐identity simplifications.
 */
class Exp : public Expression {
public:
  explicit Exp(std::unique_ptr<Expression> arg);

  [[nodiscard]] auto Copy() const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Differentiate(const Expression& var) const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Integrate(const Expression& var) const -> std::unique_ptr<Expression> override;

private:
  std::unique_ptr<Expression> _arg;
};

} // namespace Oasis

#endif // OASIS_EXP_HPP
