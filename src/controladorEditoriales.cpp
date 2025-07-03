#include "listaOrd.h"
#include "m_Editorial.h"
#include "treeRB.h"
#include <string>

class ControladorEditoriales {
 private:
  ListaOrd<datosEditorial*, char> listaPorNombreEditorial;
  ListaOrd<datosEditorial*, char> listaPorCiudad;
  ListaOrd<datosEditorial*, char> listaPorPais;
  ListaOrd<datosEditorial*, int> listaPorNumPublicaciones;
  TreeRB<100, datosEditorial*> arbolEditorial;              // Clave = IDEDITORIAL

 public:
  void agregarEditorial(datosEditorial* editorial, int numPublicaciones = 0) {
    listaPorNombreEditorial.insertarClave(editorial, editorial->nombreEditorial[0]);
    listaPorCiudad.insertarClave(editorial, editorial->ciudadOficina[0]);
    listaPorPais.insertarClave(editorial, editorial->paisOficina[0]);
    listaPorNumPublicaciones.insertarClave(editorial, numPublicaciones);
    arbolEditorial.add(editorial->IDEDITORIAL, editorial);
  }

  void eliminarEditorial(unsigned int IDEDITORIAL, int numPublicaciones = 0) {
    datosEditorial* del = arbolEditorial.getNodeKey(IDEDITORIAL)->data;
    listaPorNombreEditorial.borrarClave(del->nombreEditorial[0], del);
    listaPorCiudad.borrarClave(del->ciudadOficina[0], del);
    listaPorPais.borrarClave(del->paisOficina[0], del);
    listaPorNumPublicaciones.borrarClave(numPublicaciones, del);
    arbolEditorial.deleteKey(IDEDITORIAL);
  }

  void modificarEditorial(unsigned int IDEDITORIAL, std::string nuevoNombre,
                          std::string nuevaCiudad, std::string nuevoPais, int numPublicaciones = 0) {
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
    // Actualiza número de publicaciones si es necesario
    listaPorNumPublicaciones.borrarClave(numPublicaciones, aux);
    listaPorNumPublicaciones.insertarClave(aux, numPublicaciones);
  }

  datosEditorial const* buscarEditorial(unsigned int IDEDITORIAL) {
    return arbolEditorial.getNodeKey(IDEDITORIAL)->data;
  }
};
