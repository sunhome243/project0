//
// test_set.cpp
// CS 271 Set Project0
//
// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#include <iostream>
#include <cassert>
#include "set.cpp"

using namespace std;

// Test result counter
int tests_passed = 0;
int total_tests = 0;

void test_result(const string &test_name, bool passed)
{
    total_tests++;
    if (passed)
    {
        tests_passed++;
        cout << "O" << test_name << " PASSED" << endl;
    }
    else
    {
        cout << "X" << test_name << " FAILED" << endl;
    }
}

/**
 * Test 1: Basic insert functionality
 */
void test_basic_insert()
{
    Set s;

    // Insert single element
    s.insert(5);
    test_result("Insert single element", s.contains(5) && s.cardinality() == 1);

    // Insert multiple elements
    s.insert(10);
    s.insert(3);
    test_result("Insert multiple elements",
                s.contains(5) && s.contains(10) && s.contains(3) && s.cardinality() == 3);
}

/**
 * Test 2: Insert duplicate data (should be ignored)
 */
void test_insert_duplicates()
{
    Set s;

    s.insert(7);
    int original_size = s.cardinality();

    s.insert(7); // Duplicate
    test_result("Insert duplicate data",
                s.cardinality() == original_size && s.contains(7));

    // Multiple duplicates
    s.insert(7);
    s.insert(7);
    test_result("Insert multiple duplicates",
                s.cardinality() == original_size && s.contains(7));
}

/**
 * Test 3: Basic remove functionality
 */
void test_basic_remove()
{
    Set s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    s.remove(2);
    test_result("Remove existing element",
                !s.contains(2) && s.contains(1) && s.contains(3) && s.cardinality() == 2);
}

/**
 * Test 4: Remove from head node (special case)
 */
void test_remove_head()
{
    Set s;
    s.insert(10);
    s.insert(20); // 20 becomes new head

    s.remove(20); // Remove head
    test_result("Remove head node",
                !s.contains(20) && s.contains(10) && s.cardinality() == 1);

    s.remove(10); // Remove last element (also head)
    test_result("Remove last element as head",
                !s.contains(10) && s.cardinality() == 0);
}

/**
 * Test 5: Remove non-existing data
 */
void test_remove_nonexistent()
{
    Set s;
    s.insert(1);
    s.insert(2);
    int original_size = s.cardinality();

    s.remove(99); // Non-existent element
    test_result("Remove non-existing element",
                s.cardinality() == original_size && s.contains(1) && s.contains(2));
}

/**
 * Test 6: Remove from empty set
 */
void test_remove_from_empty()
{
    Set s;

    s.remove(5); // Remove from empty set
    test_result("Remove from empty set", s.cardinality() == 0);
}

/**
 * Test 7: Cardinality on empty set
 */
void test_cardinality_empty()
{
    Set s;
    test_result("Cardinality of empty set", s.cardinality() == 0);
}

/**
 * Test 8: Insert, insert, check cardinality
 */
void test_insert_insert_cardinality()
{
    Set s;

    s.insert(5);
    test_result("Insert one, cardinality = 1", s.cardinality() == 1);

    s.insert(10);
    test_result("Insert two, cardinality = 2", s.cardinality() == 2);

    s.insert(15);
    test_result("Insert three, cardinality = 3", s.cardinality() == 3);
}

/**
 * Test 9: Remove, insert, then check cardinality
 */
void test_remove_insert_cardinality()
{
    Set s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    test_result("Initial cardinality = 3", s.cardinality() == 3);

    s.remove(2);
    test_result("After remove, cardinality = 2", s.cardinality() == 2);

    s.insert(4);
    test_result("After insert, cardinality = 3", s.cardinality() == 3);

    test_result("Contains check after remove/insert",
                !s.contains(2) && s.contains(4) && s.contains(1) && s.contains(3));
}

/**
 * Test 10: Insert, delete, insert, delete, cardinality pattern
 */
void test_insert_delete_pattern()
{
    Set s;

    // Insert 5
    s.insert(5);
    test_result("Pattern: Insert 5, cardinality = 1", s.cardinality() == 1);

    // Delete 5
    s.remove(5);
    test_result("Pattern: Delete 5, cardinality = 0", s.cardinality() == 0);

    // Insert 10
    s.insert(10);
    test_result("Pattern: Insert 10, cardinality = 1", s.cardinality() == 1);

    // Delete 10
    s.remove(10);
    test_result("Pattern: Delete 10, cardinality = 0", s.cardinality() == 0);

    // Final state check
    test_result("Pattern: Final empty state",
                s.cardinality() == 0 && !s.contains(5) && !s.contains(10));
}

/**
 * Test 11: Contains method comprehensive test
 */
void test_contains_comprehensive()
{
    Set s;

    // Contains on empty set
    test_result("Contains on empty set", !s.contains(5));

    s.insert(1);
    s.insert(2);
    s.insert(3);

    // Contains existing elements
    test_result("Contains existing elements",
                s.contains(1) && s.contains(2) && s.contains(3));

    // Contains non-existing element
    test_result("Contains non-existing element", !s.contains(99));

    // Contains after removal
    s.remove(2);
    test_result("Contains after removal",
                s.contains(1) && !s.contains(2) && s.contains(3));
}

/**
 * Test 12: Large set operations
 */
void test_large_set()
{
    Set s;

    // Insert many elements
    for (int i = 0; i < 100; i++)
    {
        s.insert(i);
    }
    test_result("Large set cardinality", s.cardinality() == 100);

    // Check some elements
    test_result("Large set contains check",
                s.contains(0) && s.contains(50) && s.contains(99));

    // Remove some elements
    for (int i = 0; i < 50; i++)
    {
        s.remove(i);
    }
    test_result("Large set after removal", s.cardinality() == 50);

    // Check removed elements
    test_result("Large set removal check",
                !s.contains(25) && s.contains(75) && !s.contains(0));
}

int main()
{
    cout << "Starting Set Implementation Tests" << endl;
    cout << "=================================" << endl
         << endl;

    test_basic_insert();
    test_insert_duplicates();
    test_basic_remove();
    test_remove_head();
    test_remove_nonexistent();
    test_remove_from_empty();
    test_cardinality_empty();
    test_insert_insert_cardinality();
    test_remove_insert_cardinality();
    test_insert_delete_pattern();
    test_contains_comprehensive();
    test_large_set();

    cout << endl
         << "=================================" << endl;
    cout << "Test Results: " << tests_passed << "/" << total_tests << " tests passed" << endl;

    if (tests_passed == total_tests)
    {
        cout << "O All tests PASSED!" << endl;
    }
    else
    {
        cout << "X Some tests FAILED!" << endl;
    }

    return 0;
}