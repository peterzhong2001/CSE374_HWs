/**
 * Interface to Fraction number type.
 * CSE 374, 21sp (muh after HP/MW)
 */

#ifndef FRACTION_H
#define FRACTION_H

namespace Fraction374 {

class Fraction {
 public:
  // ----------- CONSTRUCTORS -----------
  // Construct Fraction 0/1
  Fraction();

  // Construct Fraction n/1
  explicit Fraction(int n);

  // Construct Fraction n/d
  Fraction(int n, int d);

  // ----------- ACCESSORS -----------
  // Return the numerator and denominator of this Fraction.
  // Results are in lowest terms (i.e., for rational r, r.n() and r.d()
  // have no common integer divisors greater than 1).
  // 'const' specifies that attributes are not changed by the function.
  int n() const;
  int d() const;


  // ----------- ARITHMETIC -----------
  // Return a new Fraction that results from combining this Fraction
  // with another.  Neither operand is changed.

  // = this + other
  Fraction plus(Fraction other) const;

  // = this - other
  Fraction minus(Fraction other) const;

  // = this * other
  Fraction times(Fraction other) const;

  // = this / other
  Fraction div(Fraction other) const;

 private:
  // Representation of a Fraction: numer/denom
  // No attempt is made to detect a denominator of 0 as an error
  int numer_;
  int denom_;
};

}  // namespace Fraction374

#endif
