//
// Created by Kirill Golubev on 09.04.2021.
//

#ifndef BOOLECTOR_COMMON_H
#define BOOLECTOR_COMMON_H

struct BoolectorNode;
struct Btor;

namespace fp {
class btor_manager
{
  static Btor*& inst ()
  {
    static Btor* btor = nullptr;
    return btor;
  }

 public:
  btor_manager () = delete;

  static void set (Btor* new_btor);

  static void unset ();

  static Btor* get ();
};
}  // namespace fp

#endif  // BOOLECTOR_COMMON_H
