#ifndef __EDI_LinkedBinaryTreeNode_HPP__
#define __EDI_LinkedBinaryTreeNode_HPP__

#include "edi_exports.hpp"

namespace edi 
{

/** @brief Implement the LinkedBinaryTreeNode ADT. */
template <class T>
class EDI_API LinkedBinaryTreeNode
{
public:
  /** @name Makers*/
  /**@{*/
  /** @brief Makes a LinkedBinaryTreeNode.
   * Time analysis: O(1).   
   * @arg[in] item is the data to be stored.
   * @arg[in] left is the link to the left child.
   * @arg[in] right is the link to the right child.
   */
  LinkedBinaryTreeNode(const T& item, 
		       LinkedBinaryTreeNode<T>* left=0,
		       LinkedBinaryTreeNode<T>* right=0) :
    _left(left), _right(right), _data (item)
  {}
  
  /** @brief Destructor.
   * Time analysis: O(n) where n is the number of nodes in the tree.
   */
  virtual ~LinkedBinaryTreeNode () 
  {
    //We will allow to reference the same node from different pointers,
    //so we will not deallocate childs here.
  }
  /**@}*/

  /** @name Observers*/
  /**@{*/
  /** @brief Gets the stored data.
   * Time analysis: O(1)
   * @return a const reference to the data.
   */
  virtual const T& item() const 
  {
    return _data;
  }
  /** @brief Gets the link to left child.
   * Time analysis: O(1)
   * @return a const pointer to left child.
   */
  virtual const LinkedBinaryTreeNode<T>* left() const
  {
    return _left;
  }
  /** @brief Gets the link to right child.
   * Time analysis: O(1)
   * @return a const pointer to right child.
   */
  virtual const LinkedBinaryTreeNode<T>* right() const
  {
    return _right;
  }  
  /**@}*/

  /** @name Mutators*/
  /**@{*/
  
  /** @brief Gets the link to left child.
   * Time analysis: O(1)
   * @return a pointer to left child.
   */
  virtual LinkedBinaryTreeNode<T>* left()
  {
    return _left;
  }
  
  /** @brief Gets the link to right child.
   * Time analysis: O(1)
   * @return a pointer to right child.
   */
  virtual LinkedBinaryTreeNode<T>* right()
  {
    return _right;
  }
  
  /** @brief Sets the link to left child.
   * Set the left child possibly freeing the memory for the old subtree.
   * Time analysis: O(n) where N is the number of nodes below the node.
   * @arg[in] left is a reference to new left node.
   * 
   */   
  virtual void setLeft(LinkedBinaryTreeNode<T>* left)
  {
    _left=left;
  }
  
  /** @brief Sets the link to right child.
   * Set the right child possibly freeing the memory for the old subtree.
   * Time analysis: O(n) where N is the number of nodes below the node.
   * @arg[in] right is a reference to new right node.
   * 
   */   
  virtual void setRight(LinkedBinaryTreeNode<T>* right)
  {
    _right=right;
  }  
  
  /** @brief Sets the stored data.   
   * Time analysis: O(1)
   * @arg[in] item is the data to be stored.
   */
  virtual void setItem (const T& item) 
  {
    _data=item;
  }  
  
  /** @brief Flushes the node.
   * Time analysis: O(N) where N is the number of nodes bellow the node.
   * @post left()==0;
   * @post right()==0;
   */
  virtual void deepFree()
  {
    if (_left)
    {
      _left->deepFree();
      delete _left;
      _left=0;
    }     
    if (_right)
    {
      _right->deepFree();
      delete _right;
      _right=0;
    }     
  }
  /**@}*/
  
private:
  
  //Avoid assign operator.
  LinkedBinaryTreeNode<T>& operator=(const LinkedBinaryTreeNode<T>& o) {return *this;}    

  //Avoid copy constructor.
  LinkedBinaryTreeNode(const LinkedBinaryTreeNode<T>& o) {}


    LinkedBinaryTreeNode<T> * _left;
    LinkedBinaryTreeNode<T> * _right;
    T _data;
};

  
} //namespace

#endif //__EDI_LinkedBinaryTreeNode_HPP__
