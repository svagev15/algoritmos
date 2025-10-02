#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include <ctime>
#include "Vector.h"  // Vector<T>      (proporcionado)  (ver cita)

using namespace std;

/* =========================
 *   MODELOS DE DOMINIO
 * ========================= */

class Programa {
    int codigo;
    string nombre;
    int evaluacion;       // 0..5
    int tipoIngenieria;   // 0..10
    int numEstudiantes;   // >= 0

    int ordAtrib; // 1=asc, -1=desc

    public:
    Programa() : codigo(-1), evaluacion(0), tipoIngenieria(0), numEstudiantes(0), ordAtrib(1) {}
    Programa(int c, const string& n, int ev, int tipo, int nes)
        : codigo(c), nombre(n), evaluacion(ev), tipoIngenieria(tipo), numEstudiantes(nes), ordAtrib(1) {}

    // Accesores básicos
    int getCodigo()        const { return codigo; }
    string getNombre()     const { return nombre; }
    int getEvaluacion()    const { return evaluacion; }
    int getTipoIngenieria() const { return tipoIngenieria; }
    int getNumEstudiantes() const { return numEstudiantes; }
    int getOrdAtrib()      const { return ordAtrib; }
    void setOrdAtrib(int a)      { ordAtrib = a; }

    string to_string() const {
        ostringstream oss;
        oss << "Programa{cod=" << codigo
            << ", nom=" << nombre
            << ", eval=" << evaluacion
            << ", tipo=" << tipoIngenieria
            << ", est=" << numEstudiantes << "}";
        return oss.str();
    }

    int compareTo(Programa p){
        // Comparación de evaluaciones, con orden definido por ordAtrib (1=asc, -1=desc)
        int cmp = 0;
        if (evaluacion < p.evaluacion) cmp = -1;
        else if (evaluacion > p.evaluacion) cmp = 1;
        // aplicar orden
        cmp *= ordAtrib;
        if (cmp != 0) return cmp;

        // Desempate por código ascendente (estable)
        if (codigo < p.codigo) return -1;
        if (codigo > p.codigo) return  1;
        return 0;
    }
    
    
    bool operator>(Programa& other) {
        if (this != &other) {
            if(compareTo(other) == 1){
                return true;
            }
        }
        return false;
    }
    
    bool operator>=(Programa& other) {
        if (this != &other) {
            if(compareTo(other) >= 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator<(Programa& other) {
        if (this != &other) {
            if(compareTo(other) == -1){
                return true;
            }
        }
        return false;
    }
    
    bool operator<=(Programa& other) {
        if (this != &other) {
            if(compareTo(other) <= 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator==(Programa& other) {
        if (this != &other) {
            if(compareTo(other) == 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator!=(Programa& other) {
        if (this != &other) {
            if(compareTo(other) != 0){
                return true;
            }
        }
        
        return false;
    }

    Programa& operator=(const Programa& other) {
        if (this != &other) {
            codigo = other.codigo;
            nombre = other.nombre;
            evaluacion = other.evaluacion;
            tipoIngenieria = other.tipoIngenieria;
            numEstudiantes = other.numEstudiantes;
            ordAtrib = other.ordAtrib;
        }
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, Programa& b) {
		return os << b.to_string();
	}


};

class Universidad {
    int codigo;
    string nombre;
    Vector<Programa> programas;
    

public:
    Universidad() : codigo(-1), nombre("") {}
    Universidad(int c, const string& n) : codigo(c), nombre(n) {}

    // Accesores básicos
    int getCodigo()   const { return codigo; }
    string getNombre() const { return nombre; }
    Vector<Programa>& getProgramas() { return programas; }
    const Vector<Programa>& getProgramas() const { return programas; }

    void addPrograma(const Programa& p) { programas.add(p); }

    // Métricas (con filtro opcional por tipo; usar tipoFiltro = -1 para "todos")
    int contarAcreditados(int tipoFiltro = -1) {
        int c = 0;
        int size = programas.getSize();
        for (int i = 0; i < size; ++i) {
            const Programa& p = programas[i];
            if ((tipoFiltro == -1 || p.getTipoIngenieria() == tipoFiltro) && p.getEvaluacion() >= 3)
                ++c;
        }
        return c;
    }

    int contarProgramas(int tipoFiltro = -1) {
        int c = 0;
        for (int i = 0; i < programas.getSize(); ++i) {
            const Programa& p = programas[i];
            if (tipoFiltro == -1 || p.getTipoIngenieria() == tipoFiltro) ++c;
        }
        return c;
    }

    int totalEstudiantes(int tipoFiltro = -1) {
        int s = 0;
        for (int i = 0; i < programas.getSize(); ++i) {
            const Programa& p = programas[i];
            if (tipoFiltro == -1 || p.getTipoIngenieria() == tipoFiltro) s += p.getNumEstudiantes();
        }
        return s;
    }

    int buscarProgramaPorCodigoBinaria(int codigoBuscado) {
        // Asumimos que los programas están agregados en orden creciente de código (como en el main)
        int l = 0;
        int r = programas.getSize() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            int codM = programas[m].getCodigo();
            if (codM == codigoBuscado) return m;   // devolver POSICIÓN
            else if (codM < codigoBuscado) l = m + 1;
            else r = m - 1;
        }
        return -1;
    }

    string to_string() {
        ostringstream oss;
        oss << "Universidad{cod=" << codigo << ", nombre=" << nombre
            << ", #prog=" << programas.getSize() << "}";
            for(int i = 0; i < programas.getSize(); i++) {
                oss << "\n\t" << programas[i].to_string();
            }
        return oss.str();
    }

    int compareTo(Universidad p){
        if (codigo < p.codigo) return -1;
        if (codigo > p.codigo) return  1;
        return 0;
    }
    
    void setOrdAtrib(int a){
        int ord = (a >= 0 ? 1 : -1);
        for (int i = 0; i < programas.getSize(); ++i) {
            programas[i].setOrdAtrib(ord);
        }
    }

    
    bool operator>(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) == 1){
                return true;
            }
        }
        return false;
    }
    
    bool operator>=(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) >= 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator<(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) == -1){
                return true;
            }
        }
        return false;
    }
    
    bool operator<=(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) <= 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator==(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) == 0){
                return true;
            }
        }else{
            return true;
        }
        
        return false;
    }
    
    bool operator!=(Universidad& other) {
        if (this != &other) {
            if(compareTo(other) != 0){
                return true;
            }
        }
        
        return false;
    }

    Universidad& operator=(const Universidad& other) {
    if (this != &other) {
        codigo = other.codigo;
        nombre = other.nombre;
         programas.clear();
        for (int i = 0; i < other.programas.getSize(); ++i) {
            programas.add(other.programas[i]);
        }
    }
    return *this;
    }

    
    friend std::ostream& operator<<(std::ostream& os, Universidad& b) {
		return os << b.to_string();
	}

};

class Teba {
    Vector<Universidad> universidades; // lista enlazada provista

public:
    void agregarUniversidad(int cod, const string& nom) {
        universidades.add(Universidad(cod, nom));
    }

    // Agrega programa a la universidad en posición idx (en la lista)
    void agregarProgramaAUniversidad(int idxUni, const Programa& p) {
        Universidad u = universidades[idxUni]; // copia
        u.addPrograma(p);
        universidades[idxUni] = u; // escribir de vuelta en el nodo
    }

    int getNumUniversidades()  { return universidades.getSize(); }


    // Acceso a universidad por índice
    Universidad getUniversidad(int idxUni) {
        return universidades[idxUni];
    }

    // Escribir de vuelta (cuando modifiquemos su vector de programas)
    void setUniversidad(int idxUni, Universidad& u) {
        universidades[idxUni] = u;
    }

    void print(){
        for(int i = 0; i<universidades.getSize(); i++){
            cout<<universidades[i]<<"\n";
            for(int j = 0; j<universidades[i].getProgramas().getSize(); j++){
                cout<<"\t"<<universidades[i].getProgramas()[j]<<"\n";
            }
        }

    }

    void setOrdUniversidades(int a){
        (void)a;
    }

    void sort(){
        // Insertion sort 
        int n = universidades.getSize();
        for (int i = 1; i < n; ++i) {
            Universidad key = universidades[i];
            int j = i - 1;
            while (j >= 0 && universidades[j].compareTo(key) > 0) {
                universidades[j + 1] = universidades[j];
                --j;
            }
            universidades[j + 1] = key;
        }
    }
};

/* =========================
 *     DATOS DE PRUEBA
 * ========================= */

static string nombresProg[] = {
    "Sistemas", "Electronica", "Industrial", "Mecanica", "Civil",
    "Ambiental", "Biomedica", "Telematica", "Software", "Quimica",
    "Energia", "Aeronautica"
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(12345);

    Teba teba;

    // Agregamos universidades
    teba.agregarUniversidad(101, "Uni Andina");
    teba.agregarUniversidad(102, "Tecnologica del Norte");
    teba.agregarUniversidad(103, "Politecnico Central");
    teba.agregarUniversidad(104, "Universidad del Pacifico");

    // Generamos programas aleatorios para cada universidad
    int numUnis = teba.getNumUniversidades();
    int codigoBase = 10000;

    for (int iu = 0; iu < numUnis; ++iu) {
        int numP = 6 + (rand() % 7); // 6..12 programas
        for (int k = 0; k < numP; ++k) {
            int codigo = codigoBase++;
            int tipo   = rand() % 11;          // 0..10
            int eval   = rand() % 6;           // 0..5
            int est    = 20 + (rand() % 481);  // 20..500
            string nombre = string("Ing. ") + nombresProg[rand() % 12];

            teba.agregarProgramaAUniversidad(iu, Programa(codigo, nombre, eval, tipo, est));
        }
    }

    
    // 2) Demostración de ORDENAMIENTO + BÚSQUEDAS en una universidad de ejemplo
    int idxEj = 1; // Tecnologica del Norte (según inserción)
    {
        cout << "Universidades en el sistema:\n";
        // Mostrar antes
        teba.print();

        teba.setOrdUniversidades(0); // Ordenar universidades por su criterio

        teba.sort();

        cout<<"\nUniversidades ORDENADAS por su criterio:\n";
        teba.print();

        // Búsqueda binaria por código
        Universidad u = teba.getUniversidad(idxEj);
        int n = u.getProgramas().getSize();
        int codigoBuscado = (n > 0) ? u.getProgramas()[n/2].getCodigo() : -1; // tomar uno existente
        int posBin = u.buscarProgramaPorCodigoBinaria(codigoBuscado);
        cout << "\nBusqueda binaria por codigo " << codigoBuscado
             << " -> pos=" << posBin << (posBin>=0 ? " (ENCONTRADO)" : " (NO)") << "\n";

    }

    return 0;
}
