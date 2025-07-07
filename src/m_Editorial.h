// Evita que el archivo se incluya más de una vez en la compilación
#pragma once
#include <string>
// ------------------------------
// Estructura de datosEditorial
// ------------------------------
// Representa la información básica de una editorial
struct datosEditorial { // Identificador único de la editorial
  unsigned int IDEDITORIAL;
  std::string nombreEditorial, ciudadOficina, paisOficina;
};
