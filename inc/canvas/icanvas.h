#pragma once

namespace svg {

/**
 * \interface
 * @brief interface for canvas
 */   
class ICanvas 
{
public:
  virtual void Draw(int a_nX, int a_nY, int color) = 0;
  virtual ~ICanvas() = default;
};

} /*end svg::*/