/** 
 * @file InfiniteInt.cpp
 * @brief Implementation for InfiniteInt, an ADT that can store
 *    and perform operations on integers with arbitrarily many digits
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "InfiniteInt.h"

/** InfiniteInt()
 * @brief   Default constructor.
 * @post    This InfiniteInt has a single digit, 0, and negative is false.
*/
InfiniteInt::InfiniteInt() : negative(false) {
   digits.pushFront(0);
}

/** InfiniteInt(int)
 * @brief   Constructs an InfiniteInt that represents the given integer.
 * @param   num   The integer to be converted to an InfiniteInt
 * @post    This InfiniteInt has the same sign and digits as num.
*/
InfiniteInt::InfiniteInt(int num) {
   // Check for INT_MIN
   if (num == INT_MIN) {
      /* Trying to change INT_MIN to positive won't work, given that its
         absolute value is greater than INT_MAX. Here we take off the lowest
         digit to make num small enough to convert in the following block that
         checks for negative inputs */
      digits.pushFront(abs(num % 10));
      num /= 10;
   }

   // Check for negative input
   if (num < 0) {
      negative = true;
      num = abs(num);
   } else {
      negative = false;
   }

   // Push digits one by one to the list of digits.
   // Using a do/while guarantees 0 will be handled correctly.
   do {
      digits.pushFront(num % 10);
      num /= 10;
   } while (num != 0);
}

/** numDigits()
 * @brief   Returns the number of decimal digits in the number represented
 *          by this InfiniteInt.
 * @post    The returned value is the number of decimal digits in the number
 *          represented by this InfiniteInt.
 * @return  The number of decimal digits in the number represented by this
 *          InfiniteInt.
*/
int InfiniteInt::numDigits() const {
   return digits.numEntries();
}

/** operator<<(ostream&, const InfiniteInt&)
 * @brief   Outputs a InfiniteInt to an output stream
 * @param   outStream      The stream to print the queue's entries to
 * @param   IIToPrint      The InfiniteInt whose entries are being printed
 * @pre     outStream is not in an error state when the function is called
 * @post    A textual representation of the number represented by this InfiniteInt
 *          has been output to outStream.
 * @return  Reference to the modified stream.
*/
std::ostream& operator<<(std::ostream& outStream, const InfiniteInt& IIToPrint) {
   // Output minus sign, if necessary
   if (IIToPrint.negative) {
      outStream << '-';
   }

   // Output the digits, from highest to lowest
   for (auto iter = IIToPrint.digits.begin(); iter != IIToPrint.digits.end(); ++iter) {
      outStream << *iter;
   }

   // Return stream
   return outStream;
}