#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Parser.h"
#include "Table.h"
#include "Record.h"
#include "Database.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "RuntimeException.h"
#include <math.h> 
#include <bitset>

class Evaluator {
public:
  // user-defined exceptions
  class DivisionByZeroException : public RuntimeException {
    public:
      DivisionByZeroException() : RuntimeException("Division by zero") {}
  };     
private:
  /* declare member variables; 
    may include a string postfix queue and a double value stack */
  LinkedStack<string> valStack;
  //LinkedQueue<string> helper;
  LinkedQueue<string> postfix;
  Table* t;
  /* declare utility functions */

public:
  Evaluator(Parser& par, Table* arg) 
  { 
    postfix = par.ToPostfix();
    t = arg;
  } // constructor

 // void usersValue(); //get the letters' value from users 
  // don't need to get value from the users 
  string getValue(); // returns the result of expression evaluation
};

#endif
