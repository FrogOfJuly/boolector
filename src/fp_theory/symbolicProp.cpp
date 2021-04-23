//
// Created by Kirill Golubev on 09.04.2021.
//

#include "symbolicProp.h"

#include <boolector.h>

fp::symbolicProp
fp::symbolicProp::fromBtorNode (BoolectorNode *node)
{
  auto btor = btor_manager::get ();
  assert (btor);
  BoolectorSort srt = boolector_get_sort (btor, node);
  assert (boolector_is_bitvec_sort (btor, srt));
  assert (boolector_bitvec_sort_get_width (btor, srt) == 1);
  return symbolicProp (node);
}
fp::symbolicProp::symbolicProp (BoolectorNode *node)
{
  auto bound_btor = btor_manager::get ();
  assert (bound_btor);
  btor_node = node;
}
fp::symbolicProp::symbolicProp (const fp::symbolicProp &old)
{
  auto btor = btor_manager::get ();
  assert (btor);
  btor_node = boolector_copy (btor, old.btor_node);
}
fp::symbolicProp
fp::symbolicProp::operator! () const
{
  auto btor = btor_manager::get ();
  return fromBtorNode (boolector_not (btor, btor_node));
}

fp::symbolicProp
fp::symbolicProp::operator&& (const fp::symbolicProp &op) const
{
  auto btor = btor_manager::get ();
  return fromBtorNode (boolector_and (btor, btor_node, op.btor_node));
}
fp::symbolicProp
fp::symbolicProp::operator|| (const fp::symbolicProp &op) const
{
  auto btor = btor_manager::get ();
  return fromBtorNode (boolector_or (btor, btor_node, op.btor_node));
}
fp::symbolicProp
fp::symbolicProp::operator== (const fp::symbolicProp &op) const
{
  auto btor = btor_manager::get ();
  return fromBtorNode (boolector_eq (btor, btor_node, op.btor_node));
}
fp::symbolicProp
fp::symbolicProp::operator^ (const fp::symbolicProp &op) const
{
  auto btor = btor_manager::get ();
  return fromBtorNode (boolector_xor (btor, btor_node, op.btor_node));
}
fp::symbolicProp::symbolicProp (bool b)
{
  auto btor = btor_manager::get ();
  auto srt  = boolector_bitvec_sort (btor, 1);
  auto zero = boolector_zero (btor, srt);
  btor_node = b ? boolector_not (btor, zero) : zero;
}
BoolectorNode *
fp::symbolicProp::get_node () const
{
  return btor_node;
}
