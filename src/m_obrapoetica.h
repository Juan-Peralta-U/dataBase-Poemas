// Evita la inclusión múltiple del archivo
#pragma once

// Librería estándar para manejar texto
#include <string>

// Incluye la definición de lista genérica (para almacenar las ediciones)
#include "lista.h"

// Incluye la estructura que define los datos de una edición
#include "m_edicion.h"

/*
 * Estructura que representa una obra poética en el sistema.
 * Cada obra tiene:
 *  • Un nombre (título).
 *  • Un tipo de poesía (por ejemplo, soneto, haiku...).
 *  • Un ID que identifica al autor.
 *  • Una lista de ediciones asociadas a la obra.
 */

// Enumeración para clasificar los tipos de poesía.
// Cada tipo tiene un valor entero asociado para facilitar su comparación o almacenamiento.

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
// Estructura que contiene los datos de una obra poética individual

struct ObraPoetica {
  unsigned int IDAUTOR; // Identificador único del autor que escribió la obra
  tipoObra obra; // Tipo de poesía, usando la enumeración tipoObra
  std::string nombre; // Nombre o título de la obra poética
  Lista<datosEdiccion> ediciones; // Lista de todas las ediciones publicadas de esta obra
};
