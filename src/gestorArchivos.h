#ifndef GESTION_DATOS_H
#define GESTION_DATOS_H

#include <string>

#include "controladorAutores.h"
#include "controladorEditoriales.h"
#include "controladorObras.h"

// Funciones para cargar datos
void cargarAutores(ControladorAutores& ctrlAutores,
                   const std::string& nombreArchivo);
void cargarObras(ControladorObras& ctrlObras, ControladorAutores& ctrlAutores,
                 const std::string& nombreArchivo);
void cargarEditoriales(ControladorEditoriales& ctrlEditoriales,
                       const std::string& nombreArchivo);
void cargarEdiciones(ControladorObras& ctrlObras,
                     const std::string& nombreArchivo);

// Funciones para guardar datos
void guardarAutores(ControladorAutores& ctrlAutores,
                    const std::string& nombreArchivo);
void guardarEditoriales(ControladorEditoriales& ctrlEditoriales,
                        const std::string& nombreArchivo);
void guardarEdiciones(ControladorObras& ctrlObras,
                      const std::string& nombreArchivo);
void guardarObras(ControladorObras& ctrlObras,
                  const std::string& nombreArchivo);

#endif  // GESTION_DATOS_H
