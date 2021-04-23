//
// Created by Kirill Golubev on 09.04.2021.
//

#include "common.h"
#include "stdexcept"
void
fp::btor_manager::set (Btor* new_btor)
{
  if (inst() != nullptr){
    throw std::runtime_error("unsetting of boolector instance is required");
  }
  inst () = new_btor;
}
void
fp::btor_manager::unset ()
{
  inst() = nullptr;
}
Btor*
fp::btor_manager::get ()
{
  return inst ();
}
