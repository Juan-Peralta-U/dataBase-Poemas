#ifndef CONTROLADOR_EDITORIALES_H
#define CONTROLADOR_EDITORIALES_H

#include <string>

#include "lista.h"
#include "listaOrd.h"
#include "m_Editorial.h"
#include "treeRB.h"

class ControladorEditoriales {
 private:
  ListaOrd<datosEditorial*, char> listaPorNombreEditorial;
  ListaOrd<datosEditorial*, char> listaPorCiudad;
  ListaOrd<datosEditorial*, char> listaPorPais;
  ListaOrd<datosEditorial*, int> listaPorNumPoetas;
  TreeRB<1000, datosEditorial*> arbolEditorial;
  TreeRB<100, Lista<unsigned int>*> autoresPublicados;

 public:
  void agregarEditorial(datosEditorial* editorial, int numPoetas = 0);
  void eliminarEditorial(unsigned int IDEDITORIAL, int numPoetas = 0);
  void modificarEditorial(unsigned int IDEDITORIAL, std::string nuevoNombre,
                          std::string nuevaCiudad, std::string nuevoPais,
                          int numPoetas = 0);
  datosEditorial const* buscarEditorial(unsigned int IDEDITORIAL);
  void mostrarEditoriales();
  void mostarNumeroDeAutores(int cantidad);
  pila<datosEditorial*> getEditoriales();
  void insertarAutorPublicado(unsigned int IDAUTOR, unsigned int IDEDITORIAL);
  Lista<unsigned int>* autoresPublicadosPorEditorial(unsigned int IDEDITORIAL);
};

#endif  // CONTROLADOR_EDITORIALES_H
