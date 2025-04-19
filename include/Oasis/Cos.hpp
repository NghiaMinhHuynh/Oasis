// Cos.hpp
#ifndef OASIS_COS_HPP
#define OASIS_COS_HPP
#include "Oasis/Expression.hpp"
#include <memory>
namespace Oasis {
class Cos : public Expression {
public:
  explicit Cos(std::unique_ptr<Expression> arg);
  [[nodiscard]] auto Copy()      const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Simplify()  const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Differentiate(const Expression& var) const -> std::unique_ptr<Expression> override;
  [[nodiscard]] auto Integrate(const Expression& var) const -> std::unique_ptr<Expression> override;
private:
  std::unique_ptr<Expression> _arg;
};
} // Oasis
#endif // OASIS_COS_HPP

// Sin.hpp (analogous)
