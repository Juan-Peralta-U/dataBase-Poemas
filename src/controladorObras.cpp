#include <string>

#include "listaOrd.h"
#include "m_edicion.h"
#include "m_obrapoetica.h"
#include "pila.h"  // Asegúrate de incluir la definición de pila
#include "treeRB.h"

class ControladorObras {
 private:
  // Listas auxiliares para consultas eficientes
  ListaOrd<ObraPoetica*, int>
      listaPorAnioPublicacion;  // Para consultas por año
  ListaOrd<ObraPoetica*, tipoObra>
      listaPorTipoPoesia;  // Para consultas por tipo de poesía
  ListaOrd<ObraPoetica*, unsigned int>
      listaPorIDAutor;  // Para consultas por autor
  ListaOrd<ObraPoetica*, unsigned int>
      listaPorIDEditorial;              // Para consultas por editorial
  TreeRB<100, ObraPoetica*> arbolObra;  // Búsqueda rápida por IDOBRA

 public:
  // Agregar una obra (sin ediciones)
  void agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR, tipoObra obraTipo,
                   const std::string& nombre) {
    ObraPoetica* nueva = new ObraPoetica{IDAUTOR, obraTipo, nombre};
    listaPorTipoPoesia.insertarClave(nueva, obraTipo);
    listaPorIDAutor.insertarClave(nueva, IDAUTOR);
    arbolObra.add(IDOBRA, nueva);
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
        int anio = std::stoi(ed.fechaDePublicacion.substr(6, 4));
        listaPorAnioPublicacion.borrarClave(anio, del);
      }
    }
    arbolObra.deleteKey(IDOBRA);
    delete del;
  }

  // Modificar datos básicos de una obra (no ediciones)
  void modificarObra(unsigned int IDOBRA, unsigned int nuevoIDAUTOR,
                     tipoObra nuevoTipo, const std::string& nuevoNombre) {
    ObraPoetica* aux = arbolObra.getNodeKey(IDOBRA)->data;
    if (aux->obra != nuevoTipo) {
      listaPorTipoPoesia.borrarClave(aux->obra, aux);
      aux->obra = nuevoTipo;
      listaPorTipoPoesia.insertarClave(aux, aux->obra);
    }
    if (aux->IDAUTOR != nuevoIDAUTOR) {
      listaPorIDAutor.borrarClave(aux->IDAUTOR, aux);
      aux->IDAUTOR = nuevoIDAUTOR;
      listaPorIDAutor.insertarClave(aux, aux->IDAUTOR);
    }
    aux->nombre = nuevoNombre;
  }

  // Buscar una obra por ID
  ObraPoetica const* buscarObra(unsigned int IDOBRA) {
    return arbolObra.getNodeKey(IDOBRA)->data;
  }

  // Agregar una edición a una obra y actualizar listas auxiliares
  void agregarEdicionAObra(unsigned int IDOBRA, const datosEdiccion& edicion) {
    ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
    obra->ediciones.insertarFinal(edicion);
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
        obra->ediciones.borrarPos(i);
        break;
      }
    }
  }

  // Puedes agregar aquí métodos para consultas avanzadas usando las listas
  // auxiliares

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

      for (int i = 0; i < obra->ediciones.getTam(); i++) {
        const datosEdiccion& ed = obra->ediciones.get(i);
        cout << "  Edicion #" << ed.numeroEdicion
             << ", Editorial: " << ed.IDEDITORIAL
             << ", Fecha: " << ed.fechaDePublicacion
             << ", Ciudad: " << ed.ciudadDePublicacion << endl;
      }
    }
  }

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
  unsigned int mostarIDAUTOR(unsigned int IDOBRA) {
    return buscarObra(IDOBRA)->IDAUTOR;
  }
};
