using namespace std;

//MÉTODOS DE LISTAS

Lista::~Lista(){
    pNodo aux;
    while(cabeza){
        aux = cabeza;
        cabeza = cabeza -> siguiente;
        delete aux;
    }
    actual = NULL;
}

void Lista::insertarNodo(paquete p){
    pNodo aux;

    if (listaVacia()){
        cabeza = new Nodo(p, NULL);
        final = cabeza;
    } else {
        aux = new Nodo(p, NULL);
        final -> siguiente = aux;
        final = aux;
    }
    cantidad++;
}

void Lista::borrarNodo(string ID){
    pNodo anterior;
    actual = cabeza;

    while (actual -> paq.ID != ID && (actual -> siguiente) != NULL){
        anterior = actual;
        actual = actual -> siguiente;
    }
    if(actual -> paq.ID == ID){
        if(actual == cabeza)
            cabeza = actual -> siguiente;
        else {
            anterior -> siguiente = actual -> siguiente;
            if(actual == final)
                final = anterior;
        }

        actual -> siguiente = NULL;
        delete actual;
        cantidad--;
    }
}

void Lista::borrarNodo(int codigo){
    pNodo anterior;
    actual = cabeza;

    while (actual -> paq.codigo != codigo && (actual -> siguiente) != NULL){
        anterior = actual;
        actual = actual -> siguiente;
    }
    if(actual -> paq.codigo == codigo){
        if(actual == cabeza)
            cabeza = actual -> siguiente;
        else {
            anterior -> siguiente = actual -> siguiente;
            if(actual == final)
                final = anterior;
        }

        actual -> siguiente = NULL;
        delete actual;
        cantidad--;
    }
}

bool Lista::listaVacia(){
    return cabeza == NULL;
}

void Lista::esCabeza(){
    actual = cabeza;
}

void Lista::esFinal(){
    actual = final;
}

void Lista::esSiguiente(){
    if(actual)
        actual = actual -> siguiente;
}

bool Lista::esActual(){
    return actual != NULL;
}

paquete Lista::valorActual(){
    return actual -> paq;
}

void Lista::recorrerLista(){
    pNodo aux;
    aux = cabeza;
    int n = 0;

    while(aux){
        n++;

        cout << "| " << aux -> paq.ID << " | " << aux -> paq.codigoString << "    | " << aux -> paq.latitud << " | " << aux-> paq.longitud;
        cout << " | " << aux -> paq.urgencia << "    | " << aux -> paq.DNI << " |   ";

        if(n%4 == 0){
            cout << endl;
            cout << "|---------|--------|--------------|--------------|------|-----------|   ";
            cout << "|---------|--------|--------------|--------------|------|-----------|   ";
            cout << "|---------|--------|--------------|--------------|------|-----------|   ";
            cout << "|---------|--------|--------------|--------------|------|-----------|" << endl;
        }

        aux = aux -> siguiente;
    }
    cout << endl;
}

void Lista::recorrerFurgoneta(){
    pNodo aux;
    aux = cabeza;
    int anchoPuerta = 0;

    //A parte de pintar la tabla con la información añadimos una presentación extra para hacerlo más visual
    cout << " /--------|--------|-----------------------------|------|----------\\" << endl;
    cout << "|---------|--------|-----------------------------|------|-----------|--------------------\\" << endl;
    cout << "|         |        |         COORDENADAS         |      |           | |------------\\  \\---\\" << endl;
    cout << "|   ID    | CODIGO |-----------------------------| TIPO |    DNI    | ||-----------\\\\  \\   \\" << endl;
    cout << "|         |        |   LATITUD    |   LONGITUD   |      |           | ||            \\\\  \\   \\" << endl;
    cout << "|---------|--------|--------------|--------------|------|-----------| ||             \\\\  \\   \\" << endl;

    for(int i = 0; i < capacidadFurgoneta; i++){
        if(i < capacidadFurgoneta / 2){
            if(!aux)
                cout << "|         |        |              |              |      |           | ||" << setw(16 + i * 2)
                << "\\\\" << "  \\   " << "\\" << endl;
            else {
                cout << "| " << aux -> paq.ID << " | " << aux -> paq.codigoString << "    | " << aux -> paq.latitud;
                cout << " | " << aux -> paq.longitud << " | " << aux -> paq.urgencia << "    | " << aux -> paq.DNI
                << " | ||" << setw(16 + i * 2) << "\\\\" << "  \\   " << "\\" << endl;
            }

            cout << "|---------|--------|--------------|--------------|------|-----------| ||" << setw(17 + i * 2)
            << "\\\\" << "  \\   " << "\\" << endl;

            anchoPuerta = 19 + i * 2;

        } else if(i < capacidadFurgoneta / 2 + 1){
            if(!aux)
                cout << "|         |        |              |              |      |           | ||";
            else {
                cout << "| " << aux -> paq.ID << " | " << aux -> paq.codigoString << "    | " << aux -> paq.latitud;
                cout << " | " << aux -> paq.longitud << " | " << aux -> paq.urgencia << "    | " << aux -> paq.DNI << " | ||";
            }

            for(int j = 0; j < anchoPuerta - 3; j++)
                cout << "-";

            cout << "\\|  \\---|" << endl;

            cout << "|---------|--------|--------------|--------------|------|-----------| | ____" << setw(anchoPuerta - 5)
            << "|" << "   ___" << "|" << endl;
        } else if((i >= capacidadFurgoneta / 2 + 1) && i != capacidadFurgoneta - 1){
            if(!aux){
                    cout << "|         |        |              |              |      |           | |" << setw(anchoPuerta)
                    << "|" << "  |   " << "|" << endl;
            } else {
                cout << "| " << aux -> paq.ID << " | " << aux -> paq.codigoString << "    | " << aux -> paq.latitud;
                cout << " | " << aux -> paq.longitud << " | " << aux -> paq.urgencia << "    | " << aux -> paq.DNI << " | |"
                << setw(anchoPuerta) << "|" << "  |   " << "|" << endl;
            }

            cout << "|---------|--------|--------------|--------------|------|-----------| |"
            << setw(anchoPuerta) << "|" << "  |   " << "|" << endl;
        } else {
            if(!aux)
                    cout << "|         |        |              |              |      |           | |" << setw(anchoPuerta + 7)
                    << "|  |___|" << endl;
            else {
                cout << "| " << aux -> paq.ID << " | " << aux -> paq.codigoString << "    | " << aux -> paq.latitud;
                cout << " | " << aux -> paq.longitud << " | " << aux -> paq.urgencia << "    | " << aux -> paq.DNI << " | |"
                << setw(anchoPuerta + 7) << "|  |___|" << endl;
            }

            cout << "|---------|--------|--------------|--------------|------|-----------| |";
            for(int k = 0; k < anchoPuerta - 1; k++)
                cout << "-";

            cout << "|      |" << endl;
        }

        if(aux)
            aux = aux -> siguiente;
    }

    cout << "|---------|--------|--------------|--------------|------|-----------|-----------------------------|" << endl;
    cout << "          \\    {}    /   \\    {}    /                                    \\    {}    /" << endl;
    cout << "           \\________/     \\________/                                      \\________/" << endl;
}

bool Lista::buscarPaquete(string ID){
    pNodo aux;
    aux = cabeza;

    while(aux){
        if(aux -> paq.ID == ID)
            return true;

        aux = aux -> siguiente;
    }
    return false;
}

bool Lista::buscarPaquete(int codigo){
    pNodo aux;
    aux = cabeza;

    while(aux){
        if(aux -> paq.codigo == codigo)
            return true;

        aux = aux -> siguiente;
    }
    return false;
}

paquete Lista::devolverPaquete(string ID){
    pNodo aux;
    aux = cabeza;

    while(aux){
        if(aux -> paq.ID == ID)
            return aux -> paq;

        aux = aux -> siguiente;
    }
}

//MÉTODOS DE ÁRBOLES

void Arbol::Insertar(Lista l){
    pNodoArbol padre = NULL;

    actual = raiz;

    while(!Vacio(actual) && l.codigo != actual -> lista.codigo){
        padre = actual;

        if(l.codigo > actual -> lista.codigo)
            actual = actual -> derecho;
        else if(l.codigo < actual -> lista.codigo)
            actual = actual -> izquierdo;
    }

    if(!Vacio(actual))
        return;
    if(Vacio(padre))
        raiz = new NodoArbol(l);
    else if(l.codigo < padre -> lista.codigo)
        padre -> izquierdo = new NodoArbol(l);
    else if(l.codigo > padre -> lista.codigo)
        padre -> derecho = new NodoArbol(l);
}

void Arbol::Borrar(int codigo){
    pNodoArbol padre = NULL;
    pNodoArbol nodo;
    int aux;

    actual = raiz;

    while(!Vacio(actual)){
        if(codigo == actual -> lista.codigo){
            if(EsHoja(actual)){
                if(padre){
                    if(padre -> derecho == actual)
                        padre -> derecho = NULL;
                    else if(padre -> izquierdo == actual)
                        padre -> izquierdo = NULL;
                }

                delete actual;
                actual = NULL;
                return;
            } else {
                padre = actual;

                if(actual -> derecho){
                    nodo = actual -> derecho;

                    while(nodo -> izquierdo){
                        padre = nodo;
                        nodo = nodo -> izquierdo;
                    }
                } else {
                    nodo = actual -> izquierdo;

                    while(nodo -> derecho){
                        padre = nodo;
                        nodo = nodo -> derecho;
                    }
                }

                aux = actual -> lista.codigo;
                actual -> lista.codigo = nodo -> lista.codigo;
                nodo -> lista.codigo = aux;
                actual = nodo;
            }
        } else {
            padre = actual;

            if(codigo > actual -> lista.codigo)
                actual = actual -> derecho;
            else if(codigo < actual -> lista.codigo)
                actual = actual -> izquierdo;
        }
    }
}

bool Arbol::Buscar(int codigo){
    actual = raiz;

    while(!Vacio(actual)){
        if(codigo == actual -> lista.codigo)
            return true;
        else if(codigo > actual -> lista.codigo)
            actual = actual -> derecho;
        else if(codigo < actual -> lista.codigo)
            actual = actual -> izquierdo;
    }
    return false;
}

pNodoArbol Arbol::Devolver(int codigo){
    actual = raiz;

    while(!Vacio(actual)){
        if(codigo == actual -> lista.codigo)
            return actual;
        else if(codigo > actual -> lista.codigo)
            actual = actual -> derecho;
        else if(codigo < actual -> lista.codigo)
            actual = actual -> izquierdo;
    }
    cout << "No encontrado" << endl;
}

Lista Arbol::generarCentralPaqueteria(bool nombreAutomatico){
    int nivel = 0;
    int suma = 0;
    int primerHijoDeFila = codigoRaizSistema;
    int codigoParaInsertar;
    Lista centralPaqueteria;
    string nombreDado;

    //Definimos que nivel estamos rellenando
    while(suma <= contador){
        suma += pow(2, nivel);
        nivel++;
    }

    //Definimos cual es el primer valor del nivel que estamos rellenando (se podría meter en el while anterior)
    for(int i = 1; i < nivel; i++){
        primerHijoDeFila = primerHijoDeFila / 2;
    }

    codigoParaInsertar = primerHijoDeFila;

    //Buscamos que valor de la fila es el primero que no aparece, y lo insertamos
    bool hacer = true;
    while(hacer){
        if(!Buscar(codigoParaInsertar)){
            centralPaqueteria.codigo = codigoParaInsertar;
            hacer = false;
        } else {
            //Los valores son una serie en la que se va sumando el primer número
            //de la fila anterior, es decir el primer número de esta fila por dos
            codigoParaInsertar += primerHijoDeFila * 2;
        }
    }

    if(!nombreAutomatico){
        cout << endl << " Inserte el nombre de la nueva central de paqueteria:" << endl;
        cin >> nombreDado;
        fflush(stdin);

        centralPaqueteria.nombre = nombreDado;
    }
    return centralPaqueteria;
}

//MÉTODOS AUXILIARES Y DE ESTRUCTURAS

coordenadas generarCoordenadas(){
    coordenadas coord;

    coord.gradosLatitud = 40;
    coord.minutosLatitud = 28 + rand() % 3;

    coord.segundosLatitud = rand() % 61;

    //Con este if controlamos la generación de paquetes con latitud 31 en los minutos,
    //si los generasemos directamente, un 25% de los paquetes más o menos serían 31,
    //de modo que el 75% de los paquetes irían al norte
    if(coord.segundosLatitud == 60){
        coord.minutosLatitud++;
        coord.segundosLatitud = 0;
    }

    coord.gradosLongitud = -3;
    coord.minutosLongitud = 19 + rand() % 6;

    coord.segundosLongitud = rand() % 61;

    //Con este if controlamos la generación de paquetes con latitud 25 en los minutos,
    //si los generasemos directamente, un 25% de los paquetes más o menos serían 25,
    //de modo que el 75% de los paquetes irían al oeste
    if(coord.segundosLongitud == 60){
        coord.minutosLongitud++;
        coord.segundosLongitud = 0;
    }
    return coord;
}

paquete generarPaquete(int cantidadDeCodigos, int codigos[]){
    paquete p;
    stringstream conversor;

    p.ID = generarID();
    p.codigo = codigos[rand() % cantidadDeCodigos];

    conversor << p.codigo;
    conversor >> p.codigoString;

    if(p.codigo < 100)
        if(p.codigo >= 10)
            p.codigoString = "0" + p.codigoString;
        else
            p.codigoString = "00" + p.codigoString;

    p.coord = generarCoordenadas();
    p.latitud = mostrarLatitud(p);
    p.longitud = mostrarLongitud(p);
    p.urgencia = rand()% 2;
    p.DNI = generarDNI();

    return p;
}

string generarNumero(int n){
    int m;
    int numero = 0;
    string stringNumero;
    stringstream conversor;

    for(int i = 0; i < n; i++){
        m = rand() % 9;

        for(int j = 0; j < i && i != 0; j++)
            m = m * 10;

        numero = numero + m;
    }

    conversor << numero;
    conversor >> stringNumero;

    //Comprobamos que el número no es más pequeño de lo que nos han pedido
    if(stringNumero.length() < n){
        int cerosQueFaltan = n - stringNumero.length();

        for(int k = 0; k < cerosQueFaltan; k++){
            stringNumero = "0" + stringNumero;
        }
    }
    return stringNumero;
}

string generarCadena(int n){
    string letra;
    string cadena;

    for(int i = 0; i < n; i++){
        letra = 'A' + rand() % 26;
        cadena = cadena + letra;
    }
    return cadena;
}

string generarID(){
    return generarNumero(2) + generarCadena(1) + generarNumero(4);
}

string generarDNI(){
    return generarNumero(8) + generarCadena(1);
}

string mostrarLatitud(paquete p){
    string stringMinutos;
    string stringSegundos;
    stringstream conversor1, conversor2;

    conversor1 << p.coord.minutosLatitud;
    conversor1 >> stringMinutos;
    conversor2 << p.coord.segundosLatitud;
    conversor2 >> stringSegundos;

    //Si los segundos son solo una cifra añadimos un cero a la izquierda
    if(p.coord.segundosLatitud < 10)
        stringSegundos = "0" + stringSegundos;

    return "40* " + stringMinutos + "' " + stringSegundos + "''";
}

string mostrarLongitud(paquete p){
    string stringMinutos;
    string stringSegundos;
    stringstream conversor1, conversor2;

    conversor1 << p.coord.minutosLongitud;
    conversor1 >> stringMinutos;
    conversor2 << p.coord.segundosLongitud;
    conversor2 >> stringSegundos;

    //Si los segundos son solo una cifra añadimos un cero a la izquierda
    if(p.coord.segundosLongitud < 10)
        stringSegundos = "0" + stringSegundos;

    return "-3* " + stringMinutos + "' " + stringSegundos + "''";
}

void pintarCabecera(){
    cout << "|---------|--------|-----------------------------|------|-----------|   ";
    cout << "|---------|--------|-----------------------------|------|-----------|   ";
    cout << "|---------|--------|-----------------------------|------|-----------|   ";
    cout << "|---------|--------|-----------------------------|------|-----------|" << endl;
    cout << "|         |        |         COORDENADAS         |      |           |   ";
    cout << "|         |        |         COORDENADAS         |      |           |   ";
    cout << "|         |        |         COORDENADAS         |      |           |   ";
    cout << "|         |        |         COORDENADAS         |      |           |" << endl;
    cout << "|   ID    | CODIGO |-----------------------------| TIPO |    DNI    |   ";
    cout << "|   ID    | CODIGO |-----------------------------| TIPO |    DNI    |   ";
    cout << "|   ID    | CODIGO |-----------------------------| TIPO |    DNI    |   ";
    cout << "|   ID    | CODIGO |-----------------------------| TIPO |    DNI    |" << endl;
    cout << "|         |        |   LATITUD    |   LONGITUD   |      |           |   ";
    cout << "|         |        |   LATITUD    |   LONGITUD   |      |           |   ";
    cout << "|         |        |   LATITUD    |   LONGITUD   |      |           |   ";
    cout << "|         |        |   LATITUD    |   LONGITUD   |      |           |" << endl;
    cout << "|---------|--------|--------------|--------------|------|-----------|   ";
    cout << "|---------|--------|--------------|--------------|------|-----------|   ";
    cout << "|---------|--------|--------------|--------------|------|-----------|   ";
    cout << "|---------|--------|--------------|--------------|------|-----------|" << endl;
}

bool cambiarDeNivel(int central){
    if(central + 2 == 2 || central + 2 == 4 || central + 2 == 8 ||
    central + 2 == 16 || central + 2 == 32 || central + 2 == 64 ||
    central + 2 == 128 || central + 2 == 256 || central + 2 == 512)
        return true;
    return false;
}
