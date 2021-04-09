//
// Created by Kirill Golubev on 09.04.2021.
//

#include "traits.h"

#include <boolector.h>
#include <fenv.h>

void
fp::traits::precondition (const fp::symbolicProp& b)
{
  boolector_assert (btor_manager::get (), b.btor_node);
  return;
}
void
fp::traits::postcondition (const fp::symbolicProp& b)
{
  boolector_assert (btor_manager::get (), b.btor_node);
  return;
}
void
fp::traits::invariant (const fp::symbolicProp& b)
{
  boolector_assert (btor_manager::get (), b.btor_node);
  return;
}

void
fp::traits::precondition (const bool b)
{
  assert (b);
}
void
fp::traits::postcondition (const bool b)
{
  assert (b);
}
void
fp::traits::invariant (const bool b)
{
  assert (b);
}

fp::symbolicRoundingMode fp::traits::RNE(void) { return symbolicRoundingMode((unsigned)FE_TONEAREST); }

fp::symbolicRoundingMode fp::traits::RNA(void) { return symbolicRoundingMode(23); }          // Could be better...
fp::symbolicRoundingMode fp::traits::RTP(void) { return symbolicRoundingMode(FE_UPWARD); }

fp::symbolicRoundingMode fp::traits::RTN(void) { return symbolicRoundingMode(FE_DOWNWARD); }

fp::symbolicRoundingMode fp::traits::RTZ(void) { return symbolicRoundingMode(FE_TOWARDZERO); }
