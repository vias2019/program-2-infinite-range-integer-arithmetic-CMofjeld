/** 
 * @file DEIntQueue.h
 * @brief Class definition for DEIntQueue, a link-based double-ended queue that stores integers
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include <iostream>  // Stream I/O

class DEIntQueue {
public:
   /** DEIntQueue()
    * @brief   Default constructor.
    * @post    This queue is empty and its size is 0.
   */
   DEIntQueue() : size(0), head(nullptr), tail(nullptr) { }

   /** numEntries()
    * @brief   Returns the number of entries in this queue.
    * @pre     size has been initialized.
    * @post    The returned value is equal to the number of entries in this queue.
    * @returns The number of entries in this queue.
   */
   int numEntries();

private:
   /** Node
    * @brief   Node struct used by DEIntQueue
   */
   struct Node {
      int data;   // integer stored in this Node
      Node* prev; // pointer to the previous Node in the queue
      Node* next; // pointer to the next Node in the queue
   };

   int size;      // # of entries in the queue
   Node* head;    // pointer to the first Node in the queue
   Node* tail;    // pointer to the last Node in the queue

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