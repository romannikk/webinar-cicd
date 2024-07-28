#include "core/editormodel.h"

namespace svg {

void CEditorModel::New()
{
  Clear();
}

void CEditorModel::Open(const std::string& a_strPath) 
{  
  if (a_strPath.empty()) {

  }
  m_strPath = a_strPath;
  NotifyUpdate();
}

void CEditorModel::Save() const
{
  if (m_strPath.empty()) {
    
  }
}

void CEditorModel::Clear()
{
  m_vPrimitives.clear();
  m_strPath.clear();
}

void CEditorModel::AddPrimitive(std::shared_ptr<IPrimitive> a_pPrimitive)
{
  if (a_pPrimitive) {
    
  }
  NotifyUpdate();
}

void CEditorModel::DeletePrimitive(std::shared_ptr<IPrimitive> a_pPrimitive)
{
  if (a_pPrimitive) {

  }
  NotifyUpdate();
}

void CEditorModel::Draw(std::shared_ptr<ICanvas> a_pCanvas)
{
  for (auto& pPrimitive : m_vPrimitives) {
    pPrimitive->Draw(a_pCanvas);
  }
}

} /*end svg::*/