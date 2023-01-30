#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
#define primesize = 11;
ifstream infile("input5.txt");
ofstream outfile("out.txt");
struct node
{
private:
    int info;
    node *next;

public:
    node() // create a dummy header for all bucket
    {
        info = 0;
        next = NULL;
    }
    node(int value)
    {
        info = value;
        next = NULL;
    }
    void set(int);
    void Delete(int);
    void search(int);
    node *getNext()
    {
        return this->next;
    }
    void setNext(node *newnode)
    {
        this->next = newnode;
    }
    int getValue()
    {
        return this->info;
    }
};
void node::set(int value)
{
    // if(info == 0)
    // {
    //     info = value;
    //     return;
    // }
    if (this->getNext() == NULL) // when this list is empty just set next
    {
        this->setNext(new node(value));
        return;
    }
    node *p = this->getNext(); // ignore the header
    while (p->getNext() != NULL)
    {
        if (p->getValue() == value)
        {
            return;
        }
        p = p->getNext();
    }
    if (p->getValue() == value)
    {
        return;
    }
    p->setNext(new node(value)); // insert at the end of list
}
void node::Delete(int value)
{
    if (this->getNext() == NULL)
    {
        outfile << value << " does not exist" << endl;
        return;
    }                                         // if this part is empty
    if (this->getNext()->getValue() == value) // if delete node is the first node
    {
        this->setNext(this->getNext()->getNext());
        outfile << value << " was deleted successfully" << endl;
        return;
    }
    node *p = this->getNext(); // ignore the header
    while (p->getNext() != NULL)
    {
        if (p->getNext()->getValue() == value)
        {
            p->setNext(p->getNext()->getNext());
            outfile << value << " was deleted successfully" << endl;
            return;
        }
        p = p->getNext();
    }
    outfile << value << " does not exist" << endl;
}
void node::search(int value)
{
    if (this->getNext() == NULL)
    {
        outfile << value << " does not exist" << endl;
        return;
    }                          // if this part is empty
    node *p = this->getNext(); // ignore the header
    while (p->getNext() != NULL)
    {
        if (p->getValue() == value)
        {
            outfile << value << " was found" << endl;
            return;
        }
        p = p->getNext();
    }
    if (p->getValue() == value) // test the last one;
    {
        outfile << value << " was found" << endl;
        return;
    }
    outfile << value << " does not exist" << endl;
}
struct MyHash
{
private:
    node *hashtable;
    int encodeFunc(int key)
    {
        return (key * 2654435769) % 1024; //斐波那契（Fibonacci）散列法
        // return key % 1024;
        // return (key * key) % 1024;
    }

public:
    MyHash()
    {
        hashtable = new node[1024];
    }
    void Insert(int value)
    {
        hashtable[encodeFunc(value)].set(value);
    }
    void Delete(int value)
    {
        hashtable[encodeFunc(value)].Delete(value);
    }
    void Search(int value)
    {
        hashtable[encodeFunc(value)].search(value);
    }
};
int main()
{
    MyHash table;
    string s;
    char ch;
    while (infile >> s)
    {
        string cmd;
        if (s == "")
        { 
            break;
        }
        int value;
        // char ch = getchar();
        if (s == "insert")
        {
            infile >> value;
            table.Insert(value);
        }
        if (s == "search")
        {
            infile >> value;
            table.Search(value);
        }
        if (s == "delete")
        {
            infile >> value;
            table.Delete(value);
        }
    }
    return 0;
}