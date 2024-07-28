#pragma once

#include "iprimitive.h"

#include <memory>

namespace svg 
{
/**
 * @brief Class point of primitive
 */ 
class CPoint : public CBasePrimitive
{
public:
  CPoint()
    : m_nX(0)
    , m_nY(0)
  {}
  CPoint(const CPoint& a_Point) = default;
  CPoint(CPoint&& a_Point) = default;
  CPoint& operator=(const CPoint& a_Point) = default;
  CPoint& operator=(CPoint&& a_Point) = default;
  ~CPoint() = default;

  /**
   * @brief Draw all primitives on canvas
   * @param a_pCanvas shared pointer to canvas
   */
  void Draw(std::shared_ptr<ICanvas> a_pCanvas) override
  {
    a_pCanvas->Draw(m_nX, m_nY, 1);
  }

private:
  int m_nX;
  int m_nY;
};

} /* end svg::*/