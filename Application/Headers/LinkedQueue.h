// LinkedQueue.h

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include "RuntimeException.h"
#include "TemplatedDoublyLinkedList.h"

template<typename T> class LinkedQueue;

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedQueue<T>& queue);

template<typename T>
class LinkedQueue {
private:
	DoublyLinkedList<T> dll; //internal LinkedList object
   /* declare member variables here */

public:
   // user-defined exceptions
   class QueueEmptyException : public RuntimeException {
   public:
     QueueEmptyException() : RuntimeException("Access to an empty queue") {}
   };
   //constructor
   LinkedQueue() : dll() {}
   //destructor
   ~LinkedQueue(){dll.~DoublyLinkedList();}
   // copy constructor
   LinkedQueue(const LinkedQueue& queue) : dll(queue.dll) { }
   // copy assignment
   LinkedQueue& operator=(const LinkedQueue& queue)
   {
      LinkedQueue q(queue);
      LinkedQueue r;
      // using two for loops to get the right sequence
      for(int i = 0; i < queue.size(); ++i)
         r.enqueue(q.dequeue());
      for(int i = 0; i < queue.size(); ++i)
         enqueue(r.dequeue());
      return *this;
   }
   
   // isEmpty function
   bool isEmpty() const
   {
   	return dll.isEmpty();
   }
   // size function
   int size() const { return dll.size();}

   //access function
   T first() const throw (QueueEmptyException)
   {
      if(dll.isEmpty())
         throw    QueueEmptyException();
      return dll.first();
   }
   
   // dequeue function
   T dequeue() throw (QueueEmptyException)
   {
      if(dll.isEmpty())
         throw QueueEmptyException();
      return dll.removeFirst();
   }

   // enqueue function
   void enqueue(T elem) { dll.insertLast(elem);}
   
   /* declare rest of functions */
   
};

/* describe rest of the functions here */

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedQueue<T>& queue)
{
   if(queue.isEmpty())
      return out << "{}";
   LinkedQueue<T> q(queue);
   out << '{';
   for(int i = 0; i< queue.size(); i++)
      {
      out << q.dequeue();
   }
  /* fill in the function */
   return out << '}';
}

#endif
