#pragma once

#include "tools/itool.h"
#include "primitives/line.h"

namespace svg {

class CLineTool : public ITool
{
public:
  CLineTool() = default;

  std::unique_ptr<IPrimitive> Create() override
  {

    return std::make_unique<CLine>(std::make_unique<CPoint>(), std::make_unique<CPoint>());
  }

  virtual ~CLineTool() = default;
};

} /* end svg::*/