#ifndef PILA_H
#define PILA_H

template <typename T>
class pila {
  struct Nodo {
    T dato;
    Nodo* sig;
  };

  Nodo* frente;
  Nodo* final;

 public:
  pila() : frente(nullptr), final(nullptr) {}

  void Push(T v) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = v;
    nuevo->sig = nullptr;

    if (final == nullptr) {
      frente = nuevo;
      final = nuevo;
    } else {
      final->sig = nuevo;
      final = nuevo;
    }
  }

  T Pop() {
    if (frente == nullptr) {
      return T();
    }

    Nodo* temp = frente;
    T dato = frente->dato;
    frente = frente->sig;
    if (frente == nullptr) {
      final = nullptr;
    }
    delete temp;
    return dato;
  }

  bool PilaVacia() { return frente == nullptr; }

  ~pila() {
    while (frente != nullptr) {
      Nodo* temp = frente;
      frente = frente->sig;
      delete temp;
    }
    final = nullptr;
  }
};

#endif
