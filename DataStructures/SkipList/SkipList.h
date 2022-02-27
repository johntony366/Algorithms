#include <iostream>
#include <cmath>
#include <cstring>
#include <random>
#include <ctime>

template <typename T> 
class Node
{
public:
    T m_data;
    // Array to hold pointers to node of different level 
    Node** m_next;
    // Node Constructor
    Node(T data, int m_level);
};

template <typename T>
Node<T>::Node(T data, int m_level): m_data{ data }, m_next{ new Node*[m_level + 1] } // Allocate memory to forward 
{
    // Fill forward array with 0(NULL)
    std::memset(m_next, 0, sizeof(Node*)*(m_level+1));
}

template <typename T>
class SkipList
{
private:
    int MAXLVL; // Maximum level for this skip list
    float P; // P is the probability of coin flip giving heads (add layer) ALSO fraction of the nodes with level i pointers also having level i+1 pointers
    
    int m_size; //Number of elements in the skip list
    int m_level; //Current (highest) level of skip list
    Node<T>* m_head; //Pointer to first node

public:
    SkipList(int MAXLVL, float P): m_size{ 0 }, m_level{ 0 }
    {
        this->MAXLVL = MAXLVL;
        this->P = P;
        // create head node and initialize key to -1
        m_head = new Node(-1, MAXLVL);
    };

    int getRandomLevel()  //get random level for new node < MAXLVL
    {
        float r = static_cast<float>(std::rand())/RAND_MAX;
        int m_level = 0;
        while (r < P && m_level < MAXLVL)
        {
            ++m_level;
            r = static_cast<float>(std::rand())/RAND_MAX;
        }
        return m_level;
    }

    void insert(T key)  //Insert key into skip list at it's proper sorted position
    {
        Node<T>* current = m_head;
        
        // create update array and initialize it
        Node<T>* update[MAXLVL + 1];
        std::memset(update, 0, sizeof(Node<T>*)*(MAXLVL + 1));


        /* start from highest level of skip list
        move the current pointer forward while key 
        is greater than data of node after current
        Otherwise insert current in update and 
        move one level down and continue search */
        for (int i = m_level; i >= 0; --i)
        {
            while ( (current->m_next[i] != nullptr) && (current->m_next[i]->m_data < key) )
            {
                current = current->m_next[i];
            }
            update[i] = current;
        }

        /* reached level 0 and forward pointer to 
        right is the desired position to 
        insert key. */
        current = current->m_next[0];

        /* if current is NULL that means we have reached
       the end of the level or if current's key is not equal
       to key to insert that means we have to insert
       node between update[0] and current node */   

        //removed if(current == nullptr || current->m_data != key) , now duplicates are allowed

        int randomLevel = getRandomLevel();  //generate a random level for node
         /* If random level is greater than list's current
           level (node with highest level inserted in 
           list so far), initialize update value with pointer
           to header for further use */
        if (randomLevel > m_level)
        {
            for (int i = m_level + 1; i <= randomLevel; ++i)
            {
                update[i] = m_head;
            }
            //update m_level
            m_level = randomLevel;
        }

        //create new node with required key and randomLevel 
        Node<T>* newNode = new Node{key, randomLevel};


        // insert node by rearranging pointers 
        for (int i = 0; i <= randomLevel; ++i)
        {
            newNode->m_next[i] = update[i]->m_next[i];
            update[i]->m_next[i] = newNode;
        }
        ++m_size;
    }

    void remove(T key)   //delete element from skip list
    {
        Node<T>* current = m_head;
        // create update array and initialize it
        Node<T>* update[MAXLVL + 1];

        std::memset(update, 0, sizeof(Node<T>*)*(MAXLVL + 1));

        /* start from highest level of skip list
        move the current pointer forward while key 
        is greater than data of node after current
        Otherwise insert current in update and 
        move one level down and continue search */
        for (int i = m_level; i >= 0; --i)
        {
            while ( (current->m_next[i] != nullptr) && (current->m_next[i]->m_data < key) )
            {
                current = current->m_next[i];
            }
            update[i] = current;
        }

        /* reached level 0 and forward pointer to 
        right is key to be deleted (if it is not null and has same m_data). */
        current = current->m_next[0];
        if (current != nullptr && current->m_data == key) // If current node is target node
        {
            for (int i = 0; i <= m_level; ++i)
            {
                /* start from lowest level and rearrange
                pointers just like we do in singly linked list
                to remove target node */
                if(update[i]->m_next[i] != current)
                {
                    break;
                }

                update[i]->m_next[i] = current->m_next[i];
            }

            // Remove levels having no elements 
            while(m_level>0 && m_head->m_next[m_level] == 0)
            {
                --m_level;
            }
            --m_size;
        }
    }

    bool find(int key)  // Search for element in skip list
    {
        Node<T>* current = m_head;
    
        /*  starting from highest level of skip list
            move the current pointer forward while key 
            is greater than key of node after current.
        */
        for(int i = m_level; i >= 0; i--)
        {
            while(current->m_next[i] && current->m_next[i]->m_data < key)
                current = current->m_next[i];
        }
    
        /* reached level 0 and advance pointer to 
        right, which is possibly our desired node*/
        current = current->m_next[0];
    
        // If current node is not null and has key equal to
        // search key, we have found our target node
        if(current and current->m_data == key) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    void displayList() // Display skip list level wise
    {
        std::cout<<"\n*****Skip List*****"<<"\n";
        for (int i=0; i<=m_level; i++)
        {
            Node<T>* node = m_head->m_next[i];
            std::cout << "Level " << i << ": ";
            while (node != NULL)
            {
                std::cout << node->m_data<<" ";
                node = node->m_next[i];
            }
            std::cout << "\n";
        }
    };
};