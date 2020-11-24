/** 
 * @file DEIntQueueTests.cpp
 * @brief Defines catch2 unit tests for DEIntQueue
 * @author Carl Mofjeld
 * @date 11/23/2020
*/

#include "catch.hpp"       // catch2 required header
#include "../DEIntQueue.h" // class being tested
#include <sstream>         // allow testing of queue contents via printing

// DEFAULT CONSTRUCTOR TESTS
TEST_CASE("DEIntQueue constructor creates empty queue", "[DEIntQueue]") {
   // Setup
   std::stringstream expected{""};  // Expected output from queue 
   std::stringstream actual;        // Actual output from queue

   // Run
   DEIntQueue queue;
   actual << queue;

   // Test
   CHECK(queue.numEntries() == 0);
   CHECK(actual.str() == expected.str());
}
// END DEFAULT CONSTRUCTOR TESTS

// PUSH FRONT TESTS
TEST_CASE("DEIntQueue::pushFront adds item to front of empty queue", "[DEIntQueue]") {
   // Setup
   std::stringstream expected{"1 "};   // Expected output from queue
   std::stringstream actual;           // Actual output from queue
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   
   // Run
   queue.pushFront(1);
   actual << queue;

   // Test
   CHECK(queue.numEntries() == 1);
   CHECK(actual.str() == expected.str());
}

TEST_CASE("DEIntQueue::pushFront adds item to front of non-empty queue", "[DEIntQueue]") {
   // Setup
   std::stringstream expected{"2 1 "};   // Expected output from queue
   std::stringstream actual;           // Actual output from queue
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   
   // Run
   queue.pushFront(1);
   queue.pushFront(2);
   actual << queue;

   // Test
   CHECK(queue.numEntries() == 2);
   CHECK(actual.str() == expected.str());
}
// END PUSH FRONT TESTS

// PUSH BACK TESTS
TEST_CASE("DEIntQueue::pushBack adds item to back of empty queue", "[DEIntQueue]") {
   // Setup
   std::stringstream expected{"1 "};   // Expected output from queue
   std::stringstream actual;           // Actual output from queue
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   
   // Run
   queue.pushBack(1);
   actual << queue;

   // Test
   CHECK(queue.numEntries() == 1);
   CHECK(actual.str() == expected.str());
}

TEST_CASE("DEIntQueue::pushBack adds item to back of non-empty queue", "[DEIntQueue]") {
   // Setup
   std::stringstream expected{"1 2 "};   // Expected output from queue
   std::stringstream actual;           // Actual output from queue
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   
   // Run
   queue.pushBack(1);
   queue.pushBack(2);
   actual << queue;

   // Test
   CHECK(queue.numEntries() == 2);
   CHECK(actual.str() == expected.str());
}
// END PUSH BACK TESTS

// FRONT TESTS
TEST_CASE("DEIntQueue::front returns the first item in a queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   
   SECTION("with 1 item in queue") {
      // Run
      queue.pushFront(1);

      // Test
      CHECK(queue.front() == 1);
   }

   SECTION("with >1 item in queue") {
      // Run
      queue.pushFront(1);
      queue.pushFront(2);

      // Test
      CHECK(queue.front() == 2);
   }
}

TEST_CASE("DEIntQueue::front throws an exception for an empty queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.front(), std::logic_error);
}
// END FRONT TESTS

// BACK TESTS
TEST_CASE("DEIntQueue::back returns the last item in a queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   
   SECTION("with 1 item in queue") {
      // Run
      queue.pushBack(1);

      // Test
      CHECK(queue.back() == 1);
   }

   SECTION("with >1 item in queue") {
      // Run
      queue.pushBack(1);
      queue.pushBack(2);

      // Test
      CHECK(queue.back() == 2);
   }
}

TEST_CASE("DEIntQueue::back throws an exception for an empty queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.back(), std::logic_error);
}
// END BACK TESTS

// POP_FRONT TESTS
TEST_CASE("DEIntQueue::popFront removes the first item in a queue with 1 item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   queue.pushFront(1);
   REQUIRE(queue.numEntries() == 1);
   
   // Run
   queue.popFront();

   // Test
   CHECK(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.front(), std::logic_error);
}

TEST_CASE("DEIntQueue::popFront removes the first item in a queue with > 1 item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   queue.pushFront(1);
   queue.pushFront(2);
   queue.pushFront(3);
   REQUIRE(queue.numEntries() == 3);
   REQUIRE(queue.front() == 3);
   
   // Run
   queue.popFront();

   // Test
   CHECK(queue.numEntries() == 2);
   CHECK(queue.front() == 2);
}

TEST_CASE("DEIntQueue::popFront throws an exception for an empty queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.popFront(), std::logic_error);
}
// END POP_FRONT TESTS

// POP_BACK TESTS
TEST_CASE("DEIntQueue::popBack removes the first item in a queue with 1 item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   queue.pushBack(1);
   REQUIRE(queue.numEntries() == 1);
   
   // Run
   queue.popBack();

   // Test
   CHECK(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.front(), std::logic_error);
}

TEST_CASE("DEIntQueue::popBack removes the first item in a queue with > 1 item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   queue.pushBack(1);
   queue.pushBack(2);
   queue.pushBack(3);
   REQUIRE(queue.numEntries() == 3);
   REQUIRE(queue.back() == 3);
   
   // Run
   queue.popBack();

   // Test
   CHECK(queue.numEntries() == 2);
   CHECK(queue.back() == 2);
}

TEST_CASE("DEIntQueue::popBack throws an exception for an empty queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   REQUIRE(queue.numEntries() == 0);
   REQUIRE_THROWS_AS(queue.popBack(), std::logic_error);
}
// END POP_BACK TESTS

// BIG THREE TESTS
TEST_CASE("DEIntQueue Copy constructor deep copies another queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue original;
   std::stringstream originalBeforeChange;
   std::stringstream originalAfterChange;
   std::stringstream actual;

   SECTION("copied queue is empty") {
      // Run
      originalBeforeChange << original;
      DEIntQueue copy(original);
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has 1 entry") {
      // Run
      original.pushFront(1);
      originalBeforeChange << original;
      DEIntQueue copy(original);
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has > 1 entry") {
      // Run
      for (int i = 0; i < 3; i++) {
         original.pushFront(i);
      }
      originalBeforeChange << original;
      DEIntQueue copy(original);
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }
}

TEST_CASE("DEIntQueue assignment operator deep copies another queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue original;
   DEIntQueue copy;
   std::stringstream originalBeforeChange;
   std::stringstream originalAfterChange;
   std::stringstream actual;

   SECTION("copied queue is empty, copying queue is empty") {
      // Run
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has 1 entry, copying queue is empty") {
      // Run
      original.pushFront(1);
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has > 1 entry, copying queue is empty") {
      // Run
      for (int i = 0; i < 3; i++) {
         original.pushFront(i);
      }
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue is empty, copying queue is not empty") {
      // Run
      copy.pushFront(4);
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has 1 entry, copying queue is not empty") {
      // Run
      copy.pushFront(4);
      original.pushFront(1);
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }

   SECTION("copied queue has > 1 entry, copying queue is not empty") {
      // Run
      copy.pushFront(4);
      for (int i = 0; i < 3; i++) {
         original.pushFront(i);
      }
      originalBeforeChange << original;
      copy = original;
      actual << copy;

      // Test
      CHECK(copy.numEntries() == original.numEntries());
      CHECK(actual.str() == originalBeforeChange.str());

      // Check for deep copy
      // Run
      copy.pushFront(1);
      originalAfterChange << original;

      // Test
      CHECK(originalBeforeChange.str() == originalAfterChange.str());
   }
}
// END BIG THREE TESTS

// ITERATOR TESTS
TEST_CASE("DEIntQueue iterator can access queue items in forward order", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }
   DEIntQueue::iterator iter = queue.begin();
   REQUIRE(iter != queue.end());

   // Run
   for (int i = 0; i < 3; i++) {
      // Test
      CHECK(*iter == i);
      ++iter;
   }

   // Test
   REQUIRE(iter == queue.end());
}

TEST_CASE("DEIntQueue iterator returned by begin references first item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }

   // Run
   DEIntQueue::iterator iter = queue.begin();

   // Test
   REQUIRE(*iter == 0);
}

TEST_CASE("DEIntQueue iterator returned by last references last item", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }

   // Run
   DEIntQueue::iterator iter = queue.last();

   // Test
   REQUIRE(*iter == 2);
}

TEST_CASE("DEIntQueue iterator can access queue items in reverse order", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }
   DEIntQueue::iterator iter = queue.last();
   REQUIRE(iter != queue.end());

   // Run
   for (int i = 2; i >= 0; i--) {
      // Test
      CHECK(*iter == i);
      --iter;
   }

   // Test
   REQUIRE(iter == queue.end());
}

TEST_CASE("DEIntQueue iterator can modify items in the queue", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   std::stringstream expected{"0 3 2 "};
   std::stringstream actual;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }
   DEIntQueue::iterator iter = queue.begin();
   REQUIRE(iter != queue.end());

   // Run
   ++iter;
   *iter = 3;
   actual << queue;

   // Test
   REQUIRE(actual.str() == expected.str());
}

TEST_CASE("DEIntQueue iterator returned by begin() is equal to the one returned by end() after a decrement", "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   for (int i = 0; i < 3; i++) {
      queue.pushBack(i);
   }
   DEIntQueue::iterator iter = queue.begin();
   REQUIRE(iter != queue.end());

   // Run
   --iter;

   // Test
   REQUIRE(iter == queue.end());
}

TEST_CASE("DEIntQueue iterator for an empty list throws exceptions for increment, decrement, and dereference",
   "[DEIntQueue]") {
   // Setup
   DEIntQueue queue;
   DEIntQueue::iterator iter = queue.begin();

   // Test
   CHECK(iter == queue.end());
   CHECK_THROWS_AS(iter++, std::out_of_range);
   CHECK_THROWS_AS(++iter, std::out_of_range);
   CHECK_THROWS_AS(iter--, std::out_of_range);
   CHECK_THROWS_AS(--iter, std::out_of_range);
   CHECK_THROWS_AS(*iter, std::out_of_range);
}
// END ITERATOR TESTS