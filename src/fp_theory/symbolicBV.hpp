//
// Created by Kirill Golubev on 09.04.2021.
//
#include <boolector.h>

#include "../../deps/easyloggingpp/src/easylogging++.h"
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
    LOG (DEBUG) << "creating zero of size " << bw;
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, bw);
    auto zero = boolector_zero (btor, srt);
    return symbolicBV<isSigned> (zero);
  }
  static symbolicBV<isSigned> one (bitWidthType bw)
  {
    LOG (DEBUG) << "creating one of size " << bw;
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt = boolector_bitvec_sort (btor, bw);
    auto one = boolector_one (btor, srt);
    return symbolicBV<isSigned> (one);
  }

  explicit symbolicBV (BoolectorNode* node)
  {
    LOG (DEBUG) << "constructing SymbolicBV around boolecotr node " << node;
    auto btor = btor_manager::get ();
    assert (btor);
    BoolectorSort srt = boolector_get_sort (btor, node);
    assert (boolector_is_bitvec_sort (btor, srt));
    btor_node  = node;
    auto width = boolector_get_width (btor, btor_node);
    LOG (DEBUG) << "constructed SymbolicBV with width " << width;
  }
  symbolicBV (const symbolicBV<isSigned>& old)
  {
    LOG (DEBUG) << "invoking copy constructor of SymbolicBV on node "
                << old.get_node ();
    auto btor = btor_manager::get ();
    assert (btor);
    btor_node = boolector_copy (btor, old.btor_node);
  }
  explicit symbolicBV (const symbolicProp& prop) : symbolicBV (prop.get_node ())
  {
    LOG (DEBUG) << "constructing SymbolicBV from proposition around "
                << prop.get_node ();
  }

  symbolicBV (bitWidthType w, int v)
  {
    LOG (DEBUG) << "constructing SymbolicBV from integer " << v
                << " with bitwidth " << w;
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, w);
    btor_node = boolector_int (btor, v, srt);
  }

  symbolicBV<isSigned> operator& (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing & on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_and (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator| (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing | on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_or (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator~ () const
  {
    LOG (DEBUG) << "doing ~ on SymbolicBV of width " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_not (btor, btor_node));
  }
  symbolicBV<isSigned> operator+ (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing + on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_add (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator- (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing - on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sub (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator* (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing * on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_mul (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> operator/ (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing / on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "doing - on SymbolicBV of width " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_neg (btor, btor_node));
  }

  symbolicBV<isSigned> increment () const
  {
    LOG (DEBUG) << "doing increment on SymbolicBV of width " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_inc (btor, btor_node));
  }
  symbolicBV<isSigned> decrement () const
  {
    LOG (DEBUG) << "doing decrement on SymbolicBV of width " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_dec (btor, btor_node));
  }

  symbolicBV<isSigned> operator<< (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing << on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_sll (btor, btor_node, right.btor_node));
  }

  symbolicBV<isSigned> operator>> (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing >> on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "doing <= on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "doing >= on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "doing % on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    if constexpr (isSigned)
    {
      return symbolicProp::fromBtorNode (
          boolector_smod (btor, btor_node, right.btor_node));
    }
    else
    {
      // todo: boolector unsigned mod???
      return symbolicProp::fromBtorNode (
          boolector_urem (btor, btor_node, right.btor_node));
    }
  }
  symbolicProp operator< (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing < on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "doing == on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicProp::fromBtorNode (
        boolector_eq (btor, btor_node, right.btor_node));
  }
  symbolicProp operator> (const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing > on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
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
    LOG (DEBUG) << "creating allones of size " << bw;
    auto btor = btor_manager::get ();
    assert (btor);
    auto srt  = boolector_bitvec_sort (btor, bw);
    auto zero = boolector_ones (btor, srt);
    return symbolicBV<isSigned> (zero);
  }
  symbolicProp isAllOnes () const
  {
    LOG (DEBUG) << "checking isAllOnes of size " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return *this == symbolicBV::allOnes (boolector_get_width (btor, btor_node));
  }
  symbolicProp isAllZeros () const
  {
    LOG (DEBUG) << "checking isAllZeros of size " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return *this == symbolicBV::zero (boolector_get_width (btor, btor_node));
  }

  symbolicBV<isSigned> maxValue () const
  {
    LOG (DEBUG) << "getting maxValue of size " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    auto w = boolector_get_width (btor, btor_node);
    return maxValue (w);
  }
  symbolicBV<isSigned> minValue () const
  {
    LOG (DEBUG) << "getting minValue of size " << getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return minValue (boolector_get_width (btor, btor_node));
  }

  static symbolicBV<isSigned> maxValue (bitWidthType w)
  {
    LOG (DEBUG) << "getting maxValue of size " << w;
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
    LOG (DEBUG) << "getting minValue of size " << w;
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
    LOG (DEBUG) << "appending from to " << getWidth () << " with size "
                << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_concat (btor, btor_node, right.btor_node));
  }
  symbolicBV<isSigned> extend (bitWidthType newSize) const
  {
    LOG (DEBUG) << "extending from size" << getWidth () << " to size "
                << newSize;
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
    LOG (DEBUG) << "resizing from size" << getWidth () << " to size "
                << newSize;
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
    LOG (DEBUG) << "contructing from size" << getWidth ()  << " to size "
                << newSize;
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (boolector_slice (btor, btor_node, newSize, 0));
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
    LOG (DEBUG) << "doing modularAdd on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << right.getWidth ();
    auto btor = btor_manager::get ();
    assert (btor);
    return symbolicBV<isSigned> (
        boolector_add (btor, btor_node, right.btor_node));
    /*if constexpr (isSigned)
    {
      return symbolicBV<isSigned> (
          boolector_saddo (btor, btor_node, right.btor_node));
    }
    else
    {
      return symbolicBV<isSigned> (
          boolector_uaddo (btor, btor_node, right.btor_node));
    }*/
  }

  symbolicBV<isSigned> matchWidth (const symbolicBV<isSigned>& op) const
  {
    LOG (DEBUG) << "doing matchWidth on SymbolicBV of width " << getWidth ()
                << " and on "
                << "another SymbolicBV of width " << op.getWidth ();
    assert (this->getWidth () <= op.getWidth ());
    return this->extend (op.getWidth () - this->getWidth ());
  }
  symbolicBV<isSigned> extract (bitWidthType upper, bitWidthType lower) const
  {
    LOG (DEBUG) << "extracting from SymbolicBV of width " << getWidth ()
                << " since " << upper << " until " << lower;
    auto btor = btor_manager::get ();
    assert (btor);
    auto res =
        symbolicBV<isSigned> (boolector_slice (btor, btor_node, upper, lower));
    LOG (DEBUG) << "resulting symbolicBV around " << res.get_node ();
    return res;
  }

  symbolicBV<isSigned> signExtendRightShift (
      const symbolicBV<isSigned>& right) const
  {
    LOG (DEBUG) << "doing signExtendRightShift of SymbolicBV of width "
                << getWidth () << "and width " << right.getWidth ();
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
};
}  // namespace fp
#undef constexpr
#endif  // BOOLECTOR_SYMBOLICBV_H
