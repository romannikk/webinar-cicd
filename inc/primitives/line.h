#pragma once

#include "iprimitive.h"
#include "point.h"

namespace svg{
/**
 * @brief Class line of primitive
 */ 
class CLine : public CBasePrimitive
{
public:
  explicit CLine(std::unique_ptr<CPoint> a_PointStart, std::unique_ptr<CPoint> a_PointEnd) noexcept
    : m_PointStart{std::move(a_PointStart)}
    , m_PointEnd{std::move(a_PointEnd)}
  {}
  
  ~CLine() = default;

  /**
   * @brief Draw all primitives on canvas
   * @param a_pCanvas shared pointer to canvas
   */
  void Draw(std::shared_ptr<ICanvas> a_pCanvas) override
  {
    m_PointStart->Draw(a_pCanvas);
    m_PointEnd->Draw(a_pCanvas);
  }

private:
  std::unique_ptr<CPoint> m_PointStart;
  std::unique_ptr<CPoint> m_PointEnd;
};

} /* end svg::*/