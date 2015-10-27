#ifndef __EDI_LinkedNode_HPP__
#define __EDI_LinkedNode_HPP__
 
#include "edi_exports.hpp"
 
namespace edi
{
 
  /** @brief Implements the LinkedNode[T] ADT used in linked versions of lineal data structured. */
  template <class T>
  class EDI_API LinkedNode
  {
    public:
      /** @name Makers*/
      /**@{*/
  
      /** @brief Makes a LinkedNode.
      * Time analysis: O(1).
      * @arg[in] item is the data to be stored.
      * @arg[in] next is the link with the next element.
      */
      LinkedNode(const T& item, LinkedNode<T>* next, LinkedNode<T>* previous) :
      _data (item), _next(next), _previous(previous)
      {}
 
      /** @brief Destroy the node.
      * Time analysis: O(1).
      * \warning The onwer data structure will have the responsability of deallocating the linked memory.
      */
      virtual ~LinkedNode () {}
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
      /** @brief Gets a link to next element.
      * Time analysis: O(1)
      * @return a const pointer to next element.
      */
      virtual const LinkedNode<T>* next() const
      {
				return _next;
      }
      /** @brief Gets a link to previous element.
      * Time analysis: O(1)
      * @return a const pointer to previous element.
      */
      virtual const LinkedNode<T>* previous() const
      {
        return _previous;
      }
    /**@}*/
  
    /** @name Mutators*/
    /**@{*/
      /** @brief Sets the link to next element.
      * @arg[in] next is a reference to next operator.
      * Time analysis: O(1)
      */
      virtual void setNext(LinkedNode<T>* next)
      {
				_next=next;
      }
      /** @brief Sets the link to previous element.
      * @arg[in] previous is a reference to previous operator.
      * Time analysis: O(1)
      */
      virtual void setPrevious(LinkedNode<T>* previous)
      {
        _previous=previous;
      }

      /** @brief Gets a link to next element.
      * Time analysis: O(1)
      * @return a pointer to next element.
      */
      virtual LinkedNode<T>* next()
      {
				return _next;	
      }
      /** @brief Gets a link to previous element.
      * Time analysis: O(1)
      * @return a pointer to previous element.
      */
      virtual LinkedNode<T>* previous()
      {
        return _previous;
      }
      /** @brief Sets the stored data.
      * Time analysis: O(1)
      * @arg[in] item is the data to be stored.
      */
      virtual void setItem (const T& item)
      {
				_data=item;
      }
    /**@}*/
    private:
      T _data;
      LinkedNode<T> * _next;
      LinkedNode<T> * _previous;
  };
  
} //namespace

#endif //__EDI_LinkedNode_HPP__