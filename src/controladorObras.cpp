#include "listaOrd.h"
#include "m_obrapoetica.h"
#include "treeRB.h"

class ControladorObras {
 private:
  ListaOrd<ObraPoetica*, int> listaAnoPublicacion;
  TreeRB<100, ObraPoetica*> arbolPorIDAutor;  // Clave = IDAUTOR

 public:
  void agregarObra(ObraPoetica* obra) {
    arbolPorIDAutor.add(obra->IDAUTOR, obra);
  }
};
