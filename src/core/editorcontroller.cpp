#include "core/editorcontroller.h"

namespace svg {
  
CEditorController::CEditorController(std::shared_ptr<CEditorModel> a_pModel)
  : m_pModel(std::move(a_pModel))
{}


void CEditorController::Open(const std::string& path) 
{
  m_pModel->Open(path);
}

void CEditorController::Clear() 
{
  m_pModel->Clear();
}

void CEditorController::Save() const
{
  m_pModel->Save();
}

void CEditorController::Run()
{

}

void CEditorController::SetColor(CColor a_Color)
{
  m_CurColor = a_Color;
}

void CEditorController::SetTool(std::unique_ptr<ITool> a_pTool)
{
  if (a_pTool) {
    m_curPrimitive = a_pTool->Create();
    m_curPrimitive->SetColor(m_CurColor);

    m_pModel->AddPrimitive(m_curPrimitive);
  }    
}

void CEditorController::DeletePrimitive() 
{
  
}

} /*end svg::*/