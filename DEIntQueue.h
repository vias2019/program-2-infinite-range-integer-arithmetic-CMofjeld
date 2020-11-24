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
   /** clear
    * @brief   Removes all the entries from this queue.
    * @post    This queue is empty and all dynamically allocated memory has been
    *          returned to the system.
   */
   void clear();

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