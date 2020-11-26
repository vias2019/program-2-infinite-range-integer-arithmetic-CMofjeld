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

   /** operator int()
    * @brief   Conversion operator. Returns the number represented by this
    *          InfiniteInt as an integer.
    * @pre     The number represented by this InfiniteInt is not greater than
    *          INT_MAX and not less than INT_MIN.
    * @post    The returned value is equal to the number represented by this
    *          InfiniteInt.
    * @return  The number represented by this InfiniteInt as an integer.
    * @throw   std::range_error if the result would be outside the range
    *          representable by an int.
   */
   operator int() const;

   /** numDigits()
    * @brief   Returns the number of decimal digits in the number represented
    *          by this InfiniteInt.
    * @post    The returned value is the number of decimal digits in the number
    *          represented by this InfiniteInt.
    * @return  The number of decimal digits in the number represented by this
    *          InfiniteInt.
   */
   int numDigits() const;

   /** operator+(const InfiniteInt&)
    * @brief   Adds the number represented by this InfiniteInt to that represented
    *          by another and returns the result as an InfiniteInt.
    * @param   rhs   The InfiniteInt to add to this one
    * @post    The returned InfiniteInt represents the sum of this InfinteInt's
    *          number and rhs's.
    * @return  InfiniteInt representing the sum of this InfinteInt's number and rhs's.
   */
   InfiniteInt operator+(const InfiniteInt& rhs) const;

   /** operator-(const InfiniteInt&)
    * @brief   Subtracts the number represented by another InfiniteInt from that represented
    *          by this one and returns the result as an InfiniteInt.
    * @param   rhs   The InfiniteInt to subtract from this one
    * @post    The returned InfiniteInt represents the difference of this InfinteInt's
    *          number and rhs's.
    * @return  InfiniteInt representing the difference of this InfinteInt's number and rhs's.
   */
   InfiniteInt operator-(const InfiniteInt& rhs) const;

   /** operator*(const InfiniteInt&)
    * @brief   Multiplies the number represented by another InfiniteInt with that represented
    *          by this one and returns the result as an InfiniteInt.
    * @param   rhs   The InfiniteInt to multiply with this one
    * @post    The returned InfiniteInt represents the product of this InfinteInt's
    *          number and rhs's.
    * @return  InfiniteInt representing the product of this InfinteInt's number and rhs's.
   */
   InfiniteInt operator*(const InfiniteInt& rhs) const;

   /** operator==(const InfiniteInt& rhs)
    * @brief   Equality operator. Checks if this InfiniteInt represents the same integer
    *          as another.
    * @param   rhs   The InfiniteInt being compared to.
    * @post    The returned value is true if both InfiniteInts have the same sign and the
    *          same digits in the same order. Otherwise, it is false.
    * @return  True if this InfiniteInt is equal to rhs and false otherwise.
   */
   bool operator==(const InfiniteInt& rhs) const;

   /** operator!=(const InfiniteInt& rhs)
    * @brief   Inequality operator. Checks if this InfiniteInt represents the same integer
    *          as another.
    * @param   rhs   The InfiniteInt being compared to.
    * @post    The returned value is false if both InfiniteInts have the same sign and the
    *          same digits in the same order. Otherwise, it is true.
    * @return  False if this InfiniteInt is equal to rhs and true otherwise.
   */
   bool operator!=(const InfiniteInt& rhs) const;

   /** operator<(const InfiniteInt& rhs)
    * @brief   Less-than operator. Checks if the integer this InfiniteInt represents
    *          is less than that of another.
    * @param   rhs   The InfiniteInt being compared to.
    * @post    The returned value is true if this InfiniteInt's integer is less than
    *          rhs's and false otherwise.
    * @return  True if this InfiniteInt is less than rhs and false otherwise.
   */
   bool operator<(const InfiniteInt& rhs) const;

private:
   // DATA MEMBERS
   DEIntQueue digits;   // stores the digits in this InfiniteInt (ordered from highest digit to lowest)
   bool isNegative;     // indicates if the number represented is negative (true) or positive (false)

   // PRIVATE METHODS
   /** add(const InfiniteInt&, const InfiniteInt&)
    * @brief   Helper method to add InfiniteInts. Ignores the sign of both InfiniteInts.
    * @param   lhs   First InfiniteInt to add
    * @param   rhs   Second InfiniteInt to add
    * @post    The returned InfiniteInt represents the sum of the absolute values of
    *          lhs's number and rhs's.
    * @return  InfiniteInt representing the sum of the absolute values of lhs's number and rhs's.
   */
   InfiniteInt add(const InfiniteInt& lhs, const InfiniteInt& rhs) const;

   /** subtract(const InfiniteInt& rhs)
    * @brief   Helper method to subtract InfiniteInts.
    * @param   lhs   The InfiniteInt being subtracted from
    * @param   rhs   InfiniteInt being subtracted from lhs
    * @post    The returned InfiniteInt represents the difference of the absolute values of
    *          lhs's number and rhs's.
    * @return  InfiniteInt representing the difference of lhs's number and rhs's.
   */
   InfiniteInt subtract(const InfiniteInt& lhs, const InfiniteInt& rhs) const;

   /** subtractAbs(const InfiniteInt& rhs)
    * @brief   Helper method to subtract InfiniteInts. Ignores the sign of both InfiniteInts.
    * @param   lhs   The larger of the two InfiniteInts
    * @param   rhs   InfiniteInt being subtracted from lhs
    * @pre     The absolute value of lhs's number must be greater than or equal to the
    *          absolute value of rhs's number.
    * @post    The returned InfiniteInt represents the difference of the absolute values of
    *          lhs's number and rhs's.
    * @return  InfiniteInt representing the difference of the absolute values of lhs's number and rhs's.
   */
   InfiniteInt subtractAbs(const InfiniteInt& lhs, const InfiniteInt& rhs) const;

   /** removeLeadingZeroes()
    * @brief   Removes any leading zero digits from this InfiniteInt.
    * @post    All leading zero digits, other than the ones digit, have been removed from this InfiniteInt.
   */
   void removeLeadingZeroes();

   /** setNegative(bool isNegative)
    * @brief   Sets the sign of this InfiniteInt
    * @param   negative  New value for isNegative
    * @post    isNegative == negative
   */
   void setNegative(bool negative);

   // Allow access to private members by stream I/O
   friend std::ostream& operator<<(std::ostream& outStream, const InfiniteInt& IIToPrint);
   friend std::istream& operator>>(std::istream& inStream, InfiniteInt& IIToFill);
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

/** operator>>(istream&, const InfiniteInt&)
 * @brief   Reads digits from an input stream and inputs them into an InfiniteInt
 * @param   inStream    The stream to read from
 * @param   IIToFill    The InfiniteInt to read into
 * @pre     inStream is not in an error state when the function is called
 * @post    All initial whitespace characters in inStream have been discarded.
 *          If the first non-whitespace character is a digit ('0' - '9'),
 *          all consecutive digits immediately following the first have been read
 *          from the stream and IIToFill contains those same digits in the same
 *          order in which they were read. If the first character was '-' followed
 *          by at least one digit, then the InfiniteInt has been set to be negative
 *          and all consecutive digits have been read and stored, as before. In
 *          all other cases, the InfiniteInt is set to zero.
 * @return  Reference to the modified stream.
*/
std::istream& operator>>(std::istream& inStream, InfiniteInt& IIToFill);