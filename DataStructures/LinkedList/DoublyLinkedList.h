#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };

private:
    int m_size;
    Node* m_head;
    Node* m_tail;

public:
    LinkedList() : m_size{ 0 }, m_head{ nullptr }, m_tail{ nullptr }
    {

    }

    ~LinkedList()
    {
        Node* current = m_head;
        while (current)
        {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
    }

    void moveToPreviousNode(Node*& current, int index)
    {
        int midIndex = (m_size-1)/2;
        if (index <= midIndex)
        {
            current = m_head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
        }
        else
        {
            current = m_tail;
            int indexFromEnd = m_size - index - 1;
            for (int i = 0; i < indexFromEnd + 1; ++i)
            {
                current = current->prev;
            }
        }
    }

    int find(T element)
    {
        Node* current = m_head;
        for (int index = 0; index < m_size - 1; ++index)
        {
            if (current->data == element)
            {
                return index;
            }
            current = current->next;
        }
        return -1;
        // bool found = false;
        // int index = 0;
        // while (current)
        // {
        //     if (current->data == element)
        //     {
        //         found = true;
        //         break;
        //     }
        //     current = current->next;
        //     ++index;
        // }

        // return found ? index : -1;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_size);
        if (index == 0)
        {
            m_head = m_head->next;
            delete m_head->prev;
            m_head->prev = nullptr;
        }
        else if (index == m_size - 1)
        {
            m_tail = m_tail->prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }

        else
        {
            Node* current;

            moveToPreviousNode(current, index);

            Node* temp = current->next->next;
            delete current->next;
            current->next = temp;
            temp->prev = current;
        }
        --m_size;
    }

    void insert(T element, int index)
    {
        assert(index >= 0 && index <= m_size);
        Node* newNode{ new Node{ element, nullptr, nullptr } };

        if (index == 0)
        {
            newNode->next = m_head;
            //newNode->prev = nullptr
            m_head = newNode;
            if (m_size == 0)
            {
                m_tail = newNode;
            }
        }

        else if (index == m_size)
        {
            if (m_size == 0)
            {
                m_tail = newNode;
            }
            else
            {
                //newNode->next = nullptr
                newNode->prev = m_tail;
                m_tail->next = newNode;
                m_tail = newNode;
            }
        }

        else
        {
            Node* current;

            moveToPreviousNode(current, index);

            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
        ++m_size;
    }

    void append(int element)
    {
        insert(element, m_size);
    }

    int getSize() const
    {
        // int size = 0;
        // Node* current{ head };
        // while (current)
        // {
        //     ++size;
        //     current = current->next;
        // }
        // return size;
        return m_size;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < m_size);
        Node* current;
        
        moveToPreviousNode(current, index);

        return current->next->data;
    }

    T operator[](int index) const
    {
        assert(index >= 0 && index < m_size);
        Node* current;
        
        moveToPreviousNode(current, index);

        return current->next->data;
    }

    std::ostream& printList(std::ostream& out) const
    {
        Node* current = m_head;
        while (current)
        {
            out << current->data << ' ';
            current = current->next;
        }
        return out;
    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list)
    {
        return list.printList(out);
    }
};