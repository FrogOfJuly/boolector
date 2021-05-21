//
// Created by Kirill Golubev on 14.05.2021.
//

#include "test_cases.h"

#include "boolector.h"

fp::test_cases::test_cases (const fp::traits::fpt& fmt,
                            rounding_mode en_rmode,
                            bool enable_btor_trapi)
    : fmt (fmt), en_rmode (en_rmode), enable_btor_trapi (enable_btor_trapi)
{
}
void
fp::test_cases::cmp_to_zero () const
{
  LOG (INFO) << "running x == 0 test";
  set_boolector ();
  auto zero    = fp::boolector_fp_zero (btor, fmt);
  auto fp_symb = fp::boolector_fp_var (btor, fmt, "x");
  auto eq      = fp::boolector_fp_eq_ieee754 (btor, fmt, fp_symb, zero);
  boolector_assert (btor, eq);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}
void
fp::test_cases::cmp_two_symb_vars () const
{
  LOG (INFO) << "running x == y test";
  set_boolector ();
  auto fp_symb1 = fp::boolector_fp_var (btor, fmt, "x");
  auto fp_symb2 = fp::boolector_fp_var (btor, fmt, "y");
  auto cond     = fp::boolector_fp_eq_smtlib (btor, fmt, fp_symb1, fp_symb2);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}

void
fp::test_cases::addition_commutation_with_zero () const
{
  LOG (INFO) << "running x + 0 == 0 + x test";
  set_boolector ();
  auto x    = fp::boolector_fp_var (btor, fmt, "x");
  auto zero = fp::boolector_fp_zero (btor, fmt);

  auto xz = fp::boolector_fp_add (btor, fmt, rmode, x, zero);
  auto zx = fp::boolector_fp_add (btor, fmt, rmode, zero, x);

  auto cond = fp::boolector_fp_eq_smtlib (btor, fmt, xz, zx);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}

void
fp::test_cases::addition_commutation () const
{
  LOG (INFO) << "running x + y == y + x test";
  set_boolector ();
  auto x = fp::boolector_fp_var (btor, fmt, "x");
  auto y = fp::boolector_fp_var (btor, fmt, "y");

  auto xy = fp::boolector_fp_add (btor, fmt, rmode, x, y);
  auto yx = fp::boolector_fp_add (btor, fmt, rmode, y, x);

  auto cond = fp::boolector_fp_eq_smtlib (btor, fmt, xy, yx);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}

void
fp::test_cases::set_boolector () const
{
  LOG (INFO) << "   ------begin test---------";
  btor = boolector_new ();
  if (enable_btor_trapi)
  {
    boolector_set_trapi (btor, stdout);
  }
  switch (en_rmode)
  {
    case RNA: rmode = boolector_get_rna_rounding_mod (btor); break;
    case RTZ: rmode = boolector_get_rtz_rounding_mod (btor); break;
    case RNE: rmode = boolector_get_rne_rounding_mod (btor); break;
    case RTP: rmode = boolector_get_rtp_rounding_mod (btor); break;
    case RTN: rmode = boolector_get_rtn_rounding_mod (btor); break;
  }
}
void
fp::test_cases::release_boolector () const
{
  boolector_release_all (btor);  //!!
  boolector_delete (btor);
  btor  = nullptr;
  rmode = nullptr;
  LOG (INFO) << "----------end test-----------";
}
void
fp::test_cases::run () const
{
  cmp_to_zero ();
  cmp_two_symb_vars ();
  multiplying_zeros ();
  substracting_zeros ();
  adding_zeroes ();
  right_zero_neutrality ();
  left_zero_neutrality ();
  addition_commutation_with_zero ();
  addition_commutation ();
  distribution_relative_to_addition ();
  trivial_unsat_test();
}
void
fp::test_cases::right_zero_neutrality () const
{
  LOG (INFO) << "running x + 0 == x test";
  set_boolector ();

  auto x    = fp::boolector_fp_var (btor, fmt, "x");
  auto zero = fp::boolector_fp_zero (btor, fmt);
  auto xz   = fp::boolector_fp_add (btor, fmt, rmode, x, zero);
  auto cond = fp::boolector_fp_eq_smtlib (btor, fmt, xz, x);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}

void
fp::test_cases::left_zero_neutrality () const
{
  LOG (INFO) << "running 0 + x == x test";
  set_boolector ();

  auto x    = fp::boolector_fp_var (btor, fmt, "x");
  auto zero = fp::boolector_fp_zero (btor, fmt);
  auto zx   = fp::boolector_fp_add (btor, fmt, rmode, zero, x);
  auto cond = fp::boolector_fp_eq_smtlib (btor, fmt, zx, x);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}
void
fp::test_cases::adding_zeroes () const
{
  LOG (INFO) << "running 0 + 0 == 0 test";
  set_boolector ();
  auto zero1 = fp::boolector_fp_zero (btor, fmt);
  auto zero2 = fp::boolector_fp_zero (btor, fmt);
  auto zz    = fp::boolector_fp_add (btor, fmt, rmode, zero1, zero2);
  auto cond  = fp::boolector_fp_eq_smtlib (btor, fmt, zz, zero1);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}

void
fp::test_cases::substracting_zeros () const
{
  LOG (INFO) << "running 0 - 0 == 0 test";
  set_boolector ();
  auto zero1 = fp::boolector_fp_zero (btor, fmt);
  auto zero2 = fp::boolector_fp_zero (btor, fmt);
  auto zz    = fp::boolector_fp_sub (btor, fmt, rmode, zero1, zero2);
  auto cond  = fp::boolector_fp_eq_smtlib (btor, fmt, zz, zero1);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}
void
fp::test_cases::multiplying_zeros () const
{
  LOG (INFO) << "running 0 * 0 == 0 test";
  set_boolector ();
  auto zero1 = fp::boolector_fp_zero (btor, fmt);
  auto zero2 = fp::boolector_fp_zero (btor, fmt);
  auto zz    = fp::boolector_fp_mult (btor, fmt, rmode, zero1, zero2);
  auto cond  = fp::boolector_fp_eq_smtlib (btor, fmt, zz, zero1);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}
void
fp::test_cases::distribution_relative_to_addition () const
{
  LOG (INFO) << "running x * (y + z) != x*y + x*z test";
  set_boolector ();
  auto x         = fp::boolector_fp_var (btor, fmt, "x");
  auto y         = fp::boolector_fp_var (btor, fmt, "y");
  auto z         = fp::boolector_fp_var (btor, fmt, "z");
  auto left_add  = fp::boolector_fp_add (btor, fmt, rmode, y, z);
  auto left_mul  = fp::boolector_fp_mult (btor, fmt, rmode, x, left_add);
  auto xy        = fp::boolector_fp_mult (btor, fmt, rmode, x, y);
  auto xz        = fp::boolector_fp_mult (btor, fmt, rmode, x, z);
  auto right_add = fp::boolector_fp_add (btor, fmt, rmode, xy, xz);
  auto cond      = fp::boolector_fp_eq_smtlib (btor, fmt, left_mul, right_add);
  auto not_cond = boolector_not(btor, cond);

  boolector_assert (btor, not_cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: sat";
  result == BOOLECTOR_SAT
      ? LOG (INFO) << "SAT"
      : LOG (INFO) << "expected sat, got: "
                      << (result == BOOLECTOR_UNSAT ? "unsat" : "unknown");
  release_boolector ();
}
void
fp::test_cases::trivial_unsat_test () const
{
  LOG (INFO) << "running 0 * 0 == 1 test";
  set_boolector ();
  auto zero1 = fp::boolector_fp_zero (btor, fmt);
  auto zero2 = fp::boolector_fp_zero (btor, fmt);
  auto one   = fp::boolector_fp_one (btor, fmt);
  auto zz    = fp::boolector_fp_mult (btor, fmt, rmode, zero1, zero2);
  auto cond  = fp::boolector_fp_eq_smtlib (btor, fmt, zz, one);

  boolector_assert (btor, cond);
  auto result = boolector_sat (btor);

  LOG (INFO) << "Expect: unsat";
  result == BOOLECTOR_UNSAT
      ? LOG (INFO) << "UNSAT"
      : LOG (INFO) << "expected unsat, got: "
                      << (result == BOOLECTOR_SAT ? "sat" : "unknown");
  release_boolector ();
}
