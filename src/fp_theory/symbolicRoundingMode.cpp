//
// Created by Kirill Golubev on 09.04.2021.
//

#include "symbolicRoundingMode.h"

#include <boolector.h>

fp::symbolicRoundingMode::symbolicRoundingMode (BoolectorNode *node)
{
  auto bound_btor = btor_manager::get ();
  assert (bound_btor);
  btor_node = node;
}
fp::symbolicRoundingMode
fp::symbolicRoundingMode::fromBtorNode (BoolectorNode *node)
{
  auto btor = btor_manager::get ();
  assert (btor);
  BoolectorSort srt = boolector_get_sort (btor, node);
  assert (boolector_is_bitvec_sort (btor, srt));
  assert (boolector_get_width (btor, node) == SYMFPU_NUMBER_OF_ROUNDING_MODES);
  return symbolicRoundingMode (node);
}
fp::symbolicRoundingMode::symbolicRoundingMode (const unsigned v)
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt  = boolector_bitvec_sort (btor, SYMFPU_NUMBER_OF_ROUNDING_MODES);
  btor_node = boolector_unsigned_int (btor, v, srt);
  assert ((v & (v - 1)) == 0 && v != 0);
}
fp::symbolicRoundingMode::symbolicRoundingMode (
    const fp::symbolicRoundingMode &old)
{
  auto btor = btor_manager::get ();
  assert (btor);
  btor_node = boolector_copy (btor, old.btor_node);
}
fp::symbolicProp
fp::symbolicRoundingMode::valid () const
{
  auto btor = btor_manager::get ();
  assert (btor);
  auto srt  = boolector_bitvec_sort (btor, SYMFPU_NUMBER_OF_ROUNDING_MODES);
  auto zero = boolector_zero (btor, srt);
  auto one  = boolector_one (btor, srt);
  return symbolicProp::fromBtorNode (boolector_and (
      btor,
      boolector_eq (
          btor,
          boolector_and (btor, btor_node, boolector_sub (btor, btor_node, one)),
          zero),
      boolector_not (btor, boolector_eq (btor, btor_node, zero))));

  //      reference from cvc5:
  //
  //      symbolicProposition(nm->mkNode(
  //      kind::BITVECTOR_AND,
  //      nm->mkNode(
  //          kind::BITVECTOR_COMP,
  //          nm->mkNode(kind::BITVECTOR_AND,
  //                     *this,
  //                     nm->mkNode(kind::BITVECTOR_SUB,
  //                                *this,
  //                                nm->mkConst(BitVector(
  //                                    SYMFPU_NUMBER_OF_ROUNDING_MODES, 1u)))),
  //          zero),
  //      nm->mkNode(kind::BITVECTOR_NOT,
  //                 nm->mkNode(kind::BITVECTOR_COMP, *this, zero))));
}
fp::symbolicProp
fp::symbolicRoundingMode::operator== (const fp::symbolicRoundingMode &lhs) const
{
  auto btor = btor_manager::get ();
  assert (btor);
  return symbolicProp::fromBtorNode (
      boolector_eq (btor, btor_node, lhs.btor_node));
}
BoolectorNode *
fp::symbolicRoundingMode::get_node ()
{
  return btor_node;
}
