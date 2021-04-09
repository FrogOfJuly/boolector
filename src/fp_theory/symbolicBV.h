//
// Created by Kirill Golubev on 09.04.2021.
//
#include "common.h"
#include "fp_info.h"
#include "symbolicProp.h"

#ifndef BOOLECTOR_SYMBOLICBV_H
#define BOOLECTOR_SYMBOLICBV_H
namespace fp {

class uSymbolicBV;
class sSymbolicBV;

class symbolicBV
{
 protected:
  BoolectorNode* btor_node;

  bitWidthType get_weidth () const;

  explicit symbolicBV (BoolectorNode* node);
  static symbolicBV fromBtorNode (BoolectorNode* node);
  static symbolicBV zero (bitWidthType bw);
  static symbolicBV one (bitWidthType bw);
  static symbolicBV allOnes (bitWidthType bw);

  symbolicBV (const symbolicBV& old);

 public:
  BoolectorNode* get_node() const;

  symbolicBV (symbolicBV&& rhs) noexcept;

  symbolicBV operator& (const symbolicBV& right) const;
  symbolicBV operator| (const symbolicBV& right) const;
  symbolicBV operator~ () const;

  symbolicBV operator+ (const symbolicBV& right) const;
  symbolicBV operator- (const symbolicBV& right) const;
  symbolicBV operator- () const;
  //  symbolicBV operator/ (const symbolicBV& right) const = 0;
  symbolicBV operator* (const symbolicBV& right) const;
  //  symbolicBV operator% (const symbolicBV& right) const = 0;

  //  symbolicProp operator<= (const symbolicBV& right) const = 0;
  //  symbolicProp operator>= (const symbolicBV& right) const = 0;
  symbolicProp operator== (const symbolicBV& right) const;
  //  symbolicProp operator< (const symbolicBV& right) const = 0;
  //  symbolicProp operator> (const symbolicBV& right) const = 0;

  symbolicBV increment () const;
  symbolicBV decrement () const;

  symbolicBV operator<< (const symbolicBV& right) const;
  //  symbolicBV operator>> (const symbolicBV& right) const = 0;

  uSymbolicBV toUnsigned () const;
  sSymbolicBV toSigned () const;

  operator uSymbolicBV () const;
  operator sSymbolicBV () const;

  //  symbolicBV maxValue () const = 0;
  //  symbolicBV minValue () const = 0;

  symbolicProp isAllOnes () const;
  symbolicProp isAllZeros () const;

  symbolicBV append (const symbolicBV& rigth) const;

  //  symbolicBV extend (const symbolicBV& right) const = 0;

  symbolicBV modularLeftShift (const symbolicBV& op) const;

  symbolicBV modularIncrement () const;
  symbolicBV modularDecrement () const;

  symbolicBV modularNegate () const;

  symbolicBV extract (bitWidthType upper, bitWidthType lower) const;
};

class uSymbolicBV : public symbolicBV
{
  explicit uSymbolicBV (BoolectorNode* node);

 public:
  using symbolicBV::zero, symbolicBV::allOnes, symbolicBV::one;
  uSymbolicBV (uSymbolicBV&& rhs) noexcept;

  uSymbolicBV (const uSymbolicBV& right);

  static uSymbolicBV fromBtorNode (BoolectorNode* node);

  symbolicProp operator<= (const uSymbolicBV& right) const;
  symbolicProp operator>= (const uSymbolicBV& right) const;

  symbolicProp operator< (const uSymbolicBV& right) const;
  symbolicProp operator> (const uSymbolicBV& right) const;

  uSymbolicBV operator>> (const uSymbolicBV& right) const;

  uSymbolicBV operator/ (const uSymbolicBV& right) const;
  uSymbolicBV operator% (const uSymbolicBV& right) const;

  uSymbolicBV maxValue () const;
  uSymbolicBV minValue () const;

  uSymbolicBV extend (bitWidthType w) const;

  uSymbolicBV resize (bitWidthType newSize) const;

  uSymbolicBV contract (bitWidthType newSize) const;

  uSymbolicBV modularRightShift (const uSymbolicBV& op) const;

  uSymbolicBV modularAdd (const uSymbolicBV& op) const;

  uSymbolicBV matchWidth (const uSymbolicBV& op) const;

  friend sSymbolicBV;
  friend symbolicBV;
};

class sSymbolicBV : public symbolicBV
{
  explicit sSymbolicBV (BoolectorNode* node);

 public:
  using symbolicBV::zero, symbolicBV::allOnes, symbolicBV::one;
  sSymbolicBV (sSymbolicBV&& rhs) noexcept;

  sSymbolicBV (const sSymbolicBV& right);
  static sSymbolicBV fromBtorNode (BoolectorNode* node);

  symbolicProp operator<= (const sSymbolicBV& right) const;
  symbolicProp operator>= (const sSymbolicBV& right) const;

  symbolicProp operator< (const sSymbolicBV& right) const;
  symbolicProp operator> (const sSymbolicBV& right) const;

  sSymbolicBV operator>> (const sSymbolicBV& right) const;

  sSymbolicBV operator/ (const sSymbolicBV& right) const;
  sSymbolicBV operator% (const sSymbolicBV& right) const;

  sSymbolicBV maxValue () const;
  sSymbolicBV minValue () const;

  sSymbolicBV extend (bitWidthType w) const;

  sSymbolicBV resize (bitWidthType newSize) const;

  sSymbolicBV contract (bitWidthType newSize) const;

  sSymbolicBV modularRightShift (const sSymbolicBV& op) const;
  sSymbolicBV modularAdd (const sSymbolicBV& op) const;

  sSymbolicBV matchWidth (const sSymbolicBV& op) const;

  friend uSymbolicBV;
  friend symbolicBV;
};
}  // namespace fp
#endif  // BOOLECTOR_SYMBOLICBV_H
