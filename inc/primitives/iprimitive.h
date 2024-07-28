#pragma once

#include "canvas/icanvas.h"
#include "common/color.h"

#include <memory>

namespace svg {

/**
 * \interface IPrimitive
 * @brief for primitives
 */
class IPrimitive
{
public:
  /**
   * @brief Draw all primitives on canvas
   * @param a_pCanvas shared pointer to canvas
   */
  virtual void Draw(std::shared_ptr<ICanvas> a_pCanvas) = 0;
  virtual void SetColor(CColor a_Color) = 0;
  virtual ~IPrimitive() = default;
};

class CBasePrimitive : public IPrimitive
{
public:
  CBasePrimitive() = default;

  void SetColor(CColor a_Color)
  {
    m_Color = a_Color;
  }

private:
  CColor m_Color;
};

} /*end svg::*/