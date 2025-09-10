template <typename T>
bool Set<T>::empty() const {
    // Pre-condition: Set exists
    // Post-condition: Returns true if set has no elements, false otherwise
    return head == nullptr;
}

template <typename T>
bool Set<T>::contains(const T& x) const {
    // Pre-condition: Set exists
    // Post-condition: Returns true if x is in set, false otherwise
    
    Node* current = head;
    while (current != nullptr) {
        if (current->data == x) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool Set<T>::operator==(const Set<T>& other) const {
    // Pre-condition: Both sets exist
    // Post-condition: Returns true if sets contain same elements, false otherwise
    
    // Check if all elements in this set are in other set
    Node* current = head;
    while (current != nullptr) {
        if (!other.contains(current->data)) {
            return false;
        }
        current = current->next;
    }
    
    // Check if all elements in other set are in this set
    current = other.head;
    while (current != nullptr) {
        if (!this->contains(current->data)) {
            return false;
        }
        current = current->next;
    }
    
    return true;
}

template <typename T>
bool Set<T>::operator<=(const Set<T>& other) const {
    // Pre-condition: Both sets exist
    // Post-condition: Returns true if this set is subset of other set, false otherwise
    
    // Check if all elements in this set are in other set
    Node* current = head;
    while (current != nullptr) {
        if (!other.contains(current->data)) {
            return false;
        }
        current = current->next;
    }
    
    return true;
}
