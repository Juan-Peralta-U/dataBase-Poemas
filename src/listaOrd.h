
#ifndef LISTAORD_H
#define LISTAORD_H

#include <iostream>

// -----------------------------
// Estructura nodo ordenado
// -----------------------------
template <typename T, typename S>
struct nodoOrd {
  T dato1;                     // Dato principal almacenado en el nodo
  nodoOrd<T, S>* sig;         // Puntero al siguiente nodo
  S clave;                    // Clave que define el orden en la lista
};

template <class T, typename S>
// -----------------------------
// Clase ListaOrdenada
// -----------------------------
class ListaOrd {
  int numElem;                // Número de elementos actuales
  nodoOrd<T, S>* cab;         // Puntero al primer nodo (cabeza)

 public:
  // Constructor: inicializa lista vacía
  ListaOrd() {
    numElem = 0;
    cab = nullptr;
  }
  // Retorna el tamaño actual de la lista
  int getTam() { return numElem; }
  // Verifica si la lista está vacía
  bool listaVacia() { return (cab == nullptr); }
  // Inserta un elemento de forma ordenada por la clave
  void insertarClave(T info1, S clave);
  // Borra el primer nodo que tenga la clave y cuyo dato coincida
  bool borrarClave(S clave, T reference);
  // Busca y retorna el primer nodo con clave exacta
  nodoOrd<T, S>* buscarClave(S clave);
  // Retorna el nodo en una posición específica
  nodoOrd<T, S>* buscarPos(int pos);
  // Modifica el dato1 en la posición dada
  bool modificarPos(T info1, int pos);
  // Elimina todos los nodos de la lista
  void vaciarLista();
  // Destructor: limpia la memoria
  ~ListaOrd() { vaciarLista(); };
};
// --------------------------------------
// Implementación de métodos
// --------------------------------------

// Inserta un nodo en orden creciente por clave
template <class T, typename S>
void ListaOrd<T, S>::insertarClave(T info1, S clave) {
  nodoOrd<T, S>* nuevo = new nodoOrd<T, S>;
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
  nodoOrd<T, S>* actual = cab;

  while (actual->sig != nullptr && actual->sig->clave <= clave) {
    actual = actual->sig;
  }

  // Insertar después de 'actual'
  nuevo->sig = actual->sig;
  actual->sig = nuevo;
  numElem++;
}
// Elimina el primer nodo que tenga la clave y el mismo puntero `reference`
template <class T, typename S>
bool ListaOrd<T, S>::borrarClave(S clave, T reference) {
  if (listaVacia()) return false;

  nodoOrd<T, S>* actual = cab;
  nodoOrd<T, S>* anterior = nullptr;

  // Buscar nodo con clave igual o mayor (aprovecha orden)
  while (actual != nullptr && actual->clave < clave &&
         actual->dato1 != reference) {
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
// Busca el primer nodo cuya clave coincida exactamente
template <class T, typename S>
nodoOrd<T, S>* ListaOrd<T, S>::buscarClave(S clave) {
  nodoOrd<T, S>* actual = cab;

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
// Borra todos los nodos y libera la memoria
template <class T, typename S>
void ListaOrd<T, S>::vaciarLista() {
  nodoOrd<T, S>* aux1 = cab;
  nodoOrd<T, S>* aux2;
  while (aux1 != nullptr) {
    aux2 = aux1->sig;
    delete aux1;
    aux1 = aux2;
  }
  cab = nullptr;
  numElem = 0;
}
// Retorna el nodo en la posición dada (0-indexado)
template <class T, typename S>
nodoOrd<T, S>* ListaOrd<T, S>::buscarPos(int pos) {
  if (pos < 0 || pos > numElem) {
    std::cerr << "posicion fuera de rango\n";
    return nullptr;
  }

  nodoOrd<T, S>* aux = cab;
  for (int i = 0; i < pos; i++) {
    aux = aux->sig;
  }

  return aux;
}

#endif
