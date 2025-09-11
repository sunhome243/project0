//
// set.cpp
// CS 271 Set Project0

// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#ifndef SET_CPP
#define SET_CPP

/**
 * Constructor: Creates an empty set
 * Pre-condition: None
 * Post-condition: Set is initialized with no elements
 */
template <typename T>
Set<T>::Set() : head(nullptr), size(0) {}

/**
 * Destructor: Deallocates all nodes in the set
 * Pre-condition: Set exists
 * Post-condition: All dynamically allocated memory is freed
 */
template <typename T>
Set<T>::~Set()
{
    clear();
}

/**
 * Copy constructor: Creates a deep copy of another set
 * Pre-condition: Other set exists
 * Post-condition: New set contains copies of all elements from other set
 */
template <typename T>
Set<T>::Set(const Set<T> &other) : head(nullptr), size(0)
{
    copy_from(other);
}

/**
 * Assignment operator: Assigns contents of another set to this set
 * Pre-condition: Both sets exist
 * Post-condition: This set contains copies of all elements from other set
 */
template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    return *this;
}

/**
 * Insert an element into the set
 * Pre-condition: Set exists
 * Post-condition: Element is added if not already present
 */
template <typename T>
void Set<T>::insert(const T &value)
{
    if (!contains(value))
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }
}

/**
 * Remove an element from the set
 * Pre-condition: Set exists
 * Post-condition: Element is removed if present
 */
template <typename T>
void Set<T>::remove(const T &value)
{
    if (contains(value))
    {
        Node *current = head;

        // Case 1: Removing the head node
        if (current->data == value)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        // Case 2: Removing a non-head node
        while (current->next != nullptr && current->next->data != value)
        {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
    }
}

/**
 * Get the cardinality (number of elements) of the set
 * Pre-condition: Set exists
 * Post-condition: Returns the number of elements in the set
 */
template <typename T>
int Set<T>::cardinality() const
{
    return size;
}

/**
 * Check if the set is empty
 * Pre-condition: Set exists
 * Post-condition: Returns true if set has no elements, false otherwise
 */
template <typename T>
bool Set<T>::empty() const
{
    return head == nullptr;
}

/**
 * Check if an element exists in the set
 * Pre-condition: Set exists
 * Post-condition: Returns true if element is in set, false otherwise
 */
template <typename T>
bool Set<T>::contains(const T &x) const
{
    Node *current = head;
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

/**
 * Convert set to string representation
 * Pre-condition: Set exists
 * Post-condition: Returns string with elements separated by spaces
 */
template <typename T>
string Set<T>::to_string() const
{
    if (empty())
    {
        return "";
    }

    stringstream ss;
    Node *current = head;
    bool first = true;

    while (current != nullptr)
    {
        if (!first)
        {
            ss << " ";
        }
        ss << current->data;
        first = false;
        current = current->next;
    }

    return ss.str();
}

/**
 * Equality operator: Check if two sets contain the same elements
 * Pre-condition: Both sets exist
 * Post-condition: Returns true if sets are equal, false otherwise
 */
template <typename T>
bool Set<T>::operator==(const Set<T> &other) const
{
    // Check if all elements in this set are in other set
    Node *current = head;
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

/**
 * Subset operator: Check if this set is a subset of another set
 * Pre-condition: Both sets exist
 * Post-condition: Returns true if this is a subset of other, false otherwise
 */
template <typename T>
bool Set<T>::operator<=(const Set<T> &other) const
{
    // Check if all elements in this set are in other set
    Node *current = head;
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
/**
 * Union operator: Create union of two sets
 * Pre-condition: Both sets exist
 * Post-condition: Returns new set containing all elements from both sets
 */
template <typename T>
Set<T> Set<T>::operator+(const Set<T> &other) const
{
    Set<T> result;
    
    // Insert all elements from the other set
    Node *current = other.head;
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
/**
 * Intersection operator: Create intersection of two sets
 * Pre-condition: Both sets exist
 * Post-condition: Returns new set containing common elements
 */
template <typename T>
Set<T> Set<T>::operator&(const Set<T> &other) const
{
    Set<T> result;
    
    // Iterate through this set and check if each element exists in the other set
    Node *current = head;
    while (current != nullptr)
    {
        if (other.contains(current->data))
        {
            result.insert(current->data);
        }
        current = current->next;
    }
    
    return result;
}

/**
 * Difference operator: Create difference of two sets
 * Pre-condition: Both sets exist
 * Post-condition: Returns new set with elements in this but not in other
 */
template <typename T>
Set<T> Set<T>::operator-(const Set<T> &other) const
{
    Set<T> result;
    
    // Iterate through this set and check if each element doesn't exist in the other set
    Node *current = head;
    while (current != nullptr)
    {
        if (!other.contains(current->data))
        {
            result.insert(current->data);
        }
        current = current->next;
    }
    
    return result;
}

/**
 * Clear all elements from the set
 * Pre-condition: Set exists
 * Post-condition: Set is empty and all memory is freed
 */
template <typename T>
void Set<T>::clear()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

/**
 * Copy elements from another set
 * Pre-condition: Both sets exist, this set is empty
 * Post-condition: This set contains copies of all elements from other
 */
template <typename T>
void Set<T>::copy_from(const Set<T> &other)
{
    // Since we insert at head, we need to traverse in reverse order
    // to maintain the same order. For simplicity, we'll just insert
    // and accept the reversed order (both are valid for unordered sets)
    Node *current = other.head;
    while (current != nullptr)
    {
        insert(current->data);
        current = current->next;
    }
}

#endif // SET_CPP