// Willem van Veldhuisen
// 12/06

#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;
//Functions
void pushNode(Node** stack, int* top, Node* b);
void push(char* a, char b, int* top);
char pop(char* a, int* top);
void enqueue(char* a, char* b, int* back);
void dequeue(char* a, int* front, int* back, char* out);
bool isOpp(char a);
void prefix(Node* current);
char peek(char* a, int top);
Node* popNode(Node** stack, int* top);
void buildTree(char* queue, Node** stack, int* front, int* back, int* top);
//struct I never used
struct data {
  char a;
  int b;
};
//Main function
int main() {
  //variables
  char* queue;
  char* stack;
  int top = 0;
  int front = 0;
  int back = 0;
  char* input;
  input = new char[50];
  stack = new char[50];
  queue = new char[50];
  //user input
  cout << "Enter Mathematical Expresion(no spaces)" << endl;
  cin >> input;
  cout << "Infix: " << input << endl;
  char* arr;
  arr = new char[20];
  int m;
  //Turn from infix into profix using SYA
  for (int i = 0; i < strlen(input); i++) {
    //if is opperation
    if (isOpp(input[i])) {
      if (strlen(arr) != 0) {
	enqueue(queue, arr, &back);
	m = 0;
	memset(arr, 0, 20 * (sizeof arr[0]));
      }
      if (input[i] == '+' || input[i] == '-') {
	if (peek(stack, top) != '^' && peek(stack, top) != '*' && peek(stack, top) != '/' && peek(stack, top) != '+' && peek(stack, top) != '-') {
	  push(stack, input[i], &top);
	}
	else {
	  for (int i = 0; i < top + 1; i++) {
	    if (peek(stack, top) != '(') {
	      queue[back + 1] = pop(stack, &top);
	      back++;
	      queue[back + 1] = ' ';
	      back++;
	    }
	    else {
	      break;
	    }
	  }
	  push(stack, input[i], &top);
	}
      }
      else if (input[i] == '*' || input[i] == '/') {
	if (peek(stack, top) != '^' && peek(stack, top) != '*' && peek(stack, top) != '/') {
	  push(stack, input[i], &top);
	}
	else {
	  for (int i = 0; i < top + 1; i++) {
	    if (peek(stack, top) != '(') {
	      queue[back + 1] = pop(stack, &top);
	      back++;
	      queue[back + 1] = ' ';
	      back++;
	    }
	    else {
	      break;
	    }
	  }
	  push(stack, input[i], &top);
	}
      }
      else if (input[i] == '(') {
	push(stack, input[i], &top);
      }
      else if (input[i] == ')') {
	while(1) {
	  if (peek(stack, top) == '(') {
	    pop(stack, &top);
	    break;
	  }
	  else {
	    queue[back + 1] = pop(stack, &top);
	    back++;
	    queue[back + 1] = ' ';
	    back++;
	  }
	}
      }
      else {
	push(stack, input[i], &top);
      }
    }
    // If is number
    else if (input[i] >= '0' && input[i]  <= '9') {
      arr[m] = input[i];
      m++;
    } else {
      cout << "Unknown character" << ends;
    }
  }
  if (strlen(arr) != 0) {
    enqueue(queue, arr, &back);
    m = 0;
    memset(arr, 0, strlen(arr) * (sizeof arr[0]));
  }
  int t = top;
  for (int i = 0; i < t + 1; i++) {
    queue[back + 1] = pop(stack, &top);
    back++;
    queue[back + 1] = ' ';
    back++;
  }
  //Present finished postfix
  cout << "Postfix: ";
  for (int i = 0; i < back + 1; i++) {
    cout << queue[i];
  }
  cout << endl;
  Node** stac;
  stac = new Node*[30];
  int tops = 0;
  buildTree(queue, stac, &front, &back, &tops);
  cout << "Prefix: " << stac[0]->getValue() << ' ';
  prefix(stac[0]);
}
//Build the tree using the postfix and a Node pointer stack
void buildTree(char* queue, Node** stack, int* front, int* back, int* top) {
  Node* node;
  char* current;
  current = new char[20];
  dequeue(queue, front, back, current);
  node = new Node(current);
  if (isOpp(current[0]) == true) {
    node->setRchild(popNode(stack, top));
    node->setLchild(popNode(stack, top));
    pushNode(stack, top, node);
  }
  else {
    pushNode(stack, top, node);
  }
  if (*front < *back) {
    (*front)++;
    buildTree(queue, stack, front, back, top);
  }
}
//Prints in prefix form using tree
void prefix(Node* current) {
  if (current->getLchild() != NULL) {
    cout << current->getLchild()->getValue() << ' ';
    prefix(current->getLchild());
  }
  if (current->getRchild() != NULL) {
    cout << current->getRchild()->getValue() << ' ';
    prefix(current->getRchild());
  }
}
//Push function for node stack
void pushNode(Node** stack, int* top, Node* b) {
  if (stack[0] != NULL) {
    stack[*top + 1] = b;
    (*top)++;
  }
  else {
    stack[0] = b;
  }
}
//Pop function for node stack
Node* popNode(Node** stack, int* top) {
  Node* temp = stack[*top];
  (*top)--;
  return temp;
}
//Check if something is an opperator
bool isOpp(char a) {
  if (a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '(' || a == ')') {
    return true;
  }
  return false;
}
//Push from a queue
void enqueue(char* a, char* b, int* back) {
  for (int i = 0; i < strlen(b); i++) {
    if (*back != 0) {
      a[*back + 1] = b[i];
      (*back)++;
    }
    else {
      if (isOpp(a[0]) == true || a[0] == '0' || a[0] == '1' || a[0] == '2' || a[0] == '3' || a[0] == '4' || a[0] == '5' || a[0] == '6' || a[0] == '7' || a[0] == '8' || a[0] == '9') {
	(*back)++;
	a[*back] = b[i];
      }
      else {
	a[0] = b[i];
      }
    }
  }
  a[*back + 1] = ' ';
  (*back)++;
}
//Pop from a queue
void dequeue(char* a, int* front, int* back, char* out) {
  int temp = 0;
  if (a[*front] == ' ') {
    (*front)++;
  }
  if (isOpp(a[*front]) == true) {
    out[0] = a[*front];
    out[1] = '\0';
    (*front)++;
  }
  else {
    while (1) {
      if (a[*front] == ' ') {
	break;
      }
      else {
	out[temp] = a[*front];
	(*front)++;
	temp++;
      }
    }
    out[temp] = '\0';
  }
}
//Push for stack
void push(char* a, char b, int* top) {
  if (*top != 0) {
    a[*top + 1] = b;
    (*top)++;
  }
  else {
    if (isOpp(a[0]) == true || a[0] == '0' || a[0] == '1' || a[0] == '2' || a[0] == '3' || a[0] == '4' || a[0] == '5' || a[0] == '6' || a[0] == '7' || a[0] == '8' || a[0] == '9') {
      (*top)++;
      a[*top] = b;
    }
    else {
      a[0] = b;
    }
    
  }
}
//Peek top value of stack
char peek(char* a, int top) {
  return a[top];
  
}
//Pop top function of stack
char pop(char* a, int* top) {
  char temp = a[*top];
  if (*top == 0) {
    a[*top] = ' ';
  }
  else {
    (*top)--;
  }
  return temp;
}
