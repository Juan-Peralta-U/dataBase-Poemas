#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

#include "pila.h"
#include "stack.h"

template <typename s>
struct RBNode {
  int key;
  s data;
  bool color;
  RBNode<s> *parent;
  RBNode<s> *izq;
  RBNode<s> *der;
};

template <int n, typename s>
class TreeRB {
  RBNode<s> datos[n + 1];

 public:
  TreeRB() {
    datos[0].key = 0;
    datos[0].data = s();
    datos[0].color = false;
    datos[0].parent = &datos[0];
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
  };

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

  pila<s> inorden();
  pila<s> preorden();
  pila<s> postorden();
  pila<s> niveles();
  pila<int> nivelesKeys();
  pila<int> inordenKeys();  // <-- Nueva función miembro

  bool add(int clave, s info);
  bool deleteKey(int clave);
  void leftRotate(RBNode<s> *x);
  void rightRotate(RBNode<s> *y);
  void adjustmentAdd(RBNode<s> *z);
  void adjustmentDelete(RBNode<s> *x);
  RBNode<s> *getNodeKey(int clave) {
    RBNode<s> *node = datos[0].izq;
    while (node != &datos[0] && node->key != clave) {
      node = (clave < node->key) ? node->izq : node->der;
    }
    return node;
  }

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
  RBNode<s> *y = x->der;
  x->der = y->izq;
  if (y->izq != &datos[0]) {
    y->izq->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == &datos[0]) {
    datos[0].izq = y;
  } else if (x == x->parent->izq) {
    x->parent->izq = y;
  } else {
    x->parent->der = y;
  }
  y->izq = x;
  x->parent = y;
}

template <int n, typename s>
void TreeRB<n, s>::rightRotate(RBNode<s> *y) {
  RBNode<s> *x = y->izq;
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
  while (z->parent->color == true) {
    if (z->parent == z->parent->parent->izq) {
      RBNode<s> *y = z->parent->parent->der;
      if (y->color == true) {
        z->parent->color = false;
        y->color = false;
        z->parent->parent->color = true;
        z = z->parent->parent;
      } else {
        if (z == z->parent->der) {
          z = z->parent;
          leftRotate(z);
        }
        z->parent->color = false;
        z->parent->parent->color = true;
        rightRotate(z->parent->parent);
      }
    } else {
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
  datos[0].izq->color = false;
}

template <int n, typename s>
void TreeRB<n, s>::adjustmentDelete(RBNode<s> *x) {
  while (x != datos[0].izq && x->color == false) {
    if (x == x->parent->izq) {
      RBNode<s> *w = x->parent->der;
      if (w->color == true) {
        w->color = false;
        x->parent->color = true;
        leftRotate(x->parent);
        w = x->parent->der;
      }
      if (w->izq->color == false && w->der->color == false) {
        w->color = true;
        x = x->parent;
      } else {
        if (w->der->color == false) {
          w->izq->color = false;
          w->color = true;
          rightRotate(w);
          w = x->parent->der;
        }
        w->color = x->parent->color;
        x->parent->color = false;
        w->der->color = false;
        leftRotate(x->parent);
        x = datos[0].izq;
      }
    } else {
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
  x->color = false;
}

template <int n, typename s>
bool TreeRB<n, s>::add(int clave, s info) {
  RBNode<s> *z = datos[0].der;

  if (z == &datos[0]) {
    return false;
  }

  datos[0].der = z->der;

  z->key = clave;
  z->data = info;
  z->color = true;

  RBNode<s> *y = &datos[0];
  RBNode<s> *x = datos[0].izq;

  while (x != &datos[0]) {
    y = x;
    if (clave < x->key) {
      x = x->izq;
    } else if (clave > x->key) {
      x = x->der;
    } else {
      z->key = 0;
      z->data = s();
      z->color = false;
      z->parent = &datos[0];
      z->izq = &datos[0];
      z->der = datos[0].der;
      datos[0].der = z;
      return false;
    }
  }

  z->parent = y;
  if (y == &datos[0]) {
    datos[0].izq = z;
  } else if (clave < y->key) {
    y->izq = z;
  } else {
    y->der = z;
  }

  z->izq = &datos[0];
  z->der = &datos[0];

  adjustmentAdd(z);

  return true;
}

template <int n, typename s>
bool TreeRB<n, s>::deleteKey(int clave) {
  RBNode<s> *z = getNodeKey(clave);
  if (z == &datos[0]) {
    return false;
  }

  RBNode<s> *y = z;
  RBNode<s> *x;
  bool y_original_color = y->color;

  if (z->izq == &datos[0]) {
    x = z->der;
    if (z->parent == &datos[0]) {
      datos[0].izq = x;
    } else if (z == z->parent->izq) {
      z->parent->izq = x;
    } else {
      z->parent->der = x;
    }
    x->parent = z->parent;
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
    RBNode<s> *current = z->der;
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

  if (y_original_color == false) {
    adjustmentDelete(x);
  }

  z->key = 0;
  z->data = s();
  z->color = false;
  z->parent = &datos[0];
  z->izq = &datos[0];

  z->der = datos[0].der;
  datos[0].der = z;

  return true;
}

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
