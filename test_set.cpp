//
// test_set.cpp
// CS 271 Set Project0
//
// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#include <iostream>
#include <cassert>
#include "set.h"
#include <climits>

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
    Set<int> s;

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
    Set<int> s;

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
    Set<int> s;
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
    Set<int> s;
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
    Set<int> s;
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
    Set<int> s;

    s.remove(5); // Remove from empty set
    test_result("Remove from empty set", s.cardinality() == 0);
}

/**
 * Test 7: Cardinality on empty set
 */
void test_cardinality_empty()
{
    Set<int> s;
    test_result("Cardinality of empty set", s.cardinality() == 0);
}

/**
 * Test 8: Insert, insert, check cardinality
 */
void test_insert_insert_cardinality()
{
    Set<int> s;

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
    Set<int> s;
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
    Set<int> s;

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
    Set<int> s;

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
    Set<int> s;

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
    Set<int> s1, s2;
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
    Set<int> s3;
    s3.insert(3);
    s3.insert(1);
    s3.insert(2);
    test_result("Same elements different order", s1 == s3);

    // Test different sets
    Set<int> s4;
    s4.insert(1);
    s4.insert(2);
    s4.insert(4);
    test_result("Different sets not equal", !(s1 == s4));

    // Test subset not equal
    Set<int> s5;
    s5.insert(1);
    s5.insert(2);
    test_result("Subset not equal to superset", !(s5 == s1));

    // Test different sizes
    Set<int> s6;
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
    Set<int> empty, non_empty;
    non_empty.insert(1);
    non_empty.insert(2);
    test_result("Empty set subset of non-empty", empty <= non_empty);

    // Test set is subset of itself
    test_result("Set subset of itself", non_empty <= non_empty);

    // Test proper subset
    Set<int> subset;
    subset.insert(1);
    test_result("Proper subset", subset <= non_empty);

    // Test not subset
    Set<int> not_subset;
    not_subset.insert(1);
    not_subset.insert(3);
    test_result("Not subset (contains element not in superset)", !(not_subset <= non_empty));

    // Test empty set subset of empty set
    Set<int> empty2;
    test_result("Empty set subset of empty set", empty <= empty2);

    // Test non-empty not subset of empty
    test_result("Non-empty not subset of empty", !(non_empty <= empty));

    // Test equal sets
    Set<int> equal;
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
    Set<int> empty1, empty2;
    Set<int> union_empty = empty1 + empty2;
    test_result("Union of empty sets", union_empty.cardinality() == 0);

    // Test union with one empty set
    Set<int> s1, s2;
    s1.insert(1);
    s1.insert(2);
    Set<int> union_with_empty = s1 + empty1;
    test_result("Union with empty set", union_with_empty == s1);

    // Test union of disjoint sets
    s2.insert(3);
    s2.insert(4);
    Set<int> union_disjoint = s1 + s2;
    test_result("Union of disjoint sets cardinality", union_disjoint.cardinality() == 4);
    test_result("Union of disjoint sets contains all elements",
                union_disjoint.contains(1) && union_disjoint.contains(2) &&
                    union_disjoint.contains(3) && union_disjoint.contains(4));

    // Test union of overlapping sets
    Set<int> s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set<int> union_overlapping = s3 + s4;
    test_result("Union of overlapping sets cardinality", union_overlapping.cardinality() == 4);
    test_result("Union of overlapping sets contains all unique elements",
                union_overlapping.contains(1) && union_overlapping.contains(2) &&
                    union_overlapping.contains(3) && union_overlapping.contains(4));

    // Test union with identical sets
    Set<int> union_identical = s1 + s1;
    test_result("Union of identical sets", union_identical == s1);
}

/**
 * Test 16: Intersection operator (&) tests
 */
void test_intersection_operator()
{
    // Test intersection of empty sets
    Set<int> empty1, empty2;
    Set<int> intersection_empty = empty1 & empty2;
    test_result("Intersection of empty sets", intersection_empty.cardinality() == 0);

    // Test intersection with empty set
    Set<int> s1, empty;
    s1.insert(1);
    s1.insert(2);
    Set<int> intersection_with_empty = s1 & empty;
    test_result("Intersection with empty set", intersection_with_empty.cardinality() == 0);

    // Test intersection of disjoint sets
    Set<int> s2;
    s2.insert(3);
    s2.insert(4);
    Set<int> intersection_disjoint = s1 & s2;
    test_result("Intersection of disjoint sets", intersection_disjoint.cardinality() == 0);

    // Test intersection of overlapping sets
    Set<int> s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set<int> intersection_overlapping = s3 & s4;
    test_result("Intersection of overlapping sets cardinality", intersection_overlapping.cardinality() == 2);
    test_result("Intersection of overlapping sets contains common elements",
                intersection_overlapping.contains(2) && intersection_overlapping.contains(3) &&
                    !intersection_overlapping.contains(1) && !intersection_overlapping.contains(4));

    // Test intersection of identical sets
    Set<int> intersection_identical = s1 & s1;
    test_result("Intersection of identical sets", intersection_identical == s1);

    // Test intersection with subset
    Set<int> subset;
    subset.insert(1);
    Set<int> intersection_subset = s1 & subset;
    test_result("Intersection with subset", intersection_subset == subset);
}

/**
 * Test 17: Difference operator (-) tests
 */
void test_difference_operator()
{
    // Test difference of empty sets
    Set<int> empty1, empty2;
    Set<int> difference_empty = empty1 - empty2;
    test_result("Difference of empty sets", difference_empty.cardinality() == 0);

    // Test difference with empty set
    Set<int> s1, empty;
    s1.insert(1);
    s1.insert(2);
    Set<int> difference_with_empty = s1 - empty;
    test_result("Difference with empty set", difference_with_empty == s1);

    // Test difference from empty set
    Set<int> difference_from_empty = empty - s1;
    test_result("Difference from empty set", difference_from_empty.cardinality() == 0);

    // Test difference of disjoint sets
    Set<int> s2;
    s2.insert(3);
    s2.insert(4);
    Set<int> difference_disjoint = s1 - s2;
    test_result("Difference of disjoint sets", difference_disjoint == s1);

    // Test difference of overlapping sets
    Set<int> s3, s4;
    s3.insert(1);
    s3.insert(2);
    s3.insert(3);
    s4.insert(2);
    s4.insert(3);
    s4.insert(4);
    Set<int> difference_overlapping = s3 - s4;
    test_result("Difference of overlapping sets cardinality", difference_overlapping.cardinality() == 1);
    test_result("Difference of overlapping sets contains only unique elements",
                difference_overlapping.contains(1) && !difference_overlapping.contains(2) &&
                    !difference_overlapping.contains(3) && !difference_overlapping.contains(4));

    // Test difference of identical sets
    Set<int> difference_identical = s1 - s1;
    test_result("Difference of identical sets", difference_identical.cardinality() == 0);

    // Test difference with subset
    Set<int> subset;
    subset.insert(1);
    Set<int> difference_subset = s1 - subset;
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
    Set<int> A, B, C;
    A.insert(1);
    A.insert(2);
    B.insert(2);
    B.insert(3);
    C.insert(2);
    C.insert(4);

    Set<int> union_AB = A + B;
    Set<int> intersection_result = union_AB & C;
    test_result("Complex: (A ∪ B) ∩ C", intersection_result.contains(2) && intersection_result.cardinality() == 1);

    // Test (A - B) ∪ (B - A) (symmetric difference)
    Set<int> diff_AB = A - B;
    Set<int> diff_BA = B - A;
    Set<int> symmetric_diff = diff_AB + diff_BA;
    test_result("Complex: Symmetric difference",
                symmetric_diff.contains(1) && symmetric_diff.contains(3) &&
                    !symmetric_diff.contains(2) && symmetric_diff.cardinality() == 2);

    // Test A ⊆ (A ∪ B)
    Set<int> union_AB2 = A + B;
    test_result("Complex: A ⊆ (A ∪ B)", A <= union_AB2);

    // Test (A ∩ B) ⊆ A
    Set<int> intersection_AB = A & B;
    test_result("Complex: (A ∩ B) ⊆ A", intersection_AB <= A);
}

void time_test()
{
    Set<int> S;
    // TO-DO: generate large set
    Set<int> T;
    // TO-DO: generate large set
    int total = 0;

    int val = rand() % 100000;
    auto begin = std::chrono::high_resolution_clock::now();
    S.insert(val);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "insert time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    S.remove(val);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "remove time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    S.cardinality();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "cardinality time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    S.empty();
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "empty time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    val = rand() % 100000;
    begin = std::chrono::high_resolution_clock::now();
    bool r = S.contains(val);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "contains time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    r = (S == T);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "equality time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    r = (S <= T);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "subset time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    Set<int> U = (S + T);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "union time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    U = (S & T);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "intersection time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    U = (S - T);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "difference time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();
    cout << "Total time: " << total << endl;
}

void test_empty_set_operations() {
    cout << "=== Empty Set Edge Cases ===" << endl;
    
    Set<int> empty;
    
    // Operations on empty set
    empty.remove(1);                    // Remove from empty
    empty.remove(0);                    // Remove zero from empty
    empty.remove(-1);                   // Remove negative from empty
    cout << "Empty after removes: " << empty.empty() << endl;
    
    // Contains on empty
    cout << "Empty contains 0: " << empty.contains(0) << endl;
    cout << "Empty contains INT_MAX: " << empty.contains(INT_MAX) << endl;
    cout << "Empty contains INT_MIN: " << empty.contains(INT_MIN) << endl;
    
    // to_string on empty
    cout << "Empty to_string: '" << empty.to_string() << "'" << endl;
    cout << "Empty to_string length: " << empty.to_string().length() << endl;
}

void test_single_element_boundaries() {
    cout << "\n=== Single Element Boundaries ===" << endl;
    
    // Single element operations
    Set<int> single;
    single.insert(42);
    
    cout << "Single element to_string: '" << single.to_string() << "'" << endl;
    
    // Remove the only element
    single.remove(42);
    cout << "After removing only element - empty: " << single.empty() << endl;
    cout << "After removing only element - cardinality: " << single.cardinality() << endl;
    cout << "After removing only element - to_string: '" << single.to_string() << "'" << endl;
    
    // Insert same element multiple times
    Set<int> duplicates;
    duplicates.insert(5);
    duplicates.insert(5);
    duplicates.insert(5);
    cout << "After multiple same inserts - cardinality: " << duplicates.cardinality() << endl;
}

void test_integer_boundaries() {
    cout << "\n=== Integer Boundary Values ===" << endl;
    
    Set<int> boundaries;
    
    // Test boundary integer values
    boundaries.insert(INT_MAX);         // 2147483647
    boundaries.insert(INT_MIN);         // -2147483648
    boundaries.insert(0);
    boundaries.insert(-1);
    boundaries.insert(1);
    
    cout << "Boundary set cardinality: " << boundaries.cardinality() << endl;
    cout << "Contains INT_MAX: " << boundaries.contains(INT_MAX) << endl;
    cout << "Contains INT_MIN: " << boundaries.contains(INT_MIN) << endl;
    cout << "Contains 0: " << boundaries.contains(0) << endl;
    
    // Remove boundary values
    boundaries.remove(INT_MAX);
    cout << "After removing INT_MAX, contains it: " << boundaries.contains(INT_MAX) << endl;
    
    boundaries.remove(INT_MIN);
    cout << "After removing INT_MIN, contains it: " << boundaries.contains(INT_MIN) << endl;
}

void test_string_edge_cases() {
    cout << "\n=== String Edge Cases ===" << endl;
    
    Set<string> str_set;
    
    // Empty string
    str_set.insert("");
    cout << "Empty string inserted, cardinality: " << str_set.cardinality() << endl;
    cout << "Contains empty string: " << str_set.contains("") << endl;
    
    // Single character strings
    str_set.insert("a");
    str_set.insert(" ");               // Space
    str_set.insert("\n");              // Newline
    str_set.insert("\t");              // Tab
    
    cout << "Special chars cardinality: " << str_set.cardinality() << endl;
    cout << "Contains space: " << str_set.contains(" ") << endl;
    cout << "Contains newline: " << str_set.contains("\n") << endl;
    
    // to_string with empty string in set
    cout << "String set to_string: '" << str_set.to_string() << "'" << endl;
}

void test_equality_edge_cases() {
    cout << "\n=== Equality Edge Cases ===" << endl;
    
    // Self equality
    Set<int> self;
    self.insert(1);
    self.insert(2);
    cout << "Self equality: " << (self == self) << endl;
    
    // Empty sets equality
    Set<int> empty1, empty2;
    cout << "Two empty sets equal: " << (empty1 == empty2) << endl;
    
    // Different sizes
    Set<int> size1, size2;
    size1.insert(1);
    size2.insert(1);
    size2.insert(2);
    cout << "Different sizes equal: " << (size1 == size2) << endl;
    
    // Same elements, different order
    Set<int> order1, order2;
    order1.insert(1);
    order1.insert(2);
    order1.insert(3);
    
    order2.insert(3);
    order2.insert(1);
    order2.insert(2);
    cout << "Same elements different order equal: " << (order1 == order2) << endl;
}

void test_subset_edge_cases() {
    cout << "\n=== Subset Edge Cases ===" << endl;
    
    // Empty subset relationships
    Set<int> empty, non_empty;
    non_empty.insert(1);
    
    cout << "Empty <= Empty: " << (empty <= empty) << endl;
    cout << "Empty <= NonEmpty: " << (empty <= non_empty) << endl;
    cout << "NonEmpty <= Empty: " << (non_empty <= empty) << endl;
    
    // Self subset
    Set<int> self_sub;
    self_sub.insert(1);
    self_sub.insert(2);
    cout << "Self subset: " << (self_sub <= self_sub) << endl;
    
    // Equal sets are mutual subsets
    Set<int> equal1, equal2;
    equal1.insert(5);
    equal1.insert(10);
    equal2.insert(10);
    equal2.insert(5);
    
    cout << "Equal1 <= Equal2: " << (equal1 <= equal2) << endl;
    cout << "Equal2 <= Equal1: " << (equal2 <= equal1) << endl;
    
    // Single element subset
    Set<int> single_elem, multi_elem;
    single_elem.insert(7);
    multi_elem.insert(7);
    multi_elem.insert(8);
    multi_elem.insert(9);
    
    cout << "Single element subset: " << (single_elem <= multi_elem) << endl;
}

void test_memory_boundaries() {
    cout << "\n=== Memory/Copy Edge Cases ===" << endl;
    
    // Self assignment
    Set<int> self_assign;
    self_assign.insert(1);
    self_assign.insert(2);
    self_assign = self_assign;
    cout << "Self assignment cardinality: " << self_assign.cardinality() << endl;
    cout << "Self assignment contains 1: " << self_assign.contains(1) << endl;
    
    // Copy empty set
    Set<int> empty_orig;
    Set<int> empty_copy(empty_orig);
    cout << "Copy of empty set is empty: " << empty_copy.empty() << endl;
    
    // Assign to non-empty from empty
    Set<int> target;
    target.insert(99);
    target = empty_orig;
    cout << "Assign empty to non-empty result empty: " << target.empty() << endl;
}

void test_remove_edge_cases() {
    cout << "\n=== Remove Edge Cases ===" << endl;
    
    Set<int> remove_test;
    remove_test.insert(1);
    remove_test.insert(2);
    remove_test.insert(3);
    
    // Remove head (first inserted is last in list due to head insertion)
    remove_test.remove(3);
    cout << "After removing head, cardinality: " << remove_test.cardinality() << endl;
    cout << "After removing head, to_string: '" << remove_test.to_string() << "'" << endl;
    
    // Remove non-existent
    remove_test.remove(99);
    cout << "After removing non-existent, cardinality: " << remove_test.cardinality() << endl;
    
    // Remove same element twice
    remove_test.remove(2);
    remove_test.remove(2);  // Remove again
    cout << "After removing same element twice, cardinality: " << remove_test.cardinality() << endl;
    
    // Remove last remaining
    remove_test.remove(1);
    cout << "After removing last element, empty: " << remove_test.empty() << endl;
    
    // Remove from now-empty set
    remove_test.remove(1);
    cout << "Remove from empty set, still empty: " << remove_test.empty() << endl;
}

void test_contains_edge_cases() {
    cout << "\n=== Contains Edge Cases ===" << endl;
    
    Set<int> contains_test;
    
    // Contains on empty
    cout << "Empty set contains 0: " << contains_test.contains(0) << endl;
    
    // Add and test immediately
    contains_test.insert(42);
    cout << "Immediately after insert, contains 42: " << contains_test.contains(42) << endl;
    
    // Test boundary of what was inserted
    cout << "Contains 41: " << contains_test.contains(41) << endl;
    cout << "Contains 43: " << contains_test.contains(43) << endl;
    
    // Remove and test immediately
    contains_test.remove(42);
    cout << "Immediately after remove, contains 42: " << contains_test.contains(42) << endl;
}

void test_insertion_order_edge_cases() {
    cout << "\n=== Insertion Order Edge Cases ===" << endl;
    
    Set<int> order_test;
    
    // Insert in ascending order
    order_test.insert(1);
    order_test.insert(2);
    order_test.insert(3);
    cout << "Ascending insertion to_string: '" << order_test.to_string() << "'" << endl;
    
    Set<int> desc_test;
    // Insert in descending order  
    desc_test.insert(3);
    desc_test.insert(2);
    desc_test.insert(1);
    cout << "Descending insertion to_string: '" << desc_test.to_string() << "'" << endl;
    
    Set<int> random_test;
    // Insert in random order
    random_test.insert(2);
    random_test.insert(1);
    random_test.insert(3);
    cout << "Random insertion to_string: '" << random_test.to_string() << "'" << endl;
    
    // All should be equal despite different insertion orders
    cout << "All insertion orders equal: " << 
        ((order_test == desc_test) && (desc_test == random_test)) << endl;
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
    test_empty_set_operations();
    test_single_element_boundaries();
    test_integer_boundaries();
    test_string_edge_cases();
    test_equality_edge_cases();
    test_subset_edge_cases();
    test_memory_boundaries();
    test_remove_edge_cases();
    test_contains_edge_cases();
    test_insertion_order_edge_cases();
    time_test();

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
