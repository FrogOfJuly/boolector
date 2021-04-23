#include <iostream>

#include "../exposed_fp_api.h"
//#include "boolector.h"

int
main (void)
{
  fp::traits::bwt e = 2;
  fp::traits::bwt s = 3;
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

  boolector_release_all(btor);//!!
  boolector_delete (btor);
  return 0;
}
