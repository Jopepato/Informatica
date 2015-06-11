#ifndef __EDI_LinkedBinaryTree_HPP__
#define __EDI_LinkedBinaryTree_HPP__

#include <cassert>
#include <edi_exports.hpp>
//#include <edi_LinkedStack.hpp>
#include <edi_BinaryTree.hpp>
#include <edi_LinkedBinaryTreeNode.hpp>

namespace edi 
{
 
//forward declaration
template <class T>
class LinkedOrderedBinaryTree;
  
/** @brief Linked implementation of the ADT BinaryTree.*/  
template<class T>
class EDI_API LinkedBinaryTree: public BinaryTree<T>
{
public:
  /** @name Makers*/
  /**@{*/
  /** @brief Makes a LinkedBinaryTree.
   * Time analysis: O(1).   
   * @post isEmpty().
   */
  LinkedBinaryTree() :
    _root (0), _isSubTree(false)
  {}
  
  /** @brief Destructor.
   * Time analysis: O(N) where N is the number of nodes in the tree.
   */
  virtual ~LinkedBinaryTree () 
  {
		flush();
  }
  /**@}*/

  /** @name Observers*/
  /**@{*/
  
  /** @brief Is the tree empty?.
   * Time analysis: O(1)
   * @return true if the tree is empty.
   */
  virtual bool isEmpty() const
  {
    return _root==0;
  }
  
  /** @brief Is this a sub-tree?.
   * Time analysis: O(1)
   * @return true if this is a sub-tree.
   */
  virtual bool isSubTree() const
  {
    return _isSubTree;
  }
  
  /** @brief Is this a leaf node?   
   * @return true if this is a leaf node.
   */
  virtual bool isLeaf() const
  {
    assert(not isEmpty());
    return _root->left()==0 and _root->right()==0;
  }
  
  /** @brief Is there a left sub-tree?.
   * Time analysis: O(1)
   * @return true if there is a left sub-tree.
   * @pre not isEmpty().
   */
  virtual bool hasLeftChild() const
  {
    assert(not isEmpty());
    return _root->left()!=0;
  }  
  
  /** @brief Is there a right sub-tree?.
   * Time analysis: O(1)
   * @return true if there is a right sub-tree.
   * @pre not isEmpty().
   */
  virtual bool hasRightChild() const
  {
    assert(not isEmpty());
    return _root->right()!=0;
  }    
  
  /** @brief Gets the left sub-tree.
   * Time Analysis: O(1)
   * @return a const pointer to the left sub-tree.
   * @pre not isEmpty().
   * @warning the user is responsible for deallocating memory.
   */
  virtual const LinkedBinaryTree<T>* leftSubTree() const
  {
    assert(not isEmpty());
    return new LinkedBinaryTree<T>(_root->left());
  }
  
  /** @brief Gets the right sub-tree.
   * Time Analysis: O(1)
   * @return a const pointer to the right sub-tree.   * 
   * @pre not isEmpty().
   * @warning the user is responsible for deallocating memory.
   */  
  virtual const LinkedBinaryTree<T>* rightSubTree() const
  {
    assert(not isEmpty());
    return new LinkedBinaryTree<T>(_root->right());
  }    
  
  /** @brief Gets the stored data int the current node.
   * Time analysis: O(1)
   * @return a const reference to the data.
   * @pre not isEmpty().
   */
  virtual const T& item() const 
  {
    assert (not isEmpty());
    return _root->item();
  }    
  /**@}*/

  /** @name Mutators*/
  /**@{*/
    
  /** @brief Gets the left sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the left sub-tree.
   * @pre not isEmpty().
   * @warning the user is responsible for deallocating memory.
   */
  virtual LinkedBinaryTree<T>* leftSubTree()
  {
    assert(not isEmpty());
    return new LinkedBinaryTree<T>(_root->left());
  }
  
  /** @brief Gets the right sub-tree.
   * Time Analysis: O(1)
   * @return a pointer to the right sub-tree.
   * @pre not isEmpty().
   * @warning the user is responsible for deallocating memory.
   */  
  virtual LinkedBinaryTree<T>* rightSubTree()
  {
    assert(hasRightChild());
    return new LinkedBinaryTree<T>(_root->right());
  }  
  
  /** @brief Sets the data stored in current.
   * Time analysis: O(1)
   * @arg[in] it is the data to be stored.
   * @pre not isEmpty().
   */
  virtual void setItem(const T& it)
  {
    assert(not isEmpty());
    _root->setItem(it);
  }
  
  /** @brief Create the root.
   * Time analysis: O(1)   
   * @pre isEmpty().
   * @pre not isSubTree().
   * @post not hasRightChild().
   * @post not hasLeftChild().
   */
  virtual void createRoot(const T& it)
  {
    assert(isEmpty());
    assert(not isSubTree());
    _root = new LinkedBinaryTreeNode<T>(it, 0, 0);    
  }  
  
  /** @brief Create the right sub-tree.
   * Time analysis: O(1)
   * @pre not isEmpty().
   * @pre not hasRightChild().
   * @post hasRightChild().
   */
  virtual void createRightSubTree(const T& it)
  {
    assert(not isEmpty());
    assert(not hasRightChild());
    _root->setRight(new LinkedBinaryTreeNode<T>(it, 0, 0));
    assert(hasRightChild());
  }
  
  /** @brief Create the left sub-tree.
   * Time analysis: O(1)
   * @pre not isEmpty().
   * @pre not hasLeftChild().
   * @post hasLeftChild().
   */
  virtual void createLeftSubTree(const T& it)
  {
    assert(not isEmpty());
    assert(not hasLeftChild());
    _root->setLeft(new LinkedBinaryTreeNode<T>(it, 0, 0));
    assert(hasLeftChild());
  }
  
		/** @brief Deallocate the tree.*/
		void flush ()
		{
			if (not isEmpty() and not isSubTree())
			{
				_root->deepFree();
				delete _root;
				_root = 0;
			}
		}
        
  /**@}*/  
private:
  
  //Avoid copy constructor and assign operator.
  LinkedBinaryTree(const LinkedBinaryTree<T>& o) {};
  LinkedBinaryTree<T>& operator=(const LinkedBinaryTree<T>* other) {return *this;}

protected:  
  
  /** @brief Makes a sub-tree.*/
  LinkedBinaryTree (LinkedBinaryTreeNode<T>* root)
  : _root(root), _isSubTree(true)
  {}
  
  /** @brief Makes a sub-tree.*/
  LinkedBinaryTree (const LinkedBinaryTreeNode<T>* root)
  : _root(const_cast<LinkedBinaryTreeNode<T>*>(root)), _isSubTree(true)
  {}
  /** @brief allow rw access to the root node.*/
  virtual LinkedBinaryTreeNode<T> * root() {return _root;}
  /** @brief allow ro access to the root node.*/
  virtual const LinkedBinaryTreeNode<T> * root() const {return _root;}
  /** @brief set the root node.*/
  virtual void setRoot(LinkedBinaryTreeNode<T> * r) { _root=r;}
  
private:  
  friend class LinkedOrderedBinaryTree<T>;
  LinkedBinaryTreeNode<T> * _root;
  bool _isSubTree;
};
}
#endif //__EDI_LinkedBinaryTree_HPP__