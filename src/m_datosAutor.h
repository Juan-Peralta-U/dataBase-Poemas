#pragma once // Directiva que evita que el archivo se incluya más de una vez
#include <string>

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
 // Enumeración que representa la formación académica del autor.
// Se asignan valores enteros a cada tipo de formación para facilitar almacenamiento y comparación.
enum Formacion {
  literatura = 0,
  artes = 1,
  cienciasSociales = 2,
  ingenierías = 3,
  áreasDeLaSalud = 4,
  jurisprudencia = 5,
  otros = 6
};
// Estructura que almacena todos los datos relevantes de un autor.
// Se utilizará en el sistema para gestionar información biográfica y profesional.
struct datosAutor {
  unsigned int IDAUTOR; // Identificador único del autor
  bool sexo; // Representa el sexo: false = Femenino, true = Masculino
  int añoIncio, añoPublicacion;
  int fechaNacimiento[3];  // tres ints para dia/mes/año facilita calculos
                           // espero
  Formacion formacion;
 // Datos personales y geográficos del autor
  std::string nombre, Apellido, cidudadNacimiento, paisNacimiento,
      ciudadResidencia;
};
