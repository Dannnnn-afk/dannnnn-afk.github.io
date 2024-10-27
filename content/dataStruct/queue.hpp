#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <exception>
#include <string>

template <class T, int ARRAYSIZE = 20>
class Queue {
 private:
  int frontPos;
  int endPos;
  T data[ARRAYSIZE];
  void copyAll(const Queue&);

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
  Queue();
  Queue(const Queue&);
  bool isEmpy() const;
  bool isFull() const;
  void enqueue(const T&);
  T dequeue();
  T getFront() const;
  Queue& operator=(const Queue&);
};

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::copyAll(const Queue& q) {
  frontPos = q.frontPos;
  endPos = q.endPos;
  int tempPos = frontPos;

  while (tempPos != endPos) {
    data[tempPos] = q.data[tempPos];
    tempPos++;
  }
  data[endPos] = q.data[endPos];
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue() : frontPos(0), endPos(ARRAYSIZE - 1) {}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue& q) {
  copyAll(q);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmpy() const {
  return (frontPos == endPos + 1) or
         (frontPos == 0 and endPos == 1 and endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull() const {
  return frontPos == endPos + 2 or
         (frontPos == 0 and endPos == ARRAYSIZE - 2) or
         (frontPos == 1 and endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& e) {
  if (isFull()) {
    throw Queue::Exception("Desbordamiento de datos, enqueue");
  }
  data[endPos = (++endPos == ARRAYSIZE) ? 0 : endPos] = e;

  /*if(++endPos== ARRAYSIZE){
      endPos=0;

  }*/
}

template <class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue() {
  if (isEmpy()) {  // Asegúrate de usar isEmpty()
    throw Exception("Insuficiencia de datos, dequeue");
  }

  // Devolver el valor en la posición 'frontPos'
  T result = data[frontPos];

  // Actualizar 'frontPos'
  frontPos = (++frontPos == ARRAYSIZE) ? 0 : frontPos;

  return result;
}

template <class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::getFront() const {
  if (isEmpy()) {
    throw Exception("Insuficiencia de datos getFront");
  }
  T result(data[frontPos]);
  return result;
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>& Queue<T, ARRAYSIZE>::operator=(const Queue& q) {
  copyAll(q);
  return *this;
}

#endif  // __QUEUE_H__