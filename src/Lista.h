#ifndef LISTA_H
#define LISTA_H

#include <iostream>
template <class T, class S>
struct nodo {
  T dato1;
  S dato2;
  nodo<T, S>* sig;
};

template <class T, class S>
class Lista {
  int numElem;
  nodo<T, S>* cab;

 public:
  Lista() {
    numElem = 0;
    cab = nullptr;
  }

  bool listaVacia() { return (cab == nullptr); }

  void insertarInicio(T info1, S info2);
  void insertarFinal(T info1, S info2);
  void insertarPos(T info1, S info2, int pos);

  bool borrarPos(int pos);
  nodo<T, S>* buscarPos(int pos);
  bool modificarPos(T info1, S info2, int pos);
  void vaciarLista();

  void imprimirLista();

  ~Lista() { vaciarLista(); };
};
template <typename T, typename S>
void Lista<T, S>::insertarInicio(T info1, S info2) {
  nodo<T, S>* aux = new nodo<T, S>;
  aux->dato1 = info1;
  aux->dato2 = info2;
  aux->sig = cab;
  cab = aux;
  numElem++;
}

template <class T, class S>
void Lista<T, S>::insertarFinal(T info1, S info2) {
  nodo<T, S>* aux = new nodo<T, S>;
  aux->dato1 = info1;
  aux->dato2 = info2;
  aux->sig = nullptr;

  if (listaVacia())
    cab = aux;
  else {
    nodo<T, S>* fin = cab;
    while (fin->sig != nullptr) fin = fin->sig;
    fin->sig = aux;
  }
  numElem++;
}

template <class T, class S>
void Lista<T, S>::insertarPos(T info1, S info2, int pos) {
  if (pos == 0) {
    insertarInicio(info1, info2);
    return;
  }

  if (pos == numElem) {
    insertarFinal(info1, info2);
    return;
  }

  if (pos < 0 || pos > numElem) {
    std::cerr << "No se pudo insertar en esa posicion\n";
    return;
  }

  nodo<T, S>* ins = cab;
  for (int i = 0; i < pos - 1; i++) ins = ins->sig;

  nodo<T, S>* aux = new nodo<T, S>;
  aux->dato1 = info1;
  aux->dato2 = info2;

  aux->sig = ins->sig;
  ins->sig = aux;

  numElem++;
}

template <class T, class S>
nodo<T, S>* Lista<T, S>::buscarPos(int pos) {
  if (pos < 0 || pos > numElem) {
    std::cerr << "posicion fuera de rango\n";
    return nullptr;
  }

  nodo<T, S>* aux = cab;
  for (int i = 0; i < pos; i++) {
    aux = aux->sig;
  }

  return aux;
}

template <class T, class S>
bool Lista<T, S>::borrarPos(int pos) {
  if (pos < 0 || pos >= numElem || listaVacia()) return false;
  nodo<T, S>* aux = cab;

  if (pos == 0) {
    cab = cab->sig;
    delete aux;
    numElem--;
    return true;
  }

  nodo<T, S>* borrarCab = buscarPos(pos - 1);
  aux = borrarCab->sig->sig;
  delete borrarCab->sig;

  borrarCab->sig = aux;

  numElem--;
  return true;
}

template <class T, class S>
bool Lista<T, S>::modificarPos(T info1, S info2, int pos) {
  nodo<T, S>* aux = buscarPos(pos);

  if (aux == nullptr) return false;

  aux->dato1 = info1;
  aux->dato2 = info2;
  return true;
}

template <class T, class S>
void Lista<T, S>::vaciarLista() {
  nodo<T, S>* aux1 = cab;
  nodo<T, S>* aux2;
  while (aux1 != nullptr) {
    aux2 = aux1->sig;
    delete aux1;
    aux1 = aux2;
  }
  cab = nullptr;
  numElem = 0;
}

template <class T, class S>
void Lista<T, S>::imprimirLista() {
  std::cerr << "[";
  if (listaVacia()) {
    std::cerr << "]";
    return;
  }

  nodo<T, S>* fin = cab;
  while (fin != nullptr) {
    std::cerr << "(" << fin->dato1 << ", " << fin->dato2 << "), ";
    fin = fin->sig;
  }

  std::cerr << "]\n";
}

#endif
