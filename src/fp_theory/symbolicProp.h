//
// Created by Kirill Golubev on 09.04.2021.
//
#include <cassert>

#include "common.h"

#ifndef BOOLECTOR_SYMBOLICPROP_H
#define BOOLECTOR_SYMBOLICPROP_H
namespace fp {
class symbolicProp
{
  BoolectorNode* btor_node;



 public:
  static symbolicProp fromBtorNode(BoolectorNode* node);
  // ^---- will it be called in some places when it is undesired??
  explicit symbolicProp (BoolectorNode* node);
  symbolicProp(const symbolicProp& old);
  symbolicProp(bool b);

  BoolectorNode* get_node() const;

  symbolicProp operator!()const;
  symbolicProp operator&&(const symbolicProp& op)const;
  symbolicProp operator||(const symbolicProp& op)const;
  symbolicProp operator==(const symbolicProp& op)const;
  symbolicProp operator^(const symbolicProp& op)const;

  friend class traits;

};
}  // namespace fp

#endif  // BOOLECTOR_SYMBOLICPROP_H
