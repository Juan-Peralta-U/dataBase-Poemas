#pragma once
#include <string>

/*
Datos de la edición
    • ID de la Editorial.
    • Número de la edición
    • Fecha de publicación.
    • Ciudad de publicación.
*/

// Definición de la estructura datosEdiccion
struct datosEdiccion {
  unsigned int IDEDITORIAL; // Identificador único de la editorial que publica esta edición
  unsigned int numeroEdicion;
  std::string fechaDePublicacion, ciudadDePublicacion;
};
