#ifndef CONTROLADOR_AUTORES_H
#define CONTROLADOR_AUTORES_H

#include <ctime>
#include <string>

#include "lista.h"
#include "listaOrd.h"
#include "m_datosAutor.h"
#include "treeRB.h"

class ControladorAutores {
 private:
  ListaOrd<datosAutor*, char> listaPorCiudadResidencia;
  ListaOrd<datosAutor*, char> listaPorCiudadNacimiento;
  ListaOrd<datosAutor*, char> listaPorPaisNacimiento;
  ListaOrd<datosAutor*, int> listaPorAñoInicio;
  ListaOrd<datosAutor*, int> listaPorAñoPublicacion;
  ListaOrd<datosAutor*, Formacion> listaPorFormacion;
  ListaOrd<datosAutor*, bool> listaPorSexo;
  TreeRB<1000, datosAutor*> arbolAutor;

 public:
  void agregarAutor(datosAutor* autor);
  void eliminarAutor(unsigned int IDAUTOR);
  void modificarAutor(unsigned int IDAUTOR, bool sexo, int añoInicio,
                      int añoPublicacion, int fechaNacimiento[3],
                      Formacion nuevaFormacion, std::string nombre,
                      std::string Apellido, std::string ciudadResidencia,
                      std::string paisNacimiento,
                      std::string cidudadNacimiento);
  datosAutor const* buscarAutor(unsigned int IDAUTOR);
  void mostrarAutores();
  pila<datosAutor*> getAutores();
  void mostrarAutor(unsigned int IDAUTOR);
  void mostrarAutoresEditorial(Lista<unsigned int>* IDAUTOR);
  void mostrarAutoresPorRangoyFormacion(int rangoEdad[2], Formacion formacion);
  void mostrarAutoresPorCiudadResidencia(Lista<unsigned int>* IDAUTOR) {
    cout << "\n--- LISTA DE AUTORES POR Ciudad de nacimiento ---\n";

    nodoOrd<datosAutor*, char>* auxRes = listaPorCiudadNacimiento.buscarPos(0);

    while (NULL != auxRes) {
      datosAutor* autor = auxRes->dato1;
      auxRes = auxRes->sig;

      if (IDAUTOR->tieneValor(autor->IDAUTOR)) continue;

      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << std::endl;
    }
  }

  void mostrarAutoresPorCiudadNacimiento(
      Lista<unsigned int>* IDAUTOR);  // Corregido nombre
  int calcularEdadActual(int IDAUTOR);
};

#endif  // CONTROLADOR_AUTORES_H
