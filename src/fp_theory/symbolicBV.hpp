//
// Created by Kirill Golubev on 09.04.2021.
//
#include <boolector.h>

#include "common.h"
#include "fp_info.h"
#include "symbolicProp.h"

#ifndef BOOLECTOR_SYMBOLICBV_H
#define BOOLECTOR_SYMBOLICBV_H

#define constexpr
namespace fp {

template <bool isSigned>
class symbolicBV
{
  BoolectorNode* btor_node;

 public:
  static symbolicBV<isSigned> zero (bitWidthType bw)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, bw);
    auto zero = boolector_zero (btor, srt);
    return symbolicBV<isSigned> (zero);
  }
  static symbolicBV<isSigned> one (bitWidthType bw)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt = boolector_bitvec_sort (btor, bw);
    auto one = boolector_zero (btor, srt);
    return symbolicBV<isSigned> (one);
  }

  explicit symbolicBV (BoolectorNode* node)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    BoolectorSort srt = boolector_get_sort (btor, node);
    assert (boolector_is_bitvec_sort (btor, srt));
    btor_node = node;
  }
  symbolicBV (const symbolicBV<isSigned>& old)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    btor_node = boolector_copy (btor, old.btor_node);
  }
  explicit symbolicBV (const symbolicProp& prop) : symbolicBV (prop.get_node ())
  {
  }
  /*symbolicBV (bitWidthType w, unsigned int v)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, w);
    btor_node = boolector_unsigned_int (btor, v, srt);
  }*/
  symbolicBV (bitWidthType w, int v)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, w);
    btor_node = boolector_int (btor, v, srt);
  }

  symbolicBV<isSigned> operator& (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_and (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator| (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_or (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator~ () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_not (btor, btor_node));
  }
  symbolicBV<isSigned> operator+ (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_add (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator- (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sub (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator* (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_mul (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator/ (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (
          boolector_sdiv (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicBV<isSigned> (
          boolector_udiv (btor, btor_node, right.btor_node));
    }
  }
  symbolicBV<isSigned> operator- () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_neg (btor, btor_node));
  }

  symbolicBV<isSigned> increment () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_inc (btor, btor_node));
  }
  symbolicBV<isSigned> decrement () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_dec (btor, btor_node));
  }

  symbolicBV<isSigned> operator<< (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sll (btor, btor_node, right.btor_node));
  }

  symbolicBV<isSigned> operator>> (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (
          boolector_sra (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicBV<isSigned> (
          boolector_srl (btor, btor_node, right.btor_node));
    }
  }

  symbolicProp operator<= (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_slte (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicProp::fromBtorNode (
          boolector_ulte (btor, btor_node, right.btor_node));
    }
  }
  symbolicProp operator>= (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_sgte (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicProp::fromBtorNode (
          boolector_ugte (btor, btor_node, right.btor_node));
    }
  }
  symbolicProp operator% (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_smod (btor, btor_node, right.btor_node));
    }
    else
    {
      //todo: boolector unsigned mod???
      return symbolicProp::fromBtorNode (
          boolector_urem (btor, btor_node, right.btor_node));
    }
  }
  symbolicProp operator< (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_slt (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicProp::fromBtorNode (
          boolector_ult (btor, btor_node, right.btor_node));
    }
  }
  symbolicProp operator== (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicProp::fromBtorNode (
        boolector_eq (btor, btor_node, right.btor_node));
  }
  symbolicProp operator> (const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_sgt (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicProp::fromBtorNode (
          boolector_ugt (btor, btor_node, right.btor_node));
    }
  }

  symbolicBV<true> toSigned () const { return symbolicBV<true> (btor_node); }
  symbolicBV<false> toUnsigned () const
  {
    return symbolicBV<false> (btor_node);
  }

  static symbolicBV<isSigned> allOnes (bitWidthType bw)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, bw);
    auto zero = boolector_ones (btor, srt);
    return symbolicBV<isSigned> (zero);
  }
  symbolicProp isAllOnes () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return *this == symbolicBV::allOnes (boolector_get_width (btor, btor_node));
  }
  symbolicProp isAllZeros () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return *this == symbolicBV::zero (boolector_get_width (btor, btor_node));
  }

  symbolicBV<isSigned> maxValue () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto w = boolector_get_width (btor, btor_node);
    return maxValue (w);
  }
  symbolicBV<isSigned> minValue () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return minValue (boolector_get_width (btor, btor_node));
  }

  static symbolicBV<isSigned> maxValue (bitWidthType w)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt = boolector_bitvec_sort (btor, w);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (boolector_max_signed (btor, srt));
    }
    else
    {
      return allOnes (w);
    }
  }

  static symbolicBV<isSigned> minValue (bitWidthType w)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt = boolector_bitvec_sort (btor, w);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (boolector_min_signed (btor, srt));
    }
    else
    {
      return symbolicBV<isSigned>::zero (w);
    }
  }

  bitWidthType getWidth () const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return boolector_get_width (btor, btor_node);
  }
  symbolicBV<isSigned> append (const symbolicBV<isSigned> right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_concat (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> extend (bitWidthType newSize) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (boolector_sext (btor, btor_node, newSize));
    }
    else
    {
      return symbolicBV<isSigned> (boolector_uext (btor, btor_node, newSize));
    }
  }
  symbolicBV<isSigned> resize (fp::bitWidthType newSize) const
  {
    auto width = this->getWidth ();

    if (newSize > width)
    {
      return this->extend (newSize - width);
    }
    else if (newSize < width)
    {
      return this->contract (width - newSize);
    }
    else
    {
      return *this;
    }
  }
  symbolicBV<isSigned> contract (fp::bitWidthType newSize) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_slice (btor, btor_node, 0, newSize));
  }

  symbolicBV<isSigned> modularLeftShift (const symbolicBV<isSigned>& op) const
  {
    return (*this) << op;
  }
  symbolicBV<isSigned> modularRightShift (const symbolicBV<isSigned>& op) const
  {
    return (*this) >> op;
  }
  symbolicBV<isSigned> modularIncrement () const { return increment (); }
  symbolicBV<isSigned> modularDecrement () const { return decrement (); }
  symbolicBV<isSigned> modularNegate () const { return -(*this); }
  symbolicBV<isSigned> modularAdd (const symbolicBV<isSigned>& right)
  {
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (
          boolector_saddo (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicBV<isSigned> (
          boolector_uaddo (btor, btor_node, right.btor_node));
    }
  }

  symbolicBV<isSigned> matchWidth (const symbolicBV<isSigned>& op) const
  {
    assert (this->getWidth () <= op.getWidth ());
    return this->extend (op.getWidth () - this->getWidth ());
  }
  symbolicBV<isSigned> extract (bitWidthType upper, bitWidthType lower) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_slice (btor, btor_node, upper, lower));
  }

  symbolicBV<isSigned> signExtendRightShift (
      const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sra (btor, btor_node, right.btor_node));  //?? not sure
  }

  symbolicBV<isSigned> signExtendLeftShift (
      const symbolicBV<isSigned>& right) const
  {
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sra (btor, btor_node, right.btor_node));
  }

  BoolectorNode* get_node () const { return btor_node; }

  /*//  static symbolicBV allOnes(bitWidthType bw);
  //
  //  symbolicBV(const symbolicBV<isSigned>& old);
  //
  //  symbolicBV (symbolicBV&& rhs) noexcept;
  //
  //  symbolicBV operator& (const symbolicBV<isSigned>& right) const;
  //  symbolicBV operator| (const symbolicBV& right) const;
  //  symbolicBV operator~ () const;
  //
  //  symbolicBV operator+ (const symbolicBV<isSigned>& right) const;
  //  symbolicBV operator- (const symbolicBV<isSigned>& right) const;
  //  symbolicBV operator- () const;
  //  //  symbolicBV operator/ (const symbolicBV& right) const = 0;
  //  symbolicBV operator* (const symbolicBV<isSigned>& right) const;
  //  //  symbolicBV operator% (const symbolicBV& right) const = 0;
  //
  //  //  symbolicProp operator<= (const symbolicBV& right) const = 0;
  //  //  symbolicProp operator>= (const symbolicBV& right) const = 0;
  //  symbolicBV operator== (const symbolicBV<isSigned>& right) const;
  //  //  symbolicProp operator< (const symbolicBV& right) const = 0;
  //  //  symbolicProp operator> (const symbolicBV& right) const = 0;
  //
  //  symbolicBV increment () const;
  //  symbolicBV decrement () const;
  //
  //  symbolicBV operator<< (const symbolicBV& right) const;
  //  //  symbolicBV operator>> (const symbolicBV& right) const = 0;
  //
  //  symbolicBV<false> toUnsigned () const;
  //  symbolicBV<true> toSigned () const;*/
};
/*
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
  BoolectorNode* get_node () const;

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
};*/
}  // namespace fp
#undef constexpr
#endif  // BOOLECTOR_SYMBOLICBV_H
