#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "RuntimeException.h"
#include <string>
#include <vector>
using namespace std;

class Parser {
private:
  /* declare constants */
  LinkedStack<string> opStack;
  LinkedQueue<string> expQueue;
  vector<string> infix;
  /* declare member variables;
   may include a string postfix queue and a integer operator stack */
  //functions for easier implementation
  bool IsOperand(string);
  bool IsOperator(string);
  int  inputPriority(string);
  int  stackPriority(string);
  int HasHigherPrecedence(int op1Weight, int op2Weight);
  bool ParanthesesBalanced();
  //bool InvaildInput();

  //void getToken(); // tokenizer function
  
  /* declare utility functions */

public:
  
  // constructor
  Parser(vector<string> s);  
  // destructor
  ~Parser();

  LinkedQueue<string> ToPostfix();
  // returns a string of the converted postfix expression stored in exp_queue 
  
  
  // accessor method
  // ? getPostfix() { }
  
  // operations
  void printInfix();
  void printPostfix();


  friend class LinkedStack<string>;
  friend class LinkedQueue<string>;
};

#endif
