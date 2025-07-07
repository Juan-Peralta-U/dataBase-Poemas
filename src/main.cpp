#include <iostream>
#include <string>

#include "controladorAutores.h"
#include "controladorEditoriales.h"
#include "controladorObras.h"
#include "gestorArchivos.h"
#include "m_Editorial.h"
#include "m_datosAutor.h"
#include "m_edicion.h"
#include "m_obrapoetica.h"

using namespace std;

ControladorObras ctrlObras;
ControladorAutores ctrlAutores;
ControladorEditoriales ctrlEditoriales;

string linea1 = "------------------------------------------------------------";
string linea2 = "============================================================";

// Funciones auxiliares para entrada de datos
void leerString(const string& msg, string& var) {
  cout << msg;
  getline(cin, var);
}
void leerUInt(const string& msg, unsigned int& var) {
  cout << msg;
  cin >> var;
  cin.ignore();
}
void leerInt(const string& msg, int& var) {
  cout << msg;
  cin >> var;
  cin.ignore();
}

// CRUD para autores
void crudAutores() {
  int op;
  do {
    cout << linea1 << "\n                   GESTION DE AUTORES\n" << linea1;
    cout << "\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. Volver\n"<<linea1<<"\nOpcion: ";
    cin >> op;
    cin.ignore();
    if (op == 1) {
      datosAutor* a = new datosAutor;
      leerUInt("ID: ", a->IDAUTOR);
      if(ctrlAutores.buscarAutor(a->IDAUTOR) != nullptr) {
        cout << "ERROR: Ya existe un autor con ese ID. No se puede agregar.\n";
        delete a;
        continue;
      }
      leerString("Nombre: ", a->nombre);
      leerString("Apellido: ", a->Apellido);
      leerInt("Sexo (0=F, 1=M): ", (int&)a->sexo);
      cout << "Fecha nacimiento (d m a): ";
      cin >> a->fechaNacimiento[0] >> a->fechaNacimiento[1] >>
          a->fechaNacimiento[2];
      cin.ignore();
      leerString("Ciudad nacimiento: ", a->cidudadNacimiento);
      leerString("Pais nacimiento: ", a->paisNacimiento);
      leerString("Ciudad residencia: ", a->ciudadResidencia);
      leerInt("Formacion(Literatura = 0, Artes = 1, CienciasSociales = 2, Ingenierias = 3, AreasDeLaSalud = 4, Jurisprudencia = 5, Otros = 6): ", (int&)a->formacion);
      leerInt("Año inicio literatura: ", a->añoIncio);
      leerInt("Año publicacion primera obra: ", a->añoPublicacion);
      ctrlAutores.agregarAutor(a);
      cout << "Autor agregado.\n";
    } else if (op == 2) {
      unsigned int id;
      leerUInt("ID a eliminar: ", id);
      if(ctrlAutores.buscarAutor(id) == nullptr) {
        cout << "ERROR: El autor con ese ID no existe. No se puede eliminar.\n";
        continue;
      }
      ctrlAutores.eliminarAutor(id);
      cout << "Autor eliminado.\n";
    } else if (op == 3) {
      unsigned int id;
      leerUInt("ID a modificar: ", id);
      if(ctrlAutores.buscarAutor(id) == nullptr) {
        cout << "ERROR: El autor con ese ID no existe. No se puede modificar.\n";
        continue;
      }
      datosAutor* a = new datosAutor;
      leerString("Nuevo nombre: ", a->nombre);
      leerString("Nuevo apellido: ", a->Apellido);
      leerInt("Nuevo sexo (0=F, 1=M): ", (int&)a->sexo);
      cout << "Nueva fecha nacimiento (d m a): ";
      cin >> a->fechaNacimiento[0] >> a->fechaNacimiento[1] >>
          a->fechaNacimiento[2];
      cin.ignore();
      leerString("Nueva ciudad nacimiento: ", a->cidudadNacimiento);
      leerString("Nuevo pais nacimiento: ", a->paisNacimiento);
      leerString("Nueva ciudad residencia: ", a->ciudadResidencia);
      leerInt("Nueva formacion(Literatura = 0, Artes = 1, CienciasSociales = 2, Ingenierias = 3, AreasDeLaSalud = 4, Jurisprudencia = 5, Otros = 6): ", (int&)a->formacion);
      leerInt("Nuevo año inicio literatura: ", a->añoIncio);
      leerInt("Nuevo año publicacion primera obra: ", a->añoPublicacion);
      ctrlAutores.modificarAutor(id, a->sexo, a->añoIncio, a->añoPublicacion,
                                 a->fechaNacimiento, a->formacion, a->nombre,
                                 a->Apellido, a->ciudadResidencia,
                                 a->paisNacimiento, a->cidudadNacimiento);
      delete a;
      cout << "Autor modificado.\n";
    }
  } while (op != 4);
}

// CRUD para editoriales
void crudEditoriales() {
  int op;
  do {
    cout << linea1 << "\n                   GESTION DE EDITORIALES\n" << linea1;
    cout << "\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. Volver\n"<<linea1<<"\nOpcion: ";
    cin >> op;
    cin.ignore();
    if (op == 1) {
      datosEditorial* e = new datosEditorial;
      leerUInt("ID: ", e->IDEDITORIAL);
      // Verificar si el ID de la editorial ya existe
      if (ctrlEditoriales.buscarEditorial(e->IDEDITORIAL) != nullptr) {
        cout << "ERROR: Ya existe una editorial con ese ID. No se puede agregar.\n";
        delete e;
        continue;
      }
      leerString("Nombre: ", e->nombreEditorial);
      leerString("Ciudad oficina: ", e->ciudadOficina);
      leerString("Pais oficina: ", e->paisOficina);
      ctrlEditoriales.agregarEditorial(e);
      cout << "Editorial agregada.\n";
    } else if (op == 2) {
      unsigned int id;
      leerUInt("ID a eliminar: ", id);
      // Verificar si la editorial existe antes de eliminarla
      if (ctrlEditoriales.buscarEditorial(id) == nullptr) {
        cout << "ERROR: La editorial con ese ID no existe. No se puede eliminar.\n";
        continue;
      }
      ctrlEditoriales.eliminarEditorial(id);
      cout << "Editorial eliminada.\n";
    } else if (op == 3) {
      unsigned int id;
      leerUInt("ID a modificar: ", id);
      // Verificar si la editorial existe antes de modificarla
      if (ctrlEditoriales.buscarEditorial(id) == nullptr) {
        cout << "ERROR: La editorial con ese ID no existe. No se puede modificar.\n";
        continue;
      }
      string nombre, ciudad, pais;
      leerString("Nuevo nombre: ", nombre);
      leerString("Nueva ciudad oficina: ", ciudad);
      leerString("Nuevo pais oficina: ", pais);
      ctrlEditoriales.modificarEditorial(id, nombre, ciudad, pais);
      cout << "Editorial modificada.\n";
    }
  } while (op != 4);
}

// CRUD para obras y ediciones
void crudObras() {
  int op;
  do {
    cout << linea1 << "\n                   GESTION DE OBRAS\n" << linea1;
    cout << "\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. "
            "Agregar edicion\n5. Eliminar edicion\n6. Volver\n"<<linea1<<"\nOpcion: ";
    cin >> op;
    cin.ignore();
    if (op == 1) {
      unsigned int idObra, idAutor;
      string nombre;
      int tipo;
      leerUInt("ID Obra: ", idObra);
      // Verificar si el ID de la obra ya existe
      if (ctrlObras.buscarObra(idObra) != nullptr) {
        cout << "ERROR: Ya existe una obra con ese ID. No se puede agregar.\n";
        continue;
      }
      leerUInt("ID Autor: ", idAutor);
      // Verificar si el autor existe antes de agregar la obra
      if (ctrlAutores.buscarAutor(idAutor) == nullptr) {
        cout << "ERROR: El autor con ese ID no existe. No se puede agregar la "
            "obra.\n";
        continue;
      }
      leerInt("Tipo de poesia(Decima = 0, Soneto = 1, Himno = 2, Haiku = 3, Romance = 4, Octava Real = 5, Lira = 6, Verso Libre = 7): ", tipo);
      leerString("Nombre: ", nombre);
      ctrlObras.agregarObra(idObra, idAutor, static_cast<tipoObra>(tipo),
                            nombre);
      cout << "Obra agregada.\n";
    } else if (op == 2) {
      unsigned int idObra;
      leerUInt("ID a eliminar: ", idObra);
      // Verificar si la obra existe antes de eliminarla
      if (ctrlObras.buscarObra(idObra) == nullptr) {
        cout << "ERROR: La obra con ese ID no existe. No se puede eliminar.\n";
        continue;
      }
      ctrlObras.eliminarObra(idObra);
      cout << "Obra eliminada.\n";
    } else if (op == 3) {
      unsigned int idObra, idAutor;
      string nombre;
      int tipo;
      // Verificar si el ID de la obra ya existe
      leerUInt("ID a modificar: ", idObra);
      if (ctrlObras.buscarObra(idObra) == nullptr) {
        cout << "ERROR: La obra con ese ID no existe. No se puede modificar.\n";
        continue;
      }
      leerUInt("Nuevo ID Autor: ", idAutor);
      if (ctrlAutores.buscarAutor(idAutor) == nullptr) {
        cout << "ERROR: El autor con ese ID no existe. No se puede modificar la obra.\n";
        continue;
      }
      leerInt("Nuevo tipo de poesia(Decima = 0, Soneto = 1, Himno = 2, Haiku = 3, Romance = 4, Octava Real = 5, Lira = 6, Verso Libre = 7): ", tipo);
      leerString("Nuevo nombre: ", nombre);
      ctrlObras.modificarObra(idObra, idAutor, static_cast<tipoObra>(tipo),
                              nombre);
      cout << "Obra modificada.\n";
    } else if (op == 4) {
      unsigned int idObra, idEditorial, numEdicion;
      string fecha, ciudad;
      leerUInt("ID Obra: ", idObra);
      // Verificar si la obra existe antes de agregar la edición
      if (ctrlObras.buscarObra(idObra) == nullptr) {
        cout << "ERROR: La obra con ese ID no existe. No se puede agregar la edición.\n";
        continue;
      }
      leerUInt("ID Editorial: ", idEditorial);
      // Verificar si la editorial existe antes de agregar la edición
      if (ctrlEditoriales.buscarEditorial(idEditorial) == nullptr) {
        cout << "ERROR: La editorial con ese ID no existe. No se puede agregar "
                "la edición.\n";
        continue;
      }
      leerUInt("Numero de edicion: ", numEdicion);
      leerString("Fecha de publicacion (dd/mm/aaaa): ", fecha);
      leerString("Ciudad de publicacion: ", ciudad);

      datosEdiccion ed{idEditorial, numEdicion, fecha, ciudad};
      ctrlObras.agregarEdicionAObra(idObra, ed);
      ctrlEditoriales.insertarAutorPublicado(ctrlObras.mostarIDAUTOR(idObra),
                                             idEditorial);
      cout << "Edicion agregada.\n";
    } else if (op == 5) {
      unsigned int idObra, numEdicion;
      leerUInt("ID Obra: ", idObra);
      // Verificar si la obra existe antes de eliminar la edición
      if (ctrlObras.buscarObra(idObra) == nullptr) {
        cout << "ERROR: La obra con ese ID no existe. No se puede eliminar la edición.\n";
        continue;
      }
      leerUInt("Numero de edicion a eliminar: ", numEdicion);
      ctrlObras.eliminarEdicionDeObra(idObra, numEdicion);
      cout << "Edicion eliminada.\n";
    }
  } while (op != 6);
}

void mostrarconsultas() {
  int op;
  unsigned int id;

  do {
    cout << linea1 << "\n                   CONSULTAS AVANZADAS\n" << linea1;
    cout << "\n1. Total de obras de un autor -> por editorial y año de publicación. "
            "\n2. Obras de un autor"
            "\n3. Autores publicados por una editorial -> por ciudad y año de inicio."
            "\n4. Editoriales con mas de N poetas -> mostrar cantidad y ubicacion."
            "\n5. Hombres y mujeres publicados -> por ciudad y pais de nacimiento."
            "\n6. Autores por edad y formación -> clasificados por año de 1ra obra."
            "\n7. Autores y ediciones -> por tipo de poesia y editorial.\n8. "
            "regresar\n";
    cout << linea1 << "\nOpcion: ";
    cin >> op;
    cin.ignore();
    switch (op) {
      case 1:
        leerUInt("ID Autor: ", id);
        if(ctrlAutores.buscarAutor(id) == nullptr) {
          cerr << "Autor no existe\n";
          break;
        }
        ctrlObras.mostrarObrasPorAutor(id);
        break;
      case 2:
        leerUInt("ID Autor: ", id);
        if(ctrlAutores.buscarAutor(id) == nullptr) {
          cerr << "Autor no existe\n";
          break;
        }
        ctrlObras.mostrarTiposObraPorAutor(id);
        break;
      case 3:
        leerUInt("ID Editorial: ", id);

        if (ctrlEditoriales.autoresPublicadosPorEditorial(id) == nullptr) {
          cerr << "Editorial no existe\n";
          break;
        }

        ctrlAutores.mostrarAutoresEditorial(
            ctrlEditoriales.autoresPublicadosPorEditorial(id));
        break;
      case 4:
        leerUInt("Catidad de Autores: ", id);

        ctrlEditoriales.mostarNumeroDeAutores(id);
        break;
      case 5: {
        pila<datosEditorial*> editoriales = ctrlEditoriales.getEditoriales();
        Lista<unsigned int>* autores;
        while (!editoriales.PilaVacia()) {
          datosEditorial* ed = editoriales.Pop();

          int tamañoH = 0, tamañoF = 0;

          autores =
              ctrlEditoriales.autoresPublicadosPorEditorial(ed->IDEDITORIAL);

          if (autores == nullptr) continue;

          for (int i = 0; i < autores->getTam(); i++)
            ctrlAutores.buscarAutor(autores->get(i))->sexo ? tamañoH++
                                                           : tamañoF++;

          std::cout << "ID: " << ed->IDEDITORIAL
                    << " | Nombre: " << ed->nombreEditorial
                    << " | Cantidad H: " << tamañoH
                    << " | Cantidad F: " << tamañoF
                    << " | Ciudad: " << ed->ciudadOficina
                    << " | Pais: " << ed->paisOficina << std::endl;

          ctrlAutores.mostrarAutoresPorCiudadResidencia(autores);
          std::cout << "\n-----------------------------------------------\n";
        }
        break;
      }
      case 6:
        int edad[2], formacion;
        leerInt("Edad Minima: ", *edad);
        leerInt("Edad Maxima: ", edad[1]);
        leerInt("Formacion(Literatura = 0, Artes = 1, CienciasSociales = 2, Ingenierias = 3, AreasDeLaSalud = 4, Jurisprudencia = 5, Otros = 6): ", formacion);
        ctrlAutores.mostrarAutoresPorRangoyFormacion(edad,
                                                     Formacion(formacion));
        break;
      case 7: {
        int tipo;
        leerUInt("ID Editorial: ", id);
        if(ctrlEditoriales.buscarEditorial(id) == nullptr) {
          cerr << "Editorial no existe\n";
          break;
        }
        leerInt("Tipo poesia(Decima = 0, Soneto = 1, Himno = 2, Haiku = 3, Romance = 4, Octava Real = 5, Lira = 6, Verso Libre = 7): ", tipo);
        unsigned int autoresId;
        Lista<unsigned int>* autores =
            ctrlEditoriales.autoresPublicadosPorEditorial(id);

        if (autores == nullptr) {
          cerr << "Editorial no existe\n";
          break;
        }

        for (int i = 0; i < autores->getTam(); i++) {
          autoresId = autores->get(i);
          ctrlAutores.mostrarAutor(autoresId);
          ctrlObras.mostrarTiposObraPorAutorYTipo(autoresId, tipoObra(tipo));
        }
        break;
      }
      case 8:
        break;
      default:
        break;
    }

  } while (op != 8);
}

// Menú mostrar
void menuMostrar() {
  int op;
  do {
    cout << linea1 << "\n                   MOSTRAR DATOS Y CONSULTAS\n" << linea1;
    cout << "\n1. Mostrar todas las obras\n2. Mostrar todas las ediciones\n3. Mostrar Autores Registrados\n4. Mostrar Editoriales\n5. "
            "Mostrar Consultas\n6. Volver\n"<<linea1<<"\nOpcion: ";
    cin >> op;
    cin.ignore();
    switch (op) {
      case 1:
        ctrlObras.mostrarObras();
        break;
      case 2:
        ctrlObras.mostrarTodasEdiciones();
        break;
      case 3:
        ctrlAutores.mostrarAutores();
        break;
      case 4:
        ctrlEditoriales.mostrarEditoriales();
        break;
      case 5:
        mostrarconsultas();
      case 6:
        break;
      default:
        cout << "Opcion invalida.\n";
    }
  } while (op != 6);
}

int main() {
  cargarAutores(ctrlAutores, "autores.txt");
  cargarEditoriales(ctrlEditoriales, "editoriales.txt");
  cargarObras(ctrlObras, ctrlAutores, "obras.txt");
  cargarEdiciones(ctrlObras, ctrlEditoriales, "ediciones.txt");

  int op;
  do {
    cout << linea2 << "\n               BIENVENIDO A POESIA LIBRERIA\n"<< linea2 << "\n";
    cout << "1. Gestionar Obras Poeticas\n2. Gestionar Autores\n3. Gestionar Editoriales\n"
        "4. Realizar Consultas Avanzadas\n5. Guardar cambios y salir del sistema\n"<<linea2 << "\nOpcion: ";
    cin >> op;
    cin.ignore();
    switch (op) {
      case 1:
        crudObras();
        break;
      case 2:
        crudAutores();
        break;
      case 3:
        crudEditoriales();
        break;
      case 4:
        menuMostrar();
        break;
      case 5:
        cout << "Saliendo...\n";
        break;
      default:
        cout << "Opcion invalida.\n";
    }
  } while (op != 5);

  guardarAutores(ctrlAutores, "autores.txt");
  guardarEditoriales(ctrlEditoriales, "editoriales.txt");
  guardarObras(ctrlObras, "obras.txt");
  guardarEdiciones(ctrlObras, "ediciones.txt");

  return 0;
}
