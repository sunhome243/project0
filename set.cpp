//
// set.cpp
// CS 271 Set Project0

// Created by Sunho Kim, Flynn Phuc Nguyen, and Ryan Reilly
// 9/8/2025

#include "set.ixx"

class Node
{
public:
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};

class Set
{
private:
    Node *head;
    int size;

    bool search(int value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true; // value already in the set
            }
            current = current->next;
        }
        return false; // value not in the set
    }

public:
    Set() : head(nullptr), size(0) {}

    void insert(int value)
    {
        if (!search(value))
        {
            Node *newNode = new Node(value);
            newNode->next = head;
            head = newNode;
            size++;
        };
    };

    void remove(int value)
    {
        if (search(value))
        {
            Node *current = head;

            if (current->data == value) // if the node to be removed is the head
            {
                Node *temp = head;
                head = head->next;
                delete temp;
                size--;
                return;
            }

            else // if the node to be removed is not the head
            {
                while (current->next != nullptr && current->next->data != value)
                {
                    current = current->next;
                }
                Node *temp = current->next; // current->next is the node to be removed
                current->next = current->next->next;
                delete temp;
                size--;
            }
        }
    }

    int cardinality()
    {
        return size;
    }
};