#pragma once

#include "primitives/iprimitive.h"

#include <string>
#include <functional>

namespace svg {

using FuncOnClick = std::function<void(void)>;
/**
 * @brief Class button
 */ 
class CButton
{
public:
  CButton() = default;
  CButton(const std::string& a_strCaption) 
    : m_strCaption(a_strCaption)
  {

  }
  ~CButton() = default;

  void SetOnClick(FuncOnClick a_OnClick)
  {
    m_OnClick = a_OnClick;
  }

  void OnClick()
  {
    m_OnClick();
  }

private:
  std::string m_strCaption;
  FuncOnClick m_OnClick;
};

} /* end svg::*/