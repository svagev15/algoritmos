#include <iostream>
#include <string>
using namespace std;

// Clase plantilla para vector dinámico
template <typename T>
class VectorDinamico {
private:
    T* v;           // Puntero al arreglo dinámico
    int size;       // Cantidad actual de elementos
    int capacidad;  // Capacidad máxima antes de redimensionar

    void resize(int nuevaCapacidad) {
        T* nuevoVector = new T[nuevaCapacidad];
        for (int i = 0; i < size; i++) {
            nuevoVector[i] = v[i];
        }
        delete[] v;
        v = nuevoVector;
        capacidad = nuevaCapacidad;
    }

public:
    VectorDinamico(int capInicial) {
        if (capInicial <= 0) capInicial = 1;
        capacidad = capInicial;
        size = 0;
        v = new T[capacidad];
    }

    ~VectorDinamico() {
        delete[] v;
    }

    void add(T valor) {
        if (size >= capacidad) {
            resize(capacidad * 2);
        }
        v[size] = valor;
        size++;
    }

    void insert(int posicion, T valor) {
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

    void deleteElemento(T valor) {
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
};

int main() {
    int capacidadInicial;
    cout << "Ingrese la capacidad inicial del vector: ";
    cin >> capacidadInicial;

    // Podemos cambiar int por string, double, char, etc.
    VectorDinamico<string> vec(capacidadInicial);

    int elementosIniciales;
    cout << "¿Cuántos elementos desea agregar inicialmente? ";
    cin >> elementosIniciales;
    cin.ignore(); // limpiar buffer para getline

    for (int i = 0; i < elementosIniciales; i++) {
        string valor;
        cout << "Elemento " << i + 1 << ": ";
        getline(cin, valor);
        vec.add(valor);
    }

    cout << "Vector inicial: ";
    vec.imprimir();

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Agregar elemento al final\n";
        cout << "2. Insertar elemento en posición\n";
        cout << "3. Eliminar elemento por valor (todas las apariciones)\n";
        cout << "4. Eliminar elemento por posición\n";
        cout << "5. Imprimir vector\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            string valor;
            cout << "Ingrese el valor a agregar: ";
            getline(cin, valor);
            vec.add(valor);
        }
        else if (opcion == 2) {
            int pos;
            string valor;
            cout << "Ingrese la posición: ";
            cin >> pos;
            cin.ignore();
            cout << "Ingrese el valor: ";
            getline(cin, valor);
            vec.insert(pos, valor);
        }
        else if (opcion == 3) {
            string valor;
            cout << "Ingrese el valor a eliminar (todas las apariciones): ";
            getline(cin, valor);
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

    } while (opcion != 0);

    return 0;
}
