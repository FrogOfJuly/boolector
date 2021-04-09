//
// Created by Kirill Golubev on 09.04.2021.
//

#include "fp_info.h"

fp::floatingPointTypeInfo::floatingPointTypeInfo (fp::bitWidthType eb,
                                                  fp::bitWidthType sb)
    : exponentBits (eb), significandBits (sb)
{
  assert (eb > 1);  // Not precondition as we don't have a traits class to use
  assert (sb > 1);
}
fp::floatingPointTypeInfo::floatingPointTypeInfo (
    const fp::floatingPointTypeInfo& old)
    : exponentBits (old.exponentBits), significandBits (old.significandBits)
{
}
fp::floatingPointTypeInfo&
fp::floatingPointTypeInfo::operator= (
    const fp::floatingPointTypeInfo& old)
{
  this->exponentBits    = old.exponentBits;
  this->significandBits = old.significandBits;

  return *this;
}
fp::bitWidthType
fp::floatingPointTypeInfo::exponentWidth (void) const
{
  return this->exponentBits;
}
fp::bitWidthType
fp::floatingPointTypeInfo::significandWidth (void) const
{
  return this->significandBits;
}
fp::bitWidthType
fp::floatingPointTypeInfo::packedWidth (void) const
{
  return this->exponentBits + this->significandBits;
}
fp::bitWidthType
fp::floatingPointTypeInfo::packedExponentWidth (void) const
{
  return this->exponentBits;
}
fp::bitWidthType
fp::floatingPointTypeInfo::packedSignificandWidth (void) const
{
  return this->significandBits - 1;
}
