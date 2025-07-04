#ifndef VISTA_CONTROLADOR_H
#define VISTA_CONTROLADOR_H

#include <iostream>
#include <string>

#include "VistaObras.h"

// Declaraciones de funciones
void mostrarMenu(const std::string& titulo, const std::string opciones[],
                 int numOpciones);

void ejecutarAccion(int menu, int opcion);

void gestionarMenu(const std::string& titulo, const std::string opciones[],
                   int numOpciones, int menuId);

void ejecutarVista();

#endif
