#pragma once

#include "tools/itool.h"
#include "primitives/point.h"

namespace svg {

class CPointTool : public ITool
{
public:
  CPointTool() = default;

  std::unique_ptr<IPrimitive> Create() override
  {
    return std::make_unique<CPoint>();
  }

  virtual ~CPointTool() = default;
};

} /* end svg::*/