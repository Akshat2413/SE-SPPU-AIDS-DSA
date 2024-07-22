#include <iostream>
#include <cstring>  // Include cstring for NULL
using namespace std;

struct node
{
    int value;
    node* next;
} *HashTable[10];

class hashing
{
public:
    hashing()
    {
        for (int i = 0; i < 10; i++)
        {
            HashTable[i] = NULL;
        }
    }

    int hashFunction(int value)
    {
        return (value % 10);
    }

    node* createNode(int val)
    {
        node* temp = new node;
        temp->next = NULL;
        temp->value = val;
        return temp;
    }

    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            node* temp = HashTable[i];
            cout << "a[" << i << "]";
            while (temp != NULL)
            {
                cout << "->" << temp->value;
                temp = temp->next;
            }
            cout << '\n';
        }
    }

    int search(int val)
    {
        bool flag = false;
        int hash_val = hashFunction(val);
        node* entry = HashTable[hash_val];
        cout << "\nElement found at:";
        while (entry != NULL)
        {
            if (entry->value == val)
            {
                cout << hash_val << ":" << entry->value;
                flag = true;
            }
            entry = entry->next;
        }
        if (!flag)
        {
            cout << "Element not found!" << endl;
            return -1;
        }
        return 0;
    }

    void deleteElement(int val)
    {
        int hash_val = hashFunction(val);
        node* entry = HashTable[hash_val];
        if (entry == NULL)
        {
            cout << "Element not found!" << endl;
            return;
        }
        if (entry->value == val)
        {
            HashTable[hash_val] = entry->next;
            delete entry;
            return;
        }
        while (entry->next != NULL && (entry->next)->value == val)
        {
            node* temp = entry->next;
            entry->next = temp->next;
            delete temp;
        }
        cout << "Element not found!" << endl;
    }

    void insertValue(int val)
    {
        int hash_val = hashFunction(val);
        node* head = createNode(val);
        if (HashTable[hash_val] == NULL)
        {
            HashTable[hash_val] = head;
        }
        else
        {
            node* temp = HashTable[hash_val];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = head;
        }
    }
};

int main()
{
    int ch;
    int value;
    hashing hash;
    while (ch != 5)
    {
        cout << "\n1.Insert \n2.Delete\n3.Display\n4.Search\n5.Exit\nEnter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter value to insert:";
            cin >> value;
            hash.insertValue(value);
            break;
        case 2:
            cout << "Enter value to delete:";
            cin >> value;
            hash.deleteElement(value);
            break;
        case 3:
            hash.display();
            break;
        case 4:
            cout << "Enter value to search:";
            cin >> value;
            hash.search(value);
            break;
        }
    }
    return 0;
}

