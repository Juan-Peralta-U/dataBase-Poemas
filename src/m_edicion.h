// Evita que el archivo se incluya más de una vez durante la compilación
#pragma once

// Permite usar strings para representar texto (como fechas o ciudades)
#include <string>

/*
 * Estructura: datosEdiccion
 * Representa la información específica de una edición de una obra.
 * Esta información se relaciona tanto con la obra como con la editorial.
 *
 * Campos:
 *  • IDEDITORIAL: Identificador único de la editorial que publica la edición.
 *  • numeroEdicion: Número que indica a qué edición pertenece (1ra, 2da, etc.).
 *  • fechaDePublicacion: Fecha en la que se publicó esa edición (puede ser solo año o fecha completa).
 *  • ciudadDePublicacion: Ciudad donde fue publicada la edición.
 */
struct datosEdiccion {
  unsigned int IDEDITORIAL;           // ID de la editorial responsable de la edición
  unsigned int numeroEdicion;         // Número de la edición (por ejemplo, 1, 2, 3...)
  std::string fechaDePublicacion;     // Fecha de publicación (por ejemplo: "12/03/2020" o "2020")
  std::string ciudadDePublicacion;    // Ciudad donde se publicó esta edición
};
