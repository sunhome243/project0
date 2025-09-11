#ifndef SET_H
#define SET_H

#include <string>
using namespace std;

template <typename T>
class Set {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    int size;

public:
    // Constructor
    Set();
    
    // Destructor
    ~Set();
    
    // Copy constructor
    Set(const Set<T>& other);
    
    // Assignment operator
    Set<T>& operator=(const Set<T>& other);
    
    // Core set operations
    void insert(const T& x);
    void remove(const T& x);
    int cardinality() const;
    bool empty() const;
    bool contains(const T& x) const;
    string to_string() const;
    
    // Set comparison operators
    bool operator==(const Set<T>& other) const;
    bool operator<=(const Set<T>& other) const;
    
    // Set operations
    Set<T> operator+(const Set<T>& other) const;  // Union
    Set<T> operator&(const Set<T>& other) const;  // Intersection
    Set<T> operator-(const Set<T>& other) const;  // Difference

private:
    // Helper methods
    void clear();
    void copy_from(const Set<T>& other);
};

#include "set.cpp"  // Include implementation for template class

#endif
