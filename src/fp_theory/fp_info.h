//
// Created by Kirill Golubev on 09.04.2021.
//

#include <cassert>
#include <cstdint>

#ifndef BOOLECTOR_FP_INFO_H
#define BOOLECTOR_FP_INFO_H
namespace fp {

typedef uint64_t bitWidthType;

class floatingPointTypeInfo
{
 private:
  bitWidthType exponentBits;
  bitWidthType significandBits;

 public:
  floatingPointTypeInfo (bitWidthType eb, bitWidthType sb);

  floatingPointTypeInfo (const floatingPointTypeInfo &old);

  floatingPointTypeInfo &operator= (const floatingPointTypeInfo &old);

  bitWidthType exponentWidth (void) const;

  bitWidthType significandWidth (void) const;

  bitWidthType packedWidth (void) const;

  bitWidthType packedExponentWidth (void) const;

  bitWidthType packedSignificandWidth (void) const;
};
}  // namespace fp

#endif  // BOOLECTOR_FP_INFO_H
