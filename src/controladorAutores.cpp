#include "controladorAutores.h" // Inclusión del archivo de cabecera correspondiente

#include <iostream> // Para entrada y salida estándar

using namespace std;
// Agrega un autor al sistema y lo inserta en todas las listas auxiliares y el árbol
void ControladorAutores::agregarAutor(datosAutor* autor) {
  listaPorCiudadResidencia.insertarClave(autor, autor->ciudadResidencia[0]);
  listaPorCiudadNacimiento.insertarClave(autor, autor->cidudadNacimiento[0]);
  listaPorPaisNacimiento.insertarClave(autor, autor->paisNacimiento[0]);
  listaPorAñoInicio.insertarClave(autor, autor->añoIncio);
  listaPorAñoPublicacion.insertarClave(autor, autor->añoPublicacion);
  listaPorFormacion.insertarClave(autor, autor->formacion);
  listaPorSexo.insertarClave(autor, autor->sexo);
  arbolAutor.add(autor->IDAUTOR, autor);
}
// Elimina un autor del sistema y actualiza todas las listas ordenadas

void ControladorAutores::eliminarAutor(unsigned int IDAUTOR) {
  datosAutor* del = arbolAutor.getNodeKey(IDAUTOR)->data;
  listaPorCiudadResidencia.borrarClave(del->ciudadResidencia[0], del);
  listaPorCiudadNacimiento.borrarClave(del->cidudadNacimiento[0], del);
  listaPorPaisNacimiento.borrarClave(del->paisNacimiento[0], del);
  listaPorAñoInicio.borrarClave(del->añoIncio, del);
  listaPorAñoPublicacion.borrarClave(del->añoPublicacion, del);
  listaPorFormacion.borrarClave(del->formacion, del);
  listaPorSexo.borrarClave(del->sexo, del);
  arbolAutor.deleteKey(del->IDAUTOR);
  delete del;
}
// Modifica un autor: actualiza listas auxiliares si cambian valores clave

void ControladorAutores::modificarAutor(
    unsigned int IDAUTOR, bool sexo, int añoInicio, int añoPublicacion,
    int fechaNacimiento[3], Formacion nuevaFormacion, std::string nombre,
    std::string Apellido, std::string ciudadResidencia,
    std::string paisNacimiento, std::string cidudadNacimiento) {
  datosAutor* aux = arbolAutor.getNodeKey(IDAUTOR)->data;

  if (aux->ciudadResidencia != ciudadResidencia) {
    listaPorCiudadResidencia.borrarClave(aux->ciudadResidencia[0], aux);
    aux->ciudadResidencia = ciudadResidencia;
    listaPorCiudadResidencia.insertarClave(aux, aux->ciudadResidencia[0]);
  }
  if (aux->cidudadNacimiento != cidudadNacimiento) {
    listaPorCiudadNacimiento.borrarClave(aux->cidudadNacimiento[0], aux);
    aux->cidudadNacimiento = cidudadNacimiento;
    listaPorCiudadNacimiento.insertarClave(aux, aux->cidudadNacimiento[0]);
  }
  if (aux->paisNacimiento != paisNacimiento) {
    listaPorPaisNacimiento.borrarClave(aux->paisNacimiento[0], aux);
    aux->paisNacimiento = paisNacimiento;
    listaPorPaisNacimiento.insertarClave(aux, aux->paisNacimiento[0]);
  }
  if (aux->añoIncio != añoInicio) {
    listaPorAñoInicio.borrarClave(aux->añoIncio, aux);
    aux->añoIncio = añoInicio;
    listaPorAñoInicio.insertarClave(aux, aux->añoIncio);
  }
  if (aux->añoPublicacion != añoPublicacion) {
    listaPorAñoPublicacion.borrarClave(aux->añoPublicacion, aux);
    aux->añoPublicacion = añoPublicacion;
    listaPorAñoPublicacion.insertarClave(aux, aux->añoPublicacion);
  }
  if (aux->formacion != nuevaFormacion) {
    listaPorFormacion.borrarClave(aux->formacion, aux);
    aux->formacion = nuevaFormacion;
    listaPorFormacion.insertarClave(aux, aux->formacion);
  }
  if (aux->sexo != sexo) {
    listaPorSexo.borrarClave(aux->sexo, aux);
    aux->sexo = sexo;
    listaPorSexo.insertarClave(aux, aux->sexo);
  }
  // Actualización de datos simples
  aux->nombre = nombre;
  aux->Apellido = Apellido;
  for (int i = 0; i < 3; ++i) aux->fechaNacimiento[i] = fechaNacimiento[i];
}
// Busca un autor por su ID y retorna un puntero constante

datosAutor const* ControladorAutores::buscarAutor(unsigned int IDAUTOR) {
  return arbolAutor.getNodeKey(IDAUTOR)->data;
}
// Muestra todos los autores registrados en el sistema

void ControladorAutores::mostrarAutores() {
  cout << "\n--- LISTA DE AUTORES ---\n";
  pila<datosAutor*> autores = arbolAutor.inorden();
  while (!autores.PilaVacia()) {
    datosAutor* autor = autores.Pop();
    cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
         << autor->Apellido << " | Sexo: " << (autor->sexo ? "M" : "F")
         << " | Ciudad residencia: " << autor->ciudadResidencia
         << " | Fecha de nacimiento: " << autor->fechaNacimiento[0] << "/"
         << autor->fechaNacimiento[1] << "/" << autor->fechaNacimiento[2]
         << endl;
  }
}
// Retorna todos los autores en forma de pila (inorden del árbol)
pila<datosAutor*> ControladorAutores::getAutores() {
  return arbolAutor.inorden();
}
// Muestra los datos completos de un autor específico
void ControladorAutores::mostrarAutor(unsigned int IDAUTOR) {
  cout << "\n--- DETALLES DEL AUTOR ---\n";
  datosAutor* autor = arbolAutor.getNodeKey(IDAUTOR)->data;
  cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
       << autor->Apellido << " | Sexo: " << (autor->sexo ? "M" : "F")
       << " | Ciudad residencia: " << autor->ciudadResidencia << endl;
}
// Muestra autores dados por una lista de ID, clasificados por ciudad y año de inicio
void ControladorAutores::mostrarAutoresEditorial(Lista<unsigned int>* IDAUTOR) {
  cout << "\n--- AUTORES POR CIUDAD DE RESIDENCIA ---\n";

  nodoOrd<datosAutor*, char>* auxRes = listaPorCiudadResidencia.buscarPos(0);
  while (auxRes != NULL) {
    datosAutor* autor = auxRes->dato1;
    auxRes = auxRes->sig;
    if (!IDAUTOR->tieneValor(autor->IDAUTOR)) continue;
    cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
         << autor->Apellido
         << " | Ciudad residencia: " << autor->ciudadResidencia << endl;
  }

  cout << "\n--- AUTORES POR AÑO DE INICIO ---\n";
  nodoOrd<datosAutor*, int>* auxAnioI = listaPorAñoInicio.buscarPos(0);
  while (auxAnioI != NULL) {
    datosAutor* autor = auxAnioI->dato1;
    auxAnioI = auxAnioI->sig;
    if (!IDAUTOR->tieneValor(autor->IDAUTOR)) continue;
    cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
         << autor->Apellido << " | Año inicio: " << autor->añoIncio << endl;
  }
}
// Muestra autores dentro de un rango de edad específico y con cierta formación
void ControladorAutores::mostrarAutoresPorRangoyFormacion(int rangoEdad[2],
                                                          Formacion formacion) {
  cout << "\n--- AUTORES POR EDAD Y FORMACIÓN ---\n";
  nodoOrd<datosAutor*, int>* auxRes = listaPorAñoPublicacion.buscarPos(0);
  while (auxRes != NULL) {
    datosAutor* autor = auxRes->dato1;
    auxRes = auxRes->sig;

    int edad = calcularEdadActual(autor->IDAUTOR);
    if (edad < rangoEdad[0] || edad > rangoEdad[1]) continue;
    if (autor->formacion != formacion) continue;

    cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
         << autor->Apellido << " | Edad: " << edad
         << " | Formación: " << static_cast<int>(autor->formacion) << endl;
  }
}
// Muestra autores por ciudad de nacimiento, según lista de ID autorizados
void ControladorAutores::mostrarAutoresPorCiudadNacimiento(
    Lista<unsigned int>* IDAUTOR) {
  cout << "\n--- AUTORES POR CIUDAD DE NACIMIENTO ---\n";
  nodoOrd<datosAutor*, char>* auxRes = listaPorCiudadNacimiento.buscarPos(0);
  while (auxRes != NULL) {
    datosAutor* autor = auxRes->dato1;
    auxRes = auxRes->sig;
    if (IDAUTOR->tieneValor(autor->IDAUTOR)) continue;
    cout << "ID: " << autor->IDAUTOR << " | Nombre: " << autor->nombre << " "
         << autor->Apellido
         << " | Ciudad nacimiento: " << autor->cidudadNacimiento << endl;
  }
}
// Calcula la edad actual del autor a partir de su fecha de nacimiento

int ControladorAutores::calcularEdadActual(int IDAUTOR) {
  datosAutor* autor = arbolAutor.getNodeKey(IDAUTOR)->data;

  time_t tiempoActual = time(nullptr);
  tm* fechaActual = localtime(&tiempoActual);

  int diaActual = fechaActual->tm_mday;
  int mesActual = fechaActual->tm_mon + 1;
  int anioActual = fechaActual->tm_year + 1900;

  int diaNac = autor->fechaNacimiento[0];
  int mesNac = autor->fechaNacimiento[1];
  int anioNac = autor->fechaNacimiento[2];

  int edad = anioActual - anioNac;
  if (mesActual < mesNac || (mesActual == mesNac && diaActual < diaNac)) {
    edad--;
  }
  return (edad < 0) ? 0 : edad;
}
