#include <iostream>
#include <ctime>  // Para srand(time(0))

using namespace std;


/*código para la matriz*/

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


/*código para el arreglo*/

int* crear_arreglo(int n) {
    int* arr = new int[n];  // Crear arreglo dinámico de tamaño n
    for (int i = 0; i < n; i++) {
        arr[i] = 0;  // Inicializar con 0 (o cualquier otro valor que desees)
    }
    return arr;
}

// Función para destruir el arreglo
void destruir_arreglo(int* arr) {
    delete[] arr;  // Liberar la memoria del arreglo dinámico
}

// Función para imprimir el arreglo
void print_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// Función para llenar el arreglo con valores
void llenar_arreglo(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor para el elemento " << i << ": ";
        cin >> arr[i];
    }
}


class Venta {
private:
    int cliente;
    int vendedor;
    int producto;
public:
    Venta() {
        cliente = -1; 
        vendedor = -1;
        producto = -1;
    }
    Venta(int c, int v, int p) {
        cliente = c;
        vendedor = v;
        producto = p;
    }
    
    //Getters
    int getCliente() const { 
        return cliente; 
    }
    void setCliente(int c) { 
        cliente = c; 
    }
    int getVendedor() const { 
        return vendedor; 
    }
    void setVendedor(int v) { 
        vendedor = v; 
    }

    int getProducto() const { 
        return producto; 
    }
    void setProducto(int p) { 
        producto = p; 
    }

    Venta& operator=(const Venta& f) {
        cliente = f.cliente;
        vendedor = f.vendedor;
        producto = f.producto;
        return *this;
    }

    string to_string() const {
        return std::to_string(cliente) + ", " + std::to_string(vendedor) + ", " + std::to_string(producto);
    }

    friend std::ostream& operator<<(std::ostream& os, const Venta& s) {
        return os << s.to_string();
    }
};

// Clase nodo con plantilla
template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}

    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setValor(T _valor) { this->valor = _valor; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// Clase lista enlazada con plantilla
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr) {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente()) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        size++;
    }

    void insertarEnPosicion(int posicion, const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);

        if (posicion == 0) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }

        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        if (actual == nullptr) {
            std::cout << "Posición inválida" << std::endl;
            delete nuevoNodo;
            return;
        }

        nuevoNodo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevoNodo);
    }

    bool eliminar(const T& _valor) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while (actual) {
            if (actual->getValor() == _valor) {
                if (anterior) {
                    anterior->setSiguiente(actual->getSiguiente());
                } else {
                    cabeza = actual->getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    Nodo<T>* buscarPorValor(const T& _valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    int get_size() const { return size; }

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
    }

    Nodo<T>* get(int i) const {
        if (i >= 0 && i < size) {
            int j = 0;
            Nodo<T>* actual = cabeza;
            while (j < i) {
                actual = actual->getSiguiente();
                j++;
            }
            return actual;
        }
        return nullptr;
    }
};

// Clase Distribuidora
class Distribuidora {
private:
    ListaEnlazada<Venta> ventas;
    int** matriz;
    int* arreglo; // Declarar el arreglo como un miembro
    int nc; // Número de clientes
    int nv; // Número de vendedores
    int np; // Número de productos
    int ns; // Número de ventas

public:
    Distribuidora(int c = 100, int v = 100, int p = 100, int s = 1000): nc(c), nv(v), np(p), ns(s) {
        matriz = crear_mat(nv, np);
        arreglo = crear_arreglo(nv);
    }

    ~Distribuidora() {
        destruir_mat(matriz, nv);
        destruir_arreglo(arreglo);
    }

    void init_lista() {
        Venta* t;
        int c, v, p;
        for (int i = 0; i < ns; i++) {
            c = rand() % nc;
            v = rand() % nv;
            p = rand() % np;
            t=new Venta(c, v, p);
            ventas.insertar(*t);
        }
        cout << "Se han generado " << ventas.get_size() << " ventas." << endl;
        ventas.mostrar();
    }

    void print() {
        ventas.mostrar();
    }

    void calcular_matriz() {
        Nodo<Venta>* ptr = ventas.get(0);
        for (int i = 0; i < ns; i++) {
            matriz[ptr->getValor().getVendedor()][ptr->getValor().getProducto()]++;
            ptr = ptr->getSiguiente();
        }
        cout << "Matriz de vendedores por producto: " << endl;
        print_mat(matriz, nv, np);
    }

    void generar_arreglo() {
        Nodo<Venta>* ptr = ventas.get(0);
        while (ptr != nullptr) {
            arreglo[ptr->getValor().getVendedor()]++;  // Incrementar el vendedor correspondiente en el arreglo
            ptr = ptr->getSiguiente();
        }
        cout << "Arreglo de vendedores: " << endl;
        print_arreglo(arreglo, nv);  // Imprimir el arreglo con los vendedores y sus ventas
    }

    int vendedor_con_mas_ventas_por_producto(int producto) {
        int max = 0;
        int vendedorm = -1;
        for (int i = 0; i < nv; i++) {
            if (matriz[i][producto] > max) {
                max = matriz[i][producto];
                vendedorm = i;
            }
        }
        return vendedorm;
    }
    
     void calcular_promedio_ventas() {
        int cont = 0;
        float promedio, suma = 0;
        for (int i = 0; i < nv; i++) {
            suma = suma + arreglo[i];
            cont = cont + 1;
        }
        promedio = suma / cont;
        cout << "El promedio de las ventas es: " << promedio << endl;
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int c = 10;
    int v = 10;
    int p = 10;
    int s = 100;
    Distribuidora dis = Distribuidora(c, v, p, s);
    dis.init_lista();
    cout << endl;
    dis.calcular_matriz();
    for (int i = 0; i < p; i++) {
        cout << "El vendedor con más ventas en el producto " << i << " es: " 
             << dis.vendedor_con_mas_ventas_por_producto(i) << endl;
    }
    cout << "-------------datos del arreglo-------------" << endl;
    dis.generar_arreglo();
    dis.calcular_promedio_ventas();
    return 0;
}
