#pragma once

#include "common/observer.h"
#include "editormodel.h"
#include "editorcontroller.h"
#include "gui/button.h"
#include "canvas/consolecanvas.h"

#include <memory>
#include <assert.h>

namespace svg {

 /**
 * @brief Class vector editor viewer
 */ 
class CEditorView : public IObserver
{
public:
  explicit CEditorView(
    std::shared_ptr<CEditorModel> a_pModel, 
    std::shared_ptr<CEditorController> a_pController
  );
  ~CEditorView() = default;

  void Update() override;

  void OnClickBtnOpen();
  void OnClickBtnSave();
  void OnClickBtnClear();

  void OnClickBtnColor();

  void OnClickBtnToolPoint();
  void OnClickBtnToolLine();
  void OnClickBtnToolDelete();

private:
  std::shared_ptr<CEditorModel> m_pModel;
  std::shared_ptr<CEditorController> m_pController;

  std::shared_ptr<ICanvas> m_pCanvas;
  
  std::unique_ptr<CButton> m_pBtnOpen = std::make_unique<CButton>(std::string("Open"));
  std::unique_ptr<CButton> m_pBtnSave = std::make_unique<CButton>(std::string("Save"));
  std::unique_ptr<CButton> m_pBtnClear = std::make_unique<CButton>(std::string("Clear"));

  std::unique_ptr<CButton> m_pBtnColor = std::make_unique<CButton>(std::string("Color"));

  std::unique_ptr<CButton> m_pBtnToolPoint = std::make_unique<CButton>(std::string("Point"));
  std::unique_ptr<CButton> m_pBtnToolLine = std::make_unique<CButton>(std::string("Line"));
  std::unique_ptr<CButton> m_pBtnToolDelete = std::make_unique<CButton>(std::string("Delete"));
};

} /*end svg::*/