#include "Oasis/Exp.hpp"
#include "Oasis/Imaginary.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Subtract.hpp"
#include "Oasis/Add.hpp"
#include "Oasis/Cos.hpp"
#include "Oasis/Sin.hpp"
#include <cmath>

namespace Oasis {

Exp::Exp(std::unique_ptr<Expression> arg)
  : _arg(std::move(arg)) {}

auto Exp::Copy() const -> std::unique_ptr<Expression> {
  return std::make_unique<Exp>(_arg->Copy());
}

auto Exp::Simplify() const -> std::unique_ptr<Expression> {
  auto a = _arg->Simplify();

  // 1) e^(i·π) → -1
  if (auto m = dynamic_cast<Multiply*>(a.get())) {
    // check factors i and Real(pi)
    Expression *c0 = m->GetLeastSigOp().get(), *c1 = m->GetMostSigOp().get();
    if ((dynamic_cast<ImaginaryUnit*>(c0) && 
         dynamic_cast<Real*>(c1) && std::abs(static_cast<Real*>(c1)->GetValue() - M_PI) < 1e-12)
     ||(dynamic_cast<ImaginaryUnit*>(c1) && 
         dynamic_cast<Real*>(c0) && std::abs(static_cast<Real*>(c0)->GetValue() - M_PI) < 1e-12))
    {
      return std::make_unique<Real>(-1.0);
    }
  }

  // 2) e^(i·θ) → cos(θ) + i·sin(θ)
  if (auto m = dynamic_cast<Multiply*>(a.get())) {
    // find ImaginaryUnit factor and angle
    ImaginaryUnit *iPart = nullptr;
    Expression* theta = nullptr;
    for (auto* child : {m->GetLeastSigOp().get(), m->GetMostSigOp().get()}) {
      if (auto ii = dynamic_cast<ImaginaryUnit*>(child)) iPart = ii;
      else theta = child;
    }
    if (iPart && theta) {
      auto cosT = std::make_unique<Cos>(theta->Copy());
      auto sinT = std::make_unique<Sin>(theta->Copy());
      auto imagSin = std::make_unique<Multiply>(
                       std::make_unique<ImaginaryUnit>(),
                       std::move(sinT));
      return std::make_unique<Add>(std::move(cosT), std::move(imagSin))
                 ->Simplify();
    }
  }

  return std::make_unique<Exp>(std::move(a));
}

auto Exp::Differentiate(const Expression& var) const -> std::unique_ptr<Expression> {
  // d/dx e^u = e^u * u'
  auto du = _arg->Differentiate(var);
  return std::make_unique<Multiply>(Copy(), *du)->Simplify();
}

auto Exp::Integrate(const Expression& var) const -> std::unique_ptr<Expression> {
  // ∫ e^u du = e^u / u'
  // for now: return e^u
  return Copy();
}

} // namespace Oasis
