#include <string>

#include "listaOrd.h"
#include "m_datosAutor.h"
#include "treeRB.h"

class ControladorAutores {
 private:
  ListaOrd<datosAutor *, char> listaPorCiudadResidencia;
  ListaOrd<datosAutor *, char> listaPorCiudadNacimiento;
  ListaOrd<datosAutor *, char> listaPorPaisNacimiento;
  ListaOrd<datosAutor *, int> listaPorAñoInicio;
  ListaOrd<datosAutor *, int> listaPorAñoPublicacion;
  TreeRB<100, datosAutor *> arbolAutor;  // Clave = IDAUTOR

 public:
  void agregarAutor(datosAutor *autor) {
    listaPorCiudadResidencia.insertarClave(autor, autor->ciudadResidencia[0]);
    listaPorCiudadNacimiento.insertarClave(autor, autor->cidudadNacimiento[0]);
    listaPorPaisNacimiento.insertarClave(autor, autor->paisNacimiento[0]);
    listaPorAñoInicio.insertarClave(autor, autor->añoIncio);
    listaPorAñoPublicacion.insertarClave(autor, autor->añoPublicacion);
    arbolAutor.add(autor->IDAUTOR, autor);
  }

  void eliminarAutor(int ID_Autor) {
    datosAutor *del = arbolAutor.getNodeKey(ID_Autor)->data;
    listaPorCiudadResidencia.borrarClave(del->ciudadResidencia[0], del);
    listaPorCiudadNacimiento.borrarClave(del->cidudadNacimiento[0], del);
    listaPorPaisNacimiento.borrarClave(del->paisNacimiento[0], del);
    listaPorAñoInicio.borrarClave(del->añoIncio, del);
    listaPorAñoPublicacion.borrarClave(del->añoPublicacion, del);
    arbolAutor.deleteKey(del->IDAUTOR);
  }

  void modificarAutor(int ID_Autor, bool sexo, int añoInicio,
                      int añoPublicacion, int fechaNacimiento[3],
                      formacion formacion, std::string nombre,
                      std::string Apellido, std::string ciudadResidencia,
                      std::string paisNacimiento,
                      std::string cidudadNacimiento) {
    datosAutor *aux = arbolAutor.getNodeKey(ID_Autor)->data;

    aux->sexo = sexo;
    aux->nombre = nombre;
    aux->Apellido = Apellido;
    aux->añoIncio = añoInicio;
    aux->añoPublicacion = añoPublicacion;
    for (int i = 3; i--; aux->fechaNacimiento[i] = fechaNacimiento[i]);
    aux->formacion = formacion;
    aux->paisNacimiento = paisNacimiento;
    aux->cidudadNacimiento = cidudadNacimiento;
  }

  datosAutor const *buscarAutor(int ID_Autor) {
    return arbolAutor.getNodeKey(ID_Autor)->data;
  }
};
