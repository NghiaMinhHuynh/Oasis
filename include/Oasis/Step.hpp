#ifndef OASIS_STEP_HPP
#define OASIS_STEP_HPP

#include "Oasis/Expression.hpp"
#include <memory>

namespace Oasis {

/**
 *  u(t) = 1  if t >= 0
 *       = 0  otherwise
 */
class Step : public Expression {
public:
  explicit Step(std::unique_ptr<Expression> arg);

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

#endif // OASIS_STEP_HPP
