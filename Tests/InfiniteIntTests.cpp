/** 
 * @file InfiniteIntTests.cpp
 * @brief Defines catch2 unit tests for InfiniteInt
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "catch.hpp"          // catch2 required header
#include "../InfiniteInt.h"   // class being tested
#include <sstream>            // allow testing of InfiniteInt contents via printing

// CONSTRUCTOR TESTS
TEST_CASE("[InfiniteInt] Default constructor creates an InfiniteInt representing 0", "[InfiniteInt constructors]") {
   // Setup
   std::stringstream expected{"0"};
   std::stringstream actual;

   // Run
   InfiniteInt ii;
   actual << ii;

   // Test
   CHECK(actual.str() == expected.str());
   CHECK(ii.numDigits() == 1);
}

void testIntConstructor(const std::string& inputDescription, int input) {
   SECTION(inputDescription) {
      // Setup
      int expectedDigits{0};
      std::stringstream expectedOut;
      std::stringstream actualOut;

      // Run
      expectedOut << input;
      InfiniteInt ii(input);
      actualOut << ii;
      do {
         ++expectedDigits;
         input /= 10;
      } while (input != 0);

      // Test
      CHECK(actualOut.str() == expectedOut.str());
      CHECK(ii.numDigits() == expectedDigits);
   }
}

TEST_CASE("[InfiniteInt] Int constructor correctly converts to InfiniteInt", "[InfiniteInt constructors]") {
   testIntConstructor("Postive integers < INT_MAX", 123456);
   testIntConstructor("Negative integers > INT_MIN", -123456);
   testIntConstructor("Zero", 0);
   testIntConstructor("INT_MAX", INT_MAX);
   testIntConstructor("INT_MIN", INT_MIN);
}
// END CONSTRUCTOR TESTS

// DEEP COPY TESTS
void testCopyCtor(const std::string& inputDescription, const InfiniteInt& original)
{
   SECTION(inputDescription) {
      // Setup
      InfiniteInt copyControl(original);
      InfiniteInt copyToChange(original);
      REQUIRE(copyControl == original);
      REQUIRE(copyToChange == original);

      // Run
      copyToChange = copyToChange + InfiniteInt(1);

      // Test
      CHECK(copyControl == original);
      CHECK(copyToChange != original);
   }
}

TEST_CASE("[InfiniteInt] Copy constructor performs a deep copy", "[InfiniteInt deep copy]") {
   testCopyCtor("Original > 0 with 1 digit", InfiniteInt(4));
   testCopyCtor("Original < 0 with 1 digit", InfiniteInt(-4));
   testCopyCtor("Original > 0 with > 1 digit", InfiniteInt(123));
   testCopyCtor("Original < 0 with > 1 digit", InfiniteInt(-123));
   testCopyCtor("Original = 0", InfiniteInt(0));
}

void testAssignment(const std::string& inputDescription,
                    int copyControlInitialVal,
                    int copyToChangeInitialVal,
                    int originalInitialVal)
{
   SECTION(inputDescription) {
      // Setup
      InfiniteInt copyControl(copyControlInitialVal);
      InfiniteInt copyToChange(copyToChangeInitialVal);
      InfiniteInt original(originalInitialVal);
      REQUIRE(copyControl != original);
      REQUIRE(copyToChange != original);
      copyControl = original;
      copyToChange = original;
      REQUIRE(copyControl == original);
      REQUIRE(copyToChange == original);

      // Run
      copyToChange = copyToChange + InfiniteInt(1);

      // Test
      CHECK(copyControl == original);
      CHECK(copyToChange != original);
   }
}

TEST_CASE("[InfiniteInt] Operator= performs a deep copy", "[InfiniteInt deep copy]") {
   testAssignment("Original > 0 with 1 digit", -123, 321, 4);
   testAssignment("Original < 0 with 1 digit", 8, -9, -4);
   testAssignment("Original > 0 with > 1 digit", 123456, -321, 123);
   testAssignment("Original < 0 with > 1 digit", 321, -123456, -123);
   testAssignment("Original = 0", 123, -9, 0);
}
// END DEEP COPY TESTS

// OPERATOR INT TESTS
void testOperatorInt(const std::string& inputDescription,
                     const InfiniteInt& testInput,
                     int expectedResult,
                     bool shouldThrowException)
{
   SECTION(inputDescription) {
      // Setup
      bool didThrowException = false;

      // Run
      try {
         int actualResult = int(testInput);
         // Test
         CHECK(actualResult == expectedResult);
      }
      catch(std::range_error) {
         didThrowException = true;
      }

      // Test
      CHECK(didThrowException == shouldThrowException);
   }
}

TEST_CASE("[InfiniteInt] Operator int produces expected values when input in legal range", "[InfiniteInt::operator int]") {
   testOperatorInt("0 < Input < INT_MAX, # digits > 1", InfiniteInt(123456), 123456, false);
   testOperatorInt("INT_MIN < Input < 0, # digits > 1", InfiniteInt(-456789), -456789, false);
   testOperatorInt("0 < Input < INT_MAX, # digits = 1", InfiniteInt(2), 2, false);
   testOperatorInt("INT_MIN < Input < 0, # digits = 1", InfiniteInt(-4), -4, false);
   testOperatorInt("Input = 0", InfiniteInt(0), 0, false);
   testOperatorInt("Input = INT_MAX", InfiniteInt(INT_MAX), INT_MAX, false);
   testOperatorInt("Input = INT_MIN", InfiniteInt(INT_MIN), INT_MIN, false);
}

TEST_CASE("[InfiniteInt] Operator int throws an exception when input outside legal range", "[InfiniteInt::operator int]") {
   InfiniteInt tooBig(INT_MAX);
   tooBig = tooBig + InfiniteInt(1);
   testOperatorInt("Input > INT_MAX", tooBig, 0, true);
   
   InfiniteInt tooSmall(INT_MIN);
   tooSmall = tooSmall - InfiniteInt(1);
   testOperatorInt("Input < INT_MIN", tooSmall, 0, true);
}
// END OPERATOR INT TESTS

// ADDITION TESTS
void testAddition(const std::string& inputDescription,
                  const InfiniteInt& lhs,
                  const InfiniteInt& rhs,
                  const std::string& expectedResult)
{
   SECTION(inputDescription) {
      // Setup
      std::stringstream stringResult;

      // Run
      InfiniteInt testResult = lhs + rhs;
      stringResult << testResult;

      // Test
      CHECK(stringResult.str() == expectedResult);
   }
}

TEST_CASE("[InfiniteInt] Addition produces expected result when both InfiniteInts have the same sign",
          "[InfiniteInt::operator+]") {
   testAddition("Both > 0, same # of digits", InfiniteInt(999), InfiniteInt(999), "1998");
   testAddition("Both < 0, same # of digits", InfiniteInt(-123456), InfiniteInt(-456789), "-580245");
   testAddition("lhs = 0, rhs > 0", InfiniteInt(0), InfiniteInt(456789), "456789");
   testAddition("lhs > 0, rhs = 0", InfiniteInt(456789), InfiniteInt(0), "456789");
   testAddition("Both > 0, lhs has more digits", InfiniteInt(123456), InfiniteInt(789), "124245");
   testAddition("Both < 0, lhs has more digits", InfiniteInt(-123456), InfiniteInt(-789), "-124245");
   testAddition("Both > 0, rhs has more digits", InfiniteInt(789), InfiniteInt(123456), "124245");
   testAddition("Both < 0, rhs has more digits", InfiniteInt(-789), InfiniteInt(-123456), "-124245");
   testAddition("Both = 0", InfiniteInt(0), InfiniteInt(0), "0");
}

TEST_CASE("[InfiniteInt] Addition handles InfiniteInts with different signs", "[InfiniteInt::operator+]") {
   testAddition("lhs > 0, lhs = -(rhs)", InfiniteInt(-123456), InfiniteInt(123456), "0");
   testAddition("lhs < 0, lhs = -(rhs)", InfiniteInt(123456), InfiniteInt(-123456), "0");
   testAddition("lhs < 0, rhs > 0, |lhs| < |rhs|, same # digits", InfiniteInt(-199), InfiniteInt(200), "1");
   testAddition("lhs > 0, rhs < 0, |lhs| < |rhs|, same # digits", InfiniteInt(199), InfiniteInt(-200), "-1");
   testAddition("lhs < 0, rhs > 0, |lhs| > |rhs|, same # digits", InfiniteInt(-200), InfiniteInt(199), "-1");
   testAddition("lhs > 0, rhs < 0, |lhs| > |rhs|, same # digits", InfiniteInt(200), InfiniteInt(-199), "1");
   testAddition("lhs < 0, rhs > 0, |lhs| > |rhs|, different # digits", InfiniteInt(-1000), InfiniteInt(999), "-1");
   testAddition("lhs > 0, rhs < 0, |lhs| > |rhs|, different # digits", InfiniteInt(1000), InfiniteInt(-999), "1");
   testAddition("lhs < 0, rhs > 0, |lhs| > |rhs|, different # digits", InfiniteInt(-999), InfiniteInt(1000), "1");
   testAddition("lhs > 0, rhs < 0, |lhs| > |rhs|, different # digits", InfiniteInt(999), InfiniteInt(-1000), "-1");
}
// END ADDITION TESTS

// EQUALITY TESTS
void testEquality(const std::string& inputDescription,
                  const InfiniteInt& lhs,
                  const InfiniteInt& rhs,
                  bool expectedResult)
{
   SECTION(inputDescription) {
      // Test
      REQUIRE((lhs == rhs) == expectedResult);
   }
}

TEST_CASE("[InfiniteInt] Equality operator returns true when both are equal", "[InfiniteInt]") {
   testEquality("Both > 0 and equal", InfiniteInt(123456), InfiniteInt(123456), true);
   testEquality("Both < 0 and equal", InfiniteInt(-456789), InfiniteInt(-456789), true);
   testEquality("Both = 0 and equal", InfiniteInt(0), InfiniteInt(0), true);
}

TEST_CASE("[InfiniteInt] Equality operator returns false when # of digits differ", "[InfiniteInt]") {
   testEquality("Both > 0, lhs has more digits", InfiniteInt(123456), InfiniteInt(12345), false);
   testEquality("Both > 0, rhs has more digits", InfiniteInt(45678), InfiniteInt(456789), false);
   testEquality("Both < 0, lhs has more digits", InfiniteInt(-123456), InfiniteInt(-12345), false);
   testEquality("Both < 0, rhs has more digits", InfiniteInt(-45678), InfiniteInt(-456789), false);
}

TEST_CASE("Equality operator returns false when signs differ", "[InfiniteInt]") {
   testEquality("lhs negative, rhs positive", InfiniteInt(-123456), InfiniteInt(123456), false);
   testEquality("lhs positive, rhs negative", InfiniteInt(456789), InfiniteInt(-456789), false);
}
// END EQUALITY TESTS

// LESS THAN TESTS
void testLessThan(const std::string& inputDescription,
                  const InfiniteInt& lhs,
                  const InfiniteInt& rhs,
                  bool expectedResult)
{
   SECTION(inputDescription) {
      // Test
      REQUIRE((lhs < rhs) == expectedResult);
   }
}

TEST_CASE("[InfiniteInt] Less than operator returns false when both are equal", "[InfiniteInt]") {
   testLessThan("Both > 0 and equal", InfiniteInt(123456), InfiniteInt(123456), false);
   testLessThan("Both < 0 and equal", InfiniteInt(-456789), InfiniteInt(-456789), false);
   testLessThan("Both = 0 and equal", InfiniteInt(0), InfiniteInt(0), false);
}

TEST_CASE("[InfiniteInt] Less than operator correctly handles differences in sign", "[InfiniteInt]") {
   testLessThan("lhs negative, rhs positive", InfiniteInt(-123456), InfiniteInt(123456), true);
   testLessThan("lhs positive, rhs negative", InfiniteInt(456789), InfiniteInt(-456789), false);
}

TEST_CASE("[InfiniteInt] Less than operator returns false when # of digits differ", "[InfiniteInt]") {
   testLessThan("Both > 0, lhs has more digits", InfiniteInt(123456), InfiniteInt(12345), false);
   testLessThan("Both > 0, rhs has more digits", InfiniteInt(45678), InfiniteInt(456789), true);
   testLessThan("Both < 0, lhs has more digits", InfiniteInt(-123456), InfiniteInt(-12345), true);
   testLessThan("Both < 0, rhs has more digits", InfiniteInt(-45678), InfiniteInt(-456789), false);
}
// END LESS THAN TESTS

// SUBTRACTION TESTS
void testSubtraction(const std::string& inputDescription,
                     const InfiniteInt& lhs,
                     const InfiniteInt& rhs,
                     const InfiniteInt& expectedResult)
{
   SECTION(inputDescription) {
      // Setup
      std::stringstream stringResult;

      // Run
      InfiniteInt testResult = lhs - rhs;

      // Test
      CHECK(testResult == expectedResult);
   }
}

TEST_CASE("[InfiniteInt] Subtraction handles InfiniteInts with same sign", "[InfiniteInt::operator-]") {
   testSubtraction("Both > 0, same # of digits, |lhs| < |rhs|", InfiniteInt(199), InfiniteInt(200), InfiniteInt(-1));
   testSubtraction("Both > 0, same # of digits, |lhs| > |rhs|", InfiniteInt(200), InfiniteInt(199), InfiniteInt(1));
   testSubtraction("Both > 0, lhs = rhs", InfiniteInt(123456), InfiniteInt(123456), InfiniteInt(0));
   testSubtraction("Both < 0, same # of digits, |lhs| < |rhs|", InfiniteInt(-199), InfiniteInt(-200), InfiniteInt(1));
   testSubtraction("Both < 0, same # of digits, |lhs| > |rhs|", InfiniteInt(-200), InfiniteInt(-199), InfiniteInt(-1));
   testSubtraction("Both < 0, lhs = rhs", InfiniteInt(-123456), InfiniteInt(-123456), InfiniteInt(0));
   testSubtraction("lhs = 0, rhs > 0", InfiniteInt(0), InfiniteInt(456789), InfiniteInt(-456789));
   testSubtraction("lhs = 0, rhs < 0", InfiniteInt(0), InfiniteInt(-456789), InfiniteInt(456789));
   testSubtraction("rhs = 0, lhs > 0", InfiniteInt(456789), InfiniteInt(0), InfiniteInt(456789));
   testSubtraction("rhs = 0, lhs < 0", InfiniteInt(-456789), InfiniteInt(0), InfiniteInt(-456789));
   testSubtraction("Both > 0, lhs has more digits", InfiniteInt(123456), InfiniteInt(789), InfiniteInt(122667));
   testSubtraction("Both > 0, rhs has more digits", InfiniteInt(789), InfiniteInt(123456), InfiniteInt(-122667));
   testSubtraction("Both < 0, lhs has more digits", InfiniteInt(-123456), InfiniteInt(-789), InfiniteInt(-122667));
   testSubtraction("Both < 0, rhs has more digits", InfiniteInt(-789), InfiniteInt(-123456), InfiniteInt(122667));
   testSubtraction("Both = 0", InfiniteInt(0), InfiniteInt(0), InfiniteInt(0));
}

TEST_CASE("[InfiniteInt] Subtraction handles InfiniteInts with different signs", "[InfiniteInt::operator-]") {
   testSubtraction("lhs < 0, rhs > 0, |lhs| < |rhs|, same # digits", InfiniteInt(-199), InfiniteInt(200), InfiniteInt(-399));
   testSubtraction("lhs > 0, rhs < 0, |lhs| < |rhs|, same # digits", InfiniteInt(199), InfiniteInt(-200), InfiniteInt(399));
   testSubtraction("lhs < 0, rhs > 0, |lhs| > |rhs|, same # digits", InfiniteInt(-200), InfiniteInt(199), InfiniteInt(-399));
   testSubtraction("lhs > 0, rhs < 0, |lhs| > |rhs|, same # digits", InfiniteInt(200), InfiniteInt(-199), InfiniteInt(399));
   testSubtraction("lhs < 0, rhs > 0, |lhs| > |rhs|, different # digits", InfiniteInt(-1000), InfiniteInt(999), InfiniteInt(-1999));
   testSubtraction("lhs > 0, rhs < 0, |lhs| > |rhs|, different # digits", InfiniteInt(1000), InfiniteInt(-999), InfiniteInt(1999));
   testSubtraction("lhs < 0, rhs > 0, |lhs| > |rhs|, different # digits", InfiniteInt(-999), InfiniteInt(1000), InfiniteInt(-1999));
   testSubtraction("lhs > 0, rhs < 0, |lhs| > |rhs|, different # digits", InfiniteInt(999), InfiniteInt(-1000), InfiniteInt(1999));
}
// END SUBTRACTION TESTS

// MULTIPLICATION TESTS
void testMultiplication(const std::string& inputDescription,
                        const InfiniteInt& lhs,
                        const InfiniteInt& rhs,
                        const std::string& expectedResult)
{
   SECTION(inputDescription) {
      // Setup
      InfiniteInt initialResult;
      std::stringstream actualResult;

      // Run
      initialResult = lhs * rhs;
      actualResult << initialResult;

      // Test
      CHECK(actualResult.str() == expectedResult);
   }
}

TEST_CASE("[InfiniteInt] Multiplication handles either argument being zero", "[InfiniteInt::operator*]") {
   testMultiplication("lhs = 0, rhs > 0", InfiniteInt(0), InfiniteInt(321), "0");
   testMultiplication("lhs = 0, rhs < 0", InfiniteInt(0), InfiniteInt(-2), "0");
   testMultiplication("lhs = 0, rhs = 0", InfiniteInt(0), InfiniteInt(0), "0");
   testMultiplication("lhs > 0, rhs = 0", InfiniteInt(2), InfiniteInt(0), "0");
   testMultiplication("lhs < 0, rhs = 0", InfiniteInt(-321), InfiniteInt(0), "0");
}

TEST_CASE("[InfiniteInt] Multiplication handles either argument being one or negative one", "[InfiniteInt::operator*]") {
   // one
   testMultiplication("lhs = 1, rhs > 0", InfiniteInt(1), InfiniteInt(321), "321");
   testMultiplication("lhs = 1, rhs < 0", InfiniteInt(1), InfiniteInt(-2), "-2");
   testMultiplication("lhs = 1, rhs = 1", InfiniteInt(1), InfiniteInt(1), "1");
   testMultiplication("lhs > 0, rhs = 1", InfiniteInt(2), InfiniteInt(1), "2");
   testMultiplication("lhs < 0, rhs = 1", InfiniteInt(-321), InfiniteInt(1), "-321");

   // negative one
   testMultiplication("lhs = -1, rhs > 0", InfiniteInt(-1), InfiniteInt(321), "-321");
   testMultiplication("lhs = -1, rhs < 0", InfiniteInt(-1), InfiniteInt(-2), "2");
   testMultiplication("lhs = -1, rhs = -1", InfiniteInt(-1), InfiniteInt(-1), "1");
   testMultiplication("lhs > 0, rhs = -1", InfiniteInt(2), InfiniteInt(-1), "-2");
   testMultiplication("lhs < 0, rhs = -1", InfiniteInt(-321), InfiniteInt(-1), "321");
}

TEST_CASE("[InfiniteInt] Multiplication handles both arguments having > 1 digit", "[InfiniteInt::operator*]") {
   testMultiplication("lhs > 0, rhs > 0", InfiniteInt(123456), InfiniteInt(456789), "56393342784");
   testMultiplication("lhs > 0, rhs < 0", InfiniteInt(456789), InfiniteInt(-123456), "-56393342784");
   testMultiplication("lhs < 0, rhs > 0", InfiniteInt(-654321), InfiniteInt(987654), "-646242752934");
   testMultiplication("lhs < 0, rhs < 0", InfiniteInt(-987654), InfiniteInt(-654321), "646242752934");
}
// END MULTIPLICATION TESTS

// OPERATOR>> TESTS
void testStreamInput(const std::string& inputDescription,
                     const std::string& inputText,
                     const InfiniteInt& testII,
                     const std::string& expectedIIValueAfterRead,
                     int expectedNumCharsRead)  // -1 if all characters were read
{
   SECTION(inputDescription) {
      // Setup
      std::stringstream inputStream(inputText);
      std::stringstream IIValueAfterRead;
      InfiniteInt IIToReadInto(testII); // create local copy so we can modify it

      // Run
      inputStream >> IIToReadInto;
      IIValueAfterRead << IIToReadInto;

      // Test
      CHECK(IIValueAfterRead.str() == expectedIIValueAfterRead);
      CHECK(inputStream.tellg() == expectedNumCharsRead);
   }
}

TEST_CASE("[InfiniteInt] Operator>> works as expected basic positive inputs",
          "[InfiniteInt operator>>]") {
   testStreamInput("InfiniteInt is positive, has 1 digit, and stream has 1 digit", "0", InfiniteInt(1), "0", -1);
   testStreamInput("InfiniteInt is negative, has 1 digit, and stream has 1 digit", "4", InfiniteInt(-1), "4", -1);
   testStreamInput("InfiniteInt is positive, has > 1 digit, and stream has 1 digit", "7", InfiniteInt(456), "7", -1);
   testStreamInput("InfiniteInt is negative, has > 1 digit, and stream has 1 digit", "9", InfiniteInt(-456), "9", -1);
   testStreamInput("InfiniteInt is positive, has 1 digit, and stream has > 1 digit", "9876543210987654321", InfiniteInt(1), "9876543210987654321", -1);
   testStreamInput("InfiniteInt is negative, has 1 digit, and stream has > 1 digit", "12345678901234567890", InfiniteInt(-1), "12345678901234567890", -1);
   testStreamInput("InfiniteInt is positive, has > 1 digit, and stream has > 1 digit", "12345678901234567890", InfiniteInt(456), "12345678901234567890", -1);
   testStreamInput("InfiniteInt is negative, has > 1 digit, and stream has > 1 digit", "9876543210987654321", InfiniteInt(-456), "9876543210987654321", -1);
}

TEST_CASE("[InfiniteInt] Operator>> works as expected for basic negative inputs",
          "[InfiniteInt operator>>]") {
   testStreamInput("InfiniteInt is positive and stream has 1 digit", "-7", InfiniteInt(456), "-7", -1);
   testStreamInput("InfiniteInt is negative and stream has 1 digit", "-9", InfiniteInt(-456), "-9", -1);
   testStreamInput("InfiniteInt is positive and stream has > 1 digit", "-12345678901234567890", InfiniteInt(456), "-12345678901234567890", -1);
   testStreamInput("InfiniteInt is negative and stream has > 1 digit", "-9876543210987654321", InfiniteInt(-456), "-9876543210987654321", -1);
}

TEST_CASE("[InfiniteInt] Operator>> ignores leading whitespace", "[InfiniteInt operator>>]") {
   testStreamInput("Spaces", "   7", InfiniteInt(456), "7", -1);
   testStreamInput("Tabs", "\t\t\t9", InfiniteInt(-456), "9", -1);
   testStreamInput("Newlines", "\n\n\n12345678901234567890", InfiniteInt(456), "12345678901234567890", -1);
   testStreamInput("Carriage returns", "\r\r\r9876543210987654321", InfiniteInt(-456), "9876543210987654321", -1);
}

TEST_CASE("[InfiniteInt] Operator>> stops reading at non-digit characters", "[InfiniteInt operator>>]") {
   testStreamInput("Following characters are whitespace, reading 1 digit", "0  5678", InfiniteInt(456), "0", 1);
   testStreamInput("Following characters are not whitespace, reading 1 digit", "9abc5678", InfiniteInt(456), "9", 1);
   testStreamInput("Following characters are whitespace, reading > 1 digit", "1234  5678", InfiniteInt(456), "1234", 4);
   testStreamInput("Following characters are not whitespace, reading > 1 digit", "1234abc5678", InfiniteInt(456), "1234", 4);
}

TEST_CASE("[InfiniteInt] Operator>> discards leading zeroes", "[InfiniteInt operator>>]") {
   testStreamInput("One leading zero", "05678", InfiniteInt(456), "5678", -1);
   testStreamInput("More than one leading zero", "0001234", InfiniteInt(456), "1234", -1);
   testStreamInput("All zeroes", "00000", InfiniteInt(456), "0", -1);
}

TEST_CASE("[InfiniteInt] Operator>> sets the InfiniteInt to zero for bad inputs", "[InfiniteInt operator>>]") {
   testStreamInput("First character read is non-digit, non-whitespace", "a5678", InfiniteInt(456), "0", 0);
   testStreamInput("First character after whitespace is non-digit", " z1234", InfiniteInt(456), "0", 1);
   testStreamInput("Minus sign followed by non-digit", "--1234", InfiniteInt(456), "0", 0);
}
// END OPERATOR>> TESTS