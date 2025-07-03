#include "listaOrd.h"
#include "m_datosAutor.h"

class ControladorAutores {
 private:
  ListaOrd<datosAutor *, char> listaPorCiudadResidencia;
  ListaOrd<datosAutor *, char> listaPorCiudadNacimiento;
  ListaOrd<datosAutor *, char> listaPorPaisNacimiento;
  ListaOrd<datosAutor *, int> listaPorAñoInicio;
  ListaOrd<datosAutor *, int> listaPorAñoPublicacion;

 public:
  void agregarAutor(datosAutor *autor) {
    listaPorCiudadResidencia.insertarClave(autor, autor->ciudadResidencia[0]);
    listaPorCiudadNacimiento.insertarClave(autor, autor->cidudadNacimiento[0]);
    listaPorPaisNacimiento.insertarClave(autor, autor->paisNacimiento[0]);
    listaPorAñoInicio.insertarClave(autor, autor->añoIncio);
    listaPorAñoPublicacion.insertarClave(autor, autor->añoPublicacion);
  }
};
