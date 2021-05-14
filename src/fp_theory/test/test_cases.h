//
// Created by Kirill Golubev on 14.05.2021.
//

#ifndef BOOLECTOR_TEST_CASES_H
#define BOOLECTOR_TEST_CASES_H

#include <optional>

#include "../exposed_fp_api.h"

namespace fp {
class test_cases
{
 public:
  enum rounding_mode
  {
    RNA,
    RNE,
    RTP,
    RTN,
    RTZ
  };

 private:
  fp::traits::fpt fmt;
  rounding_mode en_rmode;

  mutable BoolectorNode* rmode = nullptr;
  mutable Btor* btor           = nullptr;

  bool enable_btor_trapi = false;

  void set_boolector () const;
  void release_boolector () const;

  void cmp_to_zero () const;
  void cmp_two_symb_vars () const;
  void addition_commutation_with_zero () const;
  void addition_commutation () const;
  void right_zero_neutrality () const;
  void left_zero_neutrality () const;

 public:
  explicit test_cases (const fp::traits::fpt& fmt,
                       rounding_mode en_rmode,
                       bool enable_btor_trapi = false);
  void run () const;
};
};  // namespace fp

#endif  // BOOLECTOR_TEST_CASES_H
