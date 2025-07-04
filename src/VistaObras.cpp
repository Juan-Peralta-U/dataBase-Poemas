#include "VistaObras.h"

void v_agregarEdicion() {
  int IDeditorial;
  int fechaPublicacion[3];
  cout << "Ingrese datos de la primera EDICION\n";
  cout << "TODO: Aqui deberia salir una listado de "
          "editoriales\nIngrese el "
          "indice de la editorial";
  // TODO: buscar IDeditorial de una busqueda
  cin.get();

  cout << "Ingrese dia: ";
  cin >> fechaPublicacion[0];

  cout << "Ingrese mes: ";
  cin >> fechaPublicacion[1];

  cout << "Ingrese año: ";
  cin >> fechaPublicacion[2];
}

void v_agregarObras() {
  int IDautor;
  int tipoPoesia;
  string nombreObra;
  string ciudadPublicacion;

  cout << "Ingrese los siguiente datos.\n"
          "Nombre obra: ";
  cin >> nombreObra;

  cout << "0: Decima\n1: Soneto\n2: Himno\n3: Haiku\n4: Romance\n5: "
          "OctavaReal\n"
          "6: Lira\n7: VersoLibre\n"
       << "Tipo de poesia: ";
  cin >> tipoPoesia;

  cout << "TODO: Aqui deberia salir una listado de autores\nIngrese el "
          "indice del autor";
  // TODO: obtener IDAUTOR de una busqueda
  cin.get();
}

void eliminarObras() {}
