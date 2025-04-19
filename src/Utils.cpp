#include "Oasis/Utils.hpp"
#include "Oasis/Parser.hpp"
#include "Oasis/Printer.hpp"
#include <stdexcept>

namespace Oasis {

std::string SimplifyString(const std::string& expr) {
  // 1) parse
  auto ast = Parser::Parse(expr);
  if (!ast) throw std::runtime_error("Parse error in \"" + expr + "\"");

  // 2) simplify
  auto simp = ast->Simplify();

  // 3) pretty‑print
  Printer printer;
  printer.Visit(*simp);
  return printer.GetString();
}

} // namespace Oasis
