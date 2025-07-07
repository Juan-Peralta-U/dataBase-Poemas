#ifndef CONTROLADOR_OBRAS_H
#define CONTROLADOR_OBRAS_H
// Inclusión de librerías necesarias para tipos de datos y estructuras auxiliares
#include <string>

#include "listaOrd.h" // Para manejar listas ordenadas de obras
#include "m_edicion.h" // Estructura de datos para información de ediciones
#include "m_obrapoetica.h" // Estructura de datos de la obra poética
#include "pila.h"  // Estructura de pila (LIFO)
#include "treeRB.h" // Árbol rojo-negro para acceso rápido por ID
// Clase ControladorObras: se encarga de gestionar todas las obras poéticas en el sistema
class ControladorObras {
 private:
  // Listas ordenadas para clasificar obras por diferentes criterios
  ListaOrd<ObraPoetica*, int> listaPorAnioPublicacion;  // Lista ordenada por año de publicación
  ListaOrd<ObraPoetica*, tipoObra> listaPorTipoPoesia;// Lista ordenada por tipo de poesía
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDAutor;// Lista ordenada por ID del autor
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDEditorial;// Lista ordenada por ID de la editorial
  // Árbol rojo-negro para acceso eficiente a las obras mediante su ID
  TreeRB<1000, ObraPoetica*> arbolObra;
  // Árbol que almacena qué obras tienen ediciones asociadas
  TreeRB<1000, bool> obrasConEdiciones;

 public:
  // Agrega una nueva obra al sistema, insertándola en el árbol y las listas
  void agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR, tipoObra obraTipo,
                   const std::string& nombre);
  // Elimina una obra (y sus ediciones) del sistema
  void eliminarObra(unsigned int IDOBRA);
  // Modifica atributos principales de una obra (autor, tipo, nombre)
  void modificarObra(unsigned int IDOBRA, unsigned int nuevoIDAUTOR,
                     tipoObra nuevoTipo, const std::string& nuevoNombre);
  // Busca y retorna una obra a partir de su ID
  ObraPoetica const* buscarObra(unsigned int IDOBRA);
  // Agrega una nueva edición a una obra específica
  void agregarEdicionAObra(unsigned int IDOBRA, const datosEdiccion& edicion);
  // Elimina una edición específica de una obra
  void eliminarEdicionDeObra(unsigned int IDOBRA, unsigned int numEdicion);
  // Muestra en consola todas las obras del sistema
  void mostrarObras();
  // Muestra todas las ediciones de todas las obras
  void mostrarTodasEdiciones();
  // Muestra todas las obras asociadas a un autor, clasificadas por año/editorial
  void mostrarObrasPorAutor(unsigned int IDAUTOR);
  // Muestra las obras por tipo de poesía para un autor dado
  void mostrarTiposObraPorAutor(unsigned int IDAUTOR);
  // Retorna una pila con todas las obras registradas
  pila<ObraPoetica*> getObras();
  // Retorna una pila con todas las ediciones existentes
  pila<datosEdiccion> getEdiciones();
  // Retorna una pila con los ID de todas las obras
  pila<int> getClavesObras();
  // Muestra todas las obras de un autor de un tipo específico
  void mostrarTiposObraPorAutorYTipo(unsigned int IDAUTOR, tipoObra tipo);
  // Retorna el ID del autor de una obra específica
  unsigned int mostarIDAUTOR(unsigned int IDOBRA);
};

#endif  // CONTROLADOR_OBRAS_H
