#ifndef __EDI_OrderedBinaryTree_HPP__
#define __EDI_OrderedBinaryTree_HPP__

#include <cassert>
#include <edi_exports.hpp>
#include <edi_BinaryTree.hpp>

namespace edi 
{
/** @brief The ADT OrderedBinaryTree.*/  
template<class T>
class EDI_API OrderedBinaryTree: public edi::BinaryTree<T>
{
public:
  /** @name Makers*/
  /**@{*/
  /** @brief Destructor.*/
  OrderedBinaryTree() {}
  virtual ~OrderedBinaryTree() {}
  /**@}*/

  /** @name Observers*/
  /**@{*/
              
  /** @brief Is there a current item?
   * Time analysis: O(1)
   */
  virtual bool existsItem() const = 0;
	
   /** @brief Gets the stored data int the current node.
   * Time analysis: O(1)
   * @return a const reference to the data.
   * @pre not isEmpty().
	 * @pre existItem().
   */
  virtual const T& item() const = 0;
	
  /** @brief Does the tree contain x?
   * Time analysis: O(h), h is the height of the tree, worst case.
   * @arg[in] x is the value to be searched.
   * @return true if the values is stored in the tree.
   */
  virtual bool has(const T& x) const = 0;
  
  /** @brief Gets the left sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the left sub-tree.
   * @pre not isEmpty().
   * @pre hasLeftChild()
   */
  virtual const OrderedBinaryTree<T>* leftSubTree() const = 0;
  
  /** @brief Gets the right sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the right sub-tree.
   * @pre not isEmpty().
   */  
  virtual const OrderedBinaryTree<T>* rightSubTree() const = 0;
    
  /**@}*/

  /** @name Mutators*/
  /**@{*/
  
  /** @brief Move current to the root of the tree.
   * Time analysis: O(1)
   */
  virtual void goToRoot() = 0;
  
  /** @brief Go to item x, if it is in the tree.
   * Time analysis: O(h), h is the height of the tree, worst case.
   * @arg[in] x is the value to be searched.
   */
  virtual void search(const T& x) = 0;
  
  /** @brief Insert x into the tree.
   * Time analysis: O(h), h is the height of the tree, worst case.
   * @arg[in] x is the value to be inserted.
   */
  virtual void insert(const T& x) = 0;
  
  /** @brief Remove current item from the tree.
   * Time analysis: O(h) where h is the height of the tree, worst case.
   * \pre existItem()
   * \post not has(prev item())
   */
  virtual void removeItem() = 0;
  
  /** @brief Gets the left sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the left sub-tree.
   * @pre not isEmpty().
   * @pre hasLeftChild()
   */
  virtual OrderedBinaryTree<T>* leftSubTree() = 0;
  
  /** @brief Gets the right sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the right sub-tree.
   * @pre not isEmpty().
   */  
  virtual OrderedBinaryTree<T>* rightSubTree() = 0;
  
  /**@}*/  
  
private:
  
  //Avoid copy constructor and assign operator.
  OrderedBinaryTree(const OrderedBinaryTree<T>& o) {};
  OrderedBinaryTree<T>& operator=(const OrderedBinaryTree<T>* other) {return *this;}
  
protected:  
      
  /** @name Redefined as private
   * Avoid some public inherited BinaryTree methods for users.
   * @{
   * 
   */
  virtual void createRightSubTree(const T& it) = 0;
  virtual void createLeftSubTree(const T& it) = 0;
  virtual void setItem(const T& it) = 0;
  virtual void createRoot(const T& it) = 0;
  /** @}*/
};

}
#endif //__EDI_OrderedBinaryTree_HPP__
