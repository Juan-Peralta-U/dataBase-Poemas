#ifndef STACK_H
#define STACK_H
// Definición de una pila genérica (tipo plantilla)
template <typename T>
class Stack {
  // Estructura interna de nodo para la pila
  struct Node {
    T data; // Dato que almacena el nodo
    Node* next; // Puntero al siguiente nodo
  };

  Node* top; // Puntero al tope de la pila (último nodo agregado)

 public:
// Constructor: inicializa la pila vacía
  Stack() : top(nullptr) {}
 // Método para insertar un elemento en la pila (push)
  void push(T value) {
        // Crea un nuevo nodo con el valor y lo enlaza al tope actual
    Node* newNode = new Node{value, top};
        // Actualiza el tope al nuevo nodo
    top = newNode;
  }
  // Método para extraer el elemento en el tope de la pila (pop)
  T pop() {
    // Si la pila está vacía, devuelve un valor por defecto
    if (isEmpty()) {
      return T();
    }
    // Guarda temporalmente el nodo del tope
    Node* temp = top;
    // Guarda el valor del tope
    T value = temp->data;
    // Avanza el tope al siguiente nodo
    top = top->next;
    // Libera la memoria del nodo anterior
    delete temp;
     // Devuelve el valor extraído
    return value;
  }
  // Verifica si la pila está vacía
  bool isEmpty() { return top == nullptr; }
  // Destructor: libera toda la memoria de la pila
  ~Stack() {
    while (!isEmpty()) {
      pop(); // Elimina uno a uno los nodos
    }
  }
};

#endif
