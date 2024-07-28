#pragma once

#include "editormodel.h"
#include "primitives/iprimitive.h"
#include "tools/itool.h"

#include <memory>

namespace svg {

/**
 * @brief Class vector editor controller
 */ 
class CEditorController
{
public:
  explicit CEditorController(std::shared_ptr<CEditorModel> a_pModel);

  void Open(const std::string& path);
  void Clear();
  void Save() const;
  void Run();
  void SetColor(CColor a_Color);
  void SetTool(std::unique_ptr<ITool> a_pTool);
  void DeletePrimitive();

private:
  std::shared_ptr<CEditorModel> m_pModel;
  std::shared_ptr<IPrimitive> m_curPrimitive;
  CColor m_CurColor;
};

} /*end svg::*/