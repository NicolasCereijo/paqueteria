#ifndef DEFINICIONES_H_INCLUDED
#define DEFINICIONES_H_INCLUDED

#define centralesIniciales 8
#define paquetesIniciales 100
#define capacidadFurgoneta 5
#define furgonetasPorCiclo 3
#define codigoRaizSistema 500
#define maximoCentralesPermitido 15
#define posicionesNumeroMayor 3

using namespace std;

//ESTRUCTURAS DE DATOS

struct coordenadas{
    int gradosLatitud;
    int minutosLatitud;
    int segundosLatitud;

    int gradosLongitud;
    int minutosLongitud;
    int segundosLongitud;

    coordenadas generarCoordenadas();
};

struct paquete{
    string ID;
    int codigo;
    string codigoString;
    coordenadas coord;
    string latitud;
    string longitud;
    int urgencia;
    string DNI;

    paquete generarPaquete(int cantidadDeCodigos, int codigos[]);
};

//CLASES PARA LAS LISTAS QUE TRABAJAN CON PAQUETES

class Nodo{
    private:
        Nodo *siguiente;
        friend class Lista;

    public:
        paquete paq;
        Nodo(paquete p, Nodo *sig = NULL){
            paq = p;
            siguiente = sig;
        }
};

typedef Nodo *pNodo;

class Lista{
    public:
        pNodo cabeza, actual, final;
        int cantidad = 0;
        int codigo;
        string nombre;
        Lista(){
            cabeza = actual = final = NULL;
        }
        ~Lista();
        void insertarNodo(paquete p);
        void borrarNodo(string ID);
        void borrarNodo(int codigo);
        bool listaVacia();
        void esCabeza();
        void esFinal();
        void esSiguiente();
        bool esActual();
        paquete valorActual();
        void recorrerLista();
        void recorrerFurgoneta();
        bool buscarPaquete(string ID);
        bool buscarPaquete(int codigo);
        paquete devolverPaquete(string ID);
};

//CLASES PARA LOS ÁRBOLES

class NodoArbol{
    private:
        NodoArbol *izquierdo;
        NodoArbol *derecho;
        friend class Arbol;

    public:
        Lista lista;
        NodoArbol(const Lista l, NodoArbol *izq = NULL, NodoArbol *der = NULL):
            lista(l), izquierdo(izq), derecho(der){}
};
typedef NodoArbol *pNodoArbol;

class Arbol{
    private:
        pNodoArbol actual;

    public:
        pNodoArbol raiz;
        int contador = 0;
        Arbol():
            raiz(NULL), actual(NULL){}
        void Insertar(Lista l);
        void Borrar(int codigo);
        bool Buscar(int codigo);
        pNodoArbol Devolver(int codigo);
        Lista generarCentralPaqueteria(bool nombreAutomatico);
        bool Vacio(pNodoArbol r){
            return r == NULL;
        }
        bool EsHoja(pNodoArbol r){
            return !r -> derecho && !r -> izquierdo;
        }
};

//MÉTODOS AUXILIARES

string generarID();
string generarDNI();
string generarNumero(int n);
string generarCadena(int n);
string mostrarLatitud(paquete p);
string mostrarLongitud(paquete p);
void pintarCabecera();
bool cambiarDeNivel(int central);

#endif // DEFINICIONES_H_INCLUDED
