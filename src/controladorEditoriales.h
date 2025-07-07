#ifndef CONTROLADOR_EDITORIALES_H
#define CONTROLADOR_EDITORIALES_H

#include <string>
// Inclusión de estructuras de datos personalizadas y modelo de editorial
#include "lista.h"
#include "listaOrd.h"
#include "m_Editorial.h"
#include "treeRB.h"
// Clase encargada de gestionar todas las operaciones relacionadas con las editoriales
class ControladorEditoriales {
 private:
  // Listas ordenadas por primera letra de atributos para facilitar búsquedas:
  ListaOrd<datosEditorial*, char> listaPorNombreEditorial; // Ordena por nombre
  ListaOrd<datosEditorial*, char> listaPorCiudad; // Ordena por ciudad 
  ListaOrd<datosEditorial*, char> listaPorPais; // Ordena por pais
  ListaOrd<datosEditorial*, int> listaPorNumPoetas;   // Lista ordenada por número de poetas publicados
  // Árbol rojo-negro que almacena editoriales por su ID
  TreeRB<1000, datosEditorial*> arbolEditorial;
  // Árbol rojo-negro que almacena listas de IDs de autores por editorial
  TreeRB<1000, Lista<unsigned int>*> autoresPublicados;

 public:
  // Registra una nueva editorial en todas las estructuras necesarias
  void agregarEditorial(datosEditorial* editorial, int numPoetas = 0);
  // Elimina una editorial y su información asociada, incluyendo su lista de autores
  void eliminarEditorial(unsigned int IDEDITORIAL, int numPoetas = 0);
  // Modifica los datos básicos de una editorial y actualiza su ubicación en listas ordenadas
  void modificarEditorial(unsigned int IDEDITORIAL, std::string nuevoNombre,
                          std::string nuevaCiudad, std::string nuevoPais,
                          int numPoetas = 0);
  // Busca una editorial por su ID y devuelve un puntero constante a sus datos
  datosEditorial const* buscarEditorial(unsigned int IDEDITORIAL);
  // Muestra por consola todas las editoriales registradas
  void mostrarEditoriales();
  // Muestra las editoriales que han publicado al menos cierta cantidad de autores
  void mostarNumeroDeAutores(int cantidad);
  // Devuelve una pila con todas las editoriales registradas (útil para recorridos)
  pila<datosEditorial*> getEditoriales();
  // Inserta un autor como publicado por una editorial específica
  void insertarAutorPublicado(unsigned int IDAUTOR, unsigned int IDEDITORIAL);
  // Devuelve la lista de IDs de autores publicados por una editorial
  Lista<unsigned int>* autoresPublicadosPorEditorial(unsigned int IDEDITORIAL);
};

#endif  // CONTROLADOR_EDITORIALES_H
