#ifndef CONTROLADOR_OBRAS_H
#define CONTROLADOR_OBRAS_H

#include "lista.h"
#include "treeRB.h"
#include "estructuras.h"

class ControladorObras {
private:
    Lista<ObraPoetica> listaOrdenadaPorAnio;
    TreeRB<50, ObraPoetica> arbolPorIDAutor;

public:
    ControladorObras() {}

    // Métodos base
    void insertarObra(const ObraPoetica& obra);
    void listarObrasPorAnio();
    void buscarObrasPorAutor(int idAutor);

    // Otros métodos de modificación, eliminación, etc.
};

#endif
