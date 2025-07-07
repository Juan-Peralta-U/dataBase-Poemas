// Se incluye el encabezado de la clase ControladorEditoriales
#include "controladorEditoriales.h"

#include <iostream>

#include "lista.h"
#include "treeRB.h"
// Agrega una nueva editorial y la indexa en todas las estructuras
void ControladorEditoriales::agregarEditorial(datosEditorial* editorial,
                                              int numPoetas) {
    // Insertamos la editorial en las listas ordenadas por su nombre, ciudad y país
  listaPorNombreEditorial.insertarClave(editorial,
                                        editorial->nombreEditorial[0]);
  listaPorCiudad.insertarClave(editorial, editorial->ciudadOficina[0]);
  listaPorPais.insertarClave(editorial, editorial->paisOficina[0]);
  listaPorNumPoetas.insertarClave(editorial, numPoetas);
    // Insertamos en el árbol principal por ID
  arbolEditorial.add(editorial->IDEDITORIAL, editorial);
}
// Elimina una editorial del sistema, junto con sus índices y lista de autores publicados
void ControladorEditoriales::eliminarEditorial(unsigned int IDEDITORIAL,
                                               int numPoetas) {
  datosEditorial* del = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  if (!del) return;
  // Eliminamos de todas las listas ordenadas
  listaPorNombreEditorial.borrarClave(del->nombreEditorial[0], del);
  listaPorCiudad.borrarClave(del->ciudadOficina[0], del);
  listaPorPais.borrarClave(del->paisOficina[0], del);
  listaPorNumPoetas.borrarClave(numPoetas, del);
    // Eliminamos del árbol
  arbolEditorial.deleteKey(IDEDITORIAL);
  // Si la editorial tiene una lista de autores publicados, también la eliminamos
  // Eliminar lista de autores publicados si existe
  auto autoresNode = autoresPublicados.getNodeKey(IDEDITORIAL);
  if (autoresNode) {
    delete autoresNode->data;
    autoresPublicados.deleteKey(IDEDITORIAL);
  }
}
// Modifica los datos de una editorial y actualiza su ubicación en las listas ordenadas
void ControladorEditoriales::modificarEditorial(unsigned int IDEDITORIAL,
                                                std::string nuevoNombre,
                                                std::string nuevaCiudad,
                                                std::string nuevoPais,
                                                int numPoetas) {
  datosEditorial* aux = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  if (!aux) return;

  int oldNumPoetas = numPoetas;  // Asumiendo que recibimos el valor antiguo
  // Si cambia el nombre, se actualiza en la lista correspondiente
  if (aux->nombreEditorial != nuevoNombre) {
    listaPorNombreEditorial.borrarClave(aux->nombreEditorial[0], aux);
    aux->nombreEditorial = nuevoNombre;
    listaPorNombreEditorial.insertarClave(aux, aux->nombreEditorial[0]);
  }
    // Si cambia la ciudad
  if (aux->ciudadOficina != nuevaCiudad) {
    listaPorCiudad.borrarClave(aux->ciudadOficina[0], aux);
    aux->ciudadOficina = nuevaCiudad;
    listaPorCiudad.insertarClave(aux, aux->ciudadOficina[0]);
  }
    // Si cambia el país
  if (aux->paisOficina != nuevoPais) {
    listaPorPais.borrarClave(aux->paisOficina[0], aux);
    aux->paisOficina = nuevoPais;
    listaPorPais.insertarClave(aux, aux->paisOficina[0]);
  }

  // Actualizar número de poetas
  listaPorNumPoetas.borrarClave(oldNumPoetas, aux);
  listaPorNumPoetas.insertarClave(aux, numPoetas);
}
// Busca una editorial por su ID y retorna un puntero constante a su información
datosEditorial const* ControladorEditoriales::buscarEditorial(
    unsigned int IDEDITORIAL) {
  auto node = arbolEditorial.getNodeKey(IDEDITORIAL);
  return node ? node->data : nullptr;
}
// Muestra por consola todas las editoriales almacenadas
void ControladorEditoriales::mostrarEditoriales() {
  cout << "\n--- LISTA DE EDITORIALES ---\n";
  pila<datosEditorial*> editoriales = arbolEditorial.inorden();
  while (!editoriales.PilaVacia()) {
    datosEditorial* ed = editoriales.Pop();
    cout << "ID: " << ed->IDEDITORIAL << " | Nombre: " << ed->nombreEditorial
         << " | Ciudad: " << ed->ciudadOficina << " | Pais: " << ed->paisOficina
         << endl;
  }
}
// Muestra editoriales que han publicado al menos cierta cantidad de autores
void ControladorEditoriales::mostarNumeroDeAutores(int cantidad) {
  cout << "\n--- EDITORIALES CON AL MENOS " << cantidad
       << " AUTORES PUBLICADOS ---\n";
  pila<datosEditorial*> editoriales = arbolEditorial.inorden();
  while (!editoriales.PilaVacia()) {
    datosEditorial* ed = editoriales.Pop();
    auto autoresNode = autoresPublicados.getNodeKey(ed->IDEDITORIAL)->data;
    if (autoresNode == nullptr) continue;

    int tamaño = autoresNode->getTam();// Número de autores publicados
    if (tamaño < cantidad) continue;

    cout << "ID: " << ed->IDEDITORIAL << " | Nombre: " << ed->nombreEditorial
         << " | Cantidad de autores: " << tamaño
         << " | Ciudad: " << ed->ciudadOficina << " | Pais: " << ed->paisOficina
         << " | DIRECCION HX: " << autoresNode << endl;
  }
}
// Devuelve una pila con todas las editoriales
pila<datosEditorial*> ControladorEditoriales::getEditoriales() {
  return arbolEditorial.inorden();
}
// Inserta un autor en la lista de autores publicados por una editorial específica
void ControladorEditoriales::insertarAutorPublicado(unsigned int IDAUTOR,
                                                    unsigned int IDEDITORIAL) {
  // Buscar el nodo de la editorial
  RBNode<Lista<unsigned int>*>* autoresNode =
      autoresPublicados.getNodeKey(IDEDITORIAL);
  // Si el nodo existe pero su data es nullptr, inicializar la lista
  if (autoresNode->data == nullptr) {
    Lista<unsigned int>* nuevaLista = new Lista<unsigned int>();
    autoresPublicados.add(IDEDITORIAL, nuevaLista);
    nuevaLista->insertarInicio(
        IDAUTOR);  // Insertar directamente en la nueva lista
    return;        // Salir después de insertar
  }

  // Insertar el autor en la lista existente
  if (autoresNode->data->tieneValor(IDAUTOR)) return;
  // Agregamos el autor a la lista
  autoresNode->data->insertarInicio(IDAUTOR);
  // cerr << "--------------------------------------------------\n";
  // cerr << IDEDITORIAL << '\n';
  // cerr << autoresNode->data->getTam() << '\n';
}
// Retorna la lista de autores publicados por una editorial específica
Lista<unsigned int>* ControladorEditoriales::autoresPublicadosPorEditorial(
    unsigned int IDEDITORIAL) {
  if (autoresPublicados.getNodeKey(IDEDITORIAL) == nullptr) return nullptr;

  return autoresPublicados.getNodeKey(IDEDITORIAL)->data;
}
