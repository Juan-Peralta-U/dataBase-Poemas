#include <string>

#include "lista.h"
#include "listaOrd.h"
#include "m_obrapoetica.h"
#include "treeRB.h"

class ControladorObras {
 private:
  ListaOrd<ObraPoetica*, int> listaPorAnioPublicacion;
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDAutor;
  ListaOrd<ObraPoetica*, tipoObra> listaPorTipoPoesia;
  ListaOrd<ObraPoetica*, unsigned int> listaPorIDEditorial;
  TreeRB<100, ObraPoetica*> arbolObra;  // Clave = IDOBRA

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

  void agregarEdicionAObra(unsigned int IDOBRA, const datosEdiccion& edicion) {
    ObraPoetica* obra = arbolObra.getNodeKey(IDOBRA)->data;
    obra->ediciones.insertarFinal(edicion);
    listaPorIDEditorial.insertarClave(obra, edicion.IDEDITORIAL);
    // Si quieres clasificar por año, extrae el año de
    // edicion.fechaDePublicacion (formato "dd/mm/aaaa")
    if (edicion.fechaDePublicacion.size() >= 10) {
      int anio = std::stoi(edicion.fechaDePublicacion.substr(6, 4));
      listaPorAnioPublicacion.insertarClave(obra, anio);
    }
  }

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

  std::string dataParse() {
    if (listaPorIDAutor.listaVacia()) return "No hay ninguna obra";

    nodoOrd<ObraPoetica*, unsigned int>* aux = listaPorIDAutor.buscarPos(0);

    std::string ret;

    for (int i = 0; i < listaPorIDAutor.getSize(); i++) {
      /*
      Datos de la obra poética.
          • Nombre del documento
          • Tipo de poesía: décima, soneto, himno, haiku, romance, octava
      real, lira, verso libre. • ID del autor. • Listado de las ediciones
      */
      ret = i + ":\n" + "Titulo: " + aux->dato1->nombre +
            "\nTipo de Poesia: " + tiposPoema[aux->dato1->obra] +
            "\nTODO: Parse Autor"
            "\n---------------------------------------------\n";
    }

    return "ret";
  }
};
