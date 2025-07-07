#pragma once
#include <string>
// Incluye la biblioteca estándar <string> para poder usar el tipo std::string
// Estructura que representa una editorial en el sistema
struct datosEditorial {
  unsigned int IDEDITORIAL; // Identificador único de la editorial
  std::string nombreEditorial, ciudadOficina, paisOficina;
};
