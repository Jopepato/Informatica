#ifndef __EDI_LinkedOrderedBinaryTree_HPP__
#define __EDI_LinkedOrderedBinaryTree_HPP__

#include <cassert>
#include <memory>
#include <edi_exports.hpp>
//#include <edi_LinkedStack.hpp>
#include <edi_OrderedBinaryTree.hpp>
#include <edi_LinkedBinaryTree.hpp>

namespace edi 
{
/** @brief Linked implementation of the ADT OrderedBinaryTree.*/  
template<class T>
class EDI_API LinkedOrderedBinaryTree: public edi::OrderedBinaryTree<T>
{
public:
	/** @name Makers*/
	/**@{*/
	/** @brief Makes a LinkedOrderedBinaryTree.
	* Time analysis: O(1).   
	* @post isEmpty().
	*/
	LinkedOrderedBinaryTree() :
		_tree(), _curr(0), _prev(0)
	{
		assert((_invariantCount=0, checkInvariants()));
	}
	
	/** @brief Destroys a LinkedOrderedBinaryTree.
	* Time analysis: O(n).   
	* @post isEmpty().
	*/
	~LinkedOrderedBinaryTree()
	{
		flush();
		assert((_invariantCount=0, checkInvariants()));
	}
	/**@}*/

	/** @name Observers*/
	/**@{*/
	
	virtual bool isEmpty() const
	{
		return tree()->isEmpty();
	}
	virtual bool isSubTree() const 
	{
		return tree()->isSubTree();
	}
	virtual bool isLeaf() const
	{
		return tree()->isLeaf();
	}
	virtual bool hasLeftChild() const 
	{
		return tree()->hasLeftChild();
	}
	virtual bool hasRightChild() const 
	{
		return tree()->hasRightChild();
	}
						
	virtual const T& item() const 
	{    
		assert (existsItem());
		return curr()->item();
	}
		
	/** @brief Is there a current item?
	* Time analysis: O(1)
	*/
	virtual bool existsItem() const 
	{
		return curr() != 0;
	}
	
	/** @brief Does the tree contain x?
	* Time analysis: O(h), h is the height of the tree, worst case.
	* @arg[in] x is the value to be searched.
	* @return true if the values is stored in the tree.
	*/
	virtual bool has(const T& x) const
	{
		bool retVal=false;
		if (not tree()->isEmpty())
		{
			LinkedOrderedBinaryTree<T> * _this=const_cast<LinkedOrderedBinaryTree<T> *>(this);
			LinkedBinaryTreeNode<T>* saveCurr = _this->curr();
			LinkedBinaryTreeNode<T>* savePrev = _this->prev();
			_this->search(x);
			retVal=existsItem();
			_this->setCurr(saveCurr);
			_this->setPrev(savePrev);
		}
		return retVal;
	}
	/**@}*/

	/** @name Mutators*/
	/**@{*/
	
	/** @brief Move current to the root of the tree.
	* Time analysis: O(1)
	*/
	virtual void goToRoot()
	{
		setPrev(0);
		setCurr(root());
	}
	
	/** @brief Go to item x, if it is in the tree.
	* Time analysis: O(h), h is the height of the tree, worst case.
	* @arg[in] x is the value to be searched.
	*/
	virtual void search(const T& x)
	{
		assert(checkInvariants()&& ++_invariantCount);
		bool found=false;
		goToRoot();
		while (not (found or _curr==0))
		{
			if (x<curr()->item())
			{
				setPrev(curr());
				setCurr(curr()->left());
			}
			else if (x>curr()->item())
			{
				setPrev(curr());
				setCurr(curr()->right());
			}
			else
				found=true;
		}
		assert(--_invariantCount || checkInvariants());
	}
	
	/** @brief Insert x into the tree.
	* Time analysis: O(h), h is the height of the tree, worst case.
	* @arg[in] x is the value to be inserted.
	*/
	virtual void insert(const T& x)
	{
		assert(checkInvariants()&& ++_invariantCount);
		//This implementation uses the rescursive structure of a tree
		//however it is not very efficient in C++ due to the dynamic
		//memory management overload.
//     if (tree()->isEmpty())
//       createRoot(x);   
//     else if (x<root()->item())
//     {      
//       if (tree()->hasLeftChild())
// 	std::unique_ptr<edi::LinkedOrderedBinaryTree<T> > (leftSubTree())->insert(x);
//       else
// 	tree()->createLeftSubTree(x);
//     }
//     else if (x>root()->item())
//     {
//       if (tree()->hasRightChild())
// 	std::unique_ptr<edi::LinkedOrderedBinaryTree<T> >(rightSubTree())->insert(x);
//       else
// 	tree()->createRightSubTree(x);      
//     }
		if (tree()->isEmpty())
			createRoot(x);
		else
		{
			LinkedBinaryTreeNode<T>* savedCurr = curr();
			LinkedBinaryTreeNode<T>* savedPrev = prev();      
			search(x);
			if (not existsItem())
			{
				assert(prev()); //This is an invariant.     
				if (x < prev()->item())	
					prev()->setLeft(new edi::LinkedBinaryTreeNode<T>(x));	
				else	
					prev()->setRight(new edi::LinkedBinaryTreeNode<T>(x));
			}
			else
				setItem(x); //update node data.
			setCurr(savedCurr);
			setPrev(savedPrev);	
		}
		
		assert(--_invariantCount || checkInvariants());
	}
	
	/** @brief Remove current item from the tree.
	* Time analysis: O(h) where h is the height of the tree, worst case.
	* \pre existItem()
	* \post not has(prev item())
	*/
	virtual void removeItem()
	{
		assert(existsItem());
		assert(checkInvariants() && ++_invariantCount);
		edi::LinkedBinaryTreeNode<T> * replaceNode=0;
		edi::LinkedBinaryTreeNode<T> * savePrev=0;
		edi::LinkedBinaryTreeNode<T> * saveCurr=0;    
		bool replaceNodeFound=false;    
		if (not _curr->right()) //Node to remove has not rightSubTree
		{
			replaceNode=_curr->left();
			replaceNodeFound=true;
		}
		else if (not _curr->left()) //Node to remove has not leftSubTree
		{
			replaceNode=_curr->right();
			replaceNodeFound=true;
		}
		
		if (replaceNodeFound)
		{      
			if (_prev==0)		  
				setRoot(replaceNode);	
			else if (_prev->left()==_curr) //Node to remove is leftSubTree
				_prev->setLeft(replaceNode);
			else //Node to remove is rigthSubTree
				_prev->setRight(replaceNode);
			delete _curr; //free the node to remove
			_curr=replaceNode; //_curr is the repalceNode
		}
		else //Node to remove has two subtrees.
		{
			savePrev=_prev;
			saveCurr=_curr;
			findInorderPrecessor(); //seek the highest of the leftSubTree
			saveCurr->setItem(_curr->item());
			removeItem(); //Remove the highest of the leftSubTree. 
			_prev=savePrev;
			_curr=saveCurr;
		}
		assert(--_invariantCount || checkInvariants());    
	}
	
	/** @brief Remove current all the items from the tree.
	* Time analysis: O(n) where n is the number of nodes of the tree, worst case.
	* \post isEmpty()
	*/
	virtual void flush()
	{
		assert(checkInvariants()&& ++_invariantCount);
		tree()->flush();
		assert(--_invariantCount || checkInvariants());
	}
	
	
	/**@}*/  
private:
	
	//Avoid copy constructor and assign operator.
	LinkedOrderedBinaryTree(const LinkedOrderedBinaryTree<T>& o) {};
	LinkedOrderedBinaryTree<T>& operator=(const LinkedOrderedBinaryTree<T>* other) {return *this;}
	
protected:  
	
	virtual const LinkedOrderedBinaryTree<T>* leftSubTree() const 
	{
		assert(not isEmpty());
		assert(hasLeftChild());
		return new LinkedOrderedBinaryTree<T>(root()->left());
	}
	
	virtual const LinkedOrderedBinaryTree<T>* rightSubTree() const 
	{
		assert(not isEmpty());
		assert(hasRightChild());    
		return new LinkedOrderedBinaryTree<T>(root()->right());
	}

	virtual LinkedOrderedBinaryTree<T>* leftSubTree()
	{
		assert(not tree()->isEmpty());
		assert(tree()->hasLeftChild());
		return new LinkedOrderedBinaryTree<T>(root()->left());
	}
	
	virtual LinkedOrderedBinaryTree<T>* rightSubTree()
	{
		assert(not tree()->isEmpty());
		assert(tree()->hasRightChild());
		return new LinkedOrderedBinaryTree<T>(root()->right());
	}  
	
	
	/** @brief Find the in order precessor of current.
	* Time Analysis: O(h), where h is the height of the tree. Worst case.
	*/
	void findInorderPrecessor()
	{
		assert(existsItem());
		if (curr()->left())
		{
			setPrev(curr());
			setCurr(curr()->left());
			while(curr()->right())
			{
				setPrev(curr());
				setCurr(curr()->right());
			}
		}
	}

	/** @brief Get the root node.
	* is convenence function to void write the templete prefix all time.
	*/
	virtual LinkedBinaryTreeNode<T> * root() {return tree()->root();}    
	/** @brief Get the root node.
	* is convenence function to void write the templete prefix all time.
	*/  
	virtual const LinkedBinaryTreeNode<T> * root() const {return tree()->root();} 
	/** @brief Set the root node.
	* is convenence function to void write the templete prefix all time.
	*/  
	virtual void setRoot(LinkedBinaryTreeNode<T> * newRoot) { tree()->setRoot(newRoot);}
	
	/** @brief Makes an ordered sub-tree.*/
	LinkedOrderedBinaryTree (LinkedBinaryTreeNode<T>* root)
	: _tree(root), _curr(root), _prev(0)
	{
		assert((_invariantCount=0,  checkInvariants()));
	}
	
	/** @brief Makes an ordered sub-tree.*/
	LinkedOrderedBinaryTree (const LinkedBinaryTreeNode<T>* root)
	: _tree(const_cast<LinkedBinaryTreeNode<T>*>(root)), _curr(const_cast<LinkedBinaryTreeNode<T>*>(root)), _prev(0)
	{
		assert((_invariantCount=0, checkInvariants()));
	}
		
	virtual void createRightSubTree(const T& it)
	{
		tree()->createRightSubTree(it);
	}
	virtual void createLeftSubTree(const T& it)
	{
		tree()->createLeftSubTree(it);
	}
	virtual void setItem(const T& it) {tree()->setItem(it);}
	virtual void createRoot(const T& it) {tree()->createRoot(it); setCurr(root()); setPrev(0);}
	virtual LinkedBinaryTreeNode<T>* curr () { return _curr;}
	virtual const LinkedBinaryTreeNode<T>* curr () const { return _curr;}  
	virtual void setCurr(LinkedBinaryTreeNode<T>* curr) { _curr=curr;}
	virtual void setPrev(LinkedBinaryTreeNode<T>* prev) { _prev=prev;}
	virtual LinkedBinaryTreeNode<T>* prev () { return _prev;}
	virtual const LinkedBinaryTreeNode<T>* prev () const { return _prev;}
	virtual const LinkedBinaryTree<T>* tree() const {return &_tree;}
	virtual LinkedBinaryTree<T>* tree() {return &_tree;}
#ifndef NDEBUG
	//This class is used as example of Functor to check the invariant (inorderBinaryTreeProcessor is ordered).
	class CheckOrdering
	{
	public:
		CheckOrdering() :_isFirst(true), _lastItem(0) {}
		bool operator()(T const& t)
		{
			bool retVal=true;
			//check if it is the first item or is less than the last item (is ordered in a inorder processor 
			if (isFirst() or lastItem()<t) 																
				setLastItem(t); //t is the las item por the next node
			//it is not ordered, the invariant is not true
			else 
				retVal=false;
			return retVal;
		}
	protected:   
		bool isFirst() const {return _isFirst;}
		const T& lastItem() const {return *_lastItem;}
		void setLastItem(T const& t) {_lastItem=&t;_isFirst=false;}
	private:
		bool _isFirst;
		const T* _lastItem;
	};
	
	bool checkInvariants() const
	{
		bool retVal = true;
		if (_invariantCount == 0)
		{  
		LinkedOrderedBinaryTree<T> * _this=const_cast<LinkedOrderedBinaryTree<T> *>(this);
		LinkedBinaryTreeNode<T>* saveCurr = _this->curr();
		LinkedBinaryTreeNode<T>* savePrev = _this->prev();
		_this->setCurr(_this->root());
		_this->setPrev(0);
		//check the ordering is preserved.
		CheckOrdering f;
		retVal = edi::inorderBinaryTreeProcessor<T>(this, f); 
		_this->setCurr(saveCurr);
		_this->setPrev(savePrev);
		}
		return retVal;    
	}
	int _invariantCount;
#endif //NDEBUG
private:
	LinkedBinaryTree<T> _tree; /** @< the linked tree.*/ 
	LinkedBinaryTreeNode<T> * _curr; /** @< the current node.*/
	LinkedBinaryTreeNode<T> * _prev; /** @< the current's parent.*/
};

}
#endif //__EDI_LinkedOrderedBinaryTree_HPP__
