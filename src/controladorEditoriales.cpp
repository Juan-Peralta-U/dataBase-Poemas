#include "lista.h"
#include "datosEditorial.h"

class ControladorEditoriales {
private:
    Lista<datosEditorial> listaPorNombreEditorial;
    Lista<datosEditorial> listaPorNumPublicaciones; 

public:
    void agregarEditorial(const datosEditorial& editorial) {
        listaPorNombreEditorial.insertarFinal(editorial);
        listaPorNumPublicaciones.insertarFinal(editorial);
    }

    void listarEditorialesPorNombre() {
        listaPorNombreEditorial.imprimirLista();
    }
};
