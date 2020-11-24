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