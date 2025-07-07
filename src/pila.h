#ifndef PILA_H
#define PILA_H
// Clase genérica de tipo pila (aunque se comporta más como una cola FIFO)
template <typename T>
class pila {
  // Estructura interna Nodo para almacenar los elementos
  struct Nodo {
    T dato; // Dato almacenado en el nodo
    Nodo* sig; // Puntero al siguiente nodo
  };

  Nodo* frente; // Puntero al primer elemento (inicio de la pila)
  Nodo* final; // Puntero al último elemento (final de la pila)

 public:
  // Constructor: inicializa la pila como vacía
  pila() : frente(nullptr), final(nullptr) {}
  // Método para insertar un elemento al final de la pila
  void Push(T v) {
    Nodo* nuevo = new Nodo; // Se crea un nuevo nodo
    nuevo->dato = v;  // Se asigna el dato
    nuevo->sig = nullptr; // El nuevo nodo apunta a null (será el último)

    if (final == nullptr) { // Si la pila está vacía
      frente = nuevo;  // El nuevo nodo es el frente
      final = nuevo; // Y también es el final
    } else {
      final->sig = nuevo;  // El nodo actual al final apunta al nuevo
      final = nuevo; // El nuevo nodo se convierte en el final
    }
  }
  // Método para eliminar y devolver el primer elemento de la pila
  T Pop() {
    if (frente == nullptr) { // Si la pila está vacía
      return T(); // Retorna un objeto vacío por defecto
    }

    Nodo* temp = frente; // Nodo temporal para borrar
    T dato = frente->dato; // Se guarda el dato que se va a devolver
    frente = frente->sig;// El frente avanza al siguiente nodo
    if (frente == nullptr) { // Si después de avanzar queda vacía
      final = nullptr;// El final también se vuelve nulo
    }
    delete temp; // Se libera el nodo anterior
    return dato; // Se retorna el dato eliminado
  }
  // Método para verificar si la pila está vacía
  bool PilaVacia() { return frente == nullptr; }
  // Destructor: libera la memoria de todos los nodos de la pila
  ~pila() {
    while (frente != nullptr) { // Mientras haya elementos
      Nodo* temp = frente; // Se guarda el nodo actual
      frente = frente->sig;// Se avanza al siguiente
      delete temp; // Se libera el nodo anterior
    }
    final = nullptr; // Se asegura que el puntero final esté limpio
  }
};

#endif
