/*
 * Implementation of parser/calculator for fractional numerbers
 * CSE 374, 21sp, muh after HP
 */

#include "Parser.h"
#include "Fraction.h"
#include "Scanner.h"
#include "Token.h"

namespace Fraction374 {

Parser::Parser(Scanner* scanner) : scanner_(scanner) {}

Fraction Parser::expr() {
  Fraction val = term();
  while (scanner_->token().kind == PLUS || scanner_->token().kind == MINUS) {
    LexClass op = scanner_->token().kind;
    scanner_->scan();  // advance past op
    if (op == PLUS) {
      val = val.plus(term());
    } else {  // op == MINUS
      val = val.minus(term());
    }
  }
  return val;
}

Fraction Parser::term() {
  Fraction val = factor();
  while (scanner_->token().kind == TIMES || scanner_->token().kind == DIV) {
    LexClass op = scanner_->token().kind;
    scanner_->scan();  // advance past op
    if (op == TIMES) {
      val = val.times(factor());
    } else {  // op == DIV
      val = val.div(factor());
    }
  }
  return val;
}

Fraction Parser::factor() {
  int numer;
  int denom;
  Fraction val;
  switch (scanner_->token().kind) {
  case INT:
    // <int> or <int>/<int>
    numer = scanner_->token().ival;
    denom = 1;
    scanner_->scan();  // skip past first <int>
    if (scanner_->token().kind == SLASH) {
      scanner_->scan();
      denom = scanner_->token().ival;
      scanner_->scan();
    }
    return Fraction(numer, denom);

  case LPAREN:
    // parenthesized expression. parse expr but consume parens
    scanner_->scan();
    val = expr();
    scanner_->scan();
    return val;

  default:
    // something that's not a factor - skip past it so we don't get stuck
    scanner_->scan();
    return Fraction(0, 0);
  }
}

}  // namespace Fraction374
