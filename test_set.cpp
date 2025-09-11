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

/**
 * Test 13: Equality operator (==) tests
 */
void test_equality_operator()
{
    // Test empty sets
    Set s1, s2;
    test_result("Empty sets equality", s1 == s2);

    // Test identical sets
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    test_result("Identical sets equality", s1 == s2);

    // Test different order (should still be equal)
    Set s3;
    s3.insert(3);
    s3.insert(1);
    s3.insert(2);
    test_result("Same elements different order", s1 == s3);

    // Test different sets
    Set s4;
    s4.insert(1);
    s4.insert(2);
    s4.insert(4);
    test_result("Different sets not equal", !(s1 == s4));

    // Test subset not equal
    Set s5;
    s5.insert(1);
    s5.insert(2);
    test_result("Subset not equal to superset", !(s5 == s1));

    // Test different sizes
    Set s6;
    s6.insert(1);
    s6.insert(2);
    s6.insert(3);
    s6.insert(4);
    test_result("Different sizes not equal", !(s1 == s6));
}

/**
 * Test 14: Subset operator (<=) tests
 */
void test_subset_operator()
{
    // Test empty set is subset of any set
    Set empty, non_empty;
    non_empty.insert(1);
    non_empty.insert(2);
    test_result("Empty set subset of non-empty", empty <= non_empty);

    // Test set is subset of itself
    test_result("Set subset of itself", non_empty <= non_empty);

    // Test proper subset
    Set subset;
    subset.insert(1);
    test_result("Proper subset", subset <= non_empty);

    // Test not subset
    Set not_subset;
    not_subset.insert(1);
    not_subset.insert(3);
    test_result("Not subset (contains element not in superset)", !(not_subset <= non_empty));

    // Test empty set subset of empty set
    Set empty2;
    test_result("Empty set subset of empty set", empty <= empty2);

    // Test non-empty not subset of empty
    test_result("Non-empty not subset of empty", !(non_empty <= empty));

    // Test equal sets
    Set equal;
    equal.insert(1);
    equal.insert(2);
    test_result("Equal sets are subsets", non_empty <= equal && equal <= non_empty);
}

/**
 * Test 15: Union operator (+) tests
 */
void test_union_operator()
{
    // Test union of empty sets
    Set empty1, empty2;
    Set union_empty = empty1 + empty2;
    test_result("Union of empty sets", union_empty.cardinality() == 0);

    // Test union with one empty set
    Set s1, s2;
    s1.insert(1);
    s1.insert(2);
    Set union_with_empty = s1 + empty1;
    test_result("Union with empty set", union_with_empty == s1);

    // Test union of disjoint sets
    s2.insert(3);
    s2.insert(4);
    Set union_disjoint = s1 + s2;
    test_result("Union of disjoint sets cardinality", union_disjoint.cardinality() == 4);
    test_result("Union of disjoint sets contains all elements",
                union_disjoint.contains(1) && union_disjoint.contains(2) &&
                union_disjoint.contains(3) && union_disjoint.contains(4));

    // Test union of overlapping sets
    Set s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set union_overlapping = s3 + s4;
    test_result("Union of overlapping sets cardinality", union_overlapping.cardinality() == 4);
    test_result("Union of overlapping sets contains all unique elements",
                union_overlapping.contains(1) && union_overlapping.contains(2) &&
                union_overlapping.contains(3) && union_overlapping.contains(4));

    // Test union with identical sets
    Set union_identical = s1 + s1;
    test_result("Union of identical sets", union_identical == s1);
}

/**
 * Test 16: Intersection operator (&) tests
 */
void test_intersection_operator()
{
    // Test intersection of empty sets
    Set empty1, empty2;
    Set intersection_empty = empty1 & empty2;
    test_result("Intersection of empty sets", intersection_empty.cardinality() == 0);

    // Test intersection with empty set
    Set s1, empty;
    s1.insert(1);
    s1.insert(2);
    Set intersection_with_empty = s1 & empty;
    test_result("Intersection with empty set", intersection_with_empty.cardinality() == 0);

    // Test intersection of disjoint sets
    Set s2;
    s2.insert(3);
    s2.insert(4);
    Set intersection_disjoint = s1 & s2;
    test_result("Intersection of disjoint sets", intersection_disjoint.cardinality() == 0);

    // Test intersection of overlapping sets
    Set s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set intersection_overlapping = s3 & s4;
    test_result("Intersection of overlapping sets cardinality", intersection_overlapping.cardinality() == 2);
    test_result("Intersection of overlapping sets contains common elements",
                intersection_overlapping.contains(2) && intersection_overlapping.contains(3) &&
                !intersection_overlapping.contains(1) && !intersection_overlapping.contains(4));

    // Test intersection of identical sets
    Set intersection_identical = s1 & s1;
    test_result("Intersection of identical sets", intersection_identical == s1);

    // Test intersection with subset
    Set subset;
    subset.insert(1);
    Set intersection_subset = s1 & subset;
    test_result("Intersection with subset", intersection_subset == subset);
}

/**
 * Test 17: Difference operator (-) tests
 */
void test_difference_operator()
{
    // Test difference of empty sets
    Set empty1, empty2;
    Set difference_empty = empty1 - empty2;
    test_result("Difference of empty sets", difference_empty.cardinality() == 0);

    // Test difference with empty set
    Set s1, empty;
    s1.insert(1);
    s1.insert(2);
    Set difference_with_empty = s1 - empty;
    test_result("Difference with empty set", difference_with_empty == s1);

    // Test difference from empty set
    Set difference_from_empty = empty - s1;
    test_result("Difference from empty set", difference_from_empty.cardinality() == 0);

    // Test difference of disjoint sets
    Set s2;
    s2.insert(3);
    s2.insert(4);
    Set difference_disjoint = s1 - s2;
    test_result("Difference of disjoint sets", difference_disjoint == s1);

    // Test difference of overlapping sets
    Set s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set difference_overlapping = s3 - s4;
    test_result("Difference of overlapping sets cardinality", difference_overlapping.cardinality() == 1);
    test_result("Difference of overlapping sets contains only unique elements",
                difference_overlapping.contains(1) && !difference_overlapping.contains(2) &&
                !difference_overlapping.contains(3) && !difference_overlapping.contains(4));

    // Test difference of identical sets
    Set difference_identical = s1 - s1;
    test_result("Difference of identical sets", difference_identical.cardinality() == 0);

    // Test difference with subset
    Set subset;
    subset.insert(1);
    Set difference_subset = s1 - subset;
    test_result("Difference with subset cardinality", difference_subset.cardinality() == 1);
    test_result("Difference with subset contains remaining elements",
                !difference_subset.contains(1) && difference_subset.contains(2));
}

/**
 * Test 18: Complex operator combinations
 */
void test_operator_combinations()
{
    // Test (A ∪ B) ∩ C
    Set A, B, C;
    A.insert(1);
    A.insert(2);
    B.insert(2);
    B.insert(3);
    C.insert(2);
    C.insert(4);
    
    Set union_AB = A + B;
    Set intersection_result = union_AB & C;
    test_result("Complex: (A ∪ B) ∩ C", intersection_result.contains(2) && intersection_result.cardinality() == 1);

    // Test (A - B) ∪ (B - A) (symmetric difference)
    Set diff_AB = A - B;
    Set diff_BA = B - A;
    Set symmetric_diff = diff_AB + diff_BA;
    test_result("Complex: Symmetric difference", 
                symmetric_diff.contains(1) && symmetric_diff.contains(3) && 
                !symmetric_diff.contains(2) && symmetric_diff.cardinality() == 2);

    // Test A ⊆ (A ∪ B)
    Set union_AB2 = A + B;
    test_result("Complex: A ⊆ (A ∪ B)", A <= union_AB2);

    // Test (A ∩ B) ⊆ A
    Set intersection_AB = A & B;
    test_result("Complex: (A ∩ B) ⊆ A", intersection_AB <= A);
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
    test_equality_operator();
    test_subset_operator();
    test_union_operator();
    test_intersection_operator();
    test_difference_operator();
    test_operator_combinations();

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