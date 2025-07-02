#ifndef LISTA_H
#define LISTA_H

#include <iostream>
template <typename T, typename S>
struct nodo {
  T dato1;
  nodo<T, S>* sig;
  S clave;
};

template <class T, typename S>
class Lista {
  int numElem;
  nodo<T, S>* cab;

 public:
  Lista() {
    numElem = 0;
    cab = nullptr;
  }

  bool listaVacia() { return (cab == nullptr); }

  void insertarClave(T info1, S clave);

  bool borrarClave(S clave);
  nodo<T, S>* buscarClave(S clave);
  bool modificarPos(T info1, int pos);
  void vaciarLista();

  ~Lista() { vaciarLista(); };
};

template <class T, typename S>
void Lista<T, S>::insertarClave(T info1, S clave) {
  nodo<T, S>* nuevo = new nodo<T, S>;
  nuevo->clave = clave;
  nuevo->dato1 = info1;
  nuevo->sig = nullptr;

  // Caso 1: Lista vacía
  if (cab == nullptr) {
    cab = nuevo;
    numElem++;
    return;
  }

  // Caso 2: Inserción antes del primer nodo
  if (clave < cab->clave) {
    nuevo->sig = cab;
    cab = nuevo;
    numElem++;
    return;
  }

  // Búsqueda del punto de inserción
  nodo<T, S>* actual = cab;
  while (actual->sig != nullptr && actual->sig->clave <= clave) {
    actual = actual->sig;
  }

  // Insertar después de 'actual'
  nuevo->sig = actual->sig;
  actual->sig = nuevo;
  numElem++;
}

template <class T, typename S>
bool Lista<T, S>::borrarClave(S clave) {
  if (listaVacia()) return false;

  nodo<T, S>* actual = cab;
  nodo<T, S>* anterior = nullptr;

  // Buscar nodo con clave igual o mayor (aprovecha orden)
  while (actual != nullptr && actual->clave < clave) {
    anterior = actual;
    actual = actual->sig;
  }

  // Caso 1: Clave no encontrada (fin de lista o clave mayor)
  if (actual == nullptr || actual->clave != clave) {
    return false;
  }

  // Caso 2: Eliminar primer nodo
  if (anterior == nullptr) {
    cab = actual->sig;
  }
  // Caso 3: Eliminar nodo intermedio/final
  else {
    anterior->sig = actual->sig;
  }

  delete actual;
  numElem--;
  return true;
}

template <class T, typename S>
nodo<T, S>* Lista<T, S>::buscarClave(S clave) {
  nodo<T, S>* actual = cab;

  // Aprovecha el orden de la lista para búsqueda temprana
  while (actual != nullptr && actual->clave < clave) {
    actual = actual->sig;
  }

  // Verificar si encontramos el nodo con la clave exacta
  if (actual != nullptr && actual->clave == clave) {
    return actual;
  }

  // Clave no encontrada
  return nullptr;
}

template <class T, typename S>
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

#endif
