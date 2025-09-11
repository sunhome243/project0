//
// set.cpp
// CS 271 Set Project0

// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#include "set.h"

/**
 * Node class for singly linked list implementation
 * Template class to support different data types
 */
template<typename T>
class Node
{
public:
    T data;      // Value stored in the node
    Node<T> *next;  // Pointer to the next node in the list

    /**
     * Constructor: Creates a new node with given value
     * @param value - Value to store in the node
     */
    Node(const T& value) : data(value), next(nullptr) {}
};

/**
 * Set template class implemented using a singly linked list
 * Stores unique values with no duplicates allowed
 * New elements are inserted at the head of the list
 */
template<class T>
class Set
{
private:
    Node<T> *head; // Pointer to the first node in the list
    int size;      // Number of elements currently in the set

public:
    /**
     * Constructor: Creates an empty set
     * Initializes head pointer to nullptr and size to 0
     */
    Set() : head(nullptr), size(0) {}

    /**
     * Insert a value into the set
     * If value already exists, no insertion occurs (maintains uniqueness)
     * New elements are inserted at the head of the list
     * @param value - Value to insert
     * Time Complexity: O(n) due to search operation
     */
    void insert(const T& value)
    {
        if (!contains(value)) // Only insert if value doesn't already exist
        {
            Node<T> *newNode = new Node<T>(value);
            newNode->next = head; // Link new node to current head
            head = newNode;       // Update head to point to new node
            size++;
        }
    }

    /**
     * Remove a value from the set
     * If value doesn't exist, no removal occurs
     * Handles two cases: removing head node vs removing other nodes
     * @param value - Value to remove
     * Time Complexity: O(n) due to search operation
     */
    void remove(const T& value)
    {
        if (contains(value)) // Only attempt removal if value exists
        {
            Node<T> *current = head;

            // Case 1: Removing the head node
            if (current->data == value)
            {
                Node<T> *temp = head;
                head = head->next; // Update head to next node
                delete temp;       // Free memory
                size--;
                return;
            }

            // Case 2: Removing a non-head node
            else
            {
                // Find the node before the one to be removed
                while (current->next != nullptr && current->next->data != value)
                {
                    current = current->next;
                }
                Node<T> *temp = current->next;          // Node to be removed
                current->next = current->next->next;    // Link around the removed node
                delete temp;                            // Free memory
                size--;
            }
        }
    }

    /**
     * Get the number of elements in the set
     * @return Integer representing the cardinality (size) of the set
     * Time Complexity: O(1)
     */
    int cardinality()
    {
        return size;
    }
    // FLynn
    template <typename T>
    bool Set<T>::empty() const
    {
        // Pre-condition: Set exists
        // Post-condition: Returns true if set has no elements, false otherwise
        return head == nullptr;
    }

    template <typename T>
    bool Set<T>::contains(const T &x) const
    {
        // Pre-condition: Set exists
        // Post-condition: Returns true if x is in set, false otherwise

        Node<T> *current = head;
        while (current != nullptr)
        {
            if (current->data == x)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    template <typename T>
    bool Set<T>::operator==(const Set<T> &other) const
    {
        // Pre-condition: Both sets exist
        // Post-condition: Returns true if sets contain same elements, false otherwise

        // Check if all elements in this set are in other set
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (!other.contains(current->data))
            {
                return false;
            }
            current = current->next;
        }

        // Check if all elements in other set are in this set
        current = other.head;
        while (current != nullptr)
        {
            if (!this->contains(current->data))
            {
                return false;
            }
            current = current->next;
        }

        return true;
    }

    template <typename T>
    bool Set<T>::operator<=(const Set<T> &other) const
    {
        // Pre-condition: Both sets exist
        // Post-condition: Returns true if this set is subset of other set, false otherwise

        // Check if all elements in this set are in other set
        Node<T> *current = head;
        while (current != nullptr)
        {
            if (!other.contains(current->data))
            {
                return false;
            }
            current = current->next;
        }

        return true;
    }
    template <typename T>
    Set<T> Set<T>::operator+(const Set<T> &other) const
    {
        // Pre-condition: Both set exist
        // Post condition: Returns the set of union of the two set
        Set<T> result;
        
        // Insert all elements from the other set
        Node<T> *current = other.head;
        while (current != nullptr)
        {
            result.insert(current->data);
            current = current->next;
        }
        
        // Insert all elements from this set
        current = head;
        while (current != nullptr)
        {
            result.insert(current->data);
            current = current->next;
        }
        
        return result;
    }
    template <typename T>
    Set<T> Set<T>::operator&(const Set<T> &other) const
    {
        // Pre-condition: Both set exist
        // Post condition: Returns the set of intersection of the two set
        Set<T> result;
        
        // Iterate through this set and check if each element exists in the other set
        Node<T> *current = head;
        while (current != nullptr)
        {
            // If the element exists in both sets, add it to the result set
            if (other.contains(current->data))
            {
                result.insert(current->data);
            }
            current = current->next;
        }
        
        return result;
    }

    template <typename T>
    Set<T> Set<T>::operator-(const Set<T> &other) const
    {
        // Pre-condition: Both set exist
        // Post-condition: Returns the set with unique values of this set 
        Set<T> result;
        
        // Iterate through this set and check if each element exists in the other set
        Node<T> *current = head;
        while (current != nullptr)
        {
            // If the element doesn't exist in the other set, add it to the result set
            if (!other.contains(current->data))
            {
                result.insert(current->data);
            }
            current = current->next;
        }
        
        return result;
    }

};