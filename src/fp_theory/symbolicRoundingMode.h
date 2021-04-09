//
// Created by Kirill Golubev on 09.04.2021.
//
#include "common.h"
#include "symbolicProp.h"

#define SYMFPU_NUMBER_OF_ROUNDING_MODES 5

#ifndef BOOLECTOR_ROUNDING_MODE_H
#define BOOLECTOR_ROUNDING_MODE_H
namespace fp {
class symbolicRoundingMode
{
  BoolectorNode* btor_node;
  explicit symbolicRoundingMode(BoolectorNode* node);
 public:
  BoolectorNode* get_node();
  static symbolicRoundingMode fromBtorNode(BoolectorNode* node);
  symbolicRoundingMode(unsigned v);
  symbolicRoundingMode(const symbolicRoundingMode& old);
  symbolicProp valid() const;
  symbolicProp operator == (const symbolicRoundingMode& lhs) const;

};
}  // namespace fp
#endif  // BOOLECTOR_ROUNDING_MODE_H
