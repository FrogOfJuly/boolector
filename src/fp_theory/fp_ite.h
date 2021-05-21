//
// Created by Kirill Golubev on 23.04.2021.
//

#include "../../deps/easyloggingpp/src/easylogging++.h"
#include "boolector.h"
#include "common.h"
#include "traits.h"

#ifndef BOOLECTOR_FP_ITE_H
#define BOOLECTOR_FP_ITE_H

#define ITEDNF(T)                                                             \
  namespace symfpu {                                                          \
  template <>                                                                 \
  struct ite<typename fp::traits::prop, typename T>                           \
  {                                                                           \
    static const T iteOp (const fp::traits::prop& cond,                       \
                          const T& l,                                         \
                          const T& r)                                         \
    {                                                                         \
      auto btor = fp::btor_manager::get ();                                   \
      assert (btor);                                                          \
      auto e_if_srt     = boolector_get_sort (btor, l.get_node ());           \
      auto e_if_width   = boolector_bitvec_sort_get_width (btor, e_if_srt);   \
      auto e_else_srt   = boolector_get_sort (btor, r.get_node ());           \
      auto e_else_width = boolector_bitvec_sort_get_width (btor, e_else_srt); \
      LOG (DEBUG) << "enering ite with e_if sort: " << e_if_srt               \
                  << " with width " << e_if_width << " and "                  \
                  << " e_else_sort " << e_else_srt << " with width "          \
                  << e_else_width;                                            \
      return T (boolector_cond (                                              \
          btor, cond.get_node (), l.get_node (), r.get_node ()));             \
    }                                                                         \
  };                                                                          \
  }  // namespace symfpu

ITEDNF (fp::traits::ubv);
ITEDNF (fp::traits::sbv);
ITEDNF (fp::traits::prop);
ITEDNF (fp::traits::rm);

#undef ITEDNF

#endif  // BOOLECTOR_FP_ITE_H
