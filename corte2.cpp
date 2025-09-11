#include <iostream>
using namespace std;

class VectorDinamico {
private:
    int* v;           // Puntero al arreglo dinámico
    int size;         // Cantidad actual de elementos
    int capacidad;    // Capacidad máxima antes de redimensionar

    // Función privada para redimensionar
    void resize(int nuevaCapacidad) {
        int* nuevoVector = new int[nuevaCapacidad];
        for (int i = 0; i < size; i++) {
            nuevoVector[i] = v[i];
        }
        delete[] v;
        v = nuevoVector;
        capacidad = nuevaCapacidad;
    }

public:
    // Constructor con capacidad inicial
    VectorDinamico(int capInicial) {
        if (capInicial <= 0) capInicial = 1;
        capacidad = capInicial;
        size = 0;
        v = new int[capacidad];
    }

    ~VectorDinamico() {
        delete[] v;
    }

    void add(int valor) {
        if (size >= capacidad) {
            resize(capacidad * 2);
        }
        v[size] = valor;
        size++;
    }

    void insert(int posicion, int valor) {
        if (posicion < 0 || posicion > size) {
            cout << "Posición inválida" << endl;
            return;
        }
        if (size >= capacidad) {
            resize(capacidad * 2);
        }
        for (int i = size; i > posicion; i--) {
            v[i] = v[i - 1];
        }
        v[posicion] = valor;
        size++;
    }

    // Eliminar TODAS las ocurrencias de un elemento
    void deleteElemento(int valor) {
        int nuevosize = 0;
        for (int i = 0; i < size; i++) {
            if (v[i] != valor) {
                v[nuevosize] = v[i];
                nuevosize++;
            }
        }
        size = nuevosize;
    }

    void deletePosicion(int posicion) {
        if (posicion < 0 || posicion >= size) {
            cout << "Posición inválida" << endl;
            return;
        }
        for (int i = posicion; i < size - 1; i++) {
            v[i] = v[i + 1];
        }
        size--;
    }

    void imprimir() {
        if (size == 0) {
            cout << "Vector vacío" << endl;
            return;
        }
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << v[i] << " ";
        }
        cout << "]" << endl;
    }
    void selectionSort(){
        for (int i = 0; i < size - 1; i++) {
            int Minindex = i;
            for (int j = i + 1; j<size;j++){
                if (v[j]<v[Minindex]){
                    Minindex = j;
                }
            }
            if (Minindex != i){
                int temp = v[i];
                v[i] = v[Minindex];
                v[Minindex] = temp;
                
            }
        }    
    }
};

int main() {
    int capacidadInicial;
    cout << "Ingrese la capacidad inicial del vector: ";
    cin >> capacidadInicial;

    VectorDinamico vec(capacidadInicial);

    // Llenar el vector inicial
    int elementosIniciales;
    cout << "¿Cuántos elementos desea agregar inicialmente? ";
    cin >> elementosIniciales;
    for (int i = 0; i < elementosIniciales; i++) {
        int valor;
        cout << "Elemento " << i + 1 << ": ";
        cin >> valor;
        vec.add(valor);
    }

    cout << "Vector inicial: ";
    vec.imprimir();

    // Menú interactivo
    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Agregar elemento al final\n";
        cout << "2. Insertar elemento en posición\n";
        cout << "3. Eliminar elemento por valor (todas las apariciones)\n";
        cout << "4. Eliminar elemento por posición\n";
        cout << "5. Imprimir vector\n";
        cout << "6. Ordenar vector con Selection Sort\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            int valor;
            cout << "Ingrese el valor a agregar: ";
            cin >> valor;
            vec.add(valor);
        }
        else if (opcion == 2) {
            int pos, valor;
            cout << "Ingrese la posición: ";
            cin >> pos;
            cout << "Ingrese el valor: ";
            cin >> valor;
            vec.insert(pos, valor);
        }
        else if (opcion == 3) {
            int valor;
            cout << "Ingrese el valor a eliminar (todas las apariciones): ";
            cin >> valor;
            vec.deleteElemento(valor);
        }
        else if (opcion == 4) {
            int pos;
            cout << "Ingrese la posición a eliminar: ";
            cin >> pos;
            vec.deletePosicion(pos);
        }
        else if (opcion == 5) {
            vec.imprimir();
        }
        else if (opcion == 6) {
            cout << "Ordenando vector..." << endl;
            vec.selectionSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
    } while (opcion != 0);

    return 0;
}
