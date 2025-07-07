#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

#include "pila.h" // Estructura auxiliar tipo cola (FIFO)
#include "stack.h" // Estructura auxiliar tipo pila (LIFO)
// Estructura del nodo del árbol rojo-negro
template <typename s>
struct RBNode {
  int key;         // Clave que se usa para organizar el nodo
  s data;          // Dato genérico almacenado en el nodo
  bool color;      // true = rojo, false = negro
  RBNode<s> *parent; // Puntero al nodo padre
  RBNode<s> *izq;    // Puntero al hijo izquierdo
  RBNode<s> *der;    // Puntero al hijo derecho
};
// Árbol rojo-negro implementado con arreglo estático de tamaño n+1
template <int n, typename s>
class TreeRB {
  RBNode<s> datos[n + 1]; // Arreglo que almacena todos los nodos

 public:
  // Constructor que inicializa el árbol y la lista de nodos disponibles
  TreeRB() {
    datos[0].key = 0;
    datos[0].data = s();
    datos[0].color = false; // nodo de color negro
    datos[0].parent = &datos[0];
    datos[0].izq = &datos[0];

    datos[0].der = &datos[1]; // el primero disponible

    for (int i = 1; i <= n; i++) {
      datos[i].key = 0;
      datos[i].data = s();
      datos[i].color = false;
      datos[i].parent = &datos[0];
      datos[i].izq = &datos[0];

      if (i < n) {
        datos[i].der = &datos[i + 1];
      } else {
        datos[i].der = &datos[0];
      }
    }
  };
  // Muestra el contenido del árbol (para debug)
  void print() {
    cout << "Control: " << 0 << " | " << (datos[0].izq - datos) << " | "
         << (datos[0].der - datos) << "\n";
    for (int i = 1; i <= n; i++) {
      cout << i << ": " << datos[i].key << " | " << datos[i].data << " | "
           << (datos[i].parent - datos) << " | " << (datos[i].izq - datos)
           << " | " << (datos[i].der - datos) << " | "
           << (datos[i].color ? "Rojo" : "Negro") << "\n";
    }
    cout << "\n";
  }
  // Métodos para recorrer el árbol
  pila<s> inorden();
  pila<s> preorden();
  pila<s> postorden();
  pila<s> niveles(); // por niveles
  pila<int> nivelesKeys(); // claves por niveles
  pila<int> inordenKeys();  // claves en orden
 // Métodos principales del árbol
  bool add(int clave, s info); // agregar nodo
  bool deleteKey(int clave); // eliminar nodo por clave
  // Rotaciones necesarias para mantener balance del árbol
  void leftRotate(RBNode<s> *x);
  void rightRotate(RBNode<s> *y);
  // Ajustes después de inserción o eliminación
  void adjustmentAdd(RBNode<s> *z);
  void adjustmentDelete(RBNode<s> *x);
  // Buscar nodo por clave
  RBNode<s> *getNodeKey(int clave) {
    RBNode<s> *node = datos[0].izq; // raíz del árbol
    while (node != &datos[0] && node->key != clave) {
      node = (clave < node->key) ? node->izq : node->der;
    }
    return node;
  }
// Vaciar todo el árbol (reiniciar)
  void deleteTree() {
    datos[0].izq = &datos[0];

    datos[0].der = &datos[1];

    for (int i = 1; i <= n; i++) {
      datos[i].key = 0;
      datos[i].data = s();
      datos[i].color = false;
      datos[i].parent = &datos[0];
      datos[i].izq = &datos[0];

      if (i < n) {
        datos[i].der = &datos[i + 1];
      } else {
        datos[i].der = &datos[0];
      }
    }
  }
};

template <int n, typename s>
void TreeRB<n, s>::leftRotate(RBNode<s> *x) {
  RBNode<s> *y = x->der; // y toma el lugar de x
  x->der = y->izq; // el hijo izquierdo de y se convierte en el hijo derecho de x
  if (y->izq != &datos[0]) {
    y->izq->parent = x; // actualizamos el padre del hijo izquierdo de y
  }
  y->parent = x->parent; // el padre de y será el padre original de x
  if (x->parent == &datos[0]) {
    datos[0].izq = y;  // y se convierte en la nueva raíz
  } else if (x == x->parent->izq) {
    x->parent->izq = y; // x era hijo izquierdo → y ocupa su lugar
  } else {
    x->parent->der = y; // x era hijo derecho → y ocupa su lugar
  }
  y->izq = x; // x se convierte en hijo izquierdo de y
  x->parent = y;
}

template <int n, typename s>
void TreeRB<n, s>::rightRotate(RBNode<s> *y) {
  RBNode<s> *x = y->izq; // x toma el lugar de y
  y->izq = x->der;
  if (x->der != &datos[0]) {
    x->der->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == &datos[0]) {
    datos[0].izq = x;
  } else if (y == y->parent->der) {
    y->parent->der = x;
  } else {
    y->parent->izq = x;
  }
  x->der = y;
  y->parent = x;
}

template <int n, typename s>
void TreeRB<n, s>::adjustmentAdd(RBNode<s> *z) {
  while (z->parent->color == true) { // Mientras el padre sea rojo
    if (z->parent == z->parent->parent->izq) { // Padre es hijo izquierdo
      RBNode<s> *y = z->parent->parent->der; // Tío es hijo derecho
      if (y->color == true) { // Caso 1: Tío es rojo → recolorear
        z->parent->color = false;
        y->color = false;
        z->parent->parent->color = true;
        z = z->parent->parent; // Subimos
      } else {
        if (z == z->parent->der) { // Caso 2: triángulo
          z = z->parent;
          leftRotate(z);
        }

        // Caso 3: línea recta
        z->parent->color = false;
        z->parent->parent->color = true;
        rightRotate(z->parent->parent);
      }
    } else { // Padre es hijo derecho (simétrico al anterior)
      RBNode<s> *y = z->parent->parent->izq;
      if (y->color == true) {
        z->parent->color = false;
        y->color = false;
        z->parent->parent->color = true;
        z = z->parent->parent;
      } else {
        if (z == z->parent->izq) {
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = false;
        z->parent->parent->color = true;
        leftRotate(z->parent->parent);
      }
    }
  }
  datos[0].izq->color = false; // Asegurar que la raíz siempre sea negra
}

template <int n, typename s>
void TreeRB<n, s>::adjustmentDelete(RBNode<s> *x) {
  while (x != datos[0].izq && x->color == false) { // Mientras x no sea raíz y sea negro
    if (x == x->parent->izq) { // x es hijo izquierdo
      RBNode<s> *w = x->parent->der; // w es el hermano derecho
      if (w->color == true) { // Caso 1: hermano rojo → rotar y recolorear
        w->color = false;
        x->parent->color = true;
        leftRotate(x->parent);
        w = x->parent->der;
      }
      if (w->izq->color == false && w->der->color == false) { // Caso 2: ambos hijos negros
        w->color = true;
        x = x->parent;
      } else {
        if (w->der->color == false) { // Caso 3: w izquierdo rojo, derecho negro
          w->izq->color = false;
          w->color = true;
          rightRotate(w);
          w = x->parent->der;
        }
        // Caso 4: w derecho rojo
        w->color = x->parent->color;
        x->parent->color = false;
        w->der->color = false;
        leftRotate(x->parent);
        x = datos[0].izq; // salir del ciclo
      }
    } else {
      // Simétrico al caso anterior (cuando x es hijo derecho)
      RBNode<s> *w = x->parent->izq;
      if (w->color == true) {
        w->color = false;
        x->parent->color = true;
        rightRotate(x->parent);
        w = x->parent->izq;
      }
      if (w->der->color == false && w->izq->color == false) {
        w->color = true;
        x = x->parent;
      } else {
        if (w->izq->color == false) {
          w->der->color = false;
          w->color = true;
          leftRotate(w);
          w = x->parent->izq;
        }
        w->color = x->parent->color;
        x->parent->color = false;
        w->izq->color = false;
        rightRotate(x->parent);
        x = datos[0].izq;
      }
    }
  }
  x->color = false; // Siempre aseguramos que x sea negro al final
}

template <int n, typename s>
bool TreeRB<n, s>::add(int clave, s info) {
  RBNode<s> *z = datos[0].der; // z apunta al primer nodo disponible del "pool"

  if (z == &datos[0]) {
    return false; // Si no hay espacio, no se puede insertar
  }

  datos[0].der = z->der; // Actualiza el puntero al siguiente nodo libre
// Inicializa el nuevo nodo con la clave y el dato
  z->key = clave;
  z->data = info;
  z->color = true; // Los nodos se insertan como rojos

  RBNode<s> *y = &datos[0]; // y será el padre de z
  RBNode<s> *x = datos[0].izq; // x comienza desde la raíz
// Búsqueda binaria para ubicar dónde insertar el nuevo nodo
  while (x != &datos[0]) {
    y = x;
    if (clave < x->key) {
      x = x->izq;
    } else if (clave > x->key) {
      x = x->der;
    } else {
      // Si ya existe un nodo con la misma clave, se cancela la inserción
      z->key = 0;
      z->data = s();
      z->color = false;
      z->parent = &datos[0];
      z->izq = &datos[0];
      z->der = datos[0].der;
      datos[0].der = z;  // Regresa el nodo a la lista libre
      return false;
    }
  }
// Conecta z con su padre
  z->parent = y;
  if (y == &datos[0]) {
    datos[0].izq = z;  // Si el árbol estaba vacío, z se convierte en la raíz
  } else if (clave < y->key) {
    y->izq = z;
  } else {
    y->der = z;
  }
// Inicializa los hijos de z como nulos (&datos[0])
  z->izq = &datos[0];
  z->der = &datos[0];
// Llama al procedimiento para reajustar el árbol si es necesario
  adjustmentAdd(z);

  return true;
}

template <int n, typename s>
bool TreeRB<n, s>::deleteKey(int clave) {
    // Busca el nodo con la clave que se quiere eliminar
  RBNode<s> *z = getNodeKey(clave);
  if (z == &datos[0]) {
    return false;  // No se encontró el nodo
  } 

  RBNode<s> *y = z; // y es el nodo que se va a eliminar o mover
  RBNode<s> *x; // x es el nodo que lo reemplaza
  bool y_original_color = y->color; // Guarda el color original de y
  // Caso 1: z no tiene hijo izquierdo
  if (z->izq == &datos[0]) {
    x = z->der; 
    if (z->parent == &datos[0]) {
      datos[0].izq = x; // z era la raíz
    } else if (z == z->parent->izq) {
      z->parent->izq = x;
    } else {
      z->parent->der = x;
    }
    x->parent = z->parent;
      // Caso 2: z no tiene hijo derecho
  } else if (z->der == &datos[0]) {
    x = z->izq;
    if (z->parent == &datos[0]) {
      datos[0].izq = x;
    } else if (z == z->parent->izq) {
      z->parent->izq = x;
    } else {
      z->parent->der = x;
    }
    x->parent = z->parent;
  } else {
      // Caso 3: z tiene dos hijos
    RBNode<s> *current = z->der;
        // Busca el sucesor inorden (mínimo del subárbol derecho)
    while (current->izq != &datos[0]) {
      current = current->izq;
    }
    y = current;

    y_original_color = y->color;
    x = y->der;

    if (y->parent == z) {
      x->parent = y;
    } else {
      if (y->parent == &datos[0]) {
        datos[0].izq = x;
      } else if (y == y->parent->izq) {
        y->parent->izq = x;
      } else {
        y->parent->der = x;
      }
      x->parent = y->parent;

      y->der = z->der;
      y->der->parent = y;
    }

    if (z->parent == &datos[0]) {
      datos[0].izq = y;
    } else if (z == z->parent->izq) {
      z->parent->izq = y;
    } else {
      z->parent->der = y;
    }
    y->parent = z->parent;
    y->izq = z->izq;
    y->izq->parent = y;
    y->color = z->color;
  }
  // Si el nodo eliminado era negro, hay que ajustar el árbol
  if (y_original_color == false) {
    adjustmentDelete(x);
  }
  // Libera el nodo z y lo devuelve a la lista de nodos disponibles
  z->key = 0;
  z->data = s();
  z->color = false;
  z->parent = &datos[0];
  z->izq = &datos[0];

  z->der = datos[0].der;
  datos[0].der = z;

  return true;
}
  // Realiza un recorrido inorden del árbol (izquierda - raíz - derecha).
  // Utiliza una pila auxiliar para recorrer el árbol sin recursión.
  // Almacena los datos de cada nodo en una pila de resultados.
  // Esto permite devolver los elementos ordenados según sus claves.

template <int n, typename s>
pila<s> TreeRB<n, s>::inorden() {
  pila<s> colaResultado;
  Stack<RBNode<s> *> stack;

  RBNode<s> *current = datos[0].izq;

  while (current != datos || !stack.isEmpty()) {
    while (current != datos) {
      stack.push(current);
      current = current->izq;
    }
    if (!stack.isEmpty()) {
      current = stack.pop();
      colaResultado.Push(current->data);
      current = current->der;
    }
  }

  return colaResultado;
}
  // Realiza un recorrido en preorden del árbol (raíz - izquierda - derecha).
  // Utiliza una pila auxiliar para simular el recorrido recursivo.
  // Guarda los datos de los nodos en el orden en que se visitan.
  // Este recorrido es útil, por ejemplo, para clonar la estructura del árbol.
template <int n, typename s>
pila<s> TreeRB<n, s>::preorden() {
  pila<s> colaResultado;
  Stack<RBNode<s> *> stack;

  if (datos[0].izq == datos) return colaResultado;

  stack.push(datos[0].izq);

  while (!stack.isEmpty()) {
    RBNode<s> *current = stack.pop();
    colaResultado.Push(current->data);

    if (current->der != datos) {
      stack.push(current->der);
    }
    if (current->izq != datos) {
      stack.push(current->izq);
    }
  }

  return colaResultado;
}
// Realiza un recorrido postorden del árbol (izquierda - derecha - raíz).
  // Utiliza dos pilas auxiliares para recorrer el árbol sin recursión.
  // Primero almacena los nodos en orden inverso, luego los saca para obtener el orden postorden.
  // Este recorrido es útil cuando se desea eliminar o liberar la estructura desde las hojas.
template <int n, typename s>
pila<s> TreeRB<n, s>::postorden() {
  pila<s> colaResultado;
  Stack<RBNode<s> *> stack1;
  Stack<RBNode<s> *> stack2;

  if (datos[0].izq == datos) return colaResultado;

  stack1.push(datos[0].izq);

  while (!stack1.isEmpty()) {
    RBNode<s> *current = stack1.pop();
    stack2.push(current);

    if (current->izq != datos) {
      stack1.push(current->izq);
    }
    if (current->der != datos) {
      stack1.push(current->der);
    }
  }

  while (!stack2.isEmpty()) {
    RBNode<s> *node = stack2.pop();
    colaResultado.Push(node->data);
  }

  return colaResultado;
}
  // Realiza un recorrido por niveles (BFS) del árbol desde la raíz.
  // Utiliza una pila para simular una cola de recorrido y otra pila auxiliar para invertir el orden.
  // Se recorre primero la raíz, luego sus hijos, luego los hijos de sus hijos, y así sucesivamente.
  // Este recorrido es útil para visualizar el árbol por capas o niveles.
template <int n, typename s>
pila<s> TreeRB<n, s>::niveles() {
  pila<s> colaResultado;
  pila<RBNode<s> *> colaNodos;
  Stack<RBNode<s> *> auxStack;  // Pila auxiliar para invertir orden

  if (datos[0].izq == datos) return colaResultado;

  colaNodos.Push(datos[0].izq);

  while (!colaNodos.PilaVacia()) {
    RBNode<s> *current = colaNodos.Pop();
    auxStack.push(current);  // Almacenar en pila auxiliar

    if (current->der != datos) {
      colaNodos.Push(current->der);
    }
    if (current->izq != datos) {
      colaNodos.Push(current->izq);
    }
  }

  // Invertir el orden usando la pila auxiliar
  while (!auxStack.isEmpty()) {
    colaResultado.Push(auxStack.pop()->data);
  }

  return colaResultado;
}
 // Realiza un recorrido por niveles (BFS) del árbol, pero en lugar de almacenar los datos, guarda las claves (keys).
  // Usa una pila para simular la cola de recorrido y una pila auxiliar para invertir el orden al final.
  // Este recorrido permite obtener las claves del árbol nivel por nivel, útil para representar la estructura del árbol.
template <int n, typename s>
pila<int> TreeRB<n, s>::nivelesKeys() {
  pila<int> keyResult;
  pila<RBNode<s> *> nodeQueue;
  Stack<RBNode<s> *> auxStack;

  if (datos[0].izq == datos) return keyResult;

  nodeQueue.Push(datos[0].izq);

  while (!nodeQueue.PilaVacia()) {
    RBNode<s> *current = nodeQueue.Pop();
    auxStack.push(current);

    if (current->der != datos) {
      nodeQueue.Push(current->der);
    }
    if (current->izq != datos) {
      nodeQueue.Push(current->izq);
    }
  }

  while (!auxStack.isEmpty()) {
    keyResult.Push(auxStack.pop()->key);
  }

  return keyResult;
}
 // Realiza un recorrido inorden (LVR) del árbol rojo-negro para obtener únicamente las claves (keys).
  // En este recorrido se visita primero el subárbol izquierdo, luego el nodo actual y finalmente el subárbol derecho.
  // Esto genera una secuencia ordenada de claves si el árbol está correctamente estructurado como árbol binario de búsqueda.
template <int n, typename s>
pila<int> TreeRB<n, s>::inordenKeys() {
  pila<int> resultado;
  Stack<RBNode<s> *> stack;
  RBNode<s> *current = datos[0].izq;

  while (current != datos || !stack.isEmpty()) {
    while (current != datos) {
      stack.push(current);
      current = current->izq;
    }
    if (!stack.isEmpty()) {
      current = stack.pop();
      resultado.Push(current->key);
      current = current->der;
    }
  }
  return resultado;
}

#endif
