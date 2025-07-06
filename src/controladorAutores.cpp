/*
  ControladorAutores.h/.cpp
  ---------------------------------
  Esta clase gestiona el conjunto de autores literarios del sistema, incluyendo:
  - Registro, edición y eliminación de autores.
  - Búsquedas eficientes por atributos como ciudad, país, año o sexo.
  - Estructuras en memoria: listas ordenadas y árbol rojo-negro.
*/

#include <ctime>  // Para obtener la fecha actual del sistema
#include <string> // Para manipular cadenas de caracteres
// Inclusión de estructuras de listas y árboles personalizadas
#include "lista.h"
#include "listaOrd.h"
#include "m_datosAutor.h"
#include "treeRB.h"
// Clase que administra toda la información relacionada con los autores
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
  // Árbol RojiNegro para búsquedas rápidas por IDAUTOR
  TreeRB<1000, datosAutor*> arbolAutor;   // Clave = IDAUTOR

 public:
 // Agrega un autor nuevo y lo registra en todas las listas auxiliares y el árbol
  void agregarAutor(datosAutor* autor) {
   // Insertar en cada lista usando la clave correspondiente
    listaPorCiudadResidencia.insertarClave(autor, autor->ciudadResidencia[0]);
    listaPorCiudadNacimiento.insertarClave(autor, autor->cidudadNacimiento[0]);
    listaPorPaisNacimiento.insertarClave(autor, autor->paisNacimiento[0]);
    listaPorAñoInicio.insertarClave(autor, autor->añoIncio);
    listaPorAñoPublicacion.insertarClave(autor, autor->añoPublicacion);
    listaPorFormacion.insertarClave(autor, autor->formacion);
    listaPorSexo.insertarClave(autor, autor->sexo);
    // Agregar al árbol por su ID
    arbolAutor.add(autor->IDAUTOR, autor);
  }

  // Eliminar un autor y actualizar todas las listas
  void eliminarAutor(unsigned int IDAUTOR) {
   // Obtener el puntero al autor por su ID
    datosAutor* del = arbolAutor.getNodeKey(IDAUTOR)->data;
   // Borrar el autor de todas las listas auxiliares
    listaPorCiudadResidencia.borrarClave(del->ciudadResidencia[0], del);
    listaPorCiudadNacimiento.borrarClave(del->cidudadNacimiento[0], del);
    listaPorPaisNacimiento.borrarClave(del->paisNacimiento[0], del);
    listaPorAñoInicio.borrarClave(del->añoIncio, del);
    listaPorAñoPublicacion.borrarClave(del->añoPublicacion, del);
    listaPorFormacion.borrarClave(del->formacion, del);
    listaPorSexo.borrarClave(del->sexo, del);
   // Eliminar del árbol
    arbolAutor.deleteKey(del->IDAUTOR);
   // Liberar memoria del objeto autor
    delete del;
  }
 // Modifica los datos de un autor existente
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
       // Actualizar datos generales
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
    pila<datosAutor*> autores = arbolAutor.inorden(); // Recorre en orden
   
    while (!autores.PilaVacia()) {
        datosAutor* autor = autores.Pop();
        std::cout << "ID: " << autor->IDAUTOR
            << " | Nombre: " << autor->nombre
            << " " << autor->Apellido
            << " | Sexo: " << (autor->sexo ? "M" : "F")
            << " | Ciudad residencia: " << autor->ciudadResidencia
            << " | Fecha de nacimiento: "
            << autor->fechaNacimiento[0] << "/"
            << autor->fechaNacimiento[1] << "/"
            << autor->fechaNacimiento[2]
            << std::endl;
    }
  }
// Retorna la pila de autores del árbol (para otros módulos)
  pila<datosAutor*> getAutores() {
    return arbolAutor.inorden();
      datosAutor* autor = autores.Pop();
      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << std::endl;
    }
  }
// Muestra un autor específico
  void mostrarAutor(unsigned int IDAUTOR) {
    std::cout << "\n--- LISTA DE AUTORES ---\n";
    datosAutor* autor = arbolAutor.getNodeKey(IDAUTOR)->data;
    std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
              << " " << autor->Apellido
              << " | Sexo: " << (autor->sexo ? "M" : "F")
              << " | Ciudad residencia: " << autor->ciudadResidencia
              << std::endl;
  }
// Muestra autores de una lista, organizados por ciudad y año de inicio
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
// Muestra autores por rango de edad y formación
  void mostrarAutoresPorRangoyFormacion(int rangoEdad[2], Formacion formacion) {
    cout << "\n--- LISTA DE AUTORES POR Ciudad de nacimiento ---\n";

    nodoOrd<datosAutor*, int>* auxRes = listaPorAñoPublicacion.buscarPos(0);

    while (NULL != auxRes) {
      datosAutor* autor = auxRes->dato1;
      auxRes = auxRes->sig;

      int edad = calcularEdadActual(autor->IDAUTOR);

      if (rangoEdad[0] > edad || edad > rangoEdad[1]) continue;

      if (formacion != autor->formacion) continue;

      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << std::endl;
    }
  }
 // Muestra autores por ciudad de nacimiento
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
  // Calcula la edad actual de un autor a partir de su fecha de nacimiento
  int calcularEdadActual(int IDAUTOR) {
    datosAutor* autor = arbolAutor.getNodeKey(IDAUTOR)->data;

    // Obtener fecha actual del sistema
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaActual = std::localtime(&tiempoActual);

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;  // tm_mon: 0 (ene) - 11 (dic)
    int anioActual = fechaActual->tm_year + 1900;

    // Extraer fecha de nacimiento del autor
    int diaNac = autor->fechaNacimiento[0];
    int mesNac = autor->fechaNacimiento[1];
    int anioNac = autor->fechaNacimiento[2];

    // Calcular edad base (diferencia de años)
    int edad = anioActual - anioNac;

    // Verificar si ya pasó la fecha de cumpleaños en el año actual
    if (mesActual < mesNac) {
      edad--;
    } else if (mesActual == mesNac && diaActual < diaNac) {
      edad--;
    }

    // Manejar casos donde la fecha de nacimiento es futura (edad negativa)
    if (edad < 0) {
      return 0;
    }

    return edad;
  }
};
