//
//  test_set_example.cpp
//  CS 271 Set Project: Example Test File
//
//  Created by Dr. Stacey Truex
//
#include <iostream>
#include "set.cpp"

void test_insert()
{
    try
    {
        Set<int> s;
        s.insert(0);
        string set_str = s.to_string();
        if (s.to_string() != "0")
        {
            cout << "Incorrect insert result. Expected 0 but got : " << set_str << endl;
        }
        s.insert(2);
        s.insert(-1);
        set_str = s.to_string();
        if (s.to_string() != "-1 2 0")
        {
            cout << "Incorrect insert result. Expected -1 2 0 but got : " << set_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error inserting into set : " << e.what() << endl;
    }
}

void test_remove()
{
    try
    {
        Set<int> s;
        s.insert(1);
        s.insert(2);
        s.insert(3);
        s.insert(4);
        s.remove(5);
        string set_str = s.to_string();
        if (s.to_string() != "4 3 2 1")
        {
            cout << "Incorrect remove result. Expected 4 3 2 1 but got : " << set_str << endl;
        }
        s.remove(3);
        set_str = s.to_string();
        if (s.to_string() != "4 2 1")
        {
            cout << "Incorrect remove result. Expected 4 2 1 but got : " << set_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error removing from set : " << e.what() << endl;
    }
}

void test_cardinality()
{
    try
    {
        Set<int> s;
        int c = s.cardinality();
        if (c != 0)
        {
            cout << "Incorrect cardinality. Expected 0 but got : " << c << endl;
        }
        s.insert(6);
        s.insert(5);
        s.insert(4);
        s.insert(3);
        s.insert(2);
        c = s.cardinality();
        if (c != 5)
        {
            cout << "Incorrect cardinality. Expected 5 but got : " << c << endl;
        }
        s.remove(4);
        s.remove(2);
        c = s.cardinality();
        if (c != 3)
        {
            cout << "Incorrect cardinality. Expected 3 but got : " << c << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining set cardinality : " << e.what() << endl;
    }
}

void test_empty()
{
    try
    {
        Set<int> s;
        if (!s.empty())
        {
            cout << "Empty set identified as non-empty" << endl;
        }
        s.insert(1);
        s.insert(2);
        if (s.empty())
        {
            cout << "Non-empty set identified as empty" << endl;
        }
        s.remove(2);
        if (s.empty())
        {
            cout << "Non-empty set identified as empty" << endl;
        }
        s.remove(1);
        if (!s.empty())
        {
            cout << "Empty set identified as non-empty" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining if set is the empty set : " << e.what() << endl;
    }
}

void test_contains()
{
    try
    {
        Set<int> s;
        if (s.contains(5))
        {
            cout << "Incorrectly identified 5 as in the set " << s.to_string() << endl;
        }
        s.insert(1);
        s.insert(2);
        s.insert(3);
        if (s.contains(5))
        {
            cout << "Incorrectly identified 5 as in the set " << s.to_string() << endl;
        }
        if (!s.contains(2))
        {
            cout << "Incorrectly identified 2 as NOT in the set " << s.to_string() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining if value contained in se : " << e.what() << endl;
    }
}

void test_equality()
{
    try
    {
        Set<int> s;
        Set<int> t;
        if (!(s == t))
        {
            cout << "Empty sets should be considered equal" << endl;
        }
        s.insert(1);
        s.insert(2);
        s.insert(3);
        if (s == t)
        {
            cout << "Incorrectly identified set " << s.to_string() << " as equivalent to " << t.to_string() << endl;
        }
        t.insert(1);
        t.insert(2);
        t.insert(3);
        if (!(s == t))
        {
            cout << "Sets " << s.to_string() << " and " << t.to_string() << " should be considered equal." << endl;
        }
        s.remove(3);
        if (s == t)
        {
            cout << "Incorrectly identified set " << s.to_string() << " as equivalent to " << t.to_string() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining set equality : " << e.what() << endl;
    }
}

void test_subset()
{
    try
    {
        Set<int> s;
        Set<int> t;
        if (!(s <= t))
        {
            cout << "Set " << s.to_string() << " should be considered a subset of the set " << t.to_string() << endl;
        }
        t.insert(3);
        t.insert(7);
        if (!(s <= t))
        {
            cout << "Set " << s.to_string() << " should be considered a subset of the set " << t.to_string() << endl;
        }
        s.insert(7);
        s.insert(3);
        if (!(s <= t))
        {
            cout << "Set " << s.to_string() << " should be considered a subset of the set " << t.to_string() << endl;
        }
        t.insert(10);
        if (!(s <= t))
        {
            cout << "Set " << s.to_string() << " should be considered a subset of the set " << t.to_string() << endl;
        }
        s.insert(11);
        if (s <= t)
        {
            cout << "Set " << s.to_string() << " should NOT be considered a subset of the set " << t.to_string() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining subset : " << e.what() << endl;
    }
}

void test_union()
{
    try
    {
        Set<int> s;
        Set<int> t;
        string set_str = (s + t).to_string();
        if (set_str != "")
        {
            cout << "Union of the empty sets should be the empty set. Instead got : " << set_str << endl;
        }
        s.insert(1);
        s.insert(2);
        t.insert(2);
        t.insert(1);
        set_str = (s + t).to_string();
        if (set_str != "2 1")
        {
            cout << "Union of " << s.to_string() << " and " << t.to_string() << " was expected to be 2 1 but instead got : " << set_str << endl;
        }
        t.insert(6);
        set_str = (s + t).to_string();
        if (set_str != "2 1 6")
        {
            cout << "Union of " << s.to_string() << " and " << t.to_string() << " was expected to be 2 1 6 but instead got : " << set_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in generating the union set : " << e.what() << endl;
    }
}

void test_intersection()
{
    try
    {
        Set<int> s;
        Set<int> t;
        string set_str = (s & t).to_string();
        if (set_str != "")
        {
            cout << "Intersection of the empty sets should be the empty set. Instead got : " << set_str << endl;
        }
        s.insert(1);
        s.insert(2);
        t.insert(6);
        set_str = (s & t).to_string();
        if (set_str != "")
        {
            cout << "Intersection of " << s.to_string() << " and " << t.to_string() << " was expected to be the empty set but instead got : " << set_str << endl;
        }
        t.insert(2);
        t.insert(1);
        set_str = (s & t).to_string();
        if (set_str != "1 2")
        {
            cout << "Intersection of " << s.to_string() << " and " << t.to_string() << " was expected to be 1 2 but instead got : " << set_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in generating the intersection set : " << e.what() << endl;
    }
}

void test_diff()
{
    try
    {
        Set<int> s;
        Set<int> t;
        string set_str = (s - t).to_string();
        if (set_str != "")
        {
            cout << "Difference of the empty sets should be the empty set. Instead got : " << set_str << endl;
        }
        s.insert(1);
        s.insert(2);
        t.insert(6);
        set_str = (s - t).to_string();
        if (set_str != "1 2")
        {
            cout << "Set " << s.to_string() << " \\ Set " << t.to_string() << " was expected to be 1 2 set but instead got : " << set_str << endl;
        }
        t.insert(2);
        t.insert(1);
        set_str = (s - t).to_string();
        if (set_str != "")
        {
            cout << "Set " << s.to_string() << " \\ Set " << t.to_string() << " was expected to be the empty set set but instead got : " << set_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in generating the intersection set : " << e.what() << endl;
    }
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

int main()
{
    string file_name = "set.cpp";
    cout << endl
         << "Running tests for " << file_name << endl
         << endl;

    test_insert();
    test_remove();
    test_cardinality();
    test_empty();
    test_contains();
    test_equality();
    test_subset();
    test_union();
    test_intersection();
    test_diff();

    time_test();

    cout << endl
         << "Testing completed" << endl
         << endl;

    return 0;
}
