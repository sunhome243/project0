//
// set.cpp
// CS 271 Set Project0

// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#include "set.ixx"

/**
 * Node class for singly linked list implementation
 * Each node contains an integer value and pointer to the next node
 */
class Node
{
public:
    int data;     // Integer value stored in the node
    Node *next;   // Pointer to the next node in the list
    
    /**
     * Constructor: Creates a new node with given value
     * @param value - Integer value to store in the node
     */
    Node(int value) : data(value), next(nullptr) {}
};

/**
 * Set class implemented using a singly linked list
 * Stores unique integer values with no duplicates allowed
 * New elements are inserted at the head of the list
 */
class Set
{
private:
    Node *head;   // Pointer to the first node in the list
    int size;     // Number of elements currently in the set

    /**
     * Private helper method to search for a value in the set
     * @param value - Integer value to search for
     * @return true if value exists in the set, false otherwise
     * Time Complexity: O(n) where n is the number of elements
     */
    bool search(int value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true; // Value found in the set
            }
            current = current->next;
        }
        return false; // Value not found in the set
    }

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
     * @param value - Integer value to insert
     * Time Complexity: O(n) due to search operation
     */
    void insert(int value)
    {
        if (!search(value))  // Only insert if value doesn't already exist
        {
            Node *newNode = new Node(value);
            newNode->next = head;  // Link new node to current head
            head = newNode;        // Update head to point to new node
            size++;
        };
    };

    /**
     * Remove a value from the set
     * If value doesn't exist, no removal occurs
     * Handles two cases: removing head node vs removing other nodes
     * @param value - Integer value to remove
     * Time Complexity: O(n) due to search operation
     */
    void remove(int value)
    {
        if (search(value))  // Only attempt removal if value exists
        {
            Node *current = head;

            // Case 1: Removing the head node
            if (current->data == value)
            {
                Node *temp = head;
                head = head->next;  // Update head to next node
                delete temp;        // Free memory
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
                Node *temp = current->next;           // Node to be removed
                current->next = current->next->next;  // Link around the removed node
                delete temp;                          // Free memory
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
};