//
// Created by Kirill Golubev on 09.04.2021.
//

#include <boolector.h>

#include <cfenv>

#include "../deps/symfpu/core/unpackedFloat.h"
#include "fp_info.h"
#include "symbolicBV.hpp"
#include "symbolicProp.h"
#include "symbolicRoundingMode.h"

#ifndef BOOLECTOR_TREATS_H
#define BOOLECTOR_TREATS_H

namespace fp {

class traits
{
 public:
  typedef bitWidthType bwt;
  typedef symbolicRoundingMode rm;
  typedef floatingPointTypeInfo fpt;
  typedef symbolicProp prop;
  typedef symbolicBV<true> sbv;
  typedef symbolicBV<false> ubv;
  typedef symfpu::unpackedFloat<traits> uf;

  static symbolicRoundingMode RNE (void) { return symbolicRoundingMode (1); }
  static symbolicRoundingMode RNA (void) { return symbolicRoundingMode (2); }
  static symbolicRoundingMode RTP (void) { return symbolicRoundingMode (4); }

  static symbolicRoundingMode RTN (void) { return symbolicRoundingMode (8); }

  static symbolicRoundingMode RTZ (void) { return symbolicRoundingMode (16); }
  inline static void precondition (const symbolicProp& b)
  {
    boolector_assert (btor_manager::get (), b.btor_node);
  }

  inline static void postcondition (const symbolicProp& b)
  {
    boolector_assert (btor_manager::get (), b.btor_node);
  }

  inline static void invariant (const symbolicProp& b)
  {
    boolector_assert (btor_manager::get (), b.btor_node);
  }

  inline static void precondition (const bool b) { assert (b); }

  inline static void postcondition (const bool b) { assert (b); }
  inline static void invariant (const bool b) { assert (b); }
};
}  // namespace fp

#endif  // BOOLECTOR_TREATS_H
