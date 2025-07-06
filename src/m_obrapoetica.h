#pragma once
#include <string>

#include "lista.h"
#include "m_edicion.h"

/*
Datos de la obra poética.
    • Nombre del documento
    • Tipo de poesía: décima, soneto, himno, haiku, romance, octava real, lira,
verso libre. • ID del autor. • Listado de las ediciones

*/

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

struct ObraPoetica {
  unsigned int IDAUTOR;
  tipoObra obra;
  std::string nombre;
  Lista<datosEdiccion> ediciones;
};
