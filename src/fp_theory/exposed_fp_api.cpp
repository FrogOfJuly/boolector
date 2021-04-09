//
// Created by Kirill Golubev on 09.04.2021.
//

#include "traits.h"
#include "exposed_fp_api.h"

/*--some floating point logic--*/
BoolectorNode *
boolector_fp_var (
    Btor *btor, uint32_t base, uint32_t exp, const char *symbol)
{
  fp::btor_manager::set(btor);//make it `global` for symfpu internals
  //           v--< Signed bit vectors or unsigned???
  fp::traits::ubv var = fp::sSymbolicBV(sig_bit_num, exp_bit_num);
  fp::btor_manager::unset();
  return var.get_node();
}
/*--some floating point logic--*/