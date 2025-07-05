#pragma once
#include <string>

/*
Datos de la edición
    • ID de la Editorial.
    • Número de la edición
    • Fecha de publicación.
    • Ciudad de publicación.
*/

struct datosEdiccion {
  unsigned int IDEDITORIAL;
  unsigned int numeroEdicion;
  std::string fechaDePublicacion, ciudadDePublicacion;
};
