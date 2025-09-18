#include <iostream>
# include<vector>
#include <algorithm>
using namespace std;

class VectorDinamico {
private:
    int* v;
    int size;
    int capacidad;

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
    
    int binomialSearch(int valor, int izquierda = 0, int derecha = -1) {
        if (derecha == -1) derecha = size - 1;
        if (izquierda > derecha) return -1; // No encontrado
        int medio = izquierda + (derecha - izquierda) / 2;
        if (v[medio] == valor) return medio;
        if (v[medio] > valor)
            return binomialSearch(valor, izquierda, medio - 1);
        else
            return binomialSearch(valor, medio + 1, derecha);
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            int Minindex = i;
            for (int j = i + 1; j < size; j++) {
                if (v[j] < v[Minindex]) {
                    Minindex = j;
                }
            }
            if (Minindex != i) {
                int temp = v[i];
                v[i] = v[Minindex];
                v[Minindex] = temp;
            }
        }
    }

    void bubbleSort(){
        int temp;
        for (int i =0; i<size-1;i++){
            for (int j =i+1; j < size -1; j++){
                if (v[i]>v[j]){
                    temp = v[j];
                    v[j] = v[i];
                    v[i] = temp; 
                }
            }
        }
    }
    
    void insertSort(){
        int temp;
        for (int i =0; i<size-1;i++){
            for (int j =i+1; j < size; j++){
                if (v[j]<v[i]){
                    temp = v[i];
                    v[i] = v[j];
                    v[j] = temp; 
                }
            }
        }
    }
    
    // Quick Sort Helper
    void quickSortHelper(int left, int right) {
        if (left >= right) return;
        int pivot = v[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (v[j] < pivot) {
                i++;
                swap(v[i], v[j]);
            }
        }
        swap(v[i + 1], v[right]);
        quickSortHelper(left, i);
        quickSortHelper(i + 2, right);
    }
    void quickSort() {
        quickSortHelper(0, size - 1);
    }
    
    // Heap Sort Helper
    void heapify(int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && v[l] > v[largest]) largest = l;
        if (r < n && v[r] > v[largest]) largest = r;
        if (largest != i) {
            swap(v[i], v[largest]);
            heapify(n, largest);
        }
    }
    void heapSort() {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i);
        for (int i = size - 1; i > 0; i--) {
            swap(v[0], v[i]);
            heapify(i, 0);
        }
    }
    
    // Merge Sort Helper
    void merge(int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* L = new int[n1];
        int* R = new int[n2];
        for (int i = 0; i < n1; i++)
            L[i] = v[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = v[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) v[k++] = L[i++];
            else v[k++] = R[j++];
        }
        while (i < n1) v[k++] = L[i++];
        while (j < n2) v[k++] = R[j++];
        delete[] L;
        delete[] R;
    }
    void mergeSortHelper(int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSortHelper(l, m);
            mergeSortHelper(m + 1, r);
            merge(l, m, r);
        }
    }
    void mergeSort() {
        mergeSortHelper(0, size - 1);
    }
    
    // Bucket Sort
    void bucketSort() {
        if (size <= 0) return;
        int minValue = v[0];
        int maxValue = v[0];
        for (int i = 1; i < size; i++) {
            if (v[i] < minValue) minValue = v[i];
            else if (v[i] > maxValue) maxValue = v[i];
        }
        int bucketCount = (maxValue - minValue) / size + 1;
        vector<vector<int>> buckets(bucketCount);
        for (int i = 0; i < size; i++) {
            int idx = (v[i] - minValue) / size;
            buckets[idx].push_back(v[i]);
        }
        int idx = 0;
        for (int i = 0; i < bucketCount; i++) {
            sort(buckets[i].begin(), buckets[i].end());
            for (int j = 0; j < buckets[i].size(); j++) {
                v[idx++] = buckets[i][j];
            }
        }
    }
    
};

int main() {
    int capacidadInicial;
    cout << "Ingrese la capacidad inicial del vector: ";
    cin >> capacidadInicial;

    VectorDinamico vec(capacidadInicial);

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

    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Agregar elemento al final\n";
        cout << "2. Insertar elemento en posición\n";
        cout << "3. Eliminar elemento por valor (todas las apariciones)\n";
        cout << "4. Eliminar elemento por posición\n";
        cout << "5. Imprimir vector\n";
        cout << "6. Ordenar vector con Selection Sort\n";
        cout << "7. Ordenar vector con Bubble Sort\n";
        cout << "8. Ordenar vector con Insert Sort\n";
        cout << "9. Buscar elemento con Binomial Search (búqueda binaria recursiva)\n";
        cout << "10. Ordenar vector con Quick Sort\n";
        cout << "11. Ordenar vector con Heap Sort\n";
        cout << "12. Ordenar vector con Merge Sort\n";
        cout << "13. Ordenar vector con Bucket Sort\n";
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
            cout << "Ordenando vector con Selection Sort..." << endl;
            vec.selectionSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 7) {
            cout << "Ordenando vector con Bubble Sort..." << endl;
            vec.bubbleSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 8) {
            cout << "Ordenando vector con Insert Sort..." << endl;
            vec.insertSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 9) {
            int valor;
            cout << "Ingrese el valor a buscar (vector debe estar ordenado): ";
            cin >> valor;
            int idx = vec.binomialSearch(valor);
            if (idx == -1)
                cout << "No encontrado\n";
            else
                cout << "Encontrado en posición: " << idx << endl;
        }
        else if (opcion == 10) {
            cout << "Ordenando vector con Quick Sort..." << endl;
            vec.quickSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 11) {
            cout << "Ordenando vector con Heap Sort..." << endl;
            vec.heapSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 12) {
            cout << "Ordenando vector con Merge Sort..." << endl;
            vec.mergeSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
        else if (opcion == 13) {
            cout << "Ordenando vector con Bucket Sort..." << endl;
            vec.bucketSort();
            cout << "Vector ordenado: ";
            vec.imprimir();
        }
    } while (opcion != 0);

    return 0;
}
