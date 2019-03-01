#ifndef LinkList_hpp
#define LinkList_hpp

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *pre;
};

template <typename T>
class LinkList
{
  private:
    Node<T>* head;
    Node<T>* tail;
    int length;

  public:
    LinkList();
    ~LinkList();

    Node<T>* makeNode();
    bool push(T data);
    void pop();
    T indexAt(int index);
    bool insert(T data, int index);
    void display();
};

template <typename T>
LinkList<T>::LinkList()
{
    head = makeNode();
    tail = head;
    length = 0;
}

template <typename T>
Node<T>* LinkList<T>::makeNode()
{
    Node<T>* node = new Node<T>;
    return node;
}

template <typename T>
LinkList<T>::~LinkList()
{
    while(head != tail)
    {
        Node<T>* next = head->next;
        free(head);
        head = next;
    }
    free(head);
}

template <typename T>
bool LinkList<T>::push(T data)
{
    Node<T>* newNode = makeNode();
    if(!newNode)
    {
        return false;
    }

    newNode->data = data;
    tail->next = newNode;
    newNode->pre = tail;
    newNode->next = head;
    head->pre = newNode;
    tail = newNode;
    length++;
    return true;
}

template <typename T>
void LinkList<T>::pop()
{
    if(!tail)
    {
        return;
    }

    tail = tail->pre;
    tail->next = head;
    head->pre = tail;
    length--;
}

template <typename T>
bool LinkList<T>::insert(T data, int index)
{
    if(index < 1 || index > length)
    {
        return false;
    }

    Node<T>* newNode = makeNode();
    newNode->data = data;

    Node<T>* p = head;
    for(int i = 0; i < index; ++i)
    {
        p = p->next;
    }
    newNode->pre = p->pre;
    newNode->next = p;
    newNode->pre->next = newNode;
    p->pre = newNode;
    length++;
    return true;
}

template <typename T>
void LinkList<T>::display()
{
    Node<T>* p = head->next;
    cout << "data:";
    while(p != tail)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data << endl;
}


#endif