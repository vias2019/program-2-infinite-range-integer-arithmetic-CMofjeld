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
TEST_CASE("Default constructor creates an InfiniteInt representing 0", "[InfiniteInt]") {
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

TEST_CASE("Int constructor correctly converts to InfiniteInt", "[InfiniteInt]") {
   testIntConstructor("Postive integers < INT_MAX", 123456);
   testIntConstructor("Negative integers > INT_MIN", -123456);
   testIntConstructor("Zero", 0);
   testIntConstructor("INT_MAX", INT_MAX);
   testIntConstructor("INT_MIN", INT_MIN);
}
// END CONSTRUCTOR TESTS

// DEEP COPY TESTS
void testCopyCtor(const std::string& inputDescription,
                  const InfiniteInt& original) {
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

TEST_CASE("Copy constructor performs a deep copy", "[InfiniteInt deep copy]") {
   testCopyCtor("Original > 0 with 1 digit", InfiniteInt(4));
   testCopyCtor("Original < 0 with 1 digit", InfiniteInt(-4));
   testCopyCtor("Original > 0 with > 1 digit", InfiniteInt(123));
   testCopyCtor("Original < 0 with > 1 digit", InfiniteInt(-123));
   testCopyCtor("Original = 0", InfiniteInt(0));
}

void testAssignment(const std::string& inputDescription,
                    int copyControlInitialVal,
                    int copyToChangeInitialVal,
                    int originalInitialVal) {
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

TEST_CASE("Operator= performs a deep copy", "[InfiniteInt deep copy]") {
   testAssignment("Original > 0 with 1 digit", -123, 321, 4);
   testAssignment("Original < 0 with 1 digit", 8, -9, -4);
   testAssignment("Original > 0 with > 1 digit", 123456, -321, 123);
   testAssignment("Original < 0 with > 1 digit", 321, -123456, -123);
   testAssignment("Original = 0", 123, -9, 0);
}
// END DEEP COPY TESTS

// ADDITION TESTS
void testAddition(const std::string& inputDescription,
                  const InfiniteInt& lhs,
                  const InfiniteInt& rhs,
                  const std::string& expectedResult) {
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

TEST_CASE("Addition produces expected result when both InfiniteInts have the same sign",
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

TEST_CASE("Addition handles InfiniteInts with different signs", "[InfiniteInt::operator+]") {
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
                  bool expectedResult) {
   SECTION(inputDescription) {
      // Test
      REQUIRE((lhs == rhs) == expectedResult);
   }
}

TEST_CASE("Equality operator returns true when both are equal", "[InfiniteInt]") {
   testEquality("Both > 0 and equal", InfiniteInt(123456), InfiniteInt(123456), true);
   testEquality("Both < 0 and equal", InfiniteInt(-456789), InfiniteInt(-456789), true);
   testEquality("Both = 0 and equal", InfiniteInt(0), InfiniteInt(0), true);
}

TEST_CASE("Equality operator returns false when # of digits differ", "[InfiniteInt]") {
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
                  bool expectedResult) {
   SECTION(inputDescription) {
      // Test
      REQUIRE((lhs < rhs) == expectedResult);
   }
}

TEST_CASE("Less than operator returns false when both are equal", "[InfiniteInt]") {
   testLessThan("Both > 0 and equal", InfiniteInt(123456), InfiniteInt(123456), false);
   testLessThan("Both < 0 and equal", InfiniteInt(-456789), InfiniteInt(-456789), false);
   testLessThan("Both = 0 and equal", InfiniteInt(0), InfiniteInt(0), false);
}

TEST_CASE("Less than operator correctly handles differences in sign", "[InfiniteInt]") {
   testLessThan("lhs negative, rhs positive", InfiniteInt(-123456), InfiniteInt(123456), true);
   testLessThan("lhs positive, rhs negative", InfiniteInt(456789), InfiniteInt(-456789), false);
}

TEST_CASE("Less than operator returns false when # of digits differ", "[InfiniteInt]") {
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
                  const InfiniteInt& expectedResult) {
   SECTION(inputDescription) {
      // Setup
      std::stringstream stringResult;

      // Run
      InfiniteInt testResult = lhs - rhs;

      // Test
      CHECK(testResult == expectedResult);
   }
}

TEST_CASE("Subtraction handles InfiniteInts with same sign", "[InfiniteInt::operator-]") {
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

TEST_CASE("Subtraction handles InfiniteInts with different signs", "[InfiniteInt::operator-]") {
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
                  const std::string& expectedResult) {
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

TEST_CASE("Multiplication handles either argument being zero", "[InfiniteInt::operator*]") {
   testMultiplication("lhs = 0, rhs > 0", InfiniteInt(0), InfiniteInt(321), "0");
   testMultiplication("lhs = 0, rhs < 0", InfiniteInt(0), InfiniteInt(-2), "0");
   testMultiplication("lhs = 0, rhs = 0", InfiniteInt(0), InfiniteInt(0), "0");
   testMultiplication("lhs > 0, rhs = 0", InfiniteInt(2), InfiniteInt(0), "0");
   testMultiplication("lhs < 0, rhs = 0", InfiniteInt(-321), InfiniteInt(0), "0");
}

TEST_CASE("Multiplication handles either argument being one or negative one", "[InfiniteInt::operator*]") {
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

TEST_CASE("Multiplication handles both arguments having > 1 digit", "[InfiniteInt::operator*]") {
   testMultiplication("lhs > 0, rhs > 0", InfiniteInt(123456), InfiniteInt(456789), "56393342784");
   testMultiplication("lhs > 0, rhs < 0", InfiniteInt(456789), InfiniteInt(-123456), "-56393342784");
   testMultiplication("lhs < 0, rhs > 0", InfiniteInt(-654321), InfiniteInt(987654), "-646242752934");
   testMultiplication("lhs < 0, rhs < 0", InfiniteInt(-987654), InfiniteInt(-654321), "646242752934");
}
// END MULTIPLICATION TESTS