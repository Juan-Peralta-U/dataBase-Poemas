#ifndef LISTA_H
#define LISTA_H

#include <iostream>

// --------------------------
// Definición del nodo genérico
// --------------------------
template <class T>
struct nodo {
  T dato1; // Dato principal almacenado en el nodo
  nodo<T>* sig;// Puntero al siguiente nodo
};
// --------------------------
// Clase Lista (lista enlazada simple genérica)
// --------------------------
template <class T>
class Lista {
  int numElem; // Cantidad de elementos actuales en la lista
  nodo<T>* cab; // Puntero al primer nodo de la lista

 public:
  // Constructor: crea una lista vacía
  Lista() {
    numElem = 0;
    cab = nullptr;
  }
// Verifica si la lista está vacía
  bool listaVacia() { return (cab == nullptr); }
 // Métodos para insertar elementos
  void insertarInicio(T info1); // Inserta al inicio
  void insertarFinal(T info1); // Inserta al final
  void insertarPos(T info1, int pos); // Inserta en una posición específica
// Métodos para eliminar, buscar y modificar elementos 
  bool borrarPos(int pos); // Borra un nodo en la posición dada
  nodo<T>* buscarPos(int pos); // Retorna el nodo en la posición dada
  bool modificarPos(T info1, int pos); // Modifica el nodo en la posición dada
  void vaciarLista(); // Elimina todos los nodos

  bool tieneValor(T value); // Verifica si un valor existe en la lista

  void imprimirLista(); // Imprime todos los elementos (con error en implementación)

  int getTam() const { return numElem; } // Devuelve la cantidad de elementos

  // Devuelve el dato en la posición pos (0-based)
  T get(int pos) const {
    nodo<T>* aux = cab;
    for (int i = 0; i < pos && aux != nullptr; ++i) aux = aux->sig;
    if (aux) return aux->dato1;
    throw std::out_of_range("Posición fuera de rango en get()");
  }
  // Destructor: libera toda la memoria utilizada
  ~Lista() { vaciarLista(); };
};
// --------------------------
// Implementación de métodos
// --------------------------

// Inserta un nuevo nodo al inicio de la lista
template <typename T>
void Lista<T>::insertarInicio(T info1) {
  nodo<T>* aux = new nodo<T>;
  aux->dato1 = info1;
  aux->sig = cab;
  cab = aux;
  numElem++;
}
// Inserta un nuevo nodo al final de la lista
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
// Inserta un nuevo nodo en una posición específic
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
// Busca y retorna el nodo en la posición indicada
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
// Borra el nodo ubicado en la posición dada
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

  nodo<T>* borrarCab = buscarPos(pos - 1);
  aux = borrarCab->sig->sig;
  delete borrarCab->sig;

  borrarCab->sig = aux;

  numElem--;
  return true;
}

// Verifica si el valor existe en algún nodo de la lista
template <class T>
bool Lista<T>::tieneValor(T value) {
  nodo<T>* aux = cab;
  while (aux != nullptr) {  // Verifica aux en cada iteración
    if (aux->dato1 == value) return true;
    aux = aux->sig;
  }
  return false;
}
// Modifica el contenido del nodo en la posición especificada
template <class T>
bool Lista<T>::modificarPos(T info1, int pos) {
  nodo<T>* aux = buscarPos(pos);

  if (aux == nullptr) return false;

  aux->dato1 = info1;
  return true;
}
// Elimina todos los nodos de la lista, liberando la memoria
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
// Imprime el contenido de la lista (nota: intenta imprimir dato2, que no existe en esta versión)
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
