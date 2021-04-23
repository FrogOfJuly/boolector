//
// Created by Kirill Golubev on 09.04.2021.
//

#include "exposed_fp_api.h"

#include "../deps/symfpu/core/add.h"
#include "../deps/symfpu/core/classify.h"
#include "../deps/symfpu/core/compare.h"
#include "../deps/symfpu/core/divide.h"
#include "../deps/symfpu/core/fma.h"
#include "../deps/symfpu/core/multiply.h"
#include "../deps/symfpu/core/packing.h"
#include "../deps/symfpu/core/remainder.h"
#include "../deps/symfpu/core/sign.h"
#include "../deps/symfpu/core/sqrt.h"
#include "../deps/symfpu/core/unpackedFloat.h"
#include "fp_ite.h"
#include "traits.h"

/*--some floating point logic--*/
namespace fp {
BoolectorNode*
boolector_fp_var (Btor* btor,
                  const typename fp::traits::fpt& fp_info,
                  const char* symbol)
{
  assert (btor);
  fp::btor_manager::set (btor);
  auto srt = boolector_bitvec_sort (
      btor, fp_info.significandWidth () + fp_info.exponentWidth ());

  auto btor_node = boolector_var (btor, srt, symbol);

  fp::btor_manager::unset ();
  return btor_node;
}

BoolectorNode*
boolector_fp_const (Btor* btor, const char* bits)
{
  assert (btor);
  fp::btor_manager::set (btor);

  auto btor_node = boolector_const (btor, bits);

  fp::btor_manager::unset ();
  return btor_node;
}

BoolectorNode*
boolector_fp_constd (Btor* btor,
                     const typename fp::traits::fpt& fp_info,
                     const char* str)
{
  assert (btor);
  fp::btor_manager::set (btor);
  auto srt = boolector_bitvec_sort (
      btor, fp_info.significandWidth () + fp_info.exponentWidth ());
  auto btor_node = boolector_constd (btor, srt, str);

  fp::btor_manager::unset ();
  return btor_node;
}

BoolectorNode*
boolector_fp_consth (Btor* btor,
                     const typename fp::traits::fpt& fp_info,
                     const char* str)
{
  assert (btor);
  fp::btor_manager::set (btor);
  auto srt = boolector_bitvec_sort (
      btor, fp_info.significandWidth () + fp_info.exponentWidth ());
  auto btor_node = boolector_consth (btor, srt, str);

  fp::btor_manager::unset ();
  return btor_node;
}

BoolectorNode*
boolector_fp_add (Btor* btor,
                  const typename fp::traits::fpt& fp_info,
                  const typename fp::traits::rm& rm,
                  BoolectorNode* left,
                  BoolectorNode* right)
{
  fp::btor_manager::set (btor);
  auto left_bv  = fp::traits::ubv (left);
  auto right_bv = fp::traits::ubv (right);

  auto unpacked1 (symfpu::unpack<fp::traits> (fp_info, left_bv));
  auto unpacked2 (symfpu::unpack<fp::traits> (fp_info, right_bv));

  auto added (symfpu::add<fp::traits> (
      fp_info, rm, unpacked1, unpacked2, fp::symbolicProp (true)));
  auto repacked (symfpu::pack<fp::traits> (fp_info, added));
  fp::btor_manager::unset ();
  return repacked.get_node ();
}

BoolectorNode*
boolector_fp_sub (Btor* btor,
                  const typename fp::traits::fpt& fp_info,
                  const typename fp::traits::rm& rm,
                  BoolectorNode* left,
                  BoolectorNode* right)
{
  fp::btor_manager::set (btor);
  auto left_bv  = fp::traits::ubv (left);
  auto right_bv = fp::traits::ubv (right);

  auto unpacked1 (symfpu::unpack<fp::traits> (fp_info, left_bv));
  auto unpacked2 (symfpu::unpack<fp::traits> (fp_info, right_bv));
  auto negated2 (symfpu::negate (fp_info, unpacked2));
  auto subbed (symfpu::add<fp::traits> (
      fp_info, rm, unpacked1, negated2, fp::symbolicProp (true)));
  auto repacked (symfpu::pack<fp::traits> (fp_info, subbed));
  fp::btor_manager::unset ();
  return repacked.get_node ();
}

BoolectorNode*
boolector_fp_mult (Btor* btor,
                   const typename fp::traits::fpt& fp_info,
                   const typename fp::traits::rm& rm,
                   BoolectorNode* left,
                   BoolectorNode* right)
{
  fp::btor_manager::set (btor);
  auto left_bv  = fp::traits::ubv (left);
  auto right_bv = fp::traits::ubv (right);

  auto unpacked1 (symfpu::unpack<fp::traits> (fp_info, left_bv));
  auto unpacked2 (symfpu::unpack<fp::traits> (fp_info, right_bv));
  auto multed (
      symfpu::multiply<fp::traits> (fp_info, rm, unpacked1, unpacked2));
  auto repacked (symfpu::pack<fp::traits> (fp_info, multed));
  fp::btor_manager::unset ();
  return repacked.get_node ();
}

BoolectorNode*
boolector_fp_div (Btor* btor,
                  const typename fp::traits::fpt& fp_info,
                  const typename fp::traits::rm& rm,
                  BoolectorNode* left,
                  BoolectorNode* right)
{
  fp::btor_manager::set (btor);
  auto left_bv  = fp::traits::ubv (left);
  auto right_bv = fp::traits::ubv (right);

  auto unpacked1 (symfpu::unpack<fp::traits> (fp_info, left_bv));
  auto unpacked2 (symfpu::unpack<fp::traits> (fp_info, right_bv));
  auto divided (symfpu::divide<fp::traits> (fp_info, rm, unpacked1, unpacked2));
  auto repacked (symfpu::pack<fp::traits> (fp_info, divided));
  fp::btor_manager::unset ();
  return repacked.get_node ();
}

BoolectorNode*
boolector_fp_negate (Btor* btor,
                     const typename fp::traits::fpt& fp_info,
                     BoolectorNode* fp)
{
  fp::btor_manager::set (btor);
  auto fp_bv = fp::traits::ubv (fp);

  auto unpacked (symfpu::unpack<fp::traits> (fp_info, fp_bv));
  auto negated (symfpu::negate (fp_info, unpacked));
  auto repacked (symfpu::pack<fp::traits> (fp_info, negated));
  fp::btor_manager::unset ();
  return repacked.get_node ();
}

BoolectorNode*
boolector_fp_eq (Btor* btor,
                 const traits::fpt& fp_info,
                 BoolectorNode* left,
                 BoolectorNode* right)
{
  fp::btor_manager::set (btor);
  auto left_bv  = fp::traits::ubv (left);
  auto right_bv = fp::traits::ubv (right);

  auto unpacked1 (symfpu::unpack<fp::traits> (fp_info, left_bv));
  auto unpacked2 (symfpu::unpack<fp::traits> (fp_info, right_bv));
  auto res = symfpu::ieee754Equal (fp_info, unpacked1, unpacked2);
  fp::btor_manager::unset ();
  return res.get_node ();
}
}  // namespace fp
   /*--some floating point logic--*/