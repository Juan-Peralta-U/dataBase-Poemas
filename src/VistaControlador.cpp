#include <iostream>
#include <string>
using namespace std;

// --- Funciones del menú ---
void mostrarMenu(const string& titulo, const string opciones[], int numOpciones) {
    string linea = "----------------------------------------------------------------";
    cout << linea << endl;
    cout << "               " << titulo << endl;
    cout << linea << endl;

    for (int i = 0; i < numOpciones; ++i) {
        cout << i + 1 << ". " << opciones[i] << endl;
    }
}

void ejecutarAccion(int menu, int opcion) {
    switch (menu) {
        case 1: //Obras
            switch (opcion) {
                case 1: 
                    cout << "Agregar una nueva obra." << endl; 
                    //logica para agregar una obra
                    break;
                case 2: 
                    cout << "Consultar obras existentes." << endl; 
                    //logica para consultar obras
                    break;
                case 3: 
                    cout << "Modificar informacion de una obra." << endl; 
                    //logica para modificar una obra
                    break;
                case 4: 
                    cout << "Eliminar una obra." << endl; 
                    //logica para eliminar una obra
                    break;
                case 5: 
                    cout << "Volviendo al menu principal..." << endl; 
                    break;
                default: 
                    cout << "Opcion no valida." << endl;
            }
            break;
        case 2: // Ediciones
switch (opcion) {
                case 1: 
                    cout << "Agregar edicion a una obra existente." << endl; 
                    //logica para agregar una edición
                    break;
                case 2: 
                    cout << "Consultar ediciones por obra." << endl; 
                    //logica para consultar ediciones
                    break;
                case 3: 
                    cout << "Modificar datos de una edición." << endl; 
                    //logica para modificar una edición
                    break;
                case 4: 
                    cout << "Eliminar edicion." << endl; 
                    //logica para eliminar una edición
                    break;
                case 5: 
                    cout << "Volviendo al menu principal..." << endl; 
                    break;
                default: 
                    cout << "Opcion no valida." << endl;
            }
            break;
        case 3: // Autores
            switch (opcion) {
                case 1: 
                    cout << "Agregar un nuevo autor." << endl; 
                    //logica para agregar un autor
                    break;
                case 2: 
                    cout << "Consultar autores existentes." << endl; 
                    //logica para consultar autores
                    break;
                case 3: 
                    cout << "Modificar informacion de un autor." << endl; 
                    //logica para modificar un autor
                    break;
                case 4: 
                    cout << "Eliminar un autor." << endl; 
                    //logica para eliminar un autor
                    break;
                case 5: 
                    cout << "Volviendo al menu principal..." << endl; 
                    break;
                default: 
                    cout << "Opcion no valida." << endl;
            }
            break;
 case 4: // Editoriales
            switch (opcion) {
                case 1: 
                    cout << "Agregar una nueva editorial." << endl; 
                    //logica para agregar una editorial
                    break;
                case 2: 
                    cout << "Consultar editoriales existentes." << endl; 
                    //logica para consultar editoriales
                    break;
                case 3: 
                    cout << "Modificar informacion de una editorial." << endl; 
                    //logica para modificar una editorial
                    break;
                case 4: 
                    cout << "Eliminar una editorial." << endl; 
                    //logica para eliminar una editorial
                    break;
                case 5: 
                    cout << "Volviendo al menu principal..." << endl; 
                    break;
                default: 
                    cout << "Opcion no valida." << endl;
            }
            break;
        case 5:
            switch (opcion) {
                case 1: cout << "Consulta avanzada 1." << endl; break;
                case 2: cout << "Consulta avanzada 2." << endl; break;
                case 3: cout << "Consulta avanzada 3." << endl; break;
                case 4: cout << "Consulta avanzada 4." << endl; break;
                case 5: cout << "Consulta avanzada 5." << endl; break;
                case 6: cout << "Volviendo al menu principal..." << endl; break;
                default: cout << "Opcion no valida." << endl;
            }
            break;
        default:
            cout << "Menu no valido." << endl;
    }
}

void gestionarMenu(const string& titulo, const string opciones[], int numOpciones, int menuId) {
    int opcion;
    mostrarMenu(titulo, opciones, numOpciones);
    cout << "Selecciona una opcion: ";
    cin >> opcion;
    if (opcion >= 1 && opcion <= numOpciones) {
        ejecutarAccion(menuId, opcion);
    } else {
        cout << "Opcion no valida. Por favor, intenta de nuevo." << endl;
    }
}

// --- Función que controla todo el menú ---
void ejecutarVista() {
    string opcionesObras[] = {
        "Agregar una nueva obra",
        "Consultar obras existentes",
        "Modificar informacion de una obra",
        "Eliminar una obra",
        "Volver al menu principal"
    };
    string opcionesEdiciones[] = {
        "Agregar edicion a una obra existente",
        "Consultar ediciones por obra",
        "Modificar datos de una edicion",
        "Eliminar edicion",
        "Volver al menu principal"
    };
    string opcionesAutores[] = {
        "Agregar un nuevo autor",
        "Consultar autores existentes",
        "Modificar informacion de un autor",
        "Eliminar un autor",
        "Volver al menu principal"
    };
    string opcionesEditoriales[] = {
        "Agregar una nueva editorial",
        "Consultar editoriales existentes",
        "Modificar informacion de una editorial",
        "Eliminar una editorial",
        "Volver al menu principal"
    };
    string opcionesConsultas[] = {
        "Obras de un autor -> por editorial y anio de publicacion",
        "Obras de un autor -> por tipo de poesia, con fecha y edicion",
        "Autores publicados por una editorial -> por ciudad y anio de inicio",
        "Editoriales con mas de N poetas -> mostrar cantidad y ubicacion",
        "Hombres y mujeres publicados -> por ciudad y pais de nacimiento",
        "Autores por edad y formacion -> clasificados por anio de 1ra obra",
        "Autores y ediciones -> por tipo de poesia y editorial",
        "Volver al menu principal"
    };

    int opcion = 0;
    string linea = "================================================================";
    do {
        cout << linea << endl;
        cout << "               BIENVENIDO A POESIA LIBRERIA" << endl;
        cout << linea << endl;
        cout << "1. Gestionar Obras Poeticas\n2. Gestionar Ediciones\n3. Gestionar Autores\n4. Gestionar Editoriales\n5. Realizar Consultas Avanzadas\n6. Guardar y salir\n";
        cout << linea << endl;
        cout << "Ingresa el numero de la opcion: ";
        cin >> opcion;

        switch (opcion) {
            // submenus
            case 1: gestionarMenu("Gestion de Obras Poeticas", opcionesObras, 5, 1); break;
            case 2: gestionarMenu("Gestion de Ediciones", opcionesEdiciones, sizeof(opcionesEdiciones)/sizeof(opcionesEdiciones[0]), 2); break;
            case 3: gestionarMenu("Gestion de Autores", opcionesAutores, sizeof(opcionesAutores)/sizeof(opcionesAutores[0]), 3); break;
            case 4: gestionarMenu("Gestion de Editoriales", opcionesEditoriales, sizeof(opcionesEditoriales)/sizeof(opcionesEditoriales[0]), 4); break;
            case 5: gestionarMenu("Consultas Avanzadas", opcionesConsultas, sizeof(opcionesConsultas) / sizeof(opcionesConsultas[0]), 5); break;
            case 6: cout << "Guardando cambios y saliendo del sistema..." << endl; break;
            default: cout << "Opcion no valida. Por favor, intenta de nuevo." << endl;
        }
    } while (opcion != 6);
    cout << "Gracias por usar el sistema. Hasta luego!" << endl;
}
