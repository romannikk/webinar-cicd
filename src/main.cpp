#include "core/editormodel.h"
#include "core/editorview.h"
#include "core/editorcontroller.h"

#include <iostream>
#include <memory>

int main(int, const char**) 
{
  auto pModel = std::make_shared<svg::CEditorModel>();  
  auto pController = std::make_shared<svg::CEditorController>(pModel);
  auto pView = std::make_shared<svg::CEditorView>(pModel, pController);
  pModel->Subscribe(pView);
  pController->Run();
  pModel->Unsubscribe(pView);
  return 0;
}