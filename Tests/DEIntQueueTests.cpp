/** 
 * @file DEIntQueueTests.cpp
 * @brief Defines catch2 unit tests for DEIntQueue
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "catch.hpp"       // catch2 required header
#include "../DEIntQueue.h" // class being tested
#include <sstream>         // allow testing of queue contents via printing

TEST_CASE("DEIntQueue constructor creates empty queue", "[DEIntQueue") {
   std::stringstream expected{ "" };  // Expected output from queue 
   std::stringstream actual;          // Actual output from queue

   DEIntQueue queue;
   actual << queue;
   CHECK(queue.numEntries() == 0);
   CHECK(actual.str() == expected.str());
}