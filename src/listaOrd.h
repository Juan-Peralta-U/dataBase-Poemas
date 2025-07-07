
#ifndef LISTAORD_H
#define LISTAORD_H

#include <iostream>
// Definición de estructura nodoOrd para lista ordenada.
// T: tipo de dato almacenado. S: tipo de la clave usada para ordenar.
template <typename T, typename S>
struct nodoOrd {
  T dato1; // Dato principal a almacenar
  nodoOrd<T, S>* sig;  // Puntero al siguiente nodo
  S clave; // Clave usada para mantener orden en la lista
};
// Clase ListaOrd: lista enlazada ordenada por clave.
// Permite insertar, buscar y borrar elementos manteniendo orden ascendente.
template <class T, typename S>
class ListaOrd {
  int numElem; // Número total de elementos en la lista
  nodoOrd<T, S>* cab; // Puntero al primer nodo (cabeza)
 // Constructor: inicializa lista vacía
 public:
  ListaOrd() {
    numElem = 0;
    cab = nullptr;
  }
 // Verifica si la lista está vacía
  bool listaVacia() { return (cab == nullptr); }
// Inserta un elemento manteniendo el orden por clave
  void insertarClave(T info1, S clave);
// Borra un elemento con la clave y el dato de referencia
  bool borrarClave(S clave, T reference);
// Busca y devuelve el nodo con la clave exacta
  nodoOrd<T, S>* buscarClave(S clave); 
  nodoOrd<T, S>* buscarPos(int pos); // Busca y devuelve el nodo en la posición `pos` (0-indexado)
  bool modificarPos(T info1, int pos);   // Modifica el contenido del nodo en la posición indicada

  void vaciarLista();  // Elimina todos los nodos de la lista
// Destructor: libera toda la memoria de la lista
  ~ListaOrd() { vaciarLista(); };
};
// Implementación: insertar elemento en la lista manteniendo orden
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
// Implementación: borrar nodo con clave y valor específicos
template <class T, typename S>
bool ListaOrd<T, S>::borrarClave(S clave, T reference) {
  if (listaVacia()) return false;

  nodoOrd<T, S>* actual = cab;
  nodoOrd<T, S>* anterior = nullptr;

  // Buscar nodo con clave igual o mayor 
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
// Implementación: buscar nodo por clave

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
// Implementación: eliminar todos los nodos de la lista
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
// Implementación: buscar nodo por posición (0-based)
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
