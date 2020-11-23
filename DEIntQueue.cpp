/** 
 * @file DEIntQueue.cpp
 * @brief Implementation for DEIntQueue, a link-based double-ended queue that stores integers
 * @author Carl Mofjeld
 * @date 11/23/2020
*/
#include "DEIntQueue.h"

/** numEntries()
 * @brief   Returns the number of entries in this queue.
 * @pre     size has been initialized.
 * @post    The returned value is equal to the number of entries in this queue.
 * @returns The number of entries in this queue.
*/
int DEIntQueue::numEntries() {
   return size;
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