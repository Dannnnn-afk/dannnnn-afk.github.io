#ifndef __PILA_H__
#define __PILA_H__

#include <exception>
#include <string>
// pila o sta

// definicion
template <class T, int ARRAYSIZE = 1024>
class Stack {
 private:
  T data[ARRAYSIZE];
  int top;
  void copyAll(const Stack&);

 public:
  class Exception : public std::exception {
   private:
    std::string msg;

   public:
    Exception() noexcept : msg("Error indefinido") {}
    Exception(const Exception& ex) noexcept : msg(ex.msg) {}
    Exception(const std::string& m) : msg(m) {}
    Exception& operator=(const Exception& ex) noexcept {
      msg = ex.msg;
      return *this;
    }
    virtual ~Exception() {}
    virtual const char* what() const noexcept { return msg.c_str(); }
  };
  Stack();
  Stack(const Stack&);
  bool isEmpty() const;
  bool isFull() const;
  void push(const T&);
  void pop();
  T popRegresa();
  T getTop() const;

  Stack& operator=(const Stack&);
};

// implementacion.
using namespace std;

// delegacion de constructores.
template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack() : top(-1) {}

template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack& other) {
  copyAll(other);
}

template <class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty() const {
  return top == -1;
}

template <class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull() const {
  return top == ARRAYSIZE - 1;
}

template <class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T& e) {
  if (isFull()) {
    throw Exception("Desbordamiento de datos,psuh");
  }

  data[++top] = e;
}
// version que no recibe nadota
template <class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::pop() {
  if (isEmpty()) {
    throw Exception("Insuficiencia de datos, pop");
  }
  top--;
}

template <class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::popRegresa() {
  if (isEmpty()) {
    throw Exception("Insuficiencia de datos, pop");
  }

  return (data[top--]);
}

template <class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::getTop() const {
  if (isEmpty()) {
    throw Exception("Insuficiencia de datos, getTop");
  }

  return data[top];
}

template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>& Stack<T, ARRAYSIZE>::operator=(const Stack& other) {
  copyAll(other);
  return *this;
}

template <class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack&other) {
  top = other.top;
  int i(0);
  while (i <= top) {
    data[i] = other.data[i];
    i++;
  }
}

#endif  // __PILA_H__