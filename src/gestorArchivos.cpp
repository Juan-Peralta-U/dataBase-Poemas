#include "gestorArchivos.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "m_Editorial.h"
#include "m_datosAutor.h"
#include "m_edicion.h"
#include "m_obrapoetica.h"

using namespace std;


// IDAUTOR,nombre,Apellido,sexo,fechaNacimiento_dia,fechaNacimiento_mes,fechaNacimiento_año,cidudadNacimiento,paisNacimiento,ciudadResidencia,formacion,añoIncio,añoPublicacion
void cargarAutores(ControladorAutores& ctrlAutores,
                   const string& nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo de autores.\n";
    return;
  }

  string linea;
  while (getline(archivo, linea)) {
    istringstream iss(linea);
    datosAutor* autor = new datosAutor;
    string campo;

    getline(iss, campo, ',');
    autor->IDAUTOR = stoi(campo);
    getline(iss, autor->nombre, ',');
    getline(iss, autor->Apellido, ',');
    getline(iss, campo, ',');
    autor->sexo = stoi(campo);

    getline(iss, campo, ',');
    autor->fechaNacimiento[0] = stoi(campo);
    getline(iss, campo, ',');
    autor->fechaNacimiento[1] = stoi(campo);
    getline(iss, campo, ',');
    autor->fechaNacimiento[2] = stoi(campo);

    getline(iss, autor->cidudadNacimiento, ',');
    getline(iss, autor->paisNacimiento, ',');
    getline(iss, autor->ciudadResidencia, ',');

    getline(iss, campo, ',');
    autor->formacion = static_cast<Formacion>(stoi(campo));
    getline(iss, campo, ',');
    autor->añoIncio = stoi(campo);
    getline(iss, campo, ',');
    autor->añoPublicacion = stoi(campo);

    ctrlAutores.agregarAutor(autor);
  }
  archivo.close();
  cout << "Autores cargados correctamente.\n";
}

// IDEDITORIAL,nombreEditorial,ciudadOficina,paisOficina
void cargarObras(ControladorObras& ctrlObras, ControladorAutores& ctrlAutores,
                 const string& nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo de Obras.\n";
    return;
  }
  string linea;
  while (getline(archivo, linea)) {
    istringstream iss(linea);
    unsigned int idObra, idAutor;
    string nombre, campo;
    int tipo;

    getline(iss, campo, ',');
    idObra = stoi(campo);
    getline(iss, campo, ',');
    idAutor = stoi(campo);
    getline(iss, campo, ',');
    tipo = stoi(campo);
    getline(iss, nombre, ',');
    ctrlObras.agregarObra(idObra, idAutor, static_cast<tipoObra>(tipo), nombre);
  }
  archivo.close();
  cout << "Obras cargadas correctamente.\n";
}

// IDEDITORIAL,nombreEditorial,ciudadOficina,paisOficina
void cargarEditoriales(ControladorEditoriales& ctrlEditoriales,
                       const string& nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo de editoriales.\n";
    return;
  }
  string linea;
  while (getline(archivo, linea)) {
    istringstream iss(linea);
    datosEditorial* editorial = new datosEditorial;
    string campo;

    getline(iss, campo, ',');
    editorial->IDEDITORIAL = stoi(campo);
    getline(iss, editorial->nombreEditorial, ',');
    getline(iss, editorial->ciudadOficina, ',');
    getline(iss, editorial->paisOficina, ',');

    ctrlEditoriales.agregarEditorial(editorial);
  }
  archivo.close();
  cout << "Editoriales cargadas correctamente.\n";
}

// IDOBRA,IDEDITORIAL,numEdicion,fechaPublicacion,ciudadPublicacion
void cargarEdiciones(ControladorObras& ctrlObras,
                     ControladorEditoriales& ctrlEditoriales,
                     const string& nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo de Ediciones.\n";
    return;
  }
  string linea;
  while (getline(archivo, linea)) {
    istringstream iss(linea);
    unsigned int idObra, idEditorial, numEdicion;
    string fechaPublicacion, ciudadPublicacion, campo;

    getline(iss, campo, ',');
    idObra = stoi(campo);
    getline(iss, campo, ',');
    idEditorial = stoi(campo);
    getline(iss, campo, ',');
    numEdicion = stoi(campo);
    getline(iss, fechaPublicacion, ',');
    getline(iss, ciudadPublicacion, ',');

    datosEdiccion ed{idEditorial, numEdicion, fechaPublicacion,
                     ciudadPublicacion};
    ctrlObras.agregarEdicionAObra(idObra, ed);
    ctrlEditoriales.insertarAutorPublicado(ctrlObras.mostarIDAUTOR(idObra),
                                           idEditorial);
  }
  archivo.close();
  cout << "Ediciones cargadas correctamente.\n";
}

void guardarAutores(ControladorAutores& ctrlAutores,
                    const string& nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo para guardar autores.\n";
    return;
  }

  pila<datosAutor*> autores = ctrlAutores.getAutores();
  while (!autores.PilaVacia()) {
    datosAutor* a = autores.Pop();
    archivo << a->IDAUTOR << "," << a->nombre << "," << a->Apellido << ","
            << a->sexo << "," << a->fechaNacimiento[0] << ","
            << a->fechaNacimiento[1] << "," << a->fechaNacimiento[2] << ","
            << a->cidudadNacimiento << "," << a->paisNacimiento << ","
            << a->ciudadResidencia << "," << static_cast<int>(a->formacion)
            << "," << a->añoIncio << "," << a->añoPublicacion << "\n";
  }
  archivo.close();
  cout << "Autores guardados correctamente.\n";
}

void guardarEditoriales(ControladorEditoriales& ctrlEditoriales,
                        const string& nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo para guardar editoriales.\n";
    return;
  }

  pila<datosEditorial*> editoriales = ctrlEditoriales.getEditoriales();
  while (!editoriales.PilaVacia()) {
    datosEditorial* e = editoriales.Pop();
    archivo << e->IDEDITORIAL << "," << e->nombreEditorial << ","
            << e->ciudadOficina << "," << e->paisOficina << "\n";
  }
  archivo.close();
  cout << "Editoriales guardadas correctamente.\n";
}

void guardarEdiciones(ControladorObras& ctrlObras,
                      const string& nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo para guardar ediciones.\n";
    return;
  }

  pila<ObraPoetica*> obras = ctrlObras.getObras();
  pila<int> claves = ctrlObras.getClavesObras();

  while (!obras.PilaVacia() && !claves.PilaVacia()) {
    ObraPoetica* obra = obras.Pop();
    int idObra = claves.Pop();
    for (int i = 0; i < obra->ediciones.getTam(); ++i) {
      const datosEdiccion& ed = obra->ediciones.get(i);
      archivo << idObra << ","  // ID de la obra
              << ed.IDEDITORIAL << "," << ed.numeroEdicion << ","
              << ed.fechaDePublicacion << "," << ed.ciudadDePublicacion << "\n";
    }
  }
  archivo.close();
  cout << "Ediciones guardadas correctamente.\n";
}

void guardarObras(ControladorObras& ctrlObras, const string& nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    cout << "Error al abrir el archivo para guardar obras.\n";
    return;
  }

  pila<ObraPoetica*> obras = ctrlObras.getObras();
  pila<int> claves = ctrlObras.getClavesObras();

  while (!obras.PilaVacia() && !claves.PilaVacia()) {
    ObraPoetica* obra = obras.Pop();
    int idObra = claves.Pop();
    archivo << idObra << ","  // ID de la obra
            << obra->IDAUTOR << "," << static_cast<int>(obra->obra) << ","
            << obra->nombre << "\n";
  }
  archivo.close();
  cout << "Obras guardadas correctamente.\n";
}
