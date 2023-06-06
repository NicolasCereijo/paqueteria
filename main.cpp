#include <iostream>
#include <ctime>
#include <sstream>
#include <math.h>
#include <iomanip>
#include "definiciones.h"
#include "metodos.cpp"

using namespace std;

int main(){
    Lista almacen;
    Lista raiz;
    Arbol sistema;
    int cantidadDeCentrales = 0;
    int codigosCentrales[maximoCentralesPermitido + 1];
    string nombresCentrales[maximoCentralesPermitido + 1] = {"Coslada", "Meco",
    "Alcala", "Torrejon", "Garena", "Vicalvaro", "Vallecas", "Guadalajara"};
    int paquetesTotales = paquetesIniciales;

    raiz.codigo = codigoRaizSistema;
    sistema.Insertar(raiz);
    sistema.contador++;
    codigosCentrales[cantidadDeCentrales] = codigoRaizSistema;
    cantidadDeCentrales++;

    srand(time(NULL));

    for(int i = 1; i < centralesIniciales; i++){
        Lista centralPaqueteria = sistema.generarCentralPaqueteria(true);
        centralPaqueteria.nombre = nombresCentrales[i];

        sistema.Insertar(centralPaqueteria);
        sistema.contador++;

        codigosCentrales[cantidadDeCentrales] = centralPaqueteria.codigo;
        cantidadDeCentrales++;
    }

    for(int i = 0; i < paquetesIniciales; i++)
        almacen.insertarNodo(generarPaquete(cantidadDeCentrales, codigosCentrales));

    cout << endl << "Bienvenido usuario, el estado actual del sistema es:" << endl;
    cout << endl << "   - Paquetes totales en el sistema: " << paquetesIniciales << endl;
    cout << "   - Numero de centrales de paqueteria: " << centralesIniciales << endl;

    cout << "       - ";
    for(int i = 0; i < cantidadDeCentrales; i++){
        cout << nombresCentrales[i] << "   ";

        if(i != 0 && i != cantidadDeCentrales - 1 && (i + 1) % 4 == 0)
            cout << endl << "       - ";
    }
    cout << endl;

    cout << "   - Limite minimo de centrales de paqueteria: 1" << endl;
    cout << "   - Limite maximo de centrales de paqueteria: " << maximoCentralesPermitido << endl;
    cout << "   - Codigo de la central raiz (central permanente): " << codigoRaizSistema << endl;
    cout << "   - Cantidad de furgonetas que se envian por ciclo: " << furgonetasPorCiclo << endl;

    char eleccion = -1;
    while (eleccion != 0){
        eleccion = 0;

        cout << endl << " Menu de opciones, introduzca la operacion que desee realizar:" << endl << endl;
        cout << "   1. Consultar contenido del almacen principal" << endl;
        cout << "   2. Mostrar sistema de centrales de paqueteria" << endl;
        cout << "   3. Insertar nueva central de paqueteria en el sistema" << endl;
        cout << "   4. Eliminar una central de paqueteria del sistema" << endl;
        cout << "   5. Mostrar los paquetes a distribuir en una central de paqueteria" << endl;
        cout << "   6. Mostrar estadisticas" << endl;
        cout << "   7. Buscar paquete" << endl;
        cout << "   8. Eliminar paquete" << endl;
        cout << "   9. Distribuir paquete de forma manual" << endl;
        cout << "   a. Trasladar paquete entre centrales de paqueteria" << endl;
        cout << "   b. Distribuir paquetes de forma automatica" << endl;
        cout << "   c. Recibir nuevo cargamento en el almacen principal" << endl;
        cout << "   0. Cerrar programa" << endl << endl;

        cin >> eleccion;
        fflush(stdin);

        switch (eleccion){
            case '1':
                {
                    cout << endl << " Almacen principal:" << endl << endl;

                    pintarCabecera();
                    almacen.recorrerLista();

                    break;
                }

            case '2':
                {
                    cout << endl << " Contenido del sistema por niveles:" << endl << endl;
                    cout << "   Nivel 1: ";

                    for(int central = 0, nivelActual = 2; central < cantidadDeCentrales; central++){
                        cout << nombresCentrales[central] << ": " << codigosCentrales[central] << "   ";

                        if(!(central + 1 == cantidadDeCentrales) && cambiarDeNivel(central)){
                            cout << endl << "   Nivel " << nivelActual << ": ";
                            nivelActual++;
                        }
                    }
                    cout << endl << endl;

                    break;
                }

            case '3':
                {
                    if(cantidadDeCentrales == maximoCentralesPermitido){
                        cout << endl << " El sistema no puede almacenar mas centrales de paqueteria" << endl;
                    } else {
                        Lista centralPaqueteria = sistema.generarCentralPaqueteria(false);

                        sistema.Insertar(centralPaqueteria);
                        sistema.contador++;

                        codigosCentrales[cantidadDeCentrales] = centralPaqueteria.codigo;
                        cantidadDeCentrales++;

                        nombresCentrales[cantidadDeCentrales - 1] = centralPaqueteria.nombre;

                        cout << endl << " En el sistema hay " << sistema.contador << " centrales de paqueteria" << endl;
                        cout << " El codigo de la nueva central de paqueteria es: " << centralPaqueteria.codigo << endl << endl;
                    }

                    break;
                }

            case '4':
                {
                    int codigo;

                    cout << endl << " Inserte el codigo de la central que desee eliminar:" << endl;
                    cin >> codigo;
                    fflush(stdin);

                    if(codigo == 500)
                        cout << endl << " No se puede eliminar la central principal" << endl;
                    else if(sistema.Buscar(codigo)){
                        while(almacen.buscarPaquete(codigo)){
                            almacen.borrarNodo(codigo);
                            paquetesTotales--;
                        }

                        paquetesTotales -= sistema.Devolver(codigo) -> lista.cantidad;
                        sistema.Borrar(codigo);

                        for(int i = 0; i < maximoCentralesPermitido; i++){
                            if(codigosCentrales[i] == codigo){
                                for(int j = i; j < maximoCentralesPermitido; j++){
                                    if(codigosCentrales[j] + 1 == maximoCentralesPermitido){
                                        codigosCentrales[j] = NULL;
                                        nombresCentrales[j] = "";
                                    } else {
                                        codigosCentrales[j] = codigosCentrales[j + 1];
                                        nombresCentrales[j] = nombresCentrales[j + 1];
                                    }
                                }
                                i = maximoCentralesPermitido;
                            }
                        }
                        cantidadDeCentrales--;

                        cout << endl << " Central eliminada satisfactoriamente" << endl;
                    }
                    else
                        cout << endl << " Central no encontrada" << endl;

                    break;
                }

            case '5':
                {
                    int codigo;
                    cout << endl << " Inserte el codigo de la central que desee consultar:" << endl;
                    cin >> codigo;
                    fflush(stdin);

                    if(sistema.Buscar(codigo)){
                        pintarCabecera();

                        sistema.Devolver(codigo) -> lista.recorrerLista();
                    } else
                        cout << endl << " Central no encontrada" << endl;

                    break;
                }

            case '6':
                {
                    cout << endl << " Estadisticas:" << endl;
                    cout << endl << "   - Cantidad de centrales de paqueteria: " << cantidadDeCentrales << endl;
                    cout << "   - Paquetes totales en circulacion: " << paquetesTotales << endl;
                    cout << "   - Paquetes en el almacen general: " << almacen.cantidad << endl;
                    cout << "   - Paquetes en el sistema de centrales: " << paquetesTotales - almacen.cantidad << endl;
                    cout << "       - ";

                    for(int i = 0; i < cantidadDeCentrales; i++){
                        cout << nombresCentrales[i] << ": " << sistema.Devolver(codigosCentrales[i]) -> lista.cantidad << "   ";

                        if(i != 0 && i != cantidadDeCentrales - 1 && (i + 1) % 4 == 0)
                            cout << endl << "       - ";
                    }
                    cout << endl;

                    int columnaMax = 0;
                    for(int i = 0; i < cantidadDeCentrales; i++){
                        if(columnaMax < sistema.Devolver(codigosCentrales[i]) -> lista.cantidad)
                            columnaMax = sistema.Devolver(codigosCentrales[i]) -> lista.cantidad;
                    }
                    cout << endl << "   - Grafico de los paquetes por zona:" << endl << endl;

                    for(int i = columnaMax; i >= 1; i--){
                        cout << " " << setw(posicionesNumeroMayor) << i << " |          ";

                        for(int j = 0; j < cantidadDeCentrales; j++){
                            if(sistema.Devolver(codigosCentrales[j]) -> lista.cantidad == i)
                                cout << "_______          ";
                            else if(sistema.Devolver(codigosCentrales[j]) -> lista.cantidad  > i)
                                cout << "|     |          ";
                            else
                                cout << "                 ";
                        }
                        cout << endl;
                    }

                    cout << "   0 |----";
                    for(int i = 0; i < cantidadDeCentrales; i++)
                        cout << "-----------------";

                    cout << endl << "   ";
                    for(int i = 0; i < cantidadDeCentrales; i++)
                        cout << "              " << setw(posicionesNumeroMayor) << sistema.Devolver(codigosCentrales[i]) -> lista.cantidad;
                    cout << endl;

                    cout << endl << "   - Orden: ";
                    for(int i = 0; i < cantidadDeCentrales; i++){
                        cout << nombresCentrales[i];
                        if(i != cantidadDeCentrales - 1)
                            cout << " / ";
                    }
                    cout << endl;

                    break;
                }

            case '7':
                {
                    string ID;
                    bool encontrado = false;

                    cout << endl << " Inserte el ID del paquete que desee buscar:" << endl;
                    cin >> ID;
                    fflush(stdin);

                    if(almacen.buscarPaquete(ID)){
                        cout << endl << " El paquete se encuentra en el almacen" << endl;

                        encontrado = true;
                    } else {
                        for(int i = 0; i < cantidadDeCentrales; i++){
                            if(sistema.Devolver(codigosCentrales[i]) -> lista.buscarPaquete(ID)){
                                cout << endl << " El paquete se encuentra en la central: "
                                << sistema.Devolver(codigosCentrales[i]) -> lista.codigo << endl;

                                encontrado = true;
                            }
                        }
                    }

                    if(!encontrado)
                        cout << endl << " El paquete no se encuentra en el sistema" << endl;

                    break;
                }

            case '8':
                {
                    string ID;
                    bool encontrado = false;

                    cout << endl << " Inserte el ID del paquete que desee eliminar:" << endl;
                    cin >> ID;
                    fflush(stdin);

                    if(almacen.buscarPaquete(ID)){
                        almacen.borrarNodo(ID);

                        cout << endl << " El paquete ha sido eliminado del almacen" << endl;

                        encontrado = true;
                    } else {
                        for(int i = 0; i < cantidadDeCentrales; i++){
                            if(sistema.Devolver(codigosCentrales[i]) -> lista.buscarPaquete(ID)){
                                sistema.Devolver(codigosCentrales[i]) -> lista.borrarNodo(ID);

                                cout << endl << " El paquete ha sido eliminado de la central: "
                                << sistema.Devolver(codigosCentrales[i]) -> lista.codigo << endl;

                                encontrado = true;
                            }
                        }
                    }

                    if(!encontrado)
                        cout << endl << " El paquete no se encuentra en el sistema" << endl;

                    break;
                }

            case '9':
                {
                    string ID;
                    int destino;

                    cout << endl << " Introduzca el ID del paquete que desee repartir:" << endl;
                    cin >> ID;
                    fflush(stdin);

                    if(almacen.buscarPaquete(ID)){
                        cout << endl << " Introduzca el codigo de la zona a la que desee enviar el paquete:" << endl;
                        cin >> destino;
                        fflush(stdin);

                        if(sistema.Buscar(destino)){
                            sistema.Devolver(destino) -> lista.insertarNodo(almacen.devolverPaquete(ID));
                            almacen.borrarNodo(ID);

                            cout << endl << " El paquete ha sido trasladado desde el almacen principal a la central con codigo "
                            << destino << endl;
                        } else
                                cout << endl << " No hay ninguna central con ese codigo en el sistema" << endl;
                    } else
                        cout << endl << " No hay ningun paquete con ese ID en el almacen principal" << endl;
                    break;
                }

            case 'a':
                {
                    string ID;
                    int destino;
                    int origen;
                    bool encontrado = false;

                    cout << endl << " Introduzca el ID del paquete que desee trasladar:" << endl;
                    cin >> ID;
                    fflush(stdin);

                    for(int i = 0; i < cantidadDeCentrales; i++){
                        if(sistema.Devolver(codigosCentrales[i]) -> lista.buscarPaquete(ID)){
                            origen = sistema.Devolver(codigosCentrales[i]) -> lista.codigo;
                            encontrado = true;
                        }
                    }

                    if(encontrado){
                        cout << endl << " Introduzca el codigo de la zona a la que desee enviar el paquete:" << endl;
                        cin >> destino;
                        fflush(stdin);

                        if(sistema.Buscar(destino)){
                            sistema.Devolver(destino) -> lista.insertarNodo(sistema.Devolver(origen) -> lista.devolverPaquete(ID));
                            sistema.Devolver(origen) -> lista.borrarNodo(ID);

                            cout << endl << " El paquete ha sido trasladado desde la central con codigo " << origen
                            << " a la central con codigo " << destino << endl;
                        } else
                                cout << endl << " No hay ninguna central con ese codigo en el sistema" << endl;
                    } else
                        cout << endl << " No hay ningun paquete con ese ID en ninguna central" << endl;
                    break;
                }

            case 'b':
                {
                    cout << endl << " Se envian " << furgonetasPorCiclo << " furgonetas con " << capacidadFurgoneta
                    << " paquetes cada una, si el almacen puede suministralos" << endl << endl;

                    for(int i = 0; i < furgonetasPorCiclo; i++){
                        Lista furgoneta;

                        if(almacen.cantidad >= capacidadFurgoneta){
                            for(int j = 0; j < capacidadFurgoneta; j++){
                                sistema.Devolver(almacen.cabeza -> paq.codigo) -> lista.insertarNodo(almacen.cabeza -> paq);

                                furgoneta.insertarNodo(almacen.cabeza -> paq);

                                almacen.borrarNodo(almacen.cabeza -> paq.ID);
                            }

                            furgoneta.recorrerFurgoneta();
                            cout << endl;
                        } else {
                            if(almacen.cantidad > 0){
                                for(int j = 0; j <= almacen.cantidad; j++){
                                    sistema.Devolver(almacen.cabeza -> paq.codigo) -> lista.insertarNodo(almacen.cabeza -> paq);

                                    furgoneta.insertarNodo(almacen.cabeza -> paq);

                                    almacen.borrarNodo(almacen.cabeza -> paq.ID);
                                }

                                furgoneta.recorrerFurgoneta();
                                cout << endl;
                            } else {
                                cout << endl << " El almacen principal se ha vaciado por completo, no quedan paquetes por repartir" << endl;

                                i = furgonetasPorCiclo;
                            }
                        }
                    }
                    break;
                }

            case 'c':
                {
                    for(int i = 0; i < paquetesIniciales; i++){
                        almacen.insertarNodo(generarPaquete(cantidadDeCentrales, codigosCentrales));
                        paquetesTotales++;
                    }

                    break;
                }

            case '0':
                {
                    cout << " Sesion finalizada" << endl;
                    eleccion = 0;

                    break;
                }
        }
    }
}
