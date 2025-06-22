#include <string>

/*
Datos de la edición
    • ID de la Editorial.
    • Número de la edición
    • Fecha de publicación.
    • Ciudad de publicación.
*/

struct ObraPoetica {
  unsigned int IDEDITORIAL;
  unsigned int numeroEdicion;
  std::string fechaDePublicacion, ciudadDePublicacion;
};
