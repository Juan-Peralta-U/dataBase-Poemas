// ControladorObras.cpp
// ------------------------------------------
// Clase encargada de administrar las obras poéticas del sistema,
// incluyendo su registro, modificación, eliminación y consultas por diferentes criterios.
// Utiliza listas ordenadas y árbol rojo-negro para eficiencia en búsquedas.
#include <string>      // Librería para manejo de cadenas
#include "listaOrd.h" // Incluye estructura de lista ordenada
#include "m_edicion.h" // Estructura con la información de cada edición
#include "m_obrapoetica.h" // Clase base de cada obra poética
#include "pila.h" // Para recorrer estructuras como el árbol
#include "treeRB.h" // Árbol rojinegro para eficiencia en búsquedas por ID

// Clase encargada de controlar todas las operaciones sobre las obras poéticas
class ControladorObras {
 private:
  // Listas auxiliares para consultas eficientes
  ListaOrd<ObraPoetica*, int> listaPorAnioPublicacion;           // Para consultas por año
  ListaOrd<ObraPoetica*, tipoObra> listaPorTipoPoesia;           // Para consultas por tipo de poesía
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDAutor;          // Para consultas por autor
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDEditorial;      // Para consultas por editorial
  TreeRB<1000, ObraPoetica*> arbolObra;                           // Búsqueda rápida por IDOBRA

 public:
  // Agregar una obra (sin ediciones)
  void agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR, tipoObra obraTipo,
                   const std::string& nombre) {
    ObraPoetica* nueva = new ObraPoetica{IDAUTOR, obraTipo, nombre}; // Se crea la obra
    listaPorTipoPoesia.insertarClave(nueva, obraTipo);  // Se agrega a la lista por tipo
    listaPorIDAutor.insertarClave(nueva, IDAUTOR); // Se agrega a la lista por autor
    arbolObra.add(IDOBRA, nueva); // Se agrega al árbol por su ID
   
    // No se agrega a listaPorAnioPublicacion ni listaPorIDEditorial hasta que
    // tenga ediciones
  }

  // Eliminar una obra y actualizar todas las listas
  void eliminarObra(unsigned int IDOBRA) {
    ObraPoetica* del = arbolObra.getNodeKey(IDOBRA)->data;
    listaPorTipoPoesia.borrarClave(del->obra, del);
    listaPorIDAutor.borrarClave(del->IDAUTOR, del);
    // Eliminar de listas de ediciones
    int tam = del->ediciones.getTam();
    for (int i = 0; i < tam; ++i) {
      const datosEdiccion& ed = del->ediciones.get(i);
      listaPorIDEditorial.borrarClave(ed.IDEDITORIAL, del);
      if (ed.fechaDePublicacion.size() >= 10) {
        int anio = std::stoi(ed.fechaDePublicacion.substr(6, 4)); // Extrae año
        listaPorAnioPublicacion.borrarClave(anio, del);
      }
    }
    arbolObra.deleteKey(IDOBRA); // Se elimina del árbol
    delete del; // Se libera la memoria
  }

  // Modificar datos básicos de una obra (no ediciones)
  void modificarObra(unsigned int IDOBRA, unsigned int nuevoIDAUTOR,
                     tipoObra nuevoTipo, const std::string& nuevoNombre) {
    ObraPoetica* aux = arbolObra.getNodeKey(IDOBRA)->data;
   // Si el tipo cambia, se actualiza en listaPorTipoPoesia
    if (aux->obra != nuevoTipo) {
      listaPorTipoPoesia.borrarClave(aux->obra, aux);
      aux->obra = nuevoTipo;
      listaPorTipoPoesia.insertarClave(aux, aux->obra);
    }
   // Si el autor cambia, se actualiza en listaPorIDAutor
    if (aux->IDAUTOR != nuevoIDAUTOR) {
      listaPorIDAutor.borrarClave(aux->IDAUTOR, aux);
      aux->IDAUTOR = nuevoIDAUTOR;
      listaPorIDAutor.insertarClave(aux, aux->IDAUTOR);
    }
    aux->nombre = nuevoNombre; // Se actualiza el nombre
  }

  // Retorna una obra específica según su ID
  ObraPoetica const* buscarObra(unsigned int IDOBRA) {
    return arbolObra.getNodeKey(IDOBRA)->data;
  }

  // Agregar una edición a una obra y actualizar listas auxiliares
  void agregarEdicionAObra(unsigned int IDOBRA, const datosEdiccion& edicion) {
    ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
    obra->ediciones.insertarFinal(edicion);  // Se agrega la edición
    listaPorIDEditorial.insertarClave(obra, edicion.IDEDITORIAL);
    // Extraer año de la fecha (formato "dd/mm/aaaa")
    if (edicion.fechaDePublicacion.size() >= 10) {
      int anio = std::stoi(edicion.fechaDePublicacion.substr(6, 4));
      listaPorAnioPublicacion.insertarClave(obra, anio);
    }
  }

  // Eliminar una edición de una obra y actualizar listas auxiliares
  void eliminarEdicionDeObra(unsigned int IDOBRA, unsigned int numEdicion) {
    ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
    int tam = obra->ediciones.getTam();
    for (int i = 0; i < tam; ++i) {
      if (obra->ediciones.get(i).numeroEdicion == numEdicion) {
        unsigned int idEditorial = obra->ediciones.get(i).IDEDITORIAL;
        listaPorIDEditorial.borrarClave(idEditorial, obra);
        if (obra->ediciones.get(i).fechaDePublicacion.size() >= 10) {
          int anio =
              std::stoi(obra->ediciones.get(i).fechaDePublicacion.substr(6, 4));
          listaPorAnioPublicacion.borrarClave(anio, obra);
        }
        obra->ediciones.borrarPos(i); // Elimina del arreglo de ediciones
        break;
      }
    }
  }
  // Mostrar todas las obras guardadas
  void mostrarObras() {
    cout << "\n--- LISTA DE OBRAS ---\n";
    pila<ObraPoetica*> obras = arbolObra.inorden();
    while (!obras.PilaVacia()) {
      ObraPoetica* obra = obras.Pop();
      cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
           << " | Tipo: " << obra->obra << endl;
    }
  }

  // Mostrar todas las ediciones de todas las obras
  void mostrarTodasEdiciones() {
    cout << "\n--- TODAS LAS EDICIONES ---\n";
    pila<ObraPoetica*> obras = arbolObra.inorden();
    while (!obras.PilaVacia()) {
      ObraPoetica* obra = obras.Pop();
      cout << "Obra: " << obra->nombre << " (Autor: " << obra->IDAUTOR << ")\n";
      int tam = obra->ediciones.getTam();
      for (int i = 0; i < tam; ++i) {
        const datosEdiccion& ed = obra->ediciones.get(i);
        cout << "  Edicion #" << ed.numeroEdicion
             << ", Editorial: " << ed.IDEDITORIAL
             << ", Fecha: " << ed.fechaDePublicacion
             << ", Ciudad: " << ed.ciudadDePublicacion << endl;
      }
    }
  }
 // Muestra todas las obras de un autor por año y por editorial
  void mostrarObrasPorAutor(unsigned int IDAUTOR) {
    cout << "\n--- LISTA DE OBRAS POR AÑO ---\n";

    nodoOrd<ObraPoetica*, int>* auxAnio = listaPorAnioPublicacion.buscarPos(0);

    while (NULL != auxAnio) {
      ObraPoetica* obra = auxAnio->dato1;

      auxAnio = auxAnio->sig;

      if (obra->IDAUTOR != IDAUTOR) continue;

      cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
           << " | Tipo: " << obra->obra << " | Año: "
           << obra->ediciones.buscarPos(0)->dato1.fechaDePublicacion << endl;
    }

    nodoOrd<ObraPoetica*, unsigned int>* auxEdi =
        listaPorIDEditorial.buscarPos(0);

    cout << "\n--- LISTA DE OBRAS Editorial ---\n";
    while (NULL != auxEdi) {
      ObraPoetica* obra = auxEdi->dato1;

      auxEdi = auxEdi->sig;

      if (obra->IDAUTOR != IDAUTOR) continue;

      cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
           << " | Tipo: " << obra->obra << " | Editorial: "
           << obra->ediciones.buscarPos(0)->dato1.IDEDITORIAL << endl;
    }
  }
// Muestra todas las obras de un autor clasificadas por tipo
  void mostrarTiposObraPorAutor(unsigned int IDAUTOR) {
    cout << "\n--- LISTA DE OBRAS POR AÑO ---\n";

    nodoOrd<ObraPoetica*, tipoObra>* auxTipo = listaPorTipoPoesia.buscarPos(0);

    while (NULL != auxTipo) {
      ObraPoetica* obra = auxTipo->dato1;

      auxTipo = auxTipo->sig;

      if (obra->IDAUTOR != IDAUTOR) continue;

      cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
           << " | Tipo: " << obra->obra << " | Año: "
           << obra->ediciones.buscarPos(0)->dato1.fechaDePublicacion << endl;
// Muestra todas las ediciones de esa obra
      for (int i = 0; i < obra->ediciones.getTam(); i++) {
        const datosEdiccion& ed = obra->ediciones.get(i);
        cout << "  Edicion #" << ed.numeroEdicion
             << ", Editorial: " << ed.IDEDITORIAL
             << ", Fecha: " << ed.fechaDePublicacion
             << ", Ciudad: " << ed.ciudadDePublicacion << endl;
      }
    }
  }
// Devuelve todas las obras en pila
  pila<ObraPoetica*> getObras() {
    return arbolObra.inorden();
  }
// Devuelve todas las ediciones
  pila<datosEdiccion> getEdiciones() {
    pila<datosEdiccion> ediciones;
    pila<ObraPoetica*> obras = arbolObra.inorden();
    while (!obras.PilaVacia()) {
        ObraPoetica* obra = obras.Pop();
        int tam = obra->ediciones.getTam();
        for (int i = 0; i < tam; ++i) {
            ediciones.Push(obra->ediciones.get(i));
        }
    }
    return ediciones;
  }
  
 // Retorna las claves (IDOBRA) en orden ascendente
  pila<int> getClavesObras() {
    return arbolObra.inordenKeys();
     // Muestra obras de un autor que pertenecen a un tipo específico
  void mostrarTiposObraPorAutorYTipo(unsigned int IDAUTOR, tipoObra tipo) {
    cout << "\n--- TODAS LAS EDICIONES ---\n";
    pila<ObraPoetica*> obras = arbolObra.inorden();
    while (!obras.PilaVacia()) {
      ObraPoetica* obra = obras.Pop();

      if (obra->IDAUTOR != IDAUTOR) continue;
      if (obra->obra != tipo) continue;

      cout << "Obra: " << obra->nombre << " (Autor: " << obra->IDAUTOR << ")\n";
      int tam = obra->ediciones.getTam();
      for (int i = 0; i < tam; ++i) {
        const datosEdiccion& ed = obra->ediciones.get(i);
        cout << "  Edicion #" << ed.numeroEdicion
             << ", Editorial: " << ed.IDEDITORIAL
             << ", Fecha: " << ed.fechaDePublicacion
             << ", Ciudad: " << ed.ciudadDePublicacion << endl;
      }
    }
  }
  // Retorna el ID del autor de una obra específica
  unsigned int mostarIDAUTOR(unsigned int IDOBRA) {
    return buscarObra(IDOBRA)->IDAUTOR;
  }
};
