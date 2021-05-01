#include <iostream>

#include "../../../deps/easyloggingpp/src/easylogging++.h"
#include "../exposed_fp_api.h"

INITIALIZE_EASYLOGGINGPP

void eq_test ();
void cmp_test ();

int
main (int argc, char* argv[])
{
  START_EASYLOGGINGPP (argc, argv);
  std::cout << "eq test:" << std::endl;
  eq_test ();
  std::cout << "----------" << std::endl;

  std::cout << "cmp test:" << std::endl;
  cmp_test ();
  std::cout << "----------" << std::endl;
  return 0;
}

void
cmp_test ()
{
  fp::traits::bwt e = 8;
  fp::traits::bwt s = 24;
  auto fmt          = fp::traits::fpt (e, s);
  Btor* btor        = boolector_new ();

  auto zero_str = std::string (e + s, '0');

  auto zero = fp::boolector_fp_const (btor, zero_str.c_str ());

  auto fp_symb1 = fp::boolector_fp_var (btor, fmt, "x");
  auto fp_symb2 = fp::boolector_fp_var (btor, fmt, "y");

  auto lt1 = fp::boolector_fp_lt (btor, fmt, fp_symb1, zero);
  auto lt2 = fp::boolector_fp_lt (btor, fmt, fp_symb2, zero);

  boolector_assert (btor, lt1);
  boolector_assert (btor, lt2);
  std::cout << "passed 2 asserting" << std::endl;
  auto rm     = fp::boolector_get_fne_rounding_mod (btor);
  std::cout << "got rounding mod" << std::endl;
  auto fp_sum = fp::boolector_fp_add (btor, fmt, rm, fp_symb1, fp_symb2);
  std::cout << "passed add" << std::endl;
  auto cond   = fp::boolector_fp_lt (btor, fmt, fp_sum, zero);
  std::cout << "passed 3d assert" << std::endl;
  boolector_assert (btor, cond);

  auto result = boolector_sat (btor);
  printf ("Expect: unsat\n");
  printf ("Boolector: %s\n",
          result == BOOLECTOR_SAT
              ? "sat"
              : (result == BOOLECTOR_UNSAT ? "unsat" : "unknown"));

  boolector_release_all (btor);  //!!
  boolector_delete (btor);
}

void
eq_test ()
{
  fp::traits::bwt e = 8;
  fp::traits::bwt s = 24;
  auto fmt          = fp::traits::fpt (e, s);
  Btor* btor        = boolector_new ();

  auto fp_symb1 = fp::boolector_fp_var (btor, fmt, "x");
  auto fp_symb2 = fp::boolector_fp_var (btor, fmt, "y");

  auto cond = fp::boolector_fp_eq (btor, fmt, fp_symb1, fp_symb2);

  boolector_assert (btor, cond);

  auto result = boolector_sat (btor);

  printf ("Expect: unsat\n");
  printf ("Boolector: %s\n",
          result == BOOLECTOR_SAT
              ? "sat"
              : (result == BOOLECTOR_UNSAT ? "unsat" : "unknown"));

  boolector_release_all (btor);  //!!
  boolector_delete (btor);
}