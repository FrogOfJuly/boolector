//
// Created by Kirill Golubev on 09.04.2021.
//

#include "traits.h"

#ifndef BOOLECTOR_EXPOSED_FP_API_H
#define BOOLECTOR_EXPOSED_FP_API_H

/*--some floating point logic--*/
namespace fp {
BoolectorNode* boolector_fp_var (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 const char* symbol);

BoolectorNode* boolector_fp_add (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 BoolectorNode* rm,
                                 BoolectorNode* left,
                                 BoolectorNode* right);

BoolectorNode* boolector_fp_const (Btor* btor, const char* bits);

BoolectorNode* boolector_fp_constd (Btor* btor,
                                    const typename fp::traits::fpt& fp_info,
                                    const char* str);

BoolectorNode* boolector_fp_consth (Btor* btor,
                                    const typename fp::traits::fpt& fp_info,
                                    const char* str);

BoolectorNode* boolector_fp_sub (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 BoolectorNode* rm,
                                 BoolectorNode* left,
                                 BoolectorNode* right);

BoolectorNode* boolector_fp_mult (Btor* btor,
                                  const typename fp::traits::fpt& fp_info,
                                  BoolectorNode* rm,
                                  BoolectorNode* left,
                                  BoolectorNode* right);

BoolectorNode* boolector_fp_div (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 BoolectorNode* rm,
                                 BoolectorNode* left,
                                 BoolectorNode* right);

BoolectorNode* boolector_fp_negate (Btor* btor,
                                    const typename fp::traits::fpt& fp_info,
                                    BoolectorNode* fp);

BoolectorNode* boolector_fp_gt (Btor* btor,
                                const typename fp::traits::fpt& fp_info,
                                BoolectorNode* left,
                                BoolectorNode* right);
BoolectorNode* boolector_fp_gte (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 BoolectorNode* left,
                                 BoolectorNode* right);

BoolectorNode* boolector_fp_lt (Btor* btor,
                                const typename fp::traits::fpt& fp_info,
                                BoolectorNode* left,
                                BoolectorNode* right);

BoolectorNode* boolector_fp_lte (Btor* btor,
                                 const typename fp::traits::fpt& fp_info,
                                 BoolectorNode* left,
                                 BoolectorNode* right);

BoolectorNode* boolector_fp_eq_ieee754 (Btor* btor,
                                const typename fp::traits::fpt& fp_info,
                                BoolectorNode* left,
                                BoolectorNode* right);

BoolectorNode* boolector_fp_eq_smtlib (Btor* btor,
                         const traits::fpt& fp_info,
                         BoolectorNode* left,
                         BoolectorNode* right);

BoolectorNode* boolector_get_fne_rounding_mod (Btor* btor);
BoolectorNode* boolector_get_rtp_rounding_mod (Btor* btor);
BoolectorNode* boolector_get_rtn_rounding_mod (Btor* btor);
BoolectorNode* boolector_get_rna_rounding_mod (Btor* btor);
BoolectorNode* boolector_get_rtz_rounding_mod (Btor* btor);

}  // namespace fp
/*--some floating point logic--*/

#endif  // BOOLECTOR_EXPOSED_FP_API_H
