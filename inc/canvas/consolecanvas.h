#pragma once

#include "icanvas.h"

#include "iostream"

namespace svg {
  
class CConsoleCanvas : public ICanvas
{
public:
  virtual void Draw(int a_nX, int a_nY, int color) 
  {
    std::cout << a_nX << ' ' << a_nY << ' ' << color << std::endl;
  }

  virtual ~CConsoleCanvas() = default;
};

} /*end svg::*/