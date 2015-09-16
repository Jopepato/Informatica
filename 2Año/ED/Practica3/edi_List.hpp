#ifndef __EDI_List_HPP__
#define __EDI_List_HPP__

#include "edi_export.hpp"
 
namespace edi {
 
  /** @brief Abstrast template class to model the List[T] ADT.*/
  template <class T>
  class EDI_API List
  {
    public:
 
    /** @name Makers*/
    /**@{*/
      virtual ~List () {}
    /**@}*/
  
    /** @name Observers*/
    /**@{*/
      /** @brief Is the list empty?
      @return true if the list is empty.
      */
      virtual bool isEmpty() const = 0;
      /** @brief Is pos the last list's position?
      @return true if the list is empty.
      */
      virtual bool isLast(const int pos) const = 0;
      /** @brief Is pos a valid List's position?
      @return true if pos is a valid list's position.
      */
      virtual bool isValid (const int pos) const = 0;
      /** @brief Get the item at a given position.
      * @arg[in] pos is the list's position.
      * @return a const reference to the stored.
      * @pre isValid(pos)
      */
      virtual const T& item(const int pos) const = 0;
      /** @brief Find the position of a given item.
      * @arg[in] item is the data to be found.
      * @arg[in] from give a position to start the search.
      * @return -1 if it does not found or the item's position.
      * @pre isValid(from)
      * @post retVal>=0 implies isValid(retVal)
      * @post retVal>=0 implies item(retVal)=item
      */
      virtual int findItem(const T& item, const int from) const = 0;
    /**@}*/
 
    /** @name Mutators*/
    /**@{*/
      /** @brief Inserts item in an ordered way.
      * @arg[in] pos is the list's position to insert before.
      * @arg[in] item is the item to store.
      * @pre isValid(pos).
      * @post isValid(pos+1).
      * @post not isEmpty().
      * @post item(pos)=item.
      * @post item(pos+1)=old.item(pos)
      */
      virtual void inserta(const T& item) = 0;
      /** @brief Deletes the given position.
      * @arg[in] pos is the position to be deleted.
      * @pre not isEmpty()
      * @post old.isLast(pos) implies not isValid(pos).
      * @post pos=0 and old.isLast(pos) implies isEmpty().
      * @post not old.isLast(pos) implies item(pos)=old.item(pos+1)
      */
      virtual void deletePosition(const int pos) = 0;
      /**@}*/
  };
 
} //namespace
 
#endif //__EDI_List_HPP__