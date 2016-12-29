#include "Library.h"

namespace archmage {

  Project *Library::get_unit_or_null(const std::string &name) const {
    if (units.count(name))
      return units.at(name).get();

    if (incomplete_units.count(name))
      return incomplete_units.at(name).get();

    return nullptr;
  }
}