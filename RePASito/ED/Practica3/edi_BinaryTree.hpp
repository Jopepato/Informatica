#ifndef __EDI_BinaryTree_HPP__
#define __EDI_BinaryTree_HPP__

#include <cassert>
#include <memory>
#include "edi_exports.hpp"

namespace edi 
{
/** @brief ADT Binary tree.*/  
template<class T>
class EDI_API BinaryTree
{
public:
  /** @name Makers*/
  /**@{*/
  
  /** @brief Destructor.*/
  virtual ~BinaryTree (){}
  /**@}*/

  /** @name Observers*/
  /**@{*/
  
  /** @brief Is the tree empty?.
   * @return true if the tree is empty.
   */
  virtual bool isEmpty() const = 0;
  
  /** @brief Is this a sub-tree?.   
   * @return true if this is a sub-tree.
   */
  virtual bool isSubTree() const = 0;
  
  /** @brief Is this a tree without any childs?   
   * @return true if this is a leaf tree.
   */
  virtual bool isLeaf() const = 0;  
  
  /** @brief Has current got a left child?
   * @return true if current has got a left child.
   * @pre not isEmpty()
   */
  virtual bool hasLeftChild() const = 0;
  
  /** @brief Has current got a right child?
   * @return true if current has got a right child.
   * @pre not isEmpty()
   */
  virtual bool hasRightChild() const = 0;
    
  /** @brief Gets the stored data int the current node.   
   * @return a const reference to the data.
   */
  virtual const T& item() const = 0;
  
  /** @brief Gets the left sub-tree.   
   * @return a const pointer to the left sub-tree.
   * @pre not isEmpty().
   */
  virtual const BinaryTree<T>* leftSubTree() const  =0;
  
  /** @brief Gets the right sub-tree.
   * @return a const pointer to the right sub-tree.
   * @pre not isEmpty().
   */  
  virtual const BinaryTree<T>* rightSubTree() const = 0;
    
  /**@}*/

  /** @name Mutators*/
  /**@{*/

  /** @brief Gets the left sub-tree.
   * @return a pointer to the left sub-tree.
   * @pre not isEmpty().
   */
  virtual BinaryTree<T>* leftSubTree() = 0;
  
  /** @brief Gets the right sub-tree.   
   * @return a pointer to the right sub-tree.
   * @pre not isEmpty().
   */  
  virtual BinaryTree<T>* rightSubTree() = 0;  
    
  /** @brief Sets the data stored in current.
   * @arg[in] it is the data to be stored.
   * @pre not isEmpty().
   */
  virtual void setItem(const T& it) = 0;
  
  /** @brief Create the root node.   
   * @arg[in] it is the data stored in the node.
   * @pre isEmpty().
   * @pre not isSubTree().
   * @post not hasRightChild().
   * @post not hasLeftChild().   
   */
  virtual void createRoot(const T& it) = 0;  
  
  /** @brief Create the right child.
   * @arg[in] it is the data stored in the node.
   * @pre not isEmpty().
   * @pre not hasRightChild().
   * @post hasRightChild(). 
   */
  virtual void createRightSubTree(const T& it) = 0;
  
  /** @brief Create the left child.
   * @arg[in] it is the data stored in the node.   
   * @pre not isEmpty().
   * @pre not hasLeftChild().
   * @post hasLeftChild().
   */
  virtual void createLeftSubTree(const T& it) = 0;
  
  /**@}*/  
};

/** @addtogroup BTUtils Binary Tree Utilities.
 * @ingroup edi
 * @{
 */

/** @brief Carries out a post order traversal through the tree.
 * This template makes use of a Functor class with the interface:
 * 
 * bool operator()(const T& t) method.
 *  
 * @arg[in] t is the tree.
 * @arg[in] f is a functor object with the 
 * @return false if the process must stop or true in other case.
 */
template <class T, class Functor>
bool postorderBinaryTreeProcessor(const BinaryTree<T>* t, Functor& f)
{
  bool retVal=true;
  
  if (not t->isEmpty())
  {
    if (t->hasLeftChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->leftSubTree());
      retVal = postorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);
    }
    if (retVal and t->hasRightChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->rightSubTree());
      retVal = postorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);
    }
    if (retVal)
      retVal = f(t->item());      
  }
  
  return retVal;
}

/** @brief Carries out an in order traversal through the tree.
 * This template makes use of a Functor class with the interface:
 * 
 * bool operator()(const T& t) method.
 *  
 * @arg[in] t is the tree.
 * @arg[in] f is a functor object with the 
 * @return false if the process must stop or true in other case.
 */
template <class T, class Functor>
bool inorderBinaryTreeProcessor(const BinaryTree<T>* t, Functor& f)
{
  bool retVal=true;
  
  if (not t->isEmpty())
  {
    if (t->hasLeftChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->leftSubTree());
      retVal = inorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);
    }
    if (retVal)
      retVal = f(t->item());
    if (retVal and t->hasRightChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->rightSubTree());
      retVal = inorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);
    }
  }
  
  return retVal;
}

/** @brief Carries out a pre order traversal through the tree.
 * This template makes use of a Functor class with the interface:
 * 
 * bool operator()(const T& t) method.
 *  
 * @arg[in] t is the tree.
 * @arg[in] f is a functor object with the 
 * @return false if the process must stop or true in other case.
 */
template <class T, class Functor>
bool preorderBinaryTreeProcessor(const BinaryTree<T>* t, Functor& f)
{
  bool retVal=true;
  
  if (not t->isEmpty())
  {    
    retVal = f(t->item());
    if (retVal and t->hasLeftChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->leftSubTree());
      retVal = preorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);
    }
    if (retVal and t->hasRightChild())
    {
      std::auto_ptr<const BinaryTree<T> > ptr(t->rightSubTree());
      retVal = preorderBinaryTreeProcessor<T, Functor>(ptr.get(), f);      
    }
  }
  
  return retVal;
}
/** @}*/
}
#endif //__EDI_BinaryTree_HPP__