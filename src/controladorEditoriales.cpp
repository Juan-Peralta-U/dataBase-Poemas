#pragma once
#include "listaOrd.h"
#include "m_Editorial.h"
#include "treeRB.h"
#include <string>

class ControladorEditoriales {
 private:
  // Listas auxiliares para consultas eficientes
  ListaOrd<datosEditorial*, char> listaPorNombreEditorial;   // Para búsquedas por nombre
  ListaOrd<datosEditorial*, char> listaPorCiudad;            // Para búsquedas por ciudad
  ListaOrd<datosEditorial*, char> listaPorPais;              // Para búsquedas por país
  ListaOrd<datosEditorial*, int> listaPorNumPoetas;          // Para consultas por cantidad de poetas publicados
  TreeRB<1000, datosEditorial*> arbolEditorial;               // Clave = IDEDITORIAL

 public:
  // Agregar una editorial
  void agregarEditorial(datosEditorial* editorial, int numPoetas = 0) {
    listaPorNombreEditorial.insertarClave(editorial, editorial->nombreEditorial[0]);
    listaPorCiudad.insertarClave(editorial, editorial->ciudadOficina[0]);
    listaPorPais.insertarClave(editorial, editorial->paisOficina[0]);
    listaPorNumPoetas.insertarClave(editorial, numPoetas);
    arbolEditorial.add(editorial->IDEDITORIAL, editorial);
  }

  // Eliminar una editorial y actualizar todas las listas
  void eliminarEditorial(unsigned int IDEDITORIAL, int numPoetas = 0) {
    datosEditorial* del = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
    listaPorNombreEditorial.borrarClave(del->nombreEditorial[0], del);
    listaPorCiudad.borrarClave(del->ciudadOficina[0], del);
    listaPorPais.borrarClave(del->paisOficina[0], del);
    listaPorNumPoetas.borrarClave(numPoetas, del);
    arbolEditorial.deleteKey(IDEDITORIAL);
    // delete del; // Solo si manejas memoria dinámica
  }

  // Modificar datos de una editorial
  void modificarEditorial(unsigned int IDEDITORIAL, std::string nuevoNombre,
                          std::string nuevaCiudad, std::string nuevoPais, int numPoetas = 0) {
    datosEditorial* aux = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
    // Actualiza listas si cambian claves
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
    // Actualiza número de poetas publicados si es necesario
    listaPorNumPoetas.borrarClave(numPoetas, aux);
    listaPorNumPoetas.insertarClave(aux, numPoetas);
  }

  // Buscar una editorial por ID
  datosEditorial const* buscarEditorial(unsigned int IDEDITORIAL) {
    return arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  }

  // Mostrar todas las editoriales guardadas
  void mostrarEditoriales() {
    std::cout << "\n--- LISTA DE EDITORIALES ---\n";
    pila<datosEditorial*> editoriales = arbolEditorial.inorden();
    while (!editoriales.PilaVacia()) {
        datosEditorial* ed = editoriales.Pop();
        std::cout << "ID: " << ed->IDEDITORIAL
                  << " | Nombre: " << ed->nombreEditorial
                  << " | Ciudad: " << ed->ciudadOficina
                  << " | Pais: " << ed->paisOficina
                  << std::endl;
    }
  }

  pila<datosEditorial*> getEditoriales(){
    return arbolEditorial.inorden();
  }
};
