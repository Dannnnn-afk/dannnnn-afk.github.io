#ifndef __LISTA_HPP__
#define __LISTA_HPP__

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

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

template <class T, int ARRAYSIZE = 3000>
class List {
 private:
  T data[ARRAYSIZE];
  int last;

  bool isValid(const int&) const;

 public:
  List();
  bool isEmpty() const;
  bool isfull() const;
  void insertData(const int&, const T&);  // posicion elemento.
  void deleteData(const int&);
  int getFirstPos() const;
  int getLastPos() const;
  int getPrevPos(const int&) const;
  int getNextPos(const int&) const;
  int find(const T&) const;
  int findBina(const T&) const;
  T retrieve(const int&) const;
  void sortData();
  // string toString()const;
  void printData();
  void deleteALL();
};

using namespace std;

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValid(const int& p) const {
  return p >= 0 and p <= last;
}
template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() {
  last = -1;
}
template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() const {
  return last == -1;
}
template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isfull() const {
  return last == ARRAYSIZE;
}
// primero posicion despues elemento.
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertData(const int& p, const T& e) {
  if (isfull()) {
    throw Exception("Desbordamiento de datos, inserData");
  }

  if (p != -1 and !isValid(p)) {
    throw Exception("Posicion invalida,Insert Data");
  }
  // Esto es en EL PUNTO DE INTERES
  /*int i(last+1);
  while (i> p)
  {
     data[i] = data[i-1];
     i++;
  }
  DATA[P] =e;
  lat++;*/

  int i(last);
  while (i > p) {
    data[i + 1] = data[i];
    i--;
  }
  data[p + 1] = e;
  last++;
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteData(const int& p) {
  if (!isValid(p)) {
    throw Exception("Índice inválido en deleteData");
  }

  // Desplazar los elementos a la izquierda para cubrir el espacio del elemento
  // eliminado
  for (int i = p; i < last; ++i) {
    data[i] = data[i + 1];
  }

  --last;  // Decrementar el índice del último elemento
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const {
  /*if(isEmpty){
   return -1;
  }
   return 0;*/

  return isEmpty() ? -1 : 0;
}
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const {
  return last;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPos(const int& p) const {
  /*if(p == 1 or isValid(p)){
  return -1;

  }
  return p-1;
  */

  return (!isValid(p)) ? -1 : p - 1;
}
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNextPos(const int& p) const {
  return (p == last or !isValid(p)) ? -1 : p + 1;
}
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::find(const T& e) const {
  int i(0);
  while (i <= last){
    if(data[i]==e){
      return i;
    }
    i++;
   
  }
 return -1;
}
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findBina(const T& e) const {
  



}

template <class T, int ARRAYSIZE>
T List<T, ARRAYSIZE>::retrieve(const int& p) const {
  if (isValid(p)) {
    throw Exception("Desbordamiento de datos, retrieveData");
  }
  return data[p];
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortData() {
  // pendiente
}

// Aca va un std:: toSting()const para trabjar con objetos
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::printData() {
  string result;
  int i(0);
  while (i <= last) {
    cout << "Posicion " << i << ": " << data[i].toString() << endl;
    i++;
  }
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteALL() {
  last = -1;
}

#endif  // __LISTA_HPP__
