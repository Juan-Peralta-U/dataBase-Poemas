#pragma once
#include <string>
/*
 * Estructura: datosAutor
 * Contiene todos los campos relevantes para describir a un autor.
 * Los campos están especificados en el comentario con viñetas.
 */

/*
Datos del autor.
    • ID Autor
    • Nombre
    • Apellido
    • Sexo: F o M
    • Fecha de Nacimiento
    • Ciudad de Nacimiento
    • País de Nacimiento
    • Ciudad de Residencia
    • Formación de base: literatura, artes, ciencias sociales, ingenierías,
      áreas de la salud, jurisprudencia, otros
    • Año de inicio en la literatura • Año
de publicación de su primera obra
*/

// --------------------------
// Enumeración Formacion
// --------------------------
// Representa la formación académica o profesional del autor.
// Se asignan valores enteros a cada opción para facilitar almacenamiento.
enum Formacion {
  literatura = 0,
  artes = 1,
  cienciasSociales = 2,
  ingenierías = 3,
  áreasDeLaSalud = 4,
  jurisprudencia = 5,
  otros = 6
};
// --------------------------
// Estructura datosAutor
// --------------------------
// Agrupa todos los datos relevantes de un autor en un solo objeto.
struct datosAutor {
  unsigned int IDAUTOR; // Identificador único del autor
  bool sexo; // Sexo del autor (0 = Femenino, 1 = Masculino)
  int añoIncio, añoPublicacion;
  int fechaNacimiento[3];  // tres ints para dia/mes/año facilita calculos
                           // espero
  Formacion formacion; // Formación académica/profesional del autor
 // Información personal y geográfica
  std::string nombre, Apellido, cidudadNacimiento, paisNacimiento,
      ciudadResidencia;
};
