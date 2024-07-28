#pragma once

#include "primitives/iprimitive.h"

#include <memory>

namespace svg {

class ITool
{
public:  
  virtual std::unique_ptr<IPrimitive> Create() = 0;
  virtual ~ITool() = default;
};

} /* end svg::*/