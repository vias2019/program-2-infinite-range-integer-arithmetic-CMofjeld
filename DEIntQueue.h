/** 
 * @file DEIntQueue.h
 * @brief Class definition for DEIntQueue, a link-based double-ended queue that stores integers
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include <iostream>  // Stream I/O
#include <exception> // Exceptions

class DEIntQueue {
public:
   //PUBLIC METHODS
   /** DEIntQueue()
    * @brief   Default constructor.
    * @post    This queue is empty and its size is 0.
   */
   DEIntQueue() : size(0), head(nullptr), tail(nullptr) { }

   /** DEIntQueue(const DEIntQueue&)
    * @brief   Copy constructor.
    * @param   toCopy   The queue being copied
    * @post    This queue contains the same entries in the same order as toCopy.
    *          The new entries are deep copies.
   */
   DEIntQueue(const DEIntQueue& toCopy);

   /** operator=(const DEIntQueue&)
    * @brief   Assignment operator.
    * @param   toCopy   The queue being copied
    * @post    This queue contains the same entries in the same order as toCopy.
    *          The new entries are deep copies. If this queue is the same object
    *          as toCopy, it is unchanged.
   */
   DEIntQueue& operator=(const DEIntQueue& toCopy);

   /** ~DEIntQueue()
    * @brief   Destructor.
    * @post    This queue is empty and all dynamically allocated memory has been
    *          returned to the system.
   */
   virtual ~DEIntQueue();

   /** pushFront(int)
    * @brief   Adds an integer to the front of this queue.
    * @param   newItem  The integer being added to this queue.
    * @post    A new node has been inserted at the front of this
    *          queue with newItem as its data entry.
   */
   void pushFront(int newItem);

   /** pushBack(int)
    * @brief   Adds an integer to the back of this queue.
    * @param   newItem  The integer being added to this queue.
    * @post    A new node has been inserted at the back of this
    *          queue with newItem as its data entry.
   */
   void pushBack(int newItem);

   /** front()
    * @brief   Returns the first integer in this queue.
    * @pre     There is at least one integer in this queue.
    * @post    The returned value is equal to the first integer in this queue.
    * @return  The first integer in this queue.
    * @throw   std::logic_error if this queue is empty.
   */
   int front() const;

   /** back()
    * @brief   Returns the last integer in this queue.
    * @pre     There is at least one integer in this queue.
    * @post    The returned value is equal to the last integer in this queue.
    * @return  The last integer in this queue.
    * @throw   std::logic_error if this queue is empty.
   */
   int back() const;

   /** popFront()
    * @brief   Removes one integer from the front of this queue.
    * @post    The first integer in this queue has been removed and its associated
    *          dynamic memory has been deallocated.
    * @throw   std::logic_error if this queue is empty.
   */
   void popFront();

   /** popBack()
    * @brief   Removes one integer from the back of this queue.
    * @post    The last integer in this queue has been removed and its associated
    *          dynamic memory has been deallocated.
    * @throw   std::logic_error if this queue is empty.
   */
   void popBack();

   /** numEntries()
    * @brief   Returns the number of entries in this queue.
    * @pre     size has been initialized.
    * @post    The returned value is equal to the number of entries in this queue.
    * @return  The number of entries in this queue.
   */
   int numEntries() const;

   /** clear
    * @brief   Removes all the entries from this queue.
    * @post    This queue is empty and all dynamically allocated memory has been
    *          returned to the system.
   */
   void clear();

private:
   /** Node
    * @brief   Node struct used by DEIntQueue
   */
   struct Node {
      int data;   // integer stored in this Node
      Node* prev; // pointer to the previous Node in the queue
      Node* next; // pointer to the next Node in the queue
   };

   // DATA MEMBERS
   int size;      // # of entries in the queue
   Node* head;    // pointer to the first Node in the queue
   Node* tail;    // pointer to the last Node in the queue

   // PRIVATE FUNCTIONS
   /** copy
    * @brief   Copies the contents of another queue into this queue.
    * @param   toCopy   The queue being copied
    * @pre     This queue is empty and toCopy is not the same queue as this one.
    * @post    This queue contains the same entries in the same order as toCopy.
    *          The new entries are deep copies.
   */
   void copy(const DEIntQueue& toCopy);

   // Allow access to private members by operator<<
   friend std::ostream& operator<<(std::ostream& outStream, const DEIntQueue& queueToPrint);

public:
   // ITERATORS
   
   /** iterator
    * @brief   Iterator for DEIntQueue
   */
   class iterator{
   public:
      /** operator++()
       * @brief   Prefix increment. Advances to the next item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This iterator references the next item that occurs in its DEIntQueue.
       *          If the previous item was the last, then cur is set to null.
       * @return  Reference to this iterator.
       * @throw   std::out_of_range if cur is null.
      */
      iterator& operator++();

      /** operator++(int)
       * @brief   Postfix increment. Advances to the next item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This iterator references the next item that occurs in its DEIntQueue.
       *          If the previous item was the last, then cur is set to null.
       * @return  A copy of the iterator before it was modified.
       * @throw   std::out_of_range if cur is null.
      */
      iterator operator++(int);

      /** operator--()
       * @brief   Prefix decrement. Moves to the preceding item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This iterator references the preceding item that occurs in its DEIntQueue.
       *          If the previous item was the first, then cur is set to null.
       * @return  Reference to this iterator.
       * @throw   std::out_of_range if cur is null.
       */
      iterator& operator--();

      /** operator--(int)
       * @brief   Postfix decrement. Moves to the preceding item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This iterator references the preceding item that occurs in its DEIntQueue.
       *          If the previous item was the first, then cur is set to null.
       * @return  A copy of the iterator before it was modified.
       * @throw   std::out_of_range if cur is null.
       */
      iterator operator--(int);

      /** operator*()
       * @brief   Dereference operator. Returns a reference to the integer stored in the
       *          Node this iterator currently references.
       * @pre     cur is not null
       * @return  Reference to the integer stored in the Node this iterator currently references.
       * @throw   std::out_of_range if cur is null.
      */
      int& operator*();

      /** operator!=()
       * @brief   Inequality operator.
       * @param   other    The iterator being compared to
       * @post    Returns true if the two iterators do not reference the same node.
       *          Returns false otherwise.
       * @return  True if the two iterators do not both have the same node. False otherwise.
      */
      bool operator!=(const iterator& other) const;

      /** operator==()
       * @brief   Equality operator.
       * @param   other    The iterator being compared to
       * @post    Returns true if the two iterators reference the same node.
       *          Returns false otherwise.
       * @return  True if the two iterators do not both have the same node. False otherwise.
      */
      bool operator==(const iterator& other) const;

   private:
      /** iterator(DEIntQueue& container, DEIntQueue::Node*)
       * @brief   Constructor
       * @param   container   The DEIntQueue the iterator is associated with
       * @param   
      */
      iterator(DEIntQueue::Node* initCur) : cur(initCur) {}
      friend DEIntQueue;

      DEIntQueue::Node* cur;  // The current entry referenced by the iterator
   };

   class const_iterator{
   public:
      /** operator++()
       * @brief   Prefix increment. Advances to the next item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This const_iterator references the next item that occurs in its DEIntQueue.
       *          If the previous item was the last, then cur is set to null.
       * @return  Reference to this const_iterator.
       * @throw   std::out_of_range if cur is null.
      */
      const_iterator& operator++();

      /** operator++(int)
       * @brief   Postfix increment. Advances to the next item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This const_iterator references the next item that occurs in its DEIntQueue.
       *          If the previous item was the last, then cur is set to null.
       * @return  A copy of the const_iterator before it was modified.
       * @throw   std::out_of_range if cur is null.
      */
      const_iterator operator++(int);

      /** operator--()
       * @brief   Prefix decrement. Moves to the preceding item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This const_iterator references the preceding item that occurs in its DEIntQueue.
       *          If the previous item was the first, then cur is set to null.
       * @return  Reference to this const_iterator.
       * @throw   std::out_of_range if cur is null.
       */
      const_iterator& operator--();

      /** operator--(int)
       * @brief   Postfix decrement. Moves to the preceding item in its DEIntQueue.
       * @pre     cur is not null.
       * @post    This const_iterator references the preceding item that occurs in its DEIntQueue.
       *          If the previous item was the first, then cur is set to null.
       * @return  A copy of the const_iterator before it was modified.
       * @throw   std::out_of_range if cur is null.
       */
      const_iterator operator--(int);

      /** operator*()
       * @brief   Dereference operator. Returns a reference to the integer stored in the
       *          Node this const_iterator currently references.
       * @pre     cur is not null
       * @return  Reference to the integer stored in the Node this const_iterator currently references.
       * @throw   std::out_of_range if cur is null.
      */
      const int& operator*();

      /** operator!=()
       * @brief   Inequality operator.
       * @param   other    The const_iterator being compared to
       * @post    Returns true if the two const_iterators do not reference the same node.
       *          Returns false otherwise.
       * @return  True if the two const_iterators do not both have the same node. False otherwise.
      */
      bool operator!=(const const_iterator& other) const;

      /** operator==()
       * @brief   Equality operator.
       * @param   other    The const_iterator being compared to
       * @post    Returns true if the two const_iterators reference the same node.
       *          Returns false otherwise.
       * @return  True if the two const_iterators do not both have the same node. False otherwise.
      */
      bool operator==(const const_iterator& other) const;

   private:
      /** const_iterator(DEIntQueue& container, DEIntQueue::Node*)
       * @brief   Constructor
       * @param   container   The DEIntQueue the const_iterator is associated with
       * @param   
      */
      const_iterator(const DEIntQueue::Node* initCur) : cur(initCur) {}
      friend DEIntQueue;

      const DEIntQueue::Node* cur;  // The current entry referenced by the const_iterator
   };

   /** begin()
    * @brief   Returns an iterator that references the first entry in this queue.
    * @post    The returned iterator references this queue's first entry.
    *          If this queue is empty, the iterator does not reference any entry
    *          and is equivalent to the one returned by end().
    * @return  An iterator that references the first entry in this queue.
   */
   iterator begin();

   /** begin()
    * @brief   Returns a const_iterator that references the first entry in this queue.
    * @post    The returned const_iterator references this queue's first entry.
    *          If this queue is empty, the const_iterator does not reference any entry
    *          and is equivalent to the one returned by end().
    * @return  A const_iterator that references the first entry in this queue.
   */
   const_iterator begin() const;

   /** last()
    * @brief   Returns an iterator that references the last entry in this queue.
    * @post    The returned iterator references this queue's last entry.
    *          If this queue is empty, the iterator does not reference any entry
    *          and is equivalent to the one returned by end().
    * @return  An iterator that references the last entry in this queue.
   */
   iterator last();

   /** last()
    * @brief   Returns a const_iterator that references the last entry in this queue.
    * @post    The returned const_iterator references this queue's last entry.
    *          If this queue is empty, the const_iterator does not reference any entry
    *          and is equivalent to the one returned by end().
    * @return  A const_iterator that references the last entry in this queue.
   */
   const_iterator last() const;

   /** end()
    * @brief   Returns an iterator that represents the end of this queue.
    * @post    The returned iterator does not reference any entry.
    * @return  An iterator that represents the end of this queue.
   */
   iterator end() ;

   /** end()
    * @brief   Returns a const_iterator that represents the end of this queue.
    * @post    The returned const_iterator does not reference any entry.
    * @return  A const_iterator that represents the end of this queue.
   */
   const_iterator end() const;
};

/** operator<<(ostream&, const DEIntQueue&)
 * @brief   Outputs a DEIntQueue to an output stream
 * @param   outStream      The stream to print the queue's entries to
 * @param   queueToPrint   The queue whose entries are being printed
 * @pre     outStream is not in an error state when the function is called
 * @post    The entries in queueToPrint have been printed to outStream in
 *          order from head to tail, separated by single spaces.
 * @return  Reference to the modified stream.
*/
std::ostream& operator<<(std::ostream& outStream, const DEIntQueue& queueToPrint);