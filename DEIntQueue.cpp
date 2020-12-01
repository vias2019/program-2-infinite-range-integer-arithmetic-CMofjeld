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
      head_ = newNode;
      tail_ = newNode;
   } else {
      // The queue is not empty - need to update previous head_'s prev pointer
      head_->prev_ = newNode;
      newNode->next_ = head_;
      head_ = newNode;
   }

   // Update number of entries
   ++size_;
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
      head_ = newNode;
      tail_ = newNode;
   } else {
      // The queue is not empty - need to update previous tail's next pointer
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
      tail_ = newNode;
   }

   // Update number of entries
   ++size_;
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

   return head_->data_;
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

   return tail_->data_;
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

   Node* toDelete = head_;  // the node to delete

   // Update the queue
   if (numEntries() == 1) {
      // Need to update both head and tail pointers
      head_ = tail_ = nullptr;
   } else {
      // Need to update prev pointer of next node in the queue
      head_ = head_->next_;
      head_->prev_ = nullptr;
   }
   --size_;

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

   Node* toDelete = tail_;  // the node to delete

   // Update the queue
   if (numEntries() == 1) {
      // Need to update both head and tail pointers
      head_ = tail_ = nullptr;
   } else {
      // Need to update next pointer of previous node in the queue
      tail_ = tail_->prev_;
      tail_->next_ = nullptr;
   }
   --size_;

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
   return size_;
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
   size_ = 0;
}

/** copy
 * @brief   Copies the contents of another queue into this queue.
 * @param   toCopy   The queue being copied
 * @pre     This queue is empty and toCopy is not the same queue as this one.
 * @post    This queue contains the same entries in the same order as toCopy.
 *          The new entries are deep copies.
*/
void DEIntQueue::copy(const DEIntQueue& toCopy) {
   size_ = 0;
   if (toCopy.head_ == nullptr) {
      // Other list is empty
      head_ = tail_ = nullptr;
   } else {
      for (Node* copyCur = toCopy.tail_; copyCur != nullptr; copyCur = copyCur->prev_) {
         pushFront(copyCur->data_);
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
   for (DEIntQueue::Node* cur = queueToPrint.head_; cur != nullptr; cur = cur->next_) {
      outStream << cur->data_ << ' ';
   }
   return outStream;
}

// ITERATOR

/** operator++()
 * @brief   Prefix increment. Advances to the next item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This iterator references the next item that occurs in its DEIntQueue.
 *          If the previous item was the last, then cur is set to null.
 * @return  Reference to this iterator.
 * @throw   std::out_of_range if cur is null.
*/
DEIntQueue::iterator& DEIntQueue::iterator::operator++() {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   cur_ = cur_->next_;
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
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   iterator copy(*this);
   cur_ = cur_->next_;
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
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   cur_ = cur_->prev_;
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
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::iterator that references no entry.");
   }
   iterator copy(*this);
   cur_ = cur_->prev_;
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
   if (cur_ == nullptr) {
      throw std::out_of_range("Called dereference on DEIntQueue::iterator that references no entry.");
   }
   return cur_->data_;
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
   return cur_ == other.cur_;
}

/** begin()
 * @brief   Returns an iterator that references the first entry in this queue.
 * @post    The returned iterator references this queue and its first entry.
 *          If this queue is empty, the iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  An iterator that references the first entry in this queue.
*/
DEIntQueue::iterator DEIntQueue::begin() {
   return iterator(head_);
}

/** begin()
 * @brief   Returns a const_iterator that references the first entry in this queue.
 * @post    The returned const_iterator references this queue's first entry.
 *          If this queue is empty, the const_iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  A const_iterator that references the first entry in this queue.
*/
DEIntQueue::const_iterator DEIntQueue::begin() const {
   return const_iterator(head_);
}

/** last()
 * @brief   Returns an iterator that references the last entry in this queue.
 * @post    The returned iterator references this queue and its last entry.
 *          If this queue is empty, the iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  An iterator that references the last entry in this queue.
*/
DEIntQueue::iterator DEIntQueue::last() {
   return iterator(tail_);
}

/** last()
 * @brief   Returns a const_iterator that references the last entry in this queue.
 * @post    The returned const_iterator references this queue's last entry.
 *          If this queue is empty, the const_iterator does not reference any entry
 *          and is equivalent to the one returned by end().
 * @return  A const_iterator that references the last entry in this queue.
*/
DEIntQueue::const_iterator DEIntQueue::last() const {
   return const_iterator(tail_);
}

/** end()
 * @brief   Returns an iterator that represents the end of this queue.
 * @post    The returned iterator references this queue and does not reference
 *          any entry.
 * @return  An iterator that represents the end of this queue.
*/
DEIntQueue::iterator DEIntQueue::end() {
   return iterator(nullptr);
}

/** end()
 * @brief   Returns a const_iterator that represents the end of this queue.
 * @post    The returned const_iterator references this queue and does not reference
 *          any entry.
 * @return  An const_iterator that represents the end of this queue.
*/
DEIntQueue::const_iterator DEIntQueue::end() const {
   return const_iterator(nullptr);
}

// CONST ITERATOR

/** operator++()
 * @brief   Prefix increment. Advances to the next item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This const_iterator references the next item that occurs in its DEIntQueue.
 *          If the previous item was the last, then cur is set to null.
 * @return  Reference to this const_iterator.
 * @throw   std::out_of_range if cur is null.
*/
DEIntQueue::const_iterator& DEIntQueue::const_iterator::operator++() {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::const_iterator that references no entry.");
   }
   cur_ = cur_->next_;
   return *this;
}

/** operator++(int)
 * @brief   Postfix increment. Advances to the next item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This const_iterator references the next item that occurs in its DEIntQueue.
 *          If the previous item was the last, then cur is set to null.
 * @return  A copy of the const_iterator before it was modified.
 * @throw   std::out_of_range if cur is null.
*/
DEIntQueue::const_iterator DEIntQueue::const_iterator::operator++(int) {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::const_iterator that references no entry.");
   }
   const_iterator copy(*this);
   cur_ = cur_->next_;
   return copy;
}

/** operator--()
 * @brief   Prefix decrement. Moves to the preceding item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This const_iterator references the preceding item that occurs in its DEIntQueue.
 *          If the previous item was the first, then cur is set to null.
 * @return  Reference to this const_iterator.
 * @throw   std::out_of_range if cur is null.
 */
DEIntQueue::const_iterator& DEIntQueue::const_iterator::operator--() {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::const_iterator that references no entry.");
   }
   cur_ = cur_->prev_;
   return *this;
}

/** operator--(int)
 * @brief   Postfix decrement. Moves to the preceding item in its DEIntQueue.
 * @pre     cur is not null.
 * @post    This const_iterator references the preceding item that occurs in its DEIntQueue.
 *          If the previous item was the first, then cur is set to null.
 * @return  A copy of the const_iterator before it was modified.
 * @throw   std::out_of_range if cur is null.
 */
DEIntQueue::const_iterator DEIntQueue::const_iterator::operator--(int) {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called increment on DEIntQueue::const_iterator that references no entry.");
   }
   const_iterator copy(*this);
   cur_ = cur_->prev_;
   return copy;
}

/** operator*()
 * @brief   Dereference operator. Returns a reference to the integer stored in the
 *          Node this const_iterator currently references.
 * @pre     cur is not null
 * @return  Reference to the integer stored in the Node this const_iterator currently references.
 * @throw   std::out_of_range if cur is null.
*/
const int& DEIntQueue::const_iterator::operator*() {
   if (cur_ == nullptr) {
      throw std::out_of_range("Called dereference on DEIntQueue::const_iterator that references no entry.");
   }
   return cur_->data_;
}

/** operator!=()
 * @brief   Inequality operator.
 * @param   other    The const_iterator being compared to
 * @post    Returns true if the two const_iterators do not both have the same container and same node.
 *          Returns false otherwise.
 * @return  True if the two const_iterators do not both the same container and same node.
 *          False otherwise.
*/
bool DEIntQueue::const_iterator::operator!=(const const_iterator& other) const {
   return !operator==(other);
}

/** operator==()
 * @brief   Equality operator.
 * @param   other    The const_iterator being compared to
 * @post    Returns true if the two const_iterators both have the same container and same node.
 *          Returns false otherwise.
 * @return  True if the two const_iterators do not both the same container and same node.
 *          False otherwise.
*/
bool DEIntQueue::const_iterator::operator==(const const_iterator& other) const {
   return cur_ == other.cur_;
}