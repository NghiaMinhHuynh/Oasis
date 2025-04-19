#ifndef OASIS_PIECEWISE_HPP
#define OASIS_PIECEWISE_HPP

#include "Oasis/Expression.hpp"
#include <vector>
#include <memory>
#include <utility>

namespace Oasis {

/**
 * A piecewise‐defined expression of the form:
 *   piecewise {
 *     condition₁ : expr₁,
 *     condition₂ : expr₂,
 *     …,
 *     conditionₙ : exprₙ
 *   }
 *
 * The first condition that evaluates to true determines the branch.
 */
class Piecewise : public Expression {
public:
  /// A single (condition → expression) clause
  using Clause =
    std::pair<std::unique_ptr<Expression>,   // condition
              std::unique_ptr<Expression>>;  // branch

  /// Construct from a vector of (cond,expr) clauses
  explicit Piecewise(std::vector<Clause> clauses);

  [[nodiscard]] auto Copy() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Simplify() const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Differentiate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

  [[nodiscard]] auto Integrate(const Expression& var) const
    -> std::unique_ptr<Expression> override;

private:
  std::vector<Clause> _clauses;
};

} // namespace Oasis

#endif // OASIS_PIECEWISE_HPP
