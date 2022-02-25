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

    int find(T element)
    {
        Node* current = m_head;
        bool found = false;
        int index = 0;
        while (current)
        {
            if (current->data == element)
            {
                found = true;
                break;
            }
            current = current->next;
            ++index;
        }

        return found ? index : -1;
    }

    void remove(int index)
    {
        assert(index >= 0 && index < m_size);
        if (index == 0)
        {
            Node* newHead = m_head->next;
            delete m_head;
            m_head = newHead;
        }
        else
        {
            Node* current = m_head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            if (current->next == m_tail)
            {
                delete m_tail;
                current->next = nullptr;
                m_tail = current;
            }
            else
            {
                Node* temp = current->next->next;
                delete current->next;
                current->next = temp;
            }
        }
        --m_size;
    }

    void insert(T element, int index)
    {
        assert(index >= 0 && index <= m_size);
        Node* newNode{ new Node{ element, nullptr } };

        if (index == 0)
        {
            newNode->next = m_head;
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
                m_tail->next = newNode;
                m_tail = newNode;
            }
        }

        else
        {
            Node* current{ m_head };
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            newNode->next = current->next;
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
        Node* current = m_head;
        while (current && (--index >= 0))
        {
            current = current->next;
        }
        return current->data;
    }

    T operator[](int index) const
    {
        assert(index >= 0 && index < m_size);
        Node* current = m_head;
        while (current && (--index >= 0))
        {
            current = current->next;
        }
        return current->data;
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