#include<iostream>
#include"Vector.h"

using namespace std;

class Estudiante {
    int id;
    int numNotas;
    Vector<float> notas;
    // Atributos para controlar el ordenamiento
    int atributoOrden; // -1 para ID, 0+ para índice de nota
    bool ordenAscendente;

public:
    Estudiante() {
        id = -1;
        numNotas = 3;
        atributoOrden = -1; // Por defecto ordenar por ID
        ordenAscendente = true; // Por defecto ascendente
    }

    Estudiante(int i, int nN) {
        id = i;
        numNotas = nN;
        atributoOrden = -1;
        ordenAscendente = true;
    }

    float getNota(int i) {
        return notas[i];
    }

    void addNota(float n) {
        notas.add(n);
    }

    int getID() {
        return id;
    }

    void setOrdOrderAsc() {
        //Define el orden como ascendente
        ordenAscendente = true;
    }

    void setOrdOrderDesc() {
        //Define el orden como descendente
        ordenAscendente = false;
    }

    void setOrdAtrib(int i) {
        //Define el atributo i como el usado para el ordenamiento. Use -1 para ordenar por el id.
        atributoOrden = i;
    }

    float promedio() {
        //Calcular el promedio de notas del estudiante
        if (numNotas == 0) return 0.0f;
        
        float suma = 0.0f;
        for (int i = 0; i < numNotas; i++) {
            suma += notas[i];
        }
        return suma / numNotas;
    }

    string to_string() {
        string s = std::to_string(id) + " - ";

        for (int i = 0; i < numNotas; i++) {
            s = s + std::to_string(notas[i]) + ", ";
        }
        s = s + "Promedio: " + std::to_string(promedio());
        return s;
    }

    int compareTo(Estudiante e) {
        /*Defina el algoritmo de comparación entre estudiantes, de tal manera que use
        el atributo y el orden deseados
        */
        float valorThis, valorOther;
        
        // Obtener el valor a comparar para this
        if (atributoOrden == -1) {
            valorThis = (float)this->id;
        } else if (atributoOrden == -2) { // Caso especial para promedio
            valorThis = this->promedio();
        } else {
            valorThis = this->notas[atributoOrden];
        }
        
        // Obtener el valor a comparar para other
        if (atributoOrden == -1) {
            valorOther = (float)e.id;
        } else if (atributoOrden == -2) {
            valorOther = e.promedio();
        } else {
            valorOther = e.notas[atributoOrden];
        }
        
        // Realizar comparación
        if (valorThis < valorOther) {
            return ordenAscendente ? -1 : 1;
        } else if (valorThis > valorOther) {
            return ordenAscendente ? 1 : -1;
        } else {
            return 0;
        }
    }

    // Los operadores de comparación ya están implementados correctamente
    bool operator>(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) == 1) {
                return true;
            }
        }
        return false;
    }

    bool operator>=(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) >= 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator<(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) == -1) {
                return true;
            }
        }
        return false;
    }

    bool operator<=(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) <= 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator==(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) == 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator!=(Estudiante& other) {
        if (this != &other) {
            if (compareTo(other) != 0) {
                return true;
            }
        }
        return false;
    }

    Estudiante& operator=(Estudiante other) {
        //Implemente la asignación directa entre estudiantes
        if (this != &other) {
            this->id = other.id;
            this->numNotas = other.numNotas;
            this->atributoOrden = other.atributoOrden;
            this->ordenAscendente = other.ordenAscendente;
            
            //Mantenga esta parte
            this->notas.clear();
            for (int i = 0; i < other.numNotas; i++) {
                this->notas.add(other.notas[i]);
            }
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Estudiante& b) {
        return os << b.to_string();
    }
};

class Curso {
    int id;
    Vector<Estudiante> estudiantes;
    int numNotas;
    int numEstudiantes;
    int atributoOrden;
    bool ordenAscendente;

public:
    Curso() {
        id = -1;
        numNotas = 0;
        numEstudiantes = 0;
        atributoOrden = -1;
        ordenAscendente = true;
    }

    Curso(int i, int nN, int nE) {
        id = i;
        numNotas = nN;
        numEstudiantes = nE;
        atributoOrden = -1;
        ordenAscendente = true;
    }

    void setOrdOrderAsc() {
        //Define el orden como ascendente en todos los estudiantes del Curso
        ordenAscendente = true;
        for (int i = 0; i < estudiantes.getSize(); i++) {
            estudiantes[i].setOrdOrderAsc();
        }
    }

    void setOrdOrderDesc() {
        //Define el orden como descendente en todos los estudiantes del Curso
        ordenAscendente = false;
        for (int i = 0; i < estudiantes.getSize(); i++) {
            estudiantes[i].setOrdOrderDesc();
        }
    }

    void setOrdAtrib(int j) {
        //Define el atributo i como el usado para el ordenamiento en todos los estudiantes del Curso
        atributoOrden = j;
        for (int i = 0; i < estudiantes.getSize(); i++) {
            estudiantes[i].setOrdAtrib(j);
        }
    }

    void addEstudiante(Estudiante& e) {
        estudiantes.add(e);
        numEstudiantes = estudiantes.getSize();
    }

    Estudiante& getEstudiante(int i) {
        return estudiantes[i];
    }

    float promedio() {
        //Calcular el promedio del promedio de los cursos
        if (numEstudiantes == 0) return 0.0f;
        
        float suma = 0.0f;
        for (int i = 0; i < numEstudiantes; i++) {
            suma += estudiantes[i].promedio();
        }
        return suma / numEstudiantes;
    }

    string to_string() {
        string s = "***** Curso " + std::to_string(id) + " *****\n";

        for (int i = 0; i < numEstudiantes; i++) {
            s = s + estudiantes[i].to_string() + "\n";
        }
        s = s + "Promedio: " + std::to_string(this->promedio()) + "\n";
        s = s + "NumEstudiantes: " + std::to_string(this->numEstudiantes) + "\n";
        return s;
    }

    int getNumEstudiantes() {
        //Retorne el número de estudiantes
        return numEstudiantes;
    }

    int compareTo(Curso other) {
        /*Defina el algoritmo de comparación entre cursos
        */
        float valorThis, valorOther;
        
        if (atributoOrden == -1) {
            valorThis = (float)this->id;
            valorOther = (float)other.id;
        } else if (atributoOrden == -2) {
            valorThis = this->promedio();
            valorOther = other.promedio();
        } else {
            // Para cursos, comparar por número de estudiantes si el atributo es inválido
            valorThis = (float)this->numEstudiantes;
            valorOther = (float)other.numEstudiantes;
        }
        
        if (valorThis < valorOther) {
            return ordenAscendente ? -1 : 1;
        } else if (valorThis > valorOther) {
            return ordenAscendente ? 1 : -1;
        } else {
            return 0;
        }
    }

    // Operadores de comparación para Curso
    bool operator>(Curso& other) {
        if (this != &other) {
            if (compareTo(other) == 1) {
                return true;
            }
        }
        return false;
    }

    bool operator>=(Curso& other) {
        if (this != &other) {
            if (compareTo(other) >= 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator<(Curso& other) {
        if (this != &other) {
            if (compareTo(other) == -1) {
                return true;
            }
        }
        return false;
    }

    bool operator<=(Curso& other) {
        if (this != &other) {
            if (compareTo(other) <= 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator==(Curso& other) {
        if (this != &other) {
            if (compareTo(other) == 0) {
                return true;
            }
        }
        else {
            return true;
        }
        return false;
    }

    bool operator!=(Curso& other) {
        if (this != &other) {
            if (compareTo(other) != 0) {
                return true;
            }
        }
        return false;
    }

    Curso& operator=(Curso other) {
        //Implemente la asignación directa entre cursos
        if (this != &other) {
            this->id = other.id;
            this->numNotas = other.numNotas;
            this->numEstudiantes = other.numEstudiantes;
            this->atributoOrden = other.atributoOrden;
            this->ordenAscendente = other.ordenAscendente;

            this->estudiantes.clear();
            for (int i = 0; i < other.getNumEstudiantes(); i++) {
                this->estudiantes.add(other.estudiantes[i]);
            }
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, Curso& b) {
        return os << b.to_string();
    }

    void sort() {
        estudiantes.sort();
    }
};

class RegiNotas {
    Vector<Curso> cursos;
    int atributoOrden;
    bool ordenAscendente;

public:
    RegiNotas() {
        atributoOrden = -1;
        ordenAscendente = true;
    }

    void addCurso(Curso& c) {
        cursos.add(c);
    }

    Curso& getCurso(int i) {
        return cursos[i];
    }

    void setOrdOrderAsc() {
        //Define el orden como ascendente en todos los cursos
        ordenAscendente = true;
        for (int i = 0; i < cursos.getSize(); i++) {
            cursos[i].setOrdOrderAsc();
        }
    }

    void setOrdOrderDesc() {
        //Define el orden como descendente en todos los cursos
        ordenAscendente = false;
        for (int i = 0; i < cursos.getSize(); i++) {
            cursos[i].setOrdOrderDesc();
        }
    }

    void setOrdAtrib(int j) {
        //Define el atributo i como el usado para el ordenamiento en todos los cursos
        atributoOrden = j;
        for (int i = 0; i < cursos.getSize(); i++) {
            cursos[i].setOrdAtrib(j);
        }
    }

    void sort() {
        //Debe organizar los cursos, luego el interior de cada curso
        // Ordenar los cursos
        for (int i = 0; i < cursos.getSize() - 1; i++) {
            for (int j = 0; j < cursos.getSize() - i - 1; j++) {
                if (!ordenAscendente ? cursos[j] > cursos[j+1] : cursos[j] < cursos[j+1]) {
                    Curso temp = cursos[j];
                    cursos[j] = cursos[j+1];
                    cursos[j+1] = temp;
                }
            }
        }
        
        // Ordenar estudiantes dentro de cada curso
        for (int i = 0; i < cursos.getSize(); i++) {
            cursos[i].sort();
        }
    }

    string to_string() {
        string s = "***** Lista de Cursos *****\n";

        for (int i = 0; i < cursos.getSize(); i++) {
            s = s + cursos[i].to_string() + "\n";
        }
        return s;
    }

    friend std::ostream& operator<<(std::ostream& os, RegiNotas& b) {
        return os << b.to_string();
    }
};

// El main permanece igual
int main()
{
    srand(1234);
    int numEstudiantes = 10;
    int numNotas = 5;

    RegiNotas r;
    Curso* tc = nullptr;
    Estudiante* te = nullptr;
    
    // ... (el main permanece exactamente igual)
    
    return 0;
}
