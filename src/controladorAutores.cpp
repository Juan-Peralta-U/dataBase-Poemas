#include "lista.h"
#include "datosAutor.h"

class ControladorAutores {
private:
    Lista<datosAutor> listaPorCiudadResidencia;
    Lista<datosAutor> listaPorAñoInicio;
    Lista<datosAutor> listaPorAñoPublicacion;
    Lista<datosAutor> listaPorCiudadNacimiento;
    Lista<datosAutor> listaPorPaisNacimiento;

public:
    void agregarAutor(const datosAutor& autor) {
        // TODO: Insertar en las listas según los criterios
        listaPorCiudadResidencia.insertarFinal(autor);
        listaPorAñoInicio.insertarFinal(autor);
        listaPorAñoPublicacion.insertarFinal(autor);
        listaPorCiudadNacimiento.insertarFinal(autor);
        listaPorPaisNacimiento.insertarFinal(autor);
    }

    void listarAutoresPorCiudadResidencia() {
        listaPorCiudadResidencia.imprimirLista();
    }

    // Los demás métodos puedes agregarlos igual si necesitas
};
