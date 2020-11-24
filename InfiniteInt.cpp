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

/** operator+(const InfiniteInt&)
 * @brief   Adds the number represented by this InfiniteInt to that represented
 *          by another and returns the result as an InfiniteInt.
 * @param   rhs   The InfiniteInt to add to this one
 * @post    The returned InfiniteInt represents the sum of this InfinteInt's
 *          number and rhs's.
 * @return  InfiniteInt representing the sum of this InfinteInt's number and rhs's.
*/
InfiniteInt InfiniteInt::operator+(const InfiniteInt& rhs) const {
   InfiniteInt result;  // The result of adding the two InfiniteInts

   // Check signs to determine which helper to call and the sign of the result
   if (!negative && !rhs.negative) {
      // Both IIs positive - simply add and return result
      result = add(*this, rhs);
   } else if (negative && rhs.negative) {
      // Both IIs negative - add absolute values and set result's sign to negative
      result = add(*this, rhs);
      result.negative = true;
   }
   // TODO: handle cases where one is positive and the other is not

   return result;
}

/** add(const InfiniteInt&, const InfiniteInt&)
 * @brief   Helper method to add InfiniteInts. Ignores the sign of both InfiniteInts.
 * @param   rhs   The InfiniteInt to add to this one
 * @post    The returned InfiniteInt represents the sum of the absolute values of
 *          this InfinteInt's number and rhs's.
 * @return  InfiniteInt representing the sum of this InfinteInt's number and rhs's.
*/
InfiniteInt InfiniteInt::add(const InfiniteInt& lhs, const InfiniteInt& rhs) const {
   InfiniteInt result;        // The result of adding the InfiniteInts
   result.digits.popFront();  // Remove default 0 digit
   int partialSum{0};         // The total from summing two digits
   int carry{0};              // The carry value after summing two digits
   auto lhsCur = lhs.digits.last(); // iterator for this II starting at ones digit
   auto rhsCur = rhs.digits.last(); // iterator for rhs starting at ones digit

   // While both IIs have digits, add them one-by-one and record in result
   while (lhsCur != lhs.digits.end() && rhsCur != rhs.digits.end()) {
      partialSum = *lhsCur + *rhsCur + carry;   // add the digits
      result.digits.pushFront(partialSum % 10); // record result
      carry = partialSum / 10;                  // calculate carry

      // Go to next highest digits (ones digit is at the end so we need to decrement)
      --lhsCur;
      --rhsCur;
   }

   // While either II still has digits, add them to the result (accounting for carries)
   while (lhsCur != lhs.digits.end()) {
      partialSum = *lhsCur + carry;
      result.digits.pushFront(partialSum % 10);
      carry = partialSum / 10;
      --lhsCur;
   }
   while (rhsCur != rhs.digits.end()) {
      partialSum = *rhsCur + carry;
      result.digits.pushFront(partialSum % 10);
      carry = partialSum / 10;
      --rhsCur;
   }

   return result;
}

/** subtract(const InfiniteInt& rhs)
 * @brief   Helper method to subtract InfiniteInts. Ignores the sign of both InfiniteInts.
 * @param   rhs   The InfiniteInt to subract from this one
 * @post    The returned InfiniteInt represents the difference of the absolute values of
 *          this InfinteInt's number and rhs's.
 * @return  InfiniteInt representing the difference of this InfinteInt's number and rhs's.
*/
InfiniteInt InfiniteInt::subtract(const InfiniteInt& lhs, const InfiniteInt& rhs) const {
   InfiniteInt result;
   // TODO: Implement
   return result;
}

/** setNegative(bool isNegative)
 * @brief   Sets the sign of this InfiniteInt
 * @param   isNegative  New value for negative
 * @post    negative == isNegative
*/
void InfiniteInt::setNegative(bool isNegative) {
   negative = isNegative;
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