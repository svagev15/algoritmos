#pragma once
#include <iostream>
using namespace std;

template <class T>
class Vector {
private:
    T* datos;       // arreglo dinámico
    int size;       // número de elementos usados
    int capacidad;  // tamaño máximo actual

    void redimensionar(int nuevaCapacidad) {
        T* nuevo = new T[nuevaCapacidad];
        for (int i = 0; i < size; i++) {
            nuevo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo;
        capacidad = nuevaCapacidad;
    }
    
    


public:
    Vector() {
        size = 0;
        capacidad = 10; // capacidad inicial
        datos = new T[capacidad];
    }

    ~Vector() {
        delete[] datos;
    }

    int getSize() const {
        return size;
    }

    void add(const T& elem) {
        if (size == capacidad) {
            redimensionar(capacidad * 2);
        }
        datos[size++] = elem;
    }

    void clear() {
        size = 0;
    }

    T& operator[](int idx) {
        return datos[idx];
    }

    const T& operator[](int idx) const {
        return datos[idx];
    }
        
    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (datos[j+1] < datos[j]) {
                    T tmp = datos[j];
                    datos[j] = datos[j+1];
                    datos[j+1] = tmp;
                }
            }
        }
    }

    // Selección
    void sort() {
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            for (int j = i+1; j < size; j++) {
                if (datos[j] < datos[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                T tmp = datos[i];
                datos[i] = datos[minIdx];
                datos[minIdx] = tmp;
            }
        }
    }

    // Inserción
    void insertionSort() {
        for (int i = 1; i < size; i++) {
            T key = datos[i];
            int j = i - 1;
            while (j >= 0 && key < datos[j]) {
                datos[j+1] = datos[j];
                j--;
            }
            datos[j+1] = key;
        }
    }

    int binarySearch(const T& elem) {
        int izquierda = 0;
        int derecha = size - 1;
        while (izquierda <= derecha) {
            int mid = (izquierda + derecha) / 2;
            if (datos[mid] == elem) {
                return mid;
            } else if (elem < datos[mid]) {
                derecha = mid - 1;
            } else {
                izquierda = mid + 1;
            }
        }
        return -1;
    }
};
