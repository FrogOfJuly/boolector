//
// Created by Kirill Golubev on 09.04.2021.
//

#include "common.h"
void
fp::btor_manager::set (Btor* new_btor)
{
  inst () = new_btor;
}
void
fp::btor_manager::unset ()
{
  set (nullptr);
}
Btor*
fp::btor_manager::get ()
{
  return inst ();
}
