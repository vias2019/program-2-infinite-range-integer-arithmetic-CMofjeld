/** 
 * @file DEIntQueue.cpp
 * @brief Implementation for DEIntQueue, a link-based double-ended queue that stores integers
 * @author Carl Mofjeld
 * @date 11/23/2020
*/
#include "DEIntQueue.h"

/** DEIntQueue(const DEIntQueue&)
 * @brief   Copy constructor.
 * @post    This queue contains the same entries in the same order as toCopy.
 *          The new entries are deep copies.
*/
DEIntQueue::DEIntQueue(const DEIntQueue& toCopy) {
   copy(toCopy);
}

/** operator=(const DEIntQueue&)
 * @brief   Assignment operator.
 * @param   toCopy   The queue being copied
 * @post    This queue contains the same entries in the same order as toCopy.
 *          The new entries are deep copies. If this queue is the same object
 *          as toCopy, it is unchanged.
*/
DEIntQueue& DEIntQueue::operator=(const DEIntQueue& toCopy) {
   if (this != &toCopy) {
      // Not the same queue - safe to clear and copy
      clear();
      copy(toCopy);
   }
   return *this;
}

/** ~DEIntQueue()
 * @brief   Destructor.
 * @post    This queue is empty and all dynamically allocated memory has been
 *          returned to the system.
*/
DEIntQueue::~DEIntQueue() {
   clear();
}

/** pushFront(int)
 * @brief   Adds an integer to the front of this queue.
 * @param   newItem  The integer being added to this queue.
 * @post    A new node has been inserted at the front of this
 *          queue with newItem as its data entry.
*/
void DEIntQueue::pushFront(int newItem) {
   // Create the new node
   Node* newNode = new Node{ newItem, nullptr };

   // Add it to the front
   if (numEntries() == 0) {
      // The queue is empty - need to update tail as well as head
      head = newNode;
      tail = newNode;
   } else {
      // The queue is not empty - need to update previous head's prev pointer
      head->prev = newNode;
      newNode->next = head;
      head = newNode;
   }

   // Update number of entries
   ++size;
}

/** pushBack(int)
 * @brief   Adds an integer to the back of this queue.
 * @param   newItem  The integer being added to this queue.
 * @post    A new node has been inserted at the back of this
 *          queue with newItem as its data entry.
*/
void DEIntQueue::pushBack(int newItem) {
   // Create the new node
   Node* newNode = new Node{ newItem, nullptr };

   // Add it to the front
   if (numEntries() == 0) {
      // The queue is empty - need to update tail as well as head
      head = newNode;
      tail = newNode;
   } else {
      // The queue is not empty - need to update previous tail's next pointer
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
   }

   // Update number of entries
   ++size;
}

/** front()
 * @brief   Returns the first item in this queue.
 * @pre     There is at least one item in this queue.
 * @post    The returned value is equal to the first item in this queue.
 * @return  The first item in this queue.
 * @throw   std::logic_error if this queue is empty.
*/
int DEIntQueue::front() const {
   // Check for empty queue
   if (numEntries() <= 0) {
      throw std::logic_error("DEIntQueue::front() called on empty queue.");
   }

   return head->data;
}

/** back()
 * @brief   Returns the last integer in this queue.
 * @pre     There is at least one integer in this queue.
 * @post    The returned value is equal to the last integer in this queue.
 * @return  The last integer in this queue.
 * @throw   std::logic_error if this queue is empty.
*/
int DEIntQueue::back() const {
   // Check for empty queue
   if (numEntries() <= 0) {
      throw std::logic_error("DEIntQueue::back() called on empty queue.");
   }

   return tail->data;
}

/** popFront()
 * @brief   Removes one integer from the front of this queue.
 * @post    The first integer in this queue has been removed and its associated
 *          dynamic memory has been deallocated.
 * @throw   std::logic_error if this queue is empty.
*/
void DEIntQueue::popFront() {
   // Check for empty queue
   if (numEntries() <= 0) {
      throw std::logic_error("DEIntQueue::front() called on empty queue.");
   }

   Node* toDelete = head;  // the node to delete

   // Update the queue
   if (numEntries() == 1) {
      // Need to update both head and tail pointers
      head = tail = nullptr;
   } else {
      // Need to update prev pointer of next node in the queue
      head = head->next;
      head->prev = nullptr;
   }
   --size;

   // Deallocate the deleted node
   delete toDelete;
   toDelete = nullptr;
}

/** popBack()
 * @brief   Removes one integer from the back of this queue.
 * @post    The last integer in this queue has been removed and its associated
 *          dynamic memory has been deallocated.
 * @throw   std::logic_error if this queue is empty.
*/
void DEIntQueue::popBack() {
   // Check for empty queue
   if (numEntries() <= 0) {
      throw std::logic_error("DEIntQueue::front() called on empty queue.");
   }

   Node* toDelete = tail;  // the node to delete

   // Update the queue
   if (numEntries() == 1) {
      // Need to update both head and tail pointers
      head = tail = nullptr;
   } else {
      // Need to update next pointer of previous node in the queue
      tail = tail->prev;
      tail->next = nullptr;
   }
   --size;

   // Deallocate the deleted node
   delete toDelete;
   toDelete = nullptr;
}

/** numEntries()
 * @brief   Returns the number of entries in this queue.
 * @pre     size has been initialized.
 * @post    The returned value is equal to the number of entries in this queue.
 * @returns The number of entries in this queue.
*/
int DEIntQueue::numEntries() const {
   return size;
}

/** clear
 * @brief   Removes all the entries from this queue.
 * @post    This queue is empty and all dynamically allocated memory has been
 *          returned to the system.
*/
void DEIntQueue::clear() {
   while (numEntries() > 0) {
      popFront();
   }
   size = 0;
}

/** copy
 * @brief   Copies the contents of another queue into this queue.
 * @param   toCopy   The queue being copied
 * @pre     This queue is empty and toCopy is not the same queue as this one.
 * @post    This queue contains the same entries in the same order as toCopy.
 *          The new entries are deep copies.
*/
void DEIntQueue::copy(const DEIntQueue& toCopy) {
   size = 0;
   if (toCopy.head == nullptr) {
      // Other list is empty
      head = tail = nullptr;
   } else {
      for (Node* copyCur = toCopy.tail; copyCur != nullptr; copyCur = copyCur->prev) {
         pushFront(copyCur->data);
      }
   }
}

/** operator<<(ostream&, const DEIntQueue&)
 * @brief   Outputs a DEIntQueue to an output stream
 * @param   outStream      The stream to print the queue's entries to
 * @param   queueToPrint   The queue whose entries are being printed
 * @pre     outStream is not in an error state when the function is called
 * @post    The entries in queueToPrint have been printed to outStream in
 *          order from head to tail, separated by single spaces.
 * @return  Reference to the modified stream.
*/
std::ostream& operator<<(std::ostream& outStream, const DEIntQueue& queueToPrint) {
   for (DEIntQueue::Node* cur = queueToPrint.head; cur != nullptr; cur = cur->next) {
      outStream << cur->data << ' ';
   }
   return outStream;
}

// ITERATORS

/** operator++()
 * @brief   Prefix increment. Advances to the next item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This iterator references the next item that occurs in its DEIntQueue.
 *          If the previous item was the last, then cur is set to null.
 * @return  Reference to this iterator.
 * @throw   std::out_of_range if cur is null.
*/
DEIntQueue::iterator& DEIntQueue::iterator::operator++() {
   if (cur == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   cur = cur->next;
   return *this;
}

/** operator++(int)
 * @brief   Postfix increment. Advances to the next item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This iterator references the next item that occurs in its DEIntQueue.
 *          If the previous item was the last, then cur is set to null.
 * @return  A copy of the iterator before it was modified.
 * @throw   std::out_of_range if cur is null.
*/
DEIntQueue::iterator DEIntQueue::iterator::operator++(int) {
   if (cur == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   iterator copy(*this);
   cur = cur->next;
   return copy;
}

/** operator--()
 * @brief   Prefix decrement. Moves to the preceding item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This iterator references the preceding item that occurs in its DEIntQueue.
 *          If the previous item was the first, then cur is set to null.
 * @return  Reference to this iterator.
 * @throw   std::out_of_range if cur is null.
 */
DEIntQueue::iterator& DEIntQueue::iterator::operator--() {
   if (cur == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   cur = cur->prev;
   return *this;
}

/** operator--(int)
 * @brief   Postfix decrement. Moves to the preceding item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This iterator references the preceding item that occurs in its DEIntQueue.
 *          If the previous item was the first, then cur is set to null.
 * @return  A copy of the iterator before it was modified.
 * @throw   std::out_of_range if cur is null.
 */
DEIntQueue::iterator DEIntQueue::iterator::operator--(int) {
   if (cur == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   iterator copy(*this);
   cur = cur->prev;
   return copy;
}

/** operator*()
 * @brief   Dereference operator. Returns a reference to the integer stored in the
 *          Node this iterator currently references.
 * @pre     cur is not null
 * @return  Reference to the integer stored in the Node this iterator currently references.
 * @throw   std::out_of_range if cur is null.
*/
int& DEIntQueue::iterator::operator*() {
   if (cur == nullptr) {
      throw std::out_of_range("Called dereference on DEIntQueue::iterator that references no entry.");
   }
   return cur->data;
}

/** operator!=()
 * @brief   Inequality operator.
 * @param   other    The iterator being compared to
 * @post    Returns true if the two iterators do not both have the same container and same node.
 *          Returns false otherwise.
 * @return  True if the two iterators do not both the same container and same node.
 *          False otherwise.
*/
bool DEIntQueue::iterator::operator!=(const iterator& other) const {
   return !operator==(other);
}

/** operator==()
 * @brief   Equality operator.
 * @param   other    The iterator being compared to
 * @post    Returns true if the two iterators both have the same container and same node.
 *          Returns false otherwise.
 * @return  True if the two iterators do not both the same container and same node.
 *          False otherwise.
*/
bool DEIntQueue::iterator::operator==(const iterator& other) const {
   return (&container == &other.container) && (cur == other.cur);
}

/** begin()
 * @brief   Returns an iterator that references the first entry in this queue.
 * @post    The returned iterator references this queue and its first entry.
 *          If this queue is empty, the iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  An iterator that references the first entry in this queue.
*/
DEIntQueue::iterator DEIntQueue::begin() {
   return iterator(*this, head);
}

/** last()
 * @brief   Returns an iterator that references the last entry in this queue.
 * @post    The returned iterator references this queue and its last entry.
 *          If this queue is empty, the iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  An iterator that references the last entry in this queue.
*/
DEIntQueue::iterator DEIntQueue::last() {
   return iterator(*this, tail);
}

/** end()
 * @brief   Returns an iterator that represents the end of this queue.
 * @post    The returned iterator references this queue and does not reference
 *          any entry.
 * @return  An iterator that represents the end of this queue.
*/
DEIntQueue::iterator DEIntQueue::end() {
   return iterator(*this, nullptr);
}
