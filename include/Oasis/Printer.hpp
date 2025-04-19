// include/Oasis/Printer.hpp
#ifndef OASIS_PRINTER_HPP
#define OASIS_PRINTER_HPP

#include <string>
#include <sstream>
#include "Oasis/Expression.hpp"

namespace Oasis {

/**
 * Pretty-printer for Oasis expressions.
 * Usage:
 *   Printer p;
 *   p.Visit(*expr);
 *   auto s = p.GetString();
 */
class Printer {
public:
  Printer() = default;

  /// Visit any Expression node
  void Visit(const Expression& expr);

  /// Retrieve the built string
  std::string GetString() const { return _out.str(); }

  // Add overloads for specific node types as needed:
  // void Visit(const Add<...>& node);
  // void Visit(const Multiply<...>& node);
  // ...

private:
  std::ostringstream _out;
};

} // namespace Oasis

#endif // OASIS_PRINTER_HPP
