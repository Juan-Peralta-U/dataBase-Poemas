#ifndef GESTION_DATOS_H
#define GESTION_DATOS_H
// Inclusión de bibliotecas necesarias para el uso de std::string
#include <string>
// Inclusión de controladores para acceder y modificar las estructuras de datos principales
#include "controladorAutores.h"
#include "controladorEditoriales.h"
#include "controladorObras.h"
// ----------------------
// FUNCIONES DE CARGA
// ----------------------
// Carga los autores desde un archivo CSV (texto separado por comas) al sistema
void cargarAutores(ControladorAutores& ctrlAutores,
                   const std::string& nombreArchivo);
// Carga las obras desde un archivo CSV y las enlaza con los autores
void cargarObras(ControladorObras& ctrlObras, ControladorAutores& ctrlAutores,
                 const std::string& nombreArchivo);
// Carga las editoriales desde un archivo CSV al sistema
void cargarEditoriales(ControladorEditoriales& ctrlEditoriales,
                       const std::string& nombreArchivo);
// Carga las ediciones desde un archivo CSV y las enlaza con obras y editoriales
void cargarEdiciones(ControladorObras& ctrlObras,
                     ControladorEditoriales& ctrlEditoriales,
                     const string& nombreArchivo);
// ----------------------
// FUNCIONES DE GUARDADO
// ----------------------

// Guarda los autores registrados en el sistema dentro de un archivo CSV
void guardarAutores(ControladorAutores& ctrlAutores,
                    const std::string& nombreArchivo);
// Guarda las editoriales registradas en el sistema dentro de un archivo CSV
void guardarEditoriales(ControladorEditoriales& ctrlEditoriales,
                        const std::string& nombreArchivo);
// Guarda todas las ediciones de obras dentro de un archivo CSV
void guardarEdiciones(ControladorObras& ctrlObras,
                      const std::string& nombreArchivo);
// Guarda todas las obras literarias del sistema en un archivo CSV
void guardarObras(ControladorObras& ctrlObras,
                  const std::string& nombreArchivo);

#endif  // GESTION_DATOS_H
