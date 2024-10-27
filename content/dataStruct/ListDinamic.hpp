#ifndef __LISTDINAMIC_H__
#define __LISTDINAMIC_H__

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

template <class T>
class List {
 private:
  class Node {
   private:
    T data;
    Node* next = nullptr;

   public:
    Node();
    Node(const T&);
    ~Node();
    // Puede ser sin referencias
    T& getData();
    Node* getNext();
    void setData(const T&);
    void setNext(Node*);
  };

 public:
  // inicia publico.
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
  // Publico
  typedef Node* Position;

 private:
  Position anchor;

  bool isValidPos(const Position&) const;
  void copyAll(const List<T>&);

 public:
  List();
  List(const List<T>&);
  ~List();
  // No tiene concepto de llena lo que la memoria soporte neni
  bool isEmpty() const;
  void insertData(const Position&, const T&);
  void deleteData(const Position&);
  List<T>::Position getFirstPos() const;
  List<T>::Position getLastPos() const;
  List<T>::Position getPrevPos(const Position&) const;
  List<T>::Position getNextPos(const Position&) const;
  List<T>::Position findData(const T&) const;
  Position findData(const T&, int(*compare)(const T&, const T&)) const;

  // Por referencia es cambiarlo dentro de la lista
  T& retrieve(const Position&);
  std::string toString() const;
  void deleteAll();

  List& operator=(const List<T>&);
};
template <class T>
List<T>::Node::Node() : next(nullptr), data() {}

template <class T>
List<T>::Node::Node(const T& e)  : next(nullptr), data(e) {}

template <class T>
List<T>::Node::~Node() {}

template <class T>
T& List<T>::Node::getData() {
  return data;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() {
  return next;
}

template <class T>
void List<T>::Node::setData(const T& e) {
  data = e;
}

template <class T>
void List<T>::Node::setNext(Node* e) {
  next = e;
}
// Implementar lista

template <class T>
List<T>::List() : anchor(nullptr) {}
template <class T>
bool List<T>::isValidPos(const List<T>::Position& p) const {
  Position aux = anchor;
  while (aux != nullptr) {
    if (aux == p) {
      return true;
    }
    aux = aux->getNext();
  }
  return false;
}
template <class T>
void List<T>::copyAll(const List<T>& l) {
  Position aux(l.anchor), lastInserted(nullptr), newNode;
  while (aux != nullptr) {
    newNode = new(std::nothrow) Node(aux->getData());
    if (newNode == nullptr) {
      throw Exception("Memoria insuficiente");
    }
    if (lastInserted == nullptr) {
      anchor = newNode;
    } else {
      lastInserted->setNext(newNode);
    }
    lastInserted = newNode;
    aux = aux->getNext();
  }
}

template <class T>
List<T>::List(const List<T>& lista) : anchor(nullptr) {
  copyAll(lista);
}

template <class T>
List<T>::~List() {
  deleteAll();
}

template <class T>
bool List<T>::isEmpty() const {
  return anchor == nullptr;
}

template <class T>
void List<T>::insertData(const typename List<T>::Position& p, const T& e) {
  if (p != nullptr and !isValidPos(p)) {
    throw Exception("Posicion invalida, insertData");
  }
  Position aux(new Node(e));
  if (aux == nullptr) {
    /* code */ throw Exception("Memoria no disponible");
  }
  // Religado
  // Incio
  if (p == nullptr) {
    aux->setNext(anchor);
    anchor = aux;
  }  // Inserta en otro lugar
  else {
    aux->setNext(p->getNext());
    p->setNext(aux);
  }
}

template <class T>
void List<T>::deleteData(const List<T>::Position& p) {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida");
  }
  if (p == anchor) {
    anchor = p->getNext();
  } else {
    getPrevPos(p)->setNext(p->getNext());
  }
  delete p;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const {
  return anchor;
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const {
  Position aux(anchor);
  while (aux->getNext() != nullptr) {
    aux = aux->getNext();
  }
  return aux;
}

template <class T>
typename List<T>::Position List<T>::getPrevPos(const Position& p) const {
  Position aux(anchor);
  while (aux != nullptr && aux->getNext() != p) {
    aux = aux->getNext();
  }
  return aux;
}

template <class T>
typename List<T>::Position List<T>::getNextPos(const Position& p) const {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida");
  }

  return p->getNext();
}


template <class T>
typename List<T>::Position List<T>::findData(const T& e) const {
  Position aux(anchor);
  while (aux != nullptr && aux->getData() != e) {
    aux = aux->getNext();
  }
  return aux;
}
template <class T>
typename List<T>::Position List<T>::findData(const T& e, int(*compare)(const T&, const T&)) const {
    Position aux = anchor;
    while (aux != nullptr && compare(aux->getData(), e) != 0) {
        aux = aux->getNext();
    }
    return aux;
}
template <class T>
T& List<T>::retrieve(const List<T>::Position& p) {
  if (!isValidPos(p)) {
    throw Exception("Posicion Invalida");
  }
  return p->getData();
}

template <class T>
std::string List<T>::toString() const {
    Position aux;
     aux = anchor;
std::string result;
  while (aux != nullptr) {
    
    result += aux->getData().toString() + "\n";
    aux = aux->getNext();
  }
  return result;
}

template <class T>
void List<T>::deleteAll() {
  Position aux;
  while (anchor != nullptr) {
    aux = anchor;

    anchor = aux->getNext();
    delete aux;
  }
}

template <class T>
List<T>& List<T>::operator=(const List<T>& lista) {
  copyAll(lista);
  return *this;
}
#endif // __LISTDINAMIC_H__