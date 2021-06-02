// Peter Zhong
// CSE 374 HW7
// 06/06/2021

// this cpp file implements the functions of the Fraction class,
// as speficied by the provided "Fraction.h" file.

#include "Fraction.h"

int findGCD(int a, int b);

namespace Fraction374 {

  // constructors
  Fraction::Fraction() { // default to 0/1
    numer_ = 0;
    denom_ = 1;
  }
  Fraction::Fraction(int n) { // create n/1
    numer_ = n;
    denom_ = 1;
  }
  Fraction::Fraction(int n, int d) { // create n/d
    // denominator should always be positive
    if (d < 0) {
      n = 0 - n;
      d = 0 - d;
    }
    int gcd = findGCD(n, d);
    numer_ = n / gcd;
    denom_ = d / gcd;
  }

  // accessors
  int Fraction::n() const { // return numerator
    return numer_;
  }
  int Fraction::d() const { // return denominator
    return denom_;
  }

  // arithmetic
  // adding other to this and returning the result as a new fraction
  Fraction Fraction::plus(Fraction other) const {
    int newNumer = numer_ * other.d() + other.n() * denom_;
    int newDenom = denom_ * other.d();
    Fraction result(newNumer, newDenom);
    return result;
  }

  // subtracting other from this and returning the result as a new fraction
  Fraction Fraction::minus(Fraction other) const {
    Fraction neg((0 - other.n()), other.d());
    return Fraction::plus(neg);
  }

  // multiplying other to this and returning the result as a new fraction
  Fraction Fraction::times(Fraction other) const {
    int newNumer = numer_ * other.n();
    int newDenom = denom_ * other.d();
    Fraction result(newNumer, newDenom);
    return result;
  }
  
  // dividing this with other and returning the result as a new fraction
  Fraction Fraction::div(Fraction other) const {
    Fraction inv(other.d(), other.n());
    return Fraction::times(inv);
  }

}

// helper function to find and return the greatest common divisor
// of two integers
int findGCD(int a, int b) {
  // check if any of the numbers are zero
  if (a == 0 && b == 0) {
    return 1;
  } else if (a == 0) {
    return b;
  } else if (b == 0) {
    return a;
  }
  // convert numbers to positive
  if (a < 0) {
    a = 0 - a;
  }
  if (b < 0) {
    b = 0 - b;
  }
  // perform the GCD search on two non-zero integers  
  int result;
  for (int i = 1; i <= a && i <= b; i++) {
    if (a % i == 0 && b % i == 0) {
      result = i;
    }
  }
  return result;
}
