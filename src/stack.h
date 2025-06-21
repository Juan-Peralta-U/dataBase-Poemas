#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
  struct Node {
    T data;
    Node* next;
  };

  Node* top;

 public:
  Stack() : top(nullptr) {}

  void push(T value) {
    Node* newNode = new Node{value, top};
    top = newNode;
  }

  T pop() {
    if (isEmpty()) {
      return T();
    }
    Node* temp = top;
    T value = temp->data;
    top = top->next;
    delete temp;
    return value;
  }

  bool isEmpty() { return top == nullptr; }

  ~Stack() {
    while (!isEmpty()) {
      pop();
    }
  }
};

#endif
