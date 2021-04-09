//
// Created by Kirill Golubev on 09.04.2021.
//

#include "symbolicBV.h"

#include "boolector.h"

fp::symbolicBV::symbolicBV (BoolectorNode *node)
{
  auto bound_btor = btor_manager::get ();
  assert (bound_btor);
  btor_node = node;
}
fp::symbolicBV
fp::symbolicBV::fromBtorNode (BoolectorNode *node)
{
  auto btor = btor_manager::get ();
  assert (btor);
  BoolectorSort srt = boolector_get_sort (btor, node);
  assert (boolector_is_bitvec_sort (btor, srt));
  return symbolicBV (node);
}
fp::symbolicBV
fp::symbolicBV::zero (fp::bitWidthType bw)
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt  = boolector_bitvec_sort (btor, bw);
  auto zero = boolector_zero (btor, srt);
  return fromBtorNode (zero);
}
fp::symbolicBV
fp::symbolicBV::one (fp::bitWidthType bw)
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt  = boolector_bitvec_sort (btor, bw);
  auto zero = boolector_one (btor, srt);
  return fromBtorNode (zero);
}

fp::symbolicBV::symbolicBV (const fp::symbolicBV &old)
{
  auto btor = btor_manager::get ();
  assert (btor);
  btor_node = boolector_copy (btor, old.btor_node);
}

fp::symbolicBV
fp::symbolicBV::operator& (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_and (btor, btor_node, right.btor_node));
}
fp::symbolicBV
fp::symbolicBV::operator| (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_or (btor, btor_node, right.btor_node));
}
fp::symbolicBV
fp::symbolicBV::operator~ () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_not (btor, btor_node));
}

fp::symbolicBV
fp::symbolicBV::operator+ (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_add (btor, btor_node, right.btor_node));
}
fp::symbolicBV
fp::symbolicBV::operator- (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sub (btor, btor_node, right.btor_node));
}

fp::symbolicBV
fp::symbolicBV::operator* (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_mul (btor, btor_node, right.btor_node));
}

fp::symbolicBV
fp::symbolicBV::increment () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_inc (btor, btor_node));
}
fp::symbolicBV
fp::symbolicBV::decrement () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_dec (btor, btor_node));
}

fp::symbolicBV
fp::symbolicBV::operator<< (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sll (btor, btor_node, right.btor_node));
}

fp::symbolicProp
fp::symbolicBV::operator== (const fp::symbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (
      boolector_eq (btor, btor_node, right.btor_node));
}

fp::sSymbolicBV
fp::sSymbolicBV::operator>> (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sra (btor, btor_node, right.btor_node));
  //                                     ^--- signed operation
}

fp::symbolicProp
fp::sSymbolicBV::operator<= (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_slte (
      btor, btor_node, right.btor_node));  //         ^--- signed operation
}
fp::symbolicProp
fp::sSymbolicBV::operator>= (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_sgte (
      btor, btor_node, right.btor_node));  //         ^--- signed operation
}

fp::sSymbolicBV
fp::sSymbolicBV::operator% (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_smod (btor, btor_node, right.btor_node));
  //                                   ^--- signed operation
}

fp::sSymbolicBV
fp::sSymbolicBV::operator/ (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sdiv (btor, btor_node, right.btor_node));
  //                                   ^--- signed operation
}

fp::symbolicProp
fp::sSymbolicBV::operator< (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_slt (
      btor, btor_node, right.btor_node));  //   ^--- signed operation
}
fp::symbolicProp
fp::sSymbolicBV::operator> (const fp::sSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_sgt (
      btor, btor_node, right.btor_node));  //   ^--- signed operation
}
fp::sSymbolicBV::sSymbolicBV (BoolectorNode *node) : symbolicBV (node) {}
fp::uSymbolicBV
fp::symbolicBV::toUnsigned () const
{
  return uSymbolicBV::fromBtorNode (btor_node);
}
fp::sSymbolicBV
fp::symbolicBV::toSigned () const
{
  return sSymbolicBV::fromBtorNode (btor_node);
}

fp::uSymbolicBV
fp::uSymbolicBV::fromBtorNode (BoolectorNode *node)
{
  auto btor = btor_manager::get ();
  assert (btor);
  BoolectorSort srt = boolector_get_sort (btor, node);
  assert (boolector_is_bitvec_sort (btor, srt));
  return uSymbolicBV (node);
}
fp::symbolicProp
fp::uSymbolicBV::operator<= (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_ulte (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::symbolicProp
fp::uSymbolicBV::operator>= (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_ugte (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::symbolicProp
fp::uSymbolicBV::operator< (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_ult (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::symbolicProp
fp::uSymbolicBV::operator> (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (boolector_ugt (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::uSymbolicBV
fp::uSymbolicBV::operator>> (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_srl (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::uSymbolicBV
fp::uSymbolicBV::operator/ (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sdiv (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}
fp::uSymbolicBV
fp::uSymbolicBV::operator% (const fp::uSymbolicBV &right) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_smod (
      btor, btor_node, right.btor_node));  //   ^--- unsigned operation
}

fp::uSymbolicBV::uSymbolicBV (BoolectorNode *node) : symbolicBV (node) {}
fp::uSymbolicBV::uSymbolicBV (const fp::uSymbolicBV &right) : symbolicBV (right)
{
}

fp::sSymbolicBV::sSymbolicBV (const fp::sSymbolicBV &right) : symbolicBV (right)
{
}
fp::sSymbolicBV
fp::sSymbolicBV::fromBtorNode (BoolectorNode *node)
{
  auto btor = btor_manager::get ();
  assert (btor);
  BoolectorSort srt = boolector_get_sort (btor, node);
  assert (boolector_is_bitvec_sort (btor, srt));
  return sSymbolicBV (node);
}
//
// fp::sSymbolicBV
// fp::sSymbolicBV::zero (fp::bitWidthType bw)
//{
//  return symbolicBV::zero (bw).toSigned ();
//}
// fp::sSymbolicBV
// fp::sSymbolicBV::one (fp::bitWidthType bw)
//{
//  return symbolicBV::one (bw).toSigned ();
//}
// fp::sSymbolicBV
// fp::sSymbolicBV::allOnes (fp::bitWidthType bw)
//{
//  return symbolicBV::allOnes (bw).toSigned ();
//}
//
// fp::uSymbolicBV
// fp::uSymbolicBV::zero (fp::bitWidthType bw)
//{
//  return symbolicBV::zero (bw).toUnsigned ();
//}
// fp::uSymbolicBV
// fp::uSymbolicBV::one (fp::bitWidthType bw)
//{
//  return symbolicBV::one (bw).toUnsigned ();
//}
// fp::uSymbolicBV
// fp::uSymbolicBV::allOnes (fp::bitWidthType bw)
//{
//  return symbolicBV::allOnes (bw).toUnsigned ();
//}

fp::symbolicBV
fp::symbolicBV::allOnes (fp::bitWidthType bw)
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt  = boolector_bitvec_sort (btor, bw);
  auto zero = boolector_ones (btor, srt);
  return fromBtorNode (zero);
}
fp::symbolicProp
fp::symbolicBV::isAllOnes () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return *this == symbolicBV::allOnes (boolector_get_width (btor, btor_node));
}

fp::symbolicProp
fp::symbolicBV::isAllZeros () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return *this == symbolicBV::zero (boolector_get_width (btor, btor_node));
}

fp::bitWidthType
fp::symbolicBV::get_weidth () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return boolector_get_width (btor, btor_node);
}

fp::uSymbolicBV
fp::uSymbolicBV::maxValue () const
{
  return allOnes (get_weidth ());
}
fp::uSymbolicBV
fp::uSymbolicBV::minValue () const
{
  return zero (get_weidth ());
}

fp::sSymbolicBV
fp::sSymbolicBV::maxValue () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt = boolector_get_sort (btor, btor_node);
  return fromBtorNode (boolector_max_signed (btor, srt));
}
fp::sSymbolicBV
fp::sSymbolicBV::minValue () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt = boolector_get_sort (btor, btor_node);
  return fromBtorNode (boolector_min_signed (btor, srt));
}
fp::sSymbolicBV::sSymbolicBV (fp::sSymbolicBV &&rhs) noexcept
    : symbolicBV (std::move (rhs))
{
}
fp::uSymbolicBV::uSymbolicBV (fp::uSymbolicBV &&rhs) noexcept
    : symbolicBV (std::move (rhs))
{
}
fp::symbolicBV::symbolicBV (fp::symbolicBV &&rhs) noexcept = default;

fp::symbolicBV
fp::symbolicBV::append (const fp::symbolicBV &rigth) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_concat (btor, btor_node, rigth.btor_node));
}

fp::symbolicBV::operator uSymbolicBV () const { return this->toUnsigned (); }
fp::symbolicBV::operator sSymbolicBV () const { return this->toSigned (); }

fp::symbolicBV
fp::symbolicBV::operator- () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_neg (btor, btor_node));
}

fp::sSymbolicBV
fp::sSymbolicBV::extend (fp::bitWidthType w) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_sext (btor, btor_node, w));
}

fp::uSymbolicBV
fp::uSymbolicBV::extend (fp::bitWidthType w) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_uext (btor, btor_node, w));
}
fp::sSymbolicBV
fp::sSymbolicBV::resize (fp::bitWidthType newSize) const
{
  auto width = this->get_weidth ();

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
fp::sSymbolicBV
fp::sSymbolicBV::contract (fp::bitWidthType newSize) const
{
  // todo: figure out
  throw 1;
  //  return fp::sSymbolicBV (fp::sSymbolicBV ());
  //drop bits from the base side.
}

fp::uSymbolicBV
fp::uSymbolicBV::resize (fp::bitWidthType newSize) const
{
  auto width = this->get_weidth ();

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
fp::uSymbolicBV
fp::uSymbolicBV::contract (fp::bitWidthType newSize) const
{
  // todo: figure out
  throw 1;
}

fp::symbolicBV
fp::symbolicBV::modularLeftShift (const fp::symbolicBV &op) const
{
  return (*this) << op;
}

fp::symbolicBV
fp::symbolicBV::modularIncrement () const
{
  return increment ();
}
fp::symbolicBV
fp::symbolicBV::modularDecrement () const
{
  return decrement ();
}
fp::sSymbolicBV
fp::sSymbolicBV::modularAdd (const fp::sSymbolicBV &op) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_saddo (btor, btor_node, op.btor_node));
}
fp::symbolicBV
fp::symbolicBV::modularNegate () const
{
  return -(*this);
}

fp::sSymbolicBV
fp::sSymbolicBV::modularRightShift (const fp::sSymbolicBV &op) const
{
  return (*this) >> op;
}

fp::uSymbolicBV
fp::uSymbolicBV::modularRightShift (const fp::uSymbolicBV &op) const
{
  return (*this) >> op;
}

fp::uSymbolicBV
fp::uSymbolicBV::modularAdd (const fp::uSymbolicBV &op) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return fromBtorNode (boolector_uaddo (btor, btor_node, op.btor_node));
}

fp::uSymbolicBV
fp::uSymbolicBV::matchWidth (const fp::uSymbolicBV &op) const
{
  assert (this->get_weidth () <= op.get_weidth ());
  return this->extend (op.get_weidth () - this->get_weidth ());
}

fp::sSymbolicBV
fp::sSymbolicBV::matchWidth (const fp::sSymbolicBV &op) const
{
  assert (this->get_weidth () <= op.get_weidth ());
  return this->extend (op.get_weidth () - this->get_weidth ());
}

fp::symbolicBV
fp::symbolicBV::extract (bitWidthType upper, bitWidthType lower) const
{
  auto btor = btor_manager::get();
  assert(btor);

  return fromBtorNode(boolector_slice(btor, btor_node, upper, lower));
}
BoolectorNode *
fp::symbolicBV::get_node () const
{
  return btor_node;
}
