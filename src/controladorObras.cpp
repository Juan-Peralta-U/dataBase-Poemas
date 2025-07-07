#include "controladorObras.h"

#include <iostream>
#include <string>

using namespace std;

void ControladorObras::agregarObra(unsigned int IDOBRA, unsigned int IDAUTOR,
                                   tipoObra obraTipo,
                                   const std::string& nombre) {
  ObraPoetica* nueva = new ObraPoetica{IDAUTOR, obraTipo, nombre};
  listaPorTipoPoesia.insertarClave(nueva, obraTipo);
  listaPorIDAutor.insertarClave(nueva, IDAUTOR);
  arbolObra.add(IDOBRA, nueva);
}

void ControladorObras::eliminarObra(unsigned int IDOBRA) {
  ObraPoetica* del = arbolObra.getNodeKey(IDOBRA)->data;
  listaPorTipoPoesia.borrarClave(del->obra, del);
  listaPorIDAutor.borrarClave(del->IDAUTOR, del);
  int tam = del->ediciones.getTam();
  for (int i = 0; i < tam; ++i) {
    const datosEdiccion& ed = del->ediciones.get(i);
    listaPorIDEditorial.borrarClave(ed.IDEDITORIAL, del);
    if (ed.fechaDePublicacion.size() >= 10) {
      int anio = stoi(ed.fechaDePublicacion.substr(6, 4));
      listaPorAnioPublicacion.borrarClave(anio, del);
    }
  }
  arbolObra.deleteKey(IDOBRA);
  delete del;
}

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
  if (aux->IDAUTOR != nuevoIDAUTOR) {
    listaPorIDAutor.borrarClave(aux->IDAUTOR, aux);
    aux->IDAUTOR = nuevoIDAUTOR;
    listaPorIDAutor.insertarClave(aux, aux->IDAUTOR);
  }
  aux->nombre = nuevoNombre;
}

ObraPoetica const* ControladorObras::buscarObra(unsigned int IDOBRA) {
  return arbolObra.getNodeKey(IDOBRA)->data;
}

void ControladorObras::agregarEdicionAObra(unsigned int IDOBRA,
                                           const datosEdiccion& edicion) {
  ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
  obra->ediciones.insertarFinal(edicion);

  if (obrasConEdiciones.getNodeKey(IDOBRA)->data) return;

  obrasConEdiciones.add(IDOBRA, 1);

  listaPorIDEditorial.insertarClave(obra, edicion.IDEDITORIAL);

  if (edicion.fechaDePublicacion.size() >= 4) {
    int anio = stoi(edicion.fechaDePublicacion);
    listaPorAnioPublicacion.insertarClave(obra, anio);
  }
}

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
      obra->ediciones.borrarPos(i);
      break;
    }
  }
}

void ControladorObras::mostrarObras() {
  cout << "\n--- LISTA DE OBRAS ---\n";
  pila<ObraPoetica*> obras = arbolObra.inorden();
  while (!obras.PilaVacia()) {
    ObraPoetica* obra = obras.Pop();
    cout << "Autor: " << obra->IDAUTOR << " | Nombre: " << obra->nombre
         << " | Tipo: " << obra->obra << endl;
  }
}

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

pila<ObraPoetica*> ControladorObras::getObras() { return arbolObra.inorden(); }

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

pila<int> ControladorObras::getClavesObras() { return arbolObra.inordenKeys(); }

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

unsigned int ControladorObras::mostarIDAUTOR(unsigned int IDOBRA) {
  return buscarObra(IDOBRA)->IDAUTOR;
}
