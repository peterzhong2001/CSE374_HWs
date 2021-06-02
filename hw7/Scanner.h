/**
 * Interface to Scanner for fractional number calculator
 * CSE 374, 21sp, muh after HP
 */

#ifndef SCAN_H
#define SCAN_H

#include <string>

#include "Token.h"

namespace Fraction374 {

class Scanner {
 public:
  /**
   * Advance to next token on current input line, if any.
   * If we are at the end of the line, do nothing.
   * Precondition: setInput has been called.
   */
  void scan();

  /**
   * Set input line to newLine and advance token to the first token
   * in that new line (which might be end-of-line if the line is empty).
   */
  void setInput(std::string newLine);

  /**
   * Return the current token.
   */
  Token token();

 private:
  // Current token.
  Token nextTok_;

  // Current input line..
  std::string line_ = "";

  // line_[pos_...line_.size()-1] is the unprocessed part of the line.
  std::string::size_type pos_ = 0;
};

}  // namespace Fraction374

#endif
