#pragma once
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

enum Formacion {
  literatura = 0,
  artes = 1,
  cienciasSociales = 2,
  ingenierías = 3,
  áreasDeLaSalud = 4,
  jurisprudencia = 5,
  otros = 6
};

struct datosAutor {
  unsigned int IDAUTOR;
  bool sexo;
  int añoIncio, añoPublicacion;
  int fechaNacimiento[3];  // tres ints para dia/mes/año facilita calculos
                           // espero
  Formacion formacion;
  std::string nombre, Apellido, cidudadNacimiento, paisNacimiento,
      ciudadResidencia;
};
