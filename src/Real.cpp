//
// Created by Matthew McCall on 7/2/23.
//

#include <string>

#include "Oasis/Add.hpp"
#include "Oasis/Integral.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/RecursiveCast.hpp"
#include "Oasis/Variable.hpp"

namespace Oasis {

template <typename T, typename>
auto Real<T>::Differentiate(const Expression&) const -> std::unique_ptr<Expression>
{
    return std::make_unique<Real<T>>(0);
}

template <typename T, typename>
auto Real<T>::Equals(const Expression& other) const -> bool
{
    return other.Is<Real<T>>() && value == dynamic_cast<const Real<T>&>(other).value;
}

template <typename T, typename>
auto Real<T>::Integrate(const Expression& integrationVariable) const -> std::unique_ptr<Expression>
{
    if (auto variable = RecursiveCast<Variable>(integrationVariable); variable != nullptr) {
        // Constant rule
        if (value != 0) {
            Add adder {
                Multiply<Real<T>, Variable> { Real<T> { value }, Variable { (*variable).GetName() } },
                Variable { "C" }
            };
            return adder.Simplify();
        }

        // Zero rule
        return std::make_unique<Variable>(Variable { "C" })->Simplify();
    }

    Integral<Expression, Expression> integral { *(this->Copy()), *(integrationVariable.Copy()) };

    return integral.Copy();
}

// Explicit template instantiations
template class Real<float>;
template class Real<double>;
template class Real<int>;

} // namespace Oasis
