#ifndef __LISTA_H__
#define __LISTA_H__

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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

template <class T, int ARRAYSIZE = 100000>
class List {
 private:
  T data[ARRAYSIZE];
  int last;

  void mergeSort(const long&, const long&);
  void quickSort(const long&, const long&);

  bool isValid(const int&) const;
  void swapData(T&, T&) const;

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
  int find(const T&, int(const T&, const T&)) const;
  int findBina(const T&, int(const T&, const T&)) const;
  T retrieve(const int&) const;

  bool isSorted() const;

  void shorDataShell();
  void sortDataSelect();
  void sortDataBubble();
  void sortDataInsert();
  void sortDataBubbleM();

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  void sortDataSelect(int(const T&, const T&));
  // void sortDataShell(int(const T&, const T&));
  //  Revisar esto
  void mergeSort();
  void mergeSort(const int&, const int&, int(const T&, const T&));

  //
  void quickSort();
  void quickSort(int(const T&, const T&));

  void printData();
  void deleteALL();
  void writeToDisk(const std::string&);
  void readFromDisk(const std::string&);
  size_t memoryUsage() const;
};

using namespace std;

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& a, T& b) const {
  T aux(a);
  a = b;
  b = aux;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValid(const int& p) const {
  return p >= 0 && p <= ARRAYSIZE;
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
  return last == ARRAYSIZE - 1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertData(const int& p, const T& e) {
  if (isfull()) {
    throw Exception("Desbordamiento de datos, inserData");
  }

  if (p != -1 && !isValid(p)) {
    throw Exception("Posicion invalida,Insert Data");
  }

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

  for (int i = p; i < last; ++i) {
    data[i] = data[i + 1];
  }

  --last;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const {
  return isEmpty() ? -1 : 0;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const {
  return last;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPos(const int& p) const {
  return (!isValid(p)) ? -1 : p - 1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNextPos(const int& p) const {
  return (p == last || !isValid(p)) ? -1 : p + 1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::find(const T& e, int cmp(const T&, const T&)) const {
  int i = 0;
  while (i <= last) {
    if (cmp(data[i], e) == 0) {
      return i;
    }
    i++;
  }
  return -1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findBina(const T& e,
                                 int cmp(const T&, const T&)) const {
  int i = 0;
  int j = last - 1;

  while (i <= j) {
    int medio = (i + j) / 2;
    int result = cmp(data[medio], e);

    if (result == 0) {
      return medio;
    } else if (result > 0) {
      j = medio - 1;
    } else {
      i = medio + 1;
    }
  }
  return -1;
}

template <class T, int ARRAYSIZE>
T List<T, ARRAYSIZE>::retrieve(const int& p) const {
  if (!isValid(p)) {
    throw Exception("Índice inválido en retrieve");
  }
  return data[p];
}
// METODOS DE ORDENAMIENTO
//
//
//
template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isSorted() const {
  for (int i = 0; i < last; i++) {
    if (data[i] > data[i + 1]) {
      return false;
    }
  }
  return true;
}
//
//
//
//
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::shorDataShell() {
  float factor(1.0 / 2.0);
  int dif((last + 1) * factor), i, j;
  while (dif > 0) {
    i = dif;
    while (i <= last) {
      j = i;
      while (j >= dif && data[j - dif] > data[j]) {
        swapData(data[j - dif], data[j]);
        j -= dif;
      }
      i++;
    }
    dif *= factor;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataSelect() {
  int i(0), j, m;

  while (i < last) {
    m = i;

    j = i + 1;
    while (j <= last) {
      if (data[j] < data[m]) {
        m = j;
      }
      j++;
    }
    if (i != m) {
      swapData(data[i], data[m]);
    }
    i++;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble() {
  int i = last, j;

  while (i > 0) {
    j = 0;
    while (j < i) {
      if (data[j] > data[j + 1]) {
        swapData(data[j], data[j + 1]);
      }
      j++;
    }
    i--;
  }
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubbleM() {
  bool bandera;
  int i = last, j;

  while (i > 0) {
    j = 0;
    bandera = 0;
    while (j < i) {
      if (data[j] > data[j + 1]) {
        swapData(data[j], data[j + 1]);
        bandera = true;
      }
      j++;
    }
    if (!bandera) {
      break;
    }
    i--;
  }
}

// metodo interfaz le da sus primeros parametros
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::mergeSort() {
  mergeSort(0, last);
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::mergeSort(const long& left, const long& right) {
  // Criterio de paro
  if (left >= right) {
    return;
  }

  // Divide y venceras
  int m((left + right) / 2);
  mergeSort(left, m);
  mergeSort(m + 1, right);

  static T temp[ARRAYSIZE];  // Copia temporal
  // Copiar datos al array temporal
  for (int e(left); e < right; e++) {
    temp[e] = data[e];
  }

  // Intercalación
  int i(left), j(m + 1), x(left);

  while (i <= m && j <= right) {
    while (i <= m && temp[i] <= temp[j]) {
      data[x++] = temp[i++];
    }

    if (i <= m) {
      while (j <= right && temp[j] <= temp[i]) {
        data[x++] = temp[j++];
      }
    }
  }

  // Copiar los elementos restantes de la primera mitad
  while (i <= m) {
    data[x++] = temp[i++];
  }

  // Copiar los elementos restantes de la segunda mitad
  while (j <= right) {
    data[x++] = temp[j++];
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::mergeSort(const int& left,
                                   const int& right,
                                   int cmp(const T& a, const T& b)) {
  // Criterio de paro
  if (left >= right) {
    return;
  }

  // Divide
  int m = (left + right) / 2;
  mergeSort(left, m, cmp);
  mergeSort(m + 1, right, cmp);

  // Venceras
  static T temp[ARRAYSIZE];  // Copia temporal

  // Copiar datos al array temporal
  for (int e = left; e <= right; ++e) {
    temp[e] = data[e];
  }

  int i = left, j = m + 1, x = left;

  // Intercalación
  while (i <= m && j <= right) {
    if (cmp(temp[i], temp[j]) <= 0) {
      data[x++] = temp[i++];
    } else {
      data[x++] = temp[j++];
    }
  }

  // Copiar los elementos restantes de la primera mitad
  while (i <= m) {
    data[x++] = temp[i++];
  }

  // Copiar los elementos restantes de la segunda mitad
  while (j <= right) {
    data[x++] = temp[j++];
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::quickSort() {
  quickSort(0, last);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::quickSort(const long& L, const long& R) {
  if (L >= R) {
    return;
  }

  int i(L), j(R);

  while (i < j) {
    while (i < j and data[i] <= data[R]) {
      i++;
    }

    while (i < j and data[j] >= data[R]) {
      j--;
    }

    if (i != j) {
      swapData(data[i], data[j]);
    }
  }

  if (i != R) {
    swapData(data[i], data[R]);
  }

  quickSort(L, i - 1);
  quickSort(i + 1, R);
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::printData() {
  for (int i = 0; i <= last; ++i) {
    cout << data[i] << " ";
  }
  cout << endl;
}
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert() {
  int i(1), j;
  T aux;
  while (i <= last) {
    aux = data[i];
    j = i;
    while (j > 0 and aux < data[j - 1]) {
      data[j] = data[j - 1];
      j--;
    }
    if (i != j) {
      data[j] = aux;
    }
    i++;
  }
}

template <class T, int ARRAYSIZE>
size_t List<T, ARRAYSIZE>::memoryUsage() const {
  size_t totalSize = sizeof(*this);  // Size of the List object itself
  for (int i = 0; i <= last; ++i) {
    totalSize += sizeof(data[i]);  // Size of each element in the array
    cout << totalSize << endl;
  }
  return totalSize;
}
#endif
