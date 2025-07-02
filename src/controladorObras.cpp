#include "lista.h"
#include "treeRB.h"
#include "obraPoetica.h"

class ControladorObras {
private:
    Lista<ObraPoetica> listaOrdenadaPorAnioPublicacion;
    TreeRB<100, ObraPoetica> arbolPorIDAutor; // Clave = IDAUTOR

public:
    void agregarObra(const ObraPoetica& obra) {
        // Aqui hay q insertar en la lista en orden por año (a implementar)
        listaOrdenadaPorAnioPublicacion.insertarFinal(obra);
        arbolPorIDAutor.add(obra.IDAUTOR, obra);
    }

    void listarObras() {
        listaOrdenadaPorAnioPublicacion.imprimirLista();
    }
};
