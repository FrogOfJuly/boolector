//
// Created by Kirill Golubev on 23.04.2021.
//

#include "boolector.h"
#include "common.h"
#include "traits.h"

#ifndef BOOLECTOR_FP_ITE_H
#define BOOLECTOR_FP_ITE_H

#define ITEDNF(T)                                                              \
namespace symfpu {                                                             \
template <>                                                                    \
struct ite<typename fp::traits::prop, typename T>                              \
{                                                                              \
  static const T iteOp (const fp::traits::prop& cond,                         \
                          const T& l,                                          \
                          const T& r)                                          \
  {                                                                            \
    auto btor = fp::btor_manager::get ();                                      \
    assert (btor);                                                             \
    return T (                                                                 \
        boolector_cond (btor, cond.get_node (), l.get_node (), r.get_node ()));\
  }                                                                            \
};                                                                             \
}  // namespace symfpu

ITEDNF (fp::traits::ubv);
ITEDNF (fp::traits::sbv);
ITEDNF (fp::traits::prop);
ITEDNF (fp::traits::rm);

#undef ITEDNF

#endif  // BOOLECTOR_FP_ITE_H
