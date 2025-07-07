#include "controladorEditoriales.h"

#include <iostream>

#include "lista.h"
#include "treeRB.h"

void ControladorEditoriales::agregarEditorial(datosEditorial* editorial,
                                              int numPoetas) {
  listaPorNombreEditorial.insertarClave(editorial,
                                        editorial->nombreEditorial[0]);
  listaPorCiudad.insertarClave(editorial, editorial->ciudadOficina[0]);
  listaPorPais.insertarClave(editorial, editorial->paisOficina[0]);
  listaPorNumPoetas.insertarClave(editorial, numPoetas);
  arbolEditorial.add(editorial->IDEDITORIAL, editorial);
}

void ControladorEditoriales::eliminarEditorial(unsigned int IDEDITORIAL,
                                               int numPoetas) {
  datosEditorial* del = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  if (!del) return;

  listaPorNombreEditorial.borrarClave(del->nombreEditorial[0], del);
  listaPorCiudad.borrarClave(del->ciudadOficina[0], del);
  listaPorPais.borrarClave(del->paisOficina[0], del);
  listaPorNumPoetas.borrarClave(numPoetas, del);
  arbolEditorial.deleteKey(IDEDITORIAL);

  // Eliminar lista de autores publicados si existe
  auto autoresNode = autoresPublicados.getNodeKey(IDEDITORIAL);
  if (autoresNode) {
    delete autoresNode->data;
    autoresPublicados.deleteKey(IDEDITORIAL);
  }
}

void ControladorEditoriales::modificarEditorial(unsigned int IDEDITORIAL,
                                                std::string nuevoNombre,
                                                std::string nuevaCiudad,
                                                std::string nuevoPais,
                                                int numPoetas) {
  datosEditorial* aux = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  if (!aux) return;

  int oldNumPoetas = numPoetas;  // Asumiendo que recibimos el valor antiguo

  if (aux->nombreEditorial != nuevoNombre) {
    listaPorNombreEditorial.borrarClave(aux->nombreEditorial[0], aux);
    aux->nombreEditorial = nuevoNombre;
    listaPorNombreEditorial.insertarClave(aux, aux->nombreEditorial[0]);
  }
  if (aux->ciudadOficina != nuevaCiudad) {
    listaPorCiudad.borrarClave(aux->ciudadOficina[0], aux);
    aux->ciudadOficina = nuevaCiudad;
    listaPorCiudad.insertarClave(aux, aux->ciudadOficina[0]);
  }
  if (aux->paisOficina != nuevoPais) {
    listaPorPais.borrarClave(aux->paisOficina[0], aux);
    aux->paisOficina = nuevoPais;
    listaPorPais.insertarClave(aux, aux->paisOficina[0]);
  }

  // Actualizar número de poetas
  listaPorNumPoetas.borrarClave(oldNumPoetas, aux);
  listaPorNumPoetas.insertarClave(aux, numPoetas);
}

datosEditorial const* ControladorEditoriales::buscarEditorial(
    unsigned int IDEDITORIAL) {
  auto node = arbolEditorial.getNodeKey(IDEDITORIAL);
  return node ? node->data : nullptr;
}

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

void ControladorEditoriales::mostarNumeroDeAutores(int cantidad) {
  cout << "\n--- EDITORIALES CON AL MENOS " << cantidad
       << " AUTORES PUBLICADOS ---\n";
  pila<datosEditorial*> editoriales = arbolEditorial.inorden();
  while (!editoriales.PilaVacia()) {
    datosEditorial* ed = editoriales.Pop();
    auto autoresNode = autoresPublicados.getNodeKey(ed->IDEDITORIAL)->data;
    if (autoresNode == nullptr) continue;

    int tamaño = autoresNode->getTam();
    if (tamaño < cantidad) continue;

    cout << "ID: " << ed->IDEDITORIAL << " | Nombre: " << ed->nombreEditorial
         << " | Cantidad de autores: " << tamaño
         << " | Ciudad: " << ed->ciudadOficina << " | Pais: " << ed->paisOficina
         << " | DIRECCION HX: " << autoresNode << endl;
  }
}

pila<datosEditorial*> ControladorEditoriales::getEditoriales() {
  return arbolEditorial.inorden();
}

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

  autoresNode->data->insertarInicio(IDAUTOR);
  // cerr << "--------------------------------------------------\n";
  // cerr << IDEDITORIAL << '\n';
  // cerr << autoresNode->data->getTam() << '\n';
}

Lista<unsigned int>* ControladorEditoriales::autoresPublicadosPorEditorial(
    unsigned int IDEDITORIAL) {
  if (autoresPublicados.getNodeKey(IDEDITORIAL) == nullptr) return nullptr;

  return autoresPublicados.getNodeKey(IDEDITORIAL)->data;
}
