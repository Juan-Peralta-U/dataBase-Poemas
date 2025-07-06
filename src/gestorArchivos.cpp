#include <iostream> // Para entrada/salida estándar
#include <string> // Para usar strings
#include <fstream> // Para leer y escribir archivos
#include <sstream> // Para separar los campos de cada línea
// Inclusión de controladores y modelos
#include "controladorObras.cpp"
#include "controladorAutores.cpp"
#include "controladorEditoriales.cpp"
#include "m_datosAutor.h"
#include "m_Editorial.h"
#include "m_obrapoetica.h"
#include "m_edicion.h"

using namespace std;

// FUNCIONES PARA CARGAR DATOS
// Cargar autores desde un archivo CSV.
// Cada línea contiene: ID,nombre,apellido,sexo,día,mes,año,ciudadNac,paisNac,ciudadRes,formacion,añoInicio,añoPublicacion
void cargarAutores(ControladorAutores& ctrlAutores, const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de autores.\n";
        return;
    }
    string linea;
    while (getline(archivo, linea)) { // Leer cada línea del archivo
        istringstream iss(linea); // Crear flujo para dividir la línea
        datosAutor* autor = new datosAutor; // Crear nuevo objeto autor
        string campo;
// Leer y asignar cada campo al objeto autor
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
        autor->formacion = static_cast<formacion>(stoi(campo));
        getline(iss, campo, ',');
        autor->añoIncio = stoi(campo);
        getline(iss, campo, ',');
        autor->añoPublicacion = stoi(campo);
        
    // Agregar autor al controlador
        ctrlAutores.agregarAutor(autor);
    }
    archivo.close(); // Cerrar archivo
    cout << "Autores cargados correctamente.\n";
}

//Cargar Obras
//IDObra, IDAutor,tipoObra,nombre
//IDAutor debe existir en el controlador de autores
void cargarObras(ControladorObras& ctrlObras, ControladorAutores& ctrlAutores, const string &nombreArchivo){
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
// Leer los campos de la obra
        getline(iss, campo, ',');
        idObra = stoi(campo);
        getline(iss, campo, ',');
        idAutor = stoi(campo);
        getline(iss, campo, ',');
        tipo = stoi(campo);
        getline(iss, nombre, ',');
                // Crear y agregar la obra al controlador
        ctrlObras.agregarObra(idObra, idAutor, static_cast<tipoObra>(tipo), nombre);
    }
    archivo.close();
    cout << "Obras cargadas correctamente.\n";
}

//Cargar editoriales
// IDEditorial,nombreEditorial,ciudadOficina,paisOficina
void cargarEditoriales(ControladorEditoriales& ctrlEditoriales, const string &nombreArchivo) {
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
// Leer campos de la editorial
        getline(iss, campo, ',');
        editorial->IDEDITORIAL = stoi(campo);
        getline(iss, editorial->nombreEditorial, ',');
        getline(iss, editorial->ciudadOficina, ',');
        getline(iss, editorial->paisOficina, ',');
// Agregar editorial al controlador
        ctrlEditoriales.agregarEditorial(editorial);
    }
    archivo.close();
    cout << "Editoriales cargadas correctamente.\n";
}

//Cargar Ediciones
// IDObra,IDEditorial,numEdicion,fechaPublicacion,ciudadPublicacion
// IDObra debe existir en el controlador de obras y IDEditorial en el controlador de editoriales
void cargarEdiciones(ControladorObras& ctrlObras, const string &nombreArchivo) {
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
// Leer campos de la edición
        getline(iss, campo, ',');
        idObra = stoi(campo);
        getline(iss, campo, ',');
        idEditorial = stoi(campo);
        getline(iss, campo, ',');
        numEdicion = stoi(campo);
        getline(iss, fechaPublicacion, ',');
        getline(iss, ciudadPublicacion, ',');
        // Crear y agregar la edición a la obra correspondiente
        datosEdiccion ed{ idEditorial, numEdicion, fechaPublicacion, ciudadPublicacion };
        ctrlObras.agregarEdicionAObra(idObra, ed);
    }
}


//GUARDAR DATOS
// Guardar todos los autores en un archivo
void guardarAutores(ControladorAutores& ctrlAutores, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar autores.\n";
        return;
    }

    // Recorrer autores en inorden
    pila<datosAutor*> autores = ctrlAutores.getAutores(); // Obtener pila de autores
    while (!autores.PilaVacia()) {
        datosAutor* a = autores.Pop(); // Extraer autor
        archivo << a->IDAUTOR << ","
                << a->nombre << ","
                << a->Apellido << ","
                << a->sexo << ","
                << a->fechaNacimiento[0] << ","
                << a->fechaNacimiento[1] << ","
                << a->fechaNacimiento[2] << ","
                << a->cidudadNacimiento << ","
                << a->paisNacimiento << ","
                << a->ciudadResidencia << ","
                << static_cast<int>(a->formacion) << ","
                << a->añoIncio << ","
                << a->añoPublicacion << "\n";
    }
    archivo.close();
    cout << "Autores guardados correctamente.\n";
}
// Guardar todas las editoriales en un archivo
void guardarEditoriales(ControladorEditoriales& ctrlEditoriales, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar editoriales.\n";
        return;
    }

    // Recorrer editoriales en inorden
    pila<datosEditorial*> editoriales = ctrlEditoriales.getEditoriales();  // Obtener pila
    while (!editoriales.PilaVacia()) {
        datosEditorial* e = editoriales.Pop();
        archivo << e->IDEDITORIAL << ","
                << e->nombreEditorial << ","
                << e->ciudadOficina << ","
                << e->paisOficina << "\n";
    }
    archivo.close();
    cout << "Editoriales guardadas correctamente.\n";
}
// Guardar todas las ediciones de todas las obras en un archivo
void guardarEdiciones(ControladorObras& ctrlObras, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar ediciones.\n";
        return;
    }

    // Recorrer obras en inorden
    pila<ObraPoetica*> obras = ctrlObras.getObras();
    while (!obras.PilaVacia()) {
        ObraPoetica* obra = obras.Pop();
        // Recorrer ediciones de la obra
        for (int i = 0; i < obra->ediciones.getTam(); ++i) {
            const datosEdiccion& ed = obra->ediciones.get(i);
            archivo << obra->IDAUTOR << ","
                    << ed.IDEDITORIAL << ","
                    << ed.numeroEdicion << ","
                    << ed.fechaDePublicacion << ","
                    << ed.ciudadDePublicacion << "\n";
        }
    }
    archivo.close();
    cout << "Ediciones guardadas correctamente.\n";
}
// Guardar todas las obras poéticas registradas
void guardarObras(ControladorObras& ctrlObras, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para guardar obras.\n";
        return;
    }

    // Recorrer obras en inorden
    pila<ObraPoetica*> obras = ctrlObras.getObras(); // Obtener pila de obras
    pila<int> claves = ctrlObras.getClavesObras(); // Obtener pila de IDOBRA

    while (!obras.PilaVacia() && !claves.PilaVacia()) {
        ObraPoetica* obra = obras.Pop();
        int idObra = claves.Pop();
        archivo << idObra << "," // ID de la obra (clave del árbol)
                << obra->IDAUTOR << "," // ID del autor
                << static_cast<int>(obra->obra) << ","  // Tipo de obra
                << obra->nombre << "\n"; // Nombre de la obra
    }
    archivo.close();
    cout << "Obras guardadas correctamente.\n";
    
}

