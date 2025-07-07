#ifndef CONTROLADOR_AUTORES_H
#define CONTROLADOR_AUTORES_H

#include <ctime> // Biblioteca para trabajar con tiempo (fecha actual)
#include <string> // Biblioteca para usar strings
// Inclusión de estructuras y modelos necesarios
#include "lista.h" // Lista simple
#include "listaOrd.h" // Lista ordenada (clave)
#include "m_datosAutor.h" // Estructura de datos del modelo de autor
#include "treeRB.h" // Árbol rojo-negro para acceso eficiente por ID
// Clase encargada de gestionar los autores del sistema
class ControladorAutores {
 private:
  // Listas ordenadas según diferentes atributos del autor, para facilitar las búsquedas
  ListaOrd<datosAutor*, char> listaPorCiudadResidencia; // Ordena por primera letra de ciudad de residencia
  ListaOrd<datosAutor*, char> listaPorCiudadNacimiento;// Ordena por primera letra de ciudad de nacimiento
  ListaOrd<datosAutor*, char> listaPorPaisNacimiento; // Ordena por primera letra de país de nacimiento
  ListaOrd<datosAutor*, int> listaPorAñoInicio;// Ordena por año de inicio en la literatura
  ListaOrd<datosAutor*, int> listaPorAñoPublicacion;  // Ordena por año de publicación de la primera obra
  ListaOrd<datosAutor*, Formacion> listaPorFormacion; // Ordena por tipo de formación profesional
  ListaOrd<datosAutor*, bool> listaPorSexo; // Ordena por sexo (0 = F, 1 = M)

  TreeRB<1000, datosAutor*> arbolAutor; // Árbol rojo-negro para acceso rápido por IDAUTOR

 public:
  // Inserta un nuevo autor en el sistema (en el árbol y listas ordenadas
  void agregarAutor(datosAutor* autor);
  // Elimina al autor identificado por IDAUTOR del sistema
  void eliminarAutor(unsigned int IDAUTOR);
  // Modifica los datos del autor. Si cambia alguna clave usada en ordenamiento, actualiza su posición
  void modificarAutor(unsigned int IDAUTOR, bool sexo, int añoInicio,
                      int añoPublicacion, int fechaNacimiento[3],
                      Formacion nuevaFormacion, std::string nombre,
                      std::string Apellido, std::string ciudadResidencia,
                      std::string paisNacimiento,
                      std::string cidudadNacimiento);
  // Busca y retorna un puntero constante a un autor según su ID
  datosAutor const* buscarAutor(unsigned int IDAUTOR);
  // Muestra todos los autores registrados en consola (recorrido inorden del árbol)
  void mostrarAutores();
  // Devuelve todos los autores como una pila (para visualización o filtrado)
  pila<datosAutor*> getAutores();
  // Muestra en consola los detalles de un único autor identificado por su ID
  void mostrarAutor(unsigned int IDAUTOR);
  // Muestra autores que han sido publicados por una editorial (filtrados por IDAUTOR)
  void mostrarAutoresEditorial(Lista<unsigned int>* IDAUTOR);
  // Muestra autores filtrados por un rango de edad y tipo de formación
  void mostrarAutoresPorRangoyFormacion(int rangoEdad[2], Formacion formacion);
  // Muestra autores agrupados por ciudad de residencia, usando la lista ordenada correspondiente
  void mostrarAutoresPorCiudadResidencia(Lista<unsigned int>* IDAUTOR) {
    cout << "\n--- LISTA DE AUTORES POR Ciudad de nacimiento ---\n";
    // Recorre la lista ordenada por ciudad de nacimiento
    nodoOrd<datosAutor*, char>* auxRes = listaPorCiudadNacimiento.buscarPos(0);
// Recorre todos los nodos de la lista
    while (NULL != auxRes) {
      datosAutor* autor = auxRes->dato1;
      auxRes = auxRes->sig;
      // Verifica si el ID está en la lista recibida (si no, lo muestra)
      if (!IDAUTOR->tieneValor(autor->IDAUTOR)) continue;
      // Imprime los datos relevantes del autor
      std::cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre
                << " " << autor->Apellido
                << " | Sexo: " << (autor->sexo ? "M" : "F")
                << " | Ciudad residencia: " << autor->ciudadResidencia
                << std::endl;
    }
  }
  // Declaración de la función para mostrar autores por ciudad de nacimiento
  void mostrarAutoresPorCiudadNacimiento(
      Lista<unsigned int>* IDAUTOR);  // Corregido nombre
  // Calcula la edad actual del autor según la fecha del sistema y su fecha de nacimiento
  int calcularEdadActual(int IDAUTOR);
};

#endif  // CONTROLADOR_AUTORES_H
