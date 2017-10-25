//replace with your implemented version

#ifndef TEMPLATED_DOUBLY_LINKED_LIST_H
#define TEMPLATED_DOUBLY_LINKED_LIST_H
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

// DoublyLinkedlist.h
template<class T>class DoublyLinkedList; // class declaration

// list node
template<class T>class DListNode {
private:
  T obj;
  DListNode<T> *prev, *next;
  friend class DoublyLinkedList<T>;
public:
  DListNode<T>(T e=T(), DListNode<T> *p = nullptr, DListNode<T> *n = nullptr)
    : obj(e), prev(p), next(n) {}
  T getElem() const { return obj; }
  DListNode<T> * getNext() const { return next; }
  DListNode<T> * getPrev() const { return prev; }
};

// doubly linked list
template<class T>class DoublyLinkedList{
protected:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList<T>() : // constructor
    header(T()), trailer(T()) 
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList<T>(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList<T>(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // check if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  
  //size function, for count the size of stack and queue
  int size() const
  {
    int count = 0;
    if( header.next != &trailer){
      DListNode<T> *Iter = header.next; // pointer to point head of the linked list
      while(Iter != &trailer){ // stop when get to the tailer
      count++; // count number increase by 1
      Iter =  Iter -> next; // move to next object
    }
  }
    return count;
  }

  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
};
// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};
// output operator
template<class T>ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

// DoublyLinkedList.cpp

// copy constructor
template<class T>DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  // empty double linked list
  if( !dll.isEmpty()){
  DListNode<T> *Iter = dll.getFirst(); // pointer to point head of the linked list
  while(Iter != dll.getAfterLast()){ // stop when get to the tailer
    insertLast( Iter -> obj); // insert the value of dll to the new linked list
    Iter =  Iter -> next; // move to next object
  } //complexity:O(n)
  // Copy from dll
  // Complete this function
  }
}

// assignment operator
template<class T>DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // remove all old elements
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  } //complexity:O(n)
  header.next = &trailer;
  trailer.prev = &header;
  // copy elements from dll
  if( !dll.isEmpty()){
  DListNode<T> *Iter = dll.getFirst(); // pointer to point head of the linked list
  while(Iter != dll.getAfterLast()){ // stop when get to the tailer
    insertLast( Iter -> obj); // insert the value of dll to the new linked list
    Iter =  Iter -> next; // move to next object
  }//complexity:O(n)
  return *this;
  //complexity:O(n) +O(n)=O(n)
  // Complete this function

}
}

// insert the object to the first of the linked list
template<class T>void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
  DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next -> prev = newNode;
  header.next = newNode;
  // Complete this function
}
//complexity:O(1)

// insert the object to the last of the linked list
template<class T>void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}
//complexity:O(1)

// remove the first object of the list
template<class T>T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node -> next -> prev = &header;// make the first node to be null
  header.next = node -> next;
  T obj = node -> obj;
  delete node;
  return obj; //get the value of the removed node
  // Complete this function
}
//complexity:O(1)

// remove the last object of the list
template<class T>T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}
//complexity:O(1)

// destructor
template<class T>DoublyLinkedList<T>::~DoublyLinkedList<T>()
{
  DListNode<T> *prev_node, *node = header.next;
  while (node != &trailer) {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }//complexity:O(n)
  header.next = &trailer;
  trailer.prev = &header;
}

// return the first object
template<class T>T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  // Complete this function
  return header.next -> obj;
}
//complexity:O(1)

// return the last object
template<class T>T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev -> obj;
}
//complexity:O(1)

// output operator
template<class T>ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
  DListNode<T> *Iter = dll.getFirst(); // pointer to point head of the linked list
  while(Iter != dll.getAfterLast()){ // stop when get to the tailer
    out << Iter -> getElem()<< ' '; // read out value in this node
    Iter =  Iter -> getNext(); // move to next object
  }//complexity:O(n)
  // Complete this function
  return out;
}


// your code is here

#endif
