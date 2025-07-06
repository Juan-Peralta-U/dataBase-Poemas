#ifndef CONTROLADOR_OBRAS_H
#define CONTROLADOR_OBRAS_H

#include <string>

#include "listaOrd.h"
#include "m_edicion.h"
#include "m_obrapoetica.h"
#include "pila.h"
#include "treeRB.h"

class ControladorObras {
 private:
  ListaOrd<ObraPoetica*, int> listaPorAnioPublicacion;
  ListaOrd<ObraPoetica*, tipoObra> listaPorTipoPoesia;
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDAutor;
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDEditorial;
  TreeRB<1000, ObraPoetica*> arbolObra;

 public:
  void agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR, tipoObra obraTipo,
                   const std::string& nombre);
  void eliminarObra(unsigned int IDOBRA);
  void modificarObra(unsigned int IDOBRA, unsigned int nuevoIDAUTOR,
                     tipoObra nuevoTipo, const std::string& nuevoNombre);
  ObraPoetica const* buscarObra(unsigned int IDOBRA);
  void agregarEdicionAObra(unsigned int IDOBRA, const datosEdiccion& edicion);
  void eliminarEdicionDeObra(unsigned int IDOBRA, unsigned int numEdicion);
  void mostrarObras();
  void mostrarTodasEdiciones();
  void mostrarObrasPorAutor(unsigned int IDAUTOR);
  void mostrarTiposObraPorAutor(unsigned int IDAUTOR);
  pila<ObraPoetica*> getObras();
  pila<datosEdiccion> getEdiciones();
  pila<int> getClavesObras();
  void mostrarTiposObraPorAutorYTipo(unsigned int IDAUTOR, tipoObra tipo);
  unsigned int mostarIDAUTOR(unsigned int IDOBRA);
};

#endif  // CONTROLADOR_OBRAS_H
