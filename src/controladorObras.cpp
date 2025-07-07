#include "controladorObras.h"

#include <iostream>
#include <string>

using namespace std;
// Agrega una nueva obra poética al sistema
void ControladorObras::agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR,
                                   tipoObra obraTipo,
                                   const std::string& nombre) {
    // Crea el objeto obra
  ObraPoetica* nueva = new ObraPoetica{IDAUTOR, obraTipo, nombre};
    // Inserta en las listas ordenadas por tipo y por autor
  listaPorTipoPoesia.insertarClave(nueva, obraTipo);
  listaPorIDAutor.insertarClave(nueva, IDAUTOR);
    // Inserta en el árbol por ID de obra
  arbolObra.add(IDOBRA, nueva);
}
// Elimina una obra del sistema
void ControladorObras::eliminarObra(unsigned int IDOBRA) {
    // Se obtiene la obra a eliminar
  ObraPoetica* del = arbolObra.getNodeKey(IDOBRA)->data;
    // Se elimina de las listas ordenadas
  listaPorTipoPoesia.borrarClave(del->obra, del);
  listaPorIDAutor.borrarClave(del->IDAUTOR, del);
    // Se eliminan sus ediciones de otras listas
  int tam = del->ediciones.getTam();
  for (int i = 0; i < tam; ++i) {
    const datosEdiccion& ed = del->ediciones.get(i);
    listaPorIDEditorial.borrarClave(ed.IDEDITORIAL, del);
    if (ed.fechaDePublicacion.size() >= 10) {
      int anio = stoi(ed.fechaDePublicacion.substr(6, 4));
      listaPorAnioPublicacion.borrarClave(anio, del);
    }
  }
    // Se elimina del árbol y se libera memoria
  arbolObra.deleteKey(IDOBRA);
  delete del;
}
// Modifica una obra existente en el sistema
void ControladorObras::modificarObra(unsigned int IDOBRA,
                                     unsigned int nuevoIDAUTOR,
                                     tipoObra nuevoTipo,
                                     const std::string& nuevoNombre) {
  ObraPoetica* aux = arbolObra.getNodeKey(IDOBRA)->data;
  if (aux->obra != nuevoTipo) {
    listaPorTipoPoesia.borrarClave(aux->obra, aux);
    aux->obra = nuevoTipo;
    listaPorTipoPoesia.insertarClave(aux, aux->obra);
  }
    // Si cambia el tipo, actualiza la lista ordenada
  if (aux->IDAUTOR != nuevoIDAUTOR) {
    listaPorIDAutor.borrarClave(aux->IDAUTOR, aux);
    aux->IDAUTOR = nuevoIDAUTOR;
    listaPorIDAutor.insertarClave(aux, aux->IDAUTOR);
  }
    // Actualiza el nombre
  aux->nombre = nuevoNombre;
}
// Busca una obra por ID y retorna puntero constante
ObraPoetica const* ControladorObras::buscarObra(unsigned int IDOBRA) {
  return arbolObra.getNodeKey(IDOBRA)->data;
}
// Agrega una edición a una obra existente
void ControladorObras::agregarEdicionAObra(unsigned int IDOBRA,
                                           const datosEdiccion& edicion) {
  ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
  obra->ediciones.insertarFinal(edicion);
  // Si la obra ya fue marcada como con ediciones, no se vuelve a agregar
  if (obrasConEdiciones.getNodeKey(IDOBRA)->data) return;

  obrasConEdiciones.add(IDOBRA, 1);

  listaPorIDEditorial.insertarClave(obra, edicion.IDEDITORIAL);
  // Indexa por año si hay fecha válida
  if (edicion.fechaDePublicacion.size() >= 4) {
    int anio = stoi(edicion.fechaDePublicacion);
    listaPorAnioPublicacion.insertarClave(obra, anio);
  }
}
// Elimina una edición específica de una obra
void ControladorObras::eliminarEdicionDeObra(unsigned int IDOBRA,
                                             unsigned int numEdicion) {
  ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
  int tam = obra->ediciones.getTam();
  for (int i = 0; i < tam; ++i) {
    if (obra->ediciones.get(i).numeroEdicion == numEdicion) {
      unsigned int idEditorial = obra->ediciones.get(i).IDEDITORIAL;
      listaPorIDEditorial.borrarClave(idEditorial, obra);
      if (obra->ediciones.get(i).fechaDePublicacion.size() >= 10) {
        int anio = stoi(obra->ediciones.get(i).fechaDePublicacion.substr(6, 4));
        listaPorAnioPublicacion.borrarClave(anio, obra);
      }
            // Se elimina la edición de la lista de la obra
      obra->ediciones.borrarPos(i);
      break;
    }
  }
}
// Muestra todas las obras registradas
void ControladorObras::mostrarObras() {
  cout << "\n--- LISTA DE OBRAS ---\n";
  pila<ObraPoetica*> obras = arbolObra.inorden();
  while (!obras.PilaVacia()) {
    ObraPoetica* obra = obras.Pop();
    cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
         << " | Tipo: " << obra->obra << endl;
  }
}
// Muestra todas las ediciones registradas de todas las obras
void ControladorObras::mostrarTodasEdiciones() {
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
// Muestra las obras de un autor organizadas por año de publicación y editorial
void ControladorObras::mostrarObrasPorAutor(unsigned int IDAUTOR) {
  cout << "\n--- LISTA DE OBRAS POR AÑO ---\n";
  nodoOrd<ObraPoetica*, int>* auxAnio = listaPorAnioPublicacion.buscarPos(0);
  while (auxAnio != NULL) {
    ObraPoetica* obra = auxAnio->dato1;
    auxAnio = auxAnio->sig;

    if (obra->IDAUTOR != IDAUTOR) continue;
    cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
         << " | Tipo: " << obra->obra << " | Año: "
         << (obra->ediciones.getTam() > 0
                 ? obra->ediciones.get(0).fechaDePublicacion
                 : "N/A")
         << endl;
  }

  cout << "\n--- LISTA DE OBRAS Editorial ---\n";
  nodoOrd<ObraPoetica*, unsigned int>* auxEdi =
      listaPorIDEditorial.buscarPos(0);
  while (auxEdi != NULL) {
    ObraPoetica* obra = auxEdi->dato1;
    auxEdi = auxEdi->sig;
    if (obra->IDAUTOR != IDAUTOR) continue;
    cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
         << " | Tipo: " << obra->obra << " | Editorial: "
         << (obra->ediciones.getTam() > 0 ? obra->ediciones.get(0).IDEDITORIAL
                                          : 0)
         << endl;
  }
}
// Muestra todas las obras de un autor filtradas por tipo de poesía
void ControladorObras::mostrarTiposObraPorAutor(unsigned int IDAUTOR) {
  cout << "\n--- LISTA DE OBRAS POR AÑO ---\n";
  nodoOrd<ObraPoetica*, tipoObra>* auxTipo = listaPorTipoPoesia.buscarPos(0);
  while (auxTipo != NULL) {
    ObraPoetica* obra = auxTipo->dato1;
    auxTipo = auxTipo->sig;
    if (obra->IDAUTOR != IDAUTOR) continue;
    cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
         << " | Tipo: " << obra->obra << " | Año: "
         << (obra->ediciones.getTam() > 0
                 ? obra->ediciones.get(0).fechaDePublicacion
                 : "N/A")
         << endl;
    for (int i = 0; i < obra->ediciones.getTam(); i++) {
      const datosEdiccion& ed = obra->ediciones.get(i);
      cout << "  Edicion #" << ed.numeroEdicion
           << ", Editorial: " << ed.IDEDITORIAL
           << ", Fecha: " << ed.fechaDePublicacion
           << ", Ciudad: " << ed.ciudadDePublicacion << endl;
    }
  }
}
// Retorna una pila con todas las obras registradas (orden inorden)
pila<ObraPoetica*> ControladorObras::getObras() { return arbolObra.inorden(); }
// Retorna una pila con todas las ediciones registradas en el sistema
pila<datosEdiccion> ControladorObras::getEdiciones() {
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
// Retorna una pila con las claves (ID) de todas las obras
pila<int> ControladorObras::getClavesObras() { return arbolObra.inordenKeys(); }
// Muestra todas las obras de un autor filtradas por un tipo de poesía específico
void ControladorObras::mostrarTiposObraPorAutorYTipo(unsigned int IDAUTOR,
                                                     tipoObra tipo) {
  cout << "\n--- TODAS LAS EDICIONES ---\n";
  pila<ObraPoetica*> obras = arbolObra.inorden();
  while (!obras.PilaVacia()) {
    ObraPoetica* obra = obras.Pop();
    if (obra->IDAUTOR != IDAUTOR || obra->obra != tipo) continue;
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
// Retorna el ID del autor a partir del ID de obra
unsigned int ControladorObras::mostarIDAUTOR(unsigned int IDOBRA) {
  return buscarObra(IDOBRA)->IDAUTOR;
}
