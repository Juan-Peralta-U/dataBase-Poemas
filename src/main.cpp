#include <iostream>
#include <string>
#include "controladorObras.cpp"
#include "controladorAutores.cpp"
#include "controladorEditoriales.cpp"
#include "m_datosAutor.h"
#include "m_Editorial.h"
#include "m_obrapoetica.h"
#include "m_edicion.h"
#include "gestorArchivos.cpp"

using namespace std;

ControladorObras ctrlObras;
ControladorAutores ctrlAutores;
ControladorEditoriales ctrlEditoriales;

// Funciones auxiliares para entrada de datos
void leerString(const string& msg, string& var) {
    cout << msg; getline(cin, var);
}
void leerUInt(const string& msg, unsigned int& var) {
    cout << msg; cin >> var; cin.ignore();
}
void leerInt(const string& msg, int& var) {
    cout << msg; cin >> var; cin.ignore();
}

// CRUD para autores
void crudAutores() {
    int op;
    do {
        cout << "\n--- AUTORES ---\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. Volver\nOpcion: ";
        cin >> op; cin.ignore();
        if(op == 1) {
            datosAutor* a = new datosAutor;
            leerUInt("ID: ", a->IDAUTOR);
            // Verificar si ya existe un autor con ese ID
            if (ctrlAutores.buscarAutor(a->IDAUTOR) != nullptr) {
                cout << "ERROR: Ya existe un autor con ese ID. No se puede agregar.\n";
                delete a;
                continue;
            }
            leerString("Nombre: ", a->nombre);
            leerString("Apellido: ", a->Apellido);
            leerInt("Sexo (0=F, 1=M): ", (int&)a->sexo);
            cout << "Fecha nacimiento (d m a): "; cin >> a->fechaNacimiento[0] >> a->fechaNacimiento[1] >> a->fechaNacimiento[2]; cin.ignore();
            leerString("Ciudad nacimiento: ", a->cidudadNacimiento);
            leerString("Pais nacimiento: ", a->paisNacimiento);
            leerString("Ciudad residencia: ", a->ciudadResidencia);
            leerInt("Formacion (enum int): ", (int&)a->formacion);
            leerInt("Año inicio literatura: ", a->añoIncio);
            leerInt("Año publicacion primera obra: ", a->añoPublicacion);
            ctrlAutores.agregarAutor(a);
            cout << "Autor agregado.\n";
        } else if(op == 2) {
            unsigned int id; leerUInt("ID a eliminar: ", id);
            ctrlAutores.eliminarAutor(id);
            cout << "Autor eliminado.\n";
        } else if(op == 3) {
            unsigned int id; leerUInt("ID a modificar: ", id);
            datosAutor* a = new datosAutor;
            leerString("Nuevo nombre: ", a->nombre);
            leerString("Nuevo apellido: ", a->Apellido);
            leerInt("Nuevo sexo (0=F, 1=M): ", (int&)a->sexo);
            cout << "Nueva fecha nacimiento (d m a): "; cin >> a->fechaNacimiento[0] >> a->fechaNacimiento[1] >> a->fechaNacimiento[2]; cin.ignore();
            leerString("Nueva ciudad nacimiento: ", a->cidudadNacimiento);
            leerString("Nuevo pais nacimiento: ", a->paisNacimiento);
            leerString("Nueva ciudad residencia: ", a->ciudadResidencia);
            leerInt("Nueva formacion (enum int): ", (int&)a->formacion);
            leerInt("Nuevo año inicio literatura: ", a->añoIncio);
            leerInt("Nuevo año publicacion primera obra: ", a->añoPublicacion);
            ctrlAutores.modificarAutor(id, a->sexo, a->añoIncio, a->añoPublicacion, a->fechaNacimiento, a->formacion, a->nombre, a->Apellido, a->ciudadResidencia, a->paisNacimiento, a->cidudadNacimiento);
            delete a;
            cout << "Autor modificado.\n";
        }
    } while(op != 4);
}

// CRUD para editoriales
void crudEditoriales() {
    int op;
    do {
        cout << "\n--- EDITORIALES ---\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. Volver\nOpcion: ";
        cin >> op; cin.ignore();
        if(op == 1) {
            datosEditorial* e = new datosEditorial;
            leerUInt("ID: ", e->IDEDITORIAL);
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
        } else if(op == 2) {
            unsigned int id; leerUInt("ID a eliminar: ", id);
            ctrlEditoriales.eliminarEditorial(id);
            cout << "Editorial eliminada.\n";
        } else if(op == 3) {
            unsigned int id; leerUInt("ID a modificar: ", id);
            string nombre, ciudad, pais;
            leerString("Nuevo nombre: ", nombre);
            leerString("Nueva ciudad oficina: ", ciudad);
            leerString("Nuevo pais oficina: ", pais);
            ctrlEditoriales.modificarEditorial(id, nombre, ciudad, pais);
            cout << "Editorial modificada.\n";
        }
    } while(op != 4);
}

// CRUD para obras y ediciones
void crudObras() {
    int op;
    do {
        cout << "\n--- OBRAS ---\n1. Ingresar\n2. Eliminar\n3. Modificar\n4. Agregar edicion\n5. Eliminar edicion\n6. Volver\nOpcion: ";
        cin >> op; cin.ignore();
        if(op == 1) {
            unsigned int idObra, idAutor; string nombre; int tipo;
            leerUInt("ID Obra: ", idObra);
            // Verificar si ya existe una obra con ese ID
            if (ctrlObras.buscarObra(idObra) != nullptr) {
                cout << "ERROR: Ya existe una obra con ese ID. No se puede agregar.\n";
                continue;
            }
            leerUInt("ID Autor: ", idAutor);
            // Verificar si el autor existe antes de agregar la obra
            if (ctrlAutores.buscarAutor(idAutor) == nullptr) {
                cout << "ERROR: El autor con ese ID no existe. No se puede agregar la obra.\n";
                continue;
            }
            leerInt("Tipo de poesia (enum int): ", tipo);
            leerString("Nombre: ", nombre);
            ctrlObras.agregarObra(idObra, idAutor, static_cast<tipoObra>(tipo), nombre);
            cout << "Obra agregada.\n";
        } else if(op == 2) {
            unsigned int idObra; leerUInt("ID a eliminar: ", idObra);
            ctrlObras.eliminarObra(idObra);
            cout << "Obra eliminada.\n";
        } else if(op == 3) {
            unsigned int idObra, idAutor; string nombre; int tipo;
            leerUInt("ID a modificar: ", idObra);
            leerUInt("Nuevo ID Autor: ", idAutor);
            leerInt("Nuevo tipo de poesia (enum int): ", tipo);
            leerString("Nuevo nombre: ", nombre);
            ctrlObras.modificarObra(idObra, idAutor, static_cast<tipoObra>(tipo), nombre);
            cout << "Obra modificada.\n";
        } else if(op == 4) {
            unsigned int idObra, idEditorial, numEdicion;
            string fecha, ciudad;
            leerUInt("ID Obra: ", idObra);
            if(ctrlObras.buscarObra(idObra) == nullptr) {
                cout << "ERROR: La obra con ese ID no existe. No se puede agregar la edición.\n";
                continue;
            }
            leerUInt("ID Editorial: ", idEditorial);
            // Verificar si la editorial existe antes de agregar la edición
            if (ctrlEditoriales.buscarEditorial(idEditorial) == nullptr) {
                cout << "ERROR: La editorial con ese ID no existe. No se puede agregar la edición.\n";
                continue;
            }
            leerUInt("Numero de edicion: ", numEdicion);
            leerString("Fecha de publicacion (dd/mm/aaaa): ", fecha);
            leerString("Ciudad de publicacion: ", ciudad);
            datosEdiccion ed{ idEditorial, numEdicion, fecha, ciudad };
            ctrlObras.agregarEdicionAObra(idObra, ed);
            cout << "Edicion agregada.\n";
        } else if(op == 5) {
            unsigned int idObra, numEdicion;
            leerUInt("ID Obra: ", idObra);
            leerUInt("Numero de edicion a eliminar: ", numEdicion);
            ctrlObras.eliminarEdicionDeObra(idObra, numEdicion);
            cout << "Edicion eliminada.\n";
        }
    } while(op != 6);
}

// Menú mostrar
void menuMostrar() {
    int op;
    do {
        cout << "\n--- MOSTRAR DATOS ---\n";
        cout << "1. Obras\n2. Ediciones\n3. Autores\n4. Editoriales\n5. Volver\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: ctrlObras.mostrarObras(); break;
            case 2: ctrlObras.mostrarTodasEdiciones(); break;
            case 3: ctrlAutores.mostrarAutores(); break;
            case 4: ctrlEditoriales.mostrarEditoriales(); break;
            case 5: break;
            default: cout << "Opcion invalida.\n";
        }
    } while(op != 5);
}

int main() {
    cargarAutores(ctrlAutores, "autores.txt");
    cargarEditoriales(ctrlEditoriales, "editoriales.txt");
    cargarObras(ctrlObras, ctrlAutores, "obras.txt");
    cargarEdiciones(ctrlObras, "ediciones.txt");

    int op;
    do {
        cout << "\n==== MENU PRINCIPAL ====\n";
        cout << "1. Obras\n2. Autores\n3. Editoriales\n4. Mostrar\n5. Salir\nOpcion: ";
        cin >> op; cin.ignore();
        switch(op) {
            case 1: crudObras(); break;
            case 2: crudAutores(); break;
            case 3: crudEditoriales(); break;
            case 4: menuMostrar(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while(op != 5);

    guardarAutores(ctrlAutores, "autores.txt");
    guardarEditoriales(ctrlEditoriales, "editoriales.txt");
    guardarObras(ctrlObras, "obras.txt");
    guardarEdiciones(ctrlObras, "ediciones.txt");
    
    return 0;
}
