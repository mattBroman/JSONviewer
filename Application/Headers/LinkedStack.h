// LinkedStack.h

#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

#include <iostream>
#include "RuntimeException.h"
#include "TemplatedDoublyLinkedList.h"

template<typename T> class LinkedStack;

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedStack<T>& stack);
    
template<typename T>
class LinkedStack
{
private:
	DoublyLinkedList<T> dll;
  /* declare member variables here */
  
public:
   // user-defined exceptions
   class StackEmptyException : public RuntimeException {
   public:
     StackEmptyException() : RuntimeException("Stack is empty") {}
   };
   LinkedStack() : dll() {} //default constructor
   ~LinkedStack() {dll.~DoublyLinkedList();} // destructor
   LinkedStack(const LinkedStack& stack) : dll(stack.dll) { } // copy constructor
   
   //isEmpty function
   bool isEmpty() const {return dll.isEmpty();}
   // size function
   int size() const { return dll.size();}

   // access function
   // get the first element function
   T top() const throw(StackEmptyException)
   {
     if(dll.isEmpty())
      throw StackEmptyException();
    return dll.first();
   }
   // remove the first one element function
   T pop() throw(StackEmptyException)
   {
    if(dll.isEmpty())
      throw StackEmptyException();
    return dll.removeFirst();
   }
   //insert the first element
   void push(const T elem) {dll.insertFirst(elem);}


      /* declare rest of functions */
      
};

/* describe rest of the functions here */

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedStack<T>& stack)
{
  /* fill in the function */
   if(stack.isEmpty())
      return out << "{}";
   LinkedStack<T> s(stack);
   LinkedStack<T> helper;
   for(int i = 0; i< stack.size(); i++)
      helper.push(s.pop());
   out << '{';
   for(int i = 0; i< stack.size(); i++)
      {
      out << helper.pop();}
  /* fill in the function */
   return out << '}';
}

#endif
