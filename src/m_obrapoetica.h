#include <string>

#include "lista.h"
#include "treeRB.h"

/*
Datos de la obra poética.
    • Nombre del documento
    • Tipo de poesía: décima, soneto, himno, haiku, romance, octava real, lira,
verso libre. • ID del autor. • Listado de las ediciones

*/

enum tipoObra {
  decima,
  soneto,
  himno,
  haiku,
  romance,
  octavaReal,
  lira,
  versoLibre
};

struct ObraPoetica {
  unsigned int IDAUTOR;
  tipoObra obra;
  std::string nombre;
  // TODO CAMBIAR unsigned int a lista de nodos
  // TreeRB<50, Lista<class T>> listaEdiciones;
};
