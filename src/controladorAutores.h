#ifndef CONTROLADOR_AUTORES_H
#define CONTROLADOR_AUTORES_H

#include "lista.h"
#include "estructuras.h"  // struct datosAutor

class ControladorAutores {
private:
    Lista<datosAutor> listaPorCiudadResidencia;
    Lista<datosAutor> listaPorAnioInicio;
    Lista<datosAutor> listaPorAnioPublicacion;
    Lista<datosAutor> listaPorCiudadNacimiento;
    Lista<datosAutor> listaPorPaisNacimiento;

public:
    ControladorAutores() {}

    void insertarAutor(const datosAutor& autor);
    
    // Métodos de ordenamiento y consultas
    void listarPorCiudadResidencia();
    void listarPorAnioInicio();
    void listarPorAnioPublicacion();
    void listarPorCiudadNacimiento();
    void listarPorPaisNacimiento();
};

#endif
