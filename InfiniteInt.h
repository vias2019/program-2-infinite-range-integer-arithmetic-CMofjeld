/** 
 * @file InfiniteInt.h
 * @brief Class definition for InfiniteInt, an ADT that can store
 *    and perform operations on integers with arbitrarily many digits
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "DEIntQueue.h" // Data structure used to store the list of digits
#include <climits>      // INT_MIN and INT_MAX

class InfiniteInt {
public:
   //PUBLIC METHODS
   /** InfiniteInt()
    * @brief   Default constructor.
    * @post    This InfiniteInt has a single digit, 0, and negative is false.
   */
   InfiniteInt();

   /** InfiniteInt(int)
    * @brief   Constructs an InfiniteInt that represents the given integer.
    * @param   num   The integer to be converted to an InfiniteInt
    * @post    This InfiniteInt has the same sign and digits as num.
   */
   explicit InfiniteInt(int num);

   /** numDigits()
    * @brief   Returns the number of decimal digits in the number represented
    *          by this InfiniteInt.
    * @post    The returned value is the number of decimal digits in the number
    *          represented by this InfiniteInt.
    * @return  The number of decimal digits in the number represented by this
    *          InfiniteInt.
   */
   int numDigits() const;

private:
   // DATA MEMBERS
   DEIntQueue digits;   // stores the digits in this InfiniteInt (ordered from highest digit to lowest)
   bool negative;       // indicates if the number represented is negative (true) or positive (false)

   // Allow access to private members by operator<<
   friend std::ostream& operator<<(std::ostream& outStream, const InfiniteInt& IIToPrint);
};

/** operator<<(ostream&, const InfiniteInt&)
 * @brief   Outputs a InfiniteInt to an output stream
 * @param   outStream      The stream to print the queue's entries to
 * @param   IIToPrint      The InfiniteInt whose entries are being printed
 * @pre     outStream is not in an error state when the function is called
 * @post    A textual representation of the number represented by this InfiniteInt
 *          has been output to outStream.
 * @return  Reference to the modified stream.
*/
std::ostream& operator<<(std::ostream& outStream, const InfiniteInt& IIToPrint);