#include <string>

#include "lista.h"
#include "listaOrd.h"
#include "m_datosAutor.h"
#include "treeRB.h"

class ControladorAutores {
 private:
  // Listas auxiliares para consultas eficientes
  ListaOrd<datosAutor*, char>
      listaPorCiudadResidencia;  // Para consultas por ciudad de residencia
  ListaOrd<datosAutor*, char>
      listaPorCiudadNacimiento;  // Para consultas por ciudad de nacimiento
  ListaOrd<datosAutor*, char>
      listaPorPaisNacimiento;  // Para consultas por país de nacimiento
  ListaOrd<datosAutor*, int>
      listaPorAñoInicio;  // Para consultas por año de inicio en la literatura
  ListaOrd<datosAutor*, int>
      listaPorAñoPublicacion;  // Para consultas por año de publicación de la
                               // primera obra
  ListaOrd<datosAutor*, Formacion>
      listaPorFormacion;                     // Para consultas por formación
  ListaOrd<datosAutor*, bool> listaPorSexo;  // Para consultas por género
  // Puedes agregar más listas si necesitas consultas por edad, etc.
  TreeRB<100, datosAutor*> arbolAutor;  // Clave = IDAUTOR

 public:
  // Agregar un autor
  void agregarAutor(datosAutor* autor) {
    listaPorCiudadResidencia.insertarClave(autor, autor->ciudadResidencia[0]);
    listaPorCiudadNacimiento.insertarClave(autor, autor->cidudadNacimiento[0]);
    listaPorPaisNacimiento.insertarClave(autor, autor->paisNacimiento[0]);
    listaPorAñoInicio.insertarClave(autor, autor->añoIncio);
    listaPorAñoPublicacion.insertarClave(autor, autor->añoPublicacion);
    listaPorFormacion.insertarClave(autor, autor->formacion);
    listaPorSexo.insertarClave(autor, autor->sexo);
    arbolAutor.add(autor->IDAUTOR, autor);
  }

  // Eliminar un autor y actualizar todas las listas
  void eliminarAutor(unsigned int IDAUTOR) {
    datosAutor* del = arbolAutor.getNodeKey(IDAUTOR)->data;
    listaPorCiudadResidencia.borrarClave(del->ciudadResidencia[0], del);
    listaPorCiudadNacimiento.borrarClave(del->cidudadNacimiento[0], del);
    listaPorPaisNacimiento.borrarClave(del->paisNacimiento[0], del);
    listaPorAñoInicio.borrarClave(del->añoIncio, del);
    listaPorAñoPublicacion.borrarClave(del->añoPublicacion, del);
    listaPorFormacion.borrarClave(del->formacion, del);
    listaPorSexo.borrarClave(del->sexo, del);
    arbolAutor.deleteKey(del->IDAUTOR);
    delete del;
  }

  // Modificar datos de un autor
  void modificarAutor(unsigned int IDAUTOR, bool sexo, int añoInicio,
                      int añoPublicacion, int fechaNacimiento[3],
                      Formacion nuevaFormacion, std::string nombre,
                      std::string Apellido, std::string ciudadResidencia,
                      std::string paisNacimiento,
                      std::string cidudadNacimiento) {
    datosAutor* aux = arbolAutor.getNodeKey(IDAUTOR)->data;

    // Actualiza listas si cambian claves
    if (aux->ciudadResidencia != ciudadResidencia) {
      listaPorCiudadResidencia.borrarClave(aux->ciudadResidencia[0], aux);
      aux->ciudadResidencia = ciudadResidencia;
      listaPorCiudadResidencia.insertarClave(aux, aux->ciudadResidencia[0]);
    }
    if (aux->cidudadNacimiento != cidudadNacimiento) {
      listaPorCiudadNacimiento.borrarClave(aux->cidudadNacimiento[0], aux);
      aux->cidudadNacimiento = cidudadNacimiento;
      listaPorCiudadNacimiento.insertarClave(aux, aux->cidudadNacimiento[0]);
    }
    if (aux->paisNacimiento != paisNacimiento) {
      listaPorPaisNacimiento.borrarClave(aux->paisNacimiento[0], aux);
      aux->paisNacimiento = paisNacimiento;
      listaPorPaisNacimiento.insertarClave(aux, aux->paisNacimiento[0]);
    }
    if (aux->añoIncio != añoInicio) {
      listaPorAñoInicio.borrarClave(aux->añoIncio, aux);
      aux->añoIncio = añoInicio;
      listaPorAñoInicio.insertarClave(aux, aux->añoIncio);
    }
    if (aux->añoPublicacion != añoPublicacion) {
      listaPorAñoPublicacion.borrarClave(aux->añoPublicacion, aux);
      aux->añoPublicacion = añoPublicacion;
      listaPorAñoPublicacion.insertarClave(aux, aux->añoPublicacion);
    }
    if (aux->formacion != nuevaFormacion) {
      listaPorFormacion.borrarClave(aux->formacion, aux);
      aux->formacion = nuevaFormacion;
      listaPorFormacion.insertarClave(aux, aux->formacion);
    }
    if (aux->sexo != sexo) {
      listaPorSexo.borrarClave(aux->sexo, aux);
      aux->sexo = sexo;
      listaPorSexo.insertarClave(aux, aux->sexo);
    }
    aux->nombre = nombre;
    aux->Apellido = Apellido;
    for (int i = 0; i < 3; ++i) aux->fechaNacimiento[i] = fechaNacimiento[i];
  }

  // Buscar un autor por ID
  datosAutor const* buscarAutor(unsigned int IDAUTOR) {
    return arbolAutor.getNodeKey(IDAUTOR)->data;
  }

  // Mostrar todos los autores guardados
  void mostrarAutores() {
    std::cout << "\n--- LISTA DE AUTORES ---\n";
    pila<datosAutor*> autores = arbolAutor.inorden();
    while (!autores.PilaVacia()) {
      datosAutor* autor = autores.Pop();
      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << std::endl;
    }
  }

  void mostrarAutoresEditorial(Lista<unsigned int>* IDAUTOR) {
    cout << "\n--- LISTA DE AUTORES POR RESIDENCIA ---\n";

    nodoOrd<datosAutor*, char>* auxRes = listaPorCiudadResidencia.buscarPos(0);

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

    cout << "\n--- LISTA DE OBRAS POR AÑO ---\n";

    nodoOrd<datosAutor*, int>* auxAnioI = listaPorAñoInicio.buscarPos(0);

    while (NULL != auxRes) {
      datosAutor* autor = auxRes->dato1;
      auxRes = auxRes->sig;

      if (IDAUTOR->tieneValor(autor->IDAUTOR)) continue;

      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << " | Año Incio en literatura: " << autor->añoIncio
                << std::endl;
    }
  }
};
