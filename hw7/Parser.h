/**
 * Interface to Parser for fractional numbers.
 * CSE 374, 21sp, muh after HP
 */

#ifndef PARSE_H
#define PARSE_H

#include "Fraction.h"
#include "Scanner.h"

namespace Fraction374 {

/**
 * This parser/evaluator is a recursive-descent parser for expressions
 * defined by the following traditional expression grammar:
 *
 * <expr> ::= <term> | <expr> + term | <expr> - <term>
 * <term> ::= <factor> | <term> * <factor> | <term> % <factor>
 * <factor> ::= <int> | <int> / <int> | ( <expr> )
 *
 * <int> represents integer constants. A rational is either a single <int>
 * or two <int>s separated by a /. The symbol % is used in expressions
 * for division. There is no unary minus for entering negative numerbers
 * directly, although that wouldn't be too hard to add.  Subexpressions
 * may be parenthesized.
 *
 * Each function in the parser returns the value of the expression it
 * parses. If an error is encountered, 0/0 is returned when the error
 * is first encountered, which may lead to further errors (i.e., there
 * is no attempt to do graceful error handling).
 *
 * Precondition for all parser functions: scanner_->token() contains the next
 * unprocessed token in the input stream. (Which implies that each
 * function consumes all of the input corresponding to the construct
 * it parses.)
 */
class Parser {
 public:
  explicit Parser(Scanner* scanner);

  /**
   * Returns value of next expression on current input line.
   * If errors are detected, a bogus numerber like 0/0 is returned.
   * <expr> ::= <term> | <expr> + term | <expr> - <term>
   */
  Fraction expr();

 private:
  /* <term> ::= <factor> | <term> * <factor> | <term> % <factor> */
  Fraction term();

  /* <factor> ::= <int> | <int> / <int> | ( <expr> ) */
  Fraction factor();

  Scanner* scanner_;
};

}  // namespace Fraction374

#endif
