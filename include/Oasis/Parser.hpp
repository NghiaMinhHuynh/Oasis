// include/Oasis/Parser.hpp
#ifndef OASIS_PARSER_HPP
#define OASIS_PARSER_HPP

#include <string>
#include <memory>
#include "Oasis/Expression.hpp"

namespace Oasis {

/**
 * Parser for textual Oasis expressions.
 * Usage: auto ast = Parser::Parse(text);
 */
class Parser {
public:
  /**
   * Parse the input string into an Expression AST.
   * Throws on parse error.
   */
  static std::unique_ptr<Expression> Parse(const std::string& input);

private:
  explicit Parser(const std::string& input);

  // Entry point for recursive descent
  std::unique_ptr<Expression> ParseExpression();

  // Helper to parse primary, binary, function-call constructs...
  std::unique_ptr<Expression> ParsePrimary();
  std::unique_ptr<Expression> ParseBinaryOpRHS(int exprPrec,
                                               std::unique_ptr<Expression> lhs);

  // Token utilities
  void SkipWhitespace();
  std::string PeekToken() const;
  std::string GetToken();
  void Expect(const std::string& tok);
  bool TryConsume(const std::string& tok);

  // Input tracking
  const std::string _input;
  size_t _pos = 0;
};

} // namespace Oasis

#endif // OASIS_PARSER_HPP