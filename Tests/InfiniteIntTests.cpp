/** 
 * @file InfiniteIntTests.cpp
 * @brief Defines catch2 unit tests for InfiniteInt
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "catch.hpp"          // catch2 required header
#include "../InfiniteInt.h"   // class being tested
#include <sstream>            // allow testing of InfiniteInt contents via printing

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

TEST_CASE("Addition produces expected result when both InfiniteInts are positive or both are negative",
          "[InfiniteInt]") {
   testAddition("Both > 0, same # of digits", InfiniteInt(123456), InfiniteInt(456789), "580245");
   testAddition("Both < 0, same # of digits", InfiniteInt(-123456), InfiniteInt(-456789), "-580245");
   testAddition("lhs = 0, rhs > 0", InfiniteInt(0), InfiniteInt(456789), "456789");
   testAddition("lhs > 0, rhs = 0", InfiniteInt(456789), InfiniteInt(0), "456789");
   testAddition("Both > 0, lhs has more digits", InfiniteInt(123456), InfiniteInt(789), "124245");
   testAddition("Both < 0, lhs has more digits", InfiniteInt(-123456), InfiniteInt(-789), "-124245");
   testAddition("Both > 0, rhs has more digits", InfiniteInt(789), InfiniteInt(123456), "124245");
   testAddition("Both < 0, rhs has more digits", InfiniteInt(-789), InfiniteInt(-123456), "-124245");
   testAddition("Both = 0", InfiniteInt(0), InfiniteInt(0), "0");
}

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