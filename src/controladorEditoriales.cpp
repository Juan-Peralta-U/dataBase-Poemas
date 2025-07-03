#include "listaOrd.h"
#include "m_Editorial.h"

class ControladorEditoriales {
 private:
  ListaOrd<datosEditorial*, char> listaPorNombreEditorial;
  ListaOrd<datosEditorial*, int> listaPorNumPublicaciones;

 public:
  void agregarEditorial(datosEditorial* editorial) {
    listaPorNombreEditorial.insertarClave(editorial,
                                          editorial->nombreEditorial[0]);
    // listaPorNumPublicaciones.insertarClave(
    // editorial, );  // ordenar por publicaciones con el size
  }
};
