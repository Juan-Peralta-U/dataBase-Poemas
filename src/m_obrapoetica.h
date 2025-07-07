#pragma once
#include <string>

#include "lista.h"
#include "m_edicion.h"

/*
  Estructura que representa una obra poética en el sistema.

  Atributos principales:
    - Nombre de la obra (documento literario).
    - Tipo de poesía (soneto, haiku, etc.), codificado como enumeración.
    - ID del autor que la escribió.
    - Lista de ediciones publicadas de esta obra.
*/

// Enumeración que define los diferentes tipos de poesía que puede tener una obra.
enum tipoObra {
  decima = 0,
  soneto = 1,
  himno = 2,
  haiku = 3,
  romance = 4,
  octavaReal = 5,
  lira = 6,
  versoLibre = 7
};
// Estructura que modela una obra poética.
struct ObraPoetica {
  unsigned int IDAUTOR;
  tipoObra obra;
  std::string nombre;
  Lista<datosEdiccion> ediciones; // Lista de ediciones de la obra, usando la estructura Lista.
};
