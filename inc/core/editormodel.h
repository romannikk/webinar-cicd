#pragma once

#include "common/observer.h"
#include "primitives/iprimitive.h"
#include "canvas/icanvas.h"
#include <string>
#include <memory>

namespace svg {
  
 /**
 * @brief Class vector editor model
 */ 
class CEditorModel : public IObservable
{
public:
  CEditorModel() = default;
  ~CEditorModel() = default;

  /**
   * @brief Import a vector document from a file
   * @param a_strPath Path to document
   */
  void New();

  /**
   * @brief Open a vector document from a file
   * @param a_strPath Path to document
   */
  void Open(const std::string& a_strPath);

  /**
   * @brief Save current vector document to file
   */
  void Save() const;

  /**
   * @brief Clear current vector document to
   */
  void Clear();

  /**
   * @brief Add new primitive to vector document
   * @param a_pPrimitive shared pointer to IPrimitive
   */
  void AddPrimitive(std::shared_ptr<IPrimitive> a_pPrimitive);
  
  /**
   * @brief Delete primitive from vector document
   * @param a_pPrimitive shared pointer to IPrimitive
   */
  void DeletePrimitive(std::shared_ptr<IPrimitive> a_pPrimitive);

  /**
   * @brief Draw all primitives on canvas
   * @param a_pCanvas shared pointer to canvas
   */
  void Draw(std::shared_ptr<ICanvas> a_pCanvas);

private:
  std::vector<std::shared_ptr<IPrimitive>> m_vPrimitives;
  std::string m_strPath;
};

} /*end svg::*/