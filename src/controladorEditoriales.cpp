#include "lista.h"
#include "m_Editorial.h"

class ControladorEditoriales {
 private:
  Lista<datosEditorial> listaPorNombreEditorial;
  Lista<datosEditorial> listaPorNumPublicaciones;

 public:
  void agregarEditorial(const datosEditorial& editorial) {
    listaPorNombreEditorial.insertarFinal(editorial);
    listaPorNumPublicaciones.insertarFinal(
        editorial);  // ordenar por publicaciones con el size
  }

  void listarEditorialesPorNombre() { listaPorNombreEditorial.imprimirLista(); }
};
