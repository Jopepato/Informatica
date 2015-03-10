#ifndef NODO_H_
#define NODO_H_

namespace ed
{

  /** @brief Implements the LinkedNode[T] ADT used in linked versions of lineal data structured. */
  template <class T>
  class doubleLinkedNode
  {
    public:
      /** @name Makers*/
      /**@{*/

      /** @brief Makes a LinkedNode.
      * Time analysis: O(1).
      * @arg[in] item is the data to be stored.
      * @arg[in] next is the link with the next element.
      */
      doubleLinkedNode(const T& item, LinkedNode<T>* next) :
      _data (item), _next(next)
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
      /** @brief Gets a link to next element.
      * Time analysis: O(1)
      * @return a pointer to next element.
      */
      virtual LinkedNode<T>* next()
      {
        return _next;
      }

      /** @brief Sets the link to next element.
      * @arg[in] next is a reference to next operator.
      * Time analysis: O(1)
      */
      virtual void setPrevious(LikedNode<T>* previous){
        previous_ = previous;
      }
      /** @brief Gets a link to previous element.
      * Time analysis: O(1)
      * @return a pointer to previous element.
      */
      virtual LinkedNode<T>* previous(){
        return previous_;
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

#endif
