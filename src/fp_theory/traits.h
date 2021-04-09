//
// Created by Kirill Golubev on 09.04.2021.
//
#include "fp_info.h"
#include "symbolicBV.h"
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
  typedef symbolicBV sbv;
  typedef uSymbolicBV ubv;

  static symbolicRoundingMode RNE (void);

  static symbolicRoundingMode RNA (void);

  static symbolicRoundingMode RTP (void);

  static symbolicRoundingMode RTN (void);

  static symbolicRoundingMode RTZ (void);
  inline static void precondition (const symbolicProp& b);

  inline static void postcondition (const symbolicProp& b);

  inline static void invariant (const symbolicProp& b);

  inline static void precondition (const bool b);

  inline static void postcondition (const bool b);

  inline static void invariant (const bool b);
};
}  // namespace fp

#endif  // BOOLECTOR_TREATS_H
