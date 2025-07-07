#ifndef LISTA_H
#define LISTA_H

#include <iostream>
// Estructura de un nodo simple de lista enlazada
template <class T>
struct nodo {
  T dato1; // Dato principal almacenado
  nodo<T>* sig; // Puntero al siguiente nodo
};
// Clase Lista
template <class T>
class Lista {
  int numElem; // Número de elementos actuales en la lista
  nodo<T>* cab; // Puntero al primer nodo (cabeza)

 public:
// Constructor: inicializa la lista vacía
  Lista() {
    numElem = 0;
    cab = nullptr;
  }
// Verifica si la lista está vacía
  bool listaVacia() { return (cab == nullptr); }
// Métodos de inserción
  void insertarInicio(T info1); // Inserta al inicio
  void insertarFinal(T info1); // Inserta al final
  void insertarPos(T info1, int pos); // Inserta en una posición específica

// Métodos de borrado y búsqueda
  bool borrarPos(int pos); // Elimina el nodo en la posición dada
  nodo<T>* buscarPos(int pos); // Devuelve el nodo en una posición

// Modifica el valor en una posición
  bool modificarPos(T info1, int pos);
// Elimina todos los nodos de la lista
  void vaciarLista();
// Verifica si un valor existe en la lista
  bool tieneValor(T value);
// Imprime la lista
  void imprimirLista();
// Devuelve el tamaño de la lista
  int getTam() const { return numElem; }

  // Devuelve el dato en la posición pos (0-based)
  T get(int pos) const {
    nodo<T>* aux = cab;
    for (int i = 0; i < pos && aux != nullptr; ++i) aux = aux->sig;
    if (aux) return aux->dato1;
    throw std::out_of_range("Posición fuera de rango en get()");
  }
// Destructor: libera toda la memoria
  ~Lista() { vaciarLista(); };
};
// Inserta un elemento al inicio de la lista
template <typename T>
void Lista<T>::insertarInicio(T info1) {
  nodo<T>* aux = new nodo<T>;
  aux->dato1 = info1;
  aux->sig = cab;
  cab = aux;
  numElem++;
}
// Inserta un elemento al final de la lista
template <class T>
void Lista<T>::insertarFinal(T info1) {
  nodo<T>* aux = new nodo<T>;
  aux->dato1 = info1;
  aux->sig = nullptr;

  if (listaVacia())
    cab = aux;
  else {
    nodo<T>* fin = cab;
    while (fin->sig != nullptr) fin = fin->sig;
    fin->sig = aux;
  }
  numElem++;
}
// Inserta un elemento en una posición específica
template <class T>
void Lista<T>::insertarPos(T info1, int pos) {
  if (pos == 0) {
    insertarInicio(info1);
    return;
  }

  if (pos == numElem) {
    insertarFinal(info1);
    return;
  }

  if (pos < 0 || pos > numElem) {
    std::cerr << "No se pudo insertar en esa posicion\n";
    return;
  }

  nodo<T>* ins = cab;
  for (int i = 0; i < pos - 1; i++) ins = ins->sig;

  nodo<T>* aux = new nodo<T>;
  aux->dato1 = info1;

  aux->sig = ins->sig;
  ins->sig = aux;

  numElem++;
}
// Devuelve el nodo en una posición específica
template <class T>
nodo<T>* Lista<T>::buscarPos(int pos) {
  if (pos < 0 || pos > numElem) {
    std::cerr << "posicion fuera de rango\n";
    return nullptr;
  }

  nodo<T>* aux = cab;
  for (int i = 0; i < pos; i++) {
    aux = aux->sig;
  }

  return aux;
}
// Elimina un nodo en una posición específica
template <class T>
bool Lista<T>::borrarPos(int pos) {
  if (pos < 0 || pos >= numElem || listaVacia()) return false;
  nodo<T>* aux = cab;

  if (pos == 0) {
    cab = cab->sig;
    delete aux;
    numElem--;
    return true;
  }

  nodo<T>* borrarCab = buscarPos(pos - 1); // Nodo anterior al que se va a borrar
  aux = borrarCab->sig->sig;
  delete borrarCab->sig;

  borrarCab->sig = aux;

  numElem--;
  return true;
}
// Verifica si la lista contiene un valor específico
template <class T>
bool Lista<T>::tieneValor(T value) {
  nodo<T>* aux = cab;
  for (int i = 0; i < getTam(); i++) {
    if (aux->dato1 == value) return true;
    aux = aux->sig;
  }

  return false;
}
// Modifica el valor en una posición específica
template <class T>
bool Lista<T>::modificarPos(T info1, int pos) {
  nodo<T>* aux = buscarPos(pos);

  if (aux == nullptr) return false;

  aux->dato1 = info1;
  return true;
}
// Elimina todos los nodos de la lista
template <class T>
void Lista<T>::vaciarLista() {
  nodo<T>* aux1 = cab;
  nodo<T>* aux2;
  while (aux1 != nullptr) {
    aux2 = aux1->sig;
    delete aux1;
    aux1 = aux2;
  }
  cab = nullptr;
  numElem = 0;
}
// Imprime la lista en consola
template <class T>
void Lista<T>::imprimirLista() {
  std::cerr << "[";
  if (listaVacia()) {
    std::cerr << "]";
    return;
  }

  nodo<T>* fin = cab;
  while (fin != nullptr) {
    std::cerr << "(" << fin->dato1 << ", " << fin->dato2 << "), ";
    fin = fin->sig;
  }

  std::cerr << "]\n";
}

#endif
