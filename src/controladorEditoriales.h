#ifndef CONTROLADOR_EDITORIALES_H
#define CONTROLADOR_EDITORIALES_H

#include "lista.h"
#include "estructuras.h"  // struct datosEditorial

class ControladorEditoriales {
private:
    Lista<datosEditorial> listaPorNombreEditorial;
    Lista<datosEditorial> listaPorNumPublicaciones;

public:
    ControladorEditoriales() {}

    void insertarEditorial(const datosEditorial& editorial);
    
    void listarPorNombreEditorial();
  
};

#endif
