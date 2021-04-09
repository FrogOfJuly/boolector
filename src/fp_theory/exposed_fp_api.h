//
// Created by Kirill Golubev on 09.04.2021.
//

#ifndef BOOLECTOR_EXPOSED_FP_API_H
#define BOOLECTOR_EXPOSED_FP_API_H

/*--some floating point logic--*/

BoolectorNode *boolector_fp_var (
    Btor *btor, uint32_t base, uint32_t exp, const char *symbol);

/*--some floating point logic--*/

#endif  // BOOLECTOR_EXPOSED_FP_API_H
