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
        int diff = this->evaluacion - p.evaluacion;
        return diff * ordAtrib;
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
    
Universidad(const Universidad& other) {
    codigo = other.codigo;
    nombre = other.nombre;
    for (int i = 0; i < other.programas.getSize(); i++) {
        programas.add(other.programas[i]);
    }
}


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

    int buscarProgramaPorCodigoBinaria(int codigoBuscado, int tipoFiltro = -1) {
    Vector<Programa> temp;
    Vector<int> idx;

    for (int i = 0; i < programas.getSize(); i++) {
        const Programa& p = programas[i];
        if (tipoFiltro == -1 || p.getTipoIngenieria() == tipoFiltro) {
            temp.add(programas[i]);
            idx.add(i);
        }
    }

    if (temp.getSize() == 0) return -1;

    for (int i = 0; i < temp.getSize() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < temp.getSize(); j++) {
            if (temp[j].getCodigo() < temp[minIndex].getCodigo()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
           
            Programa auxP = temp[i];
            temp[i] = temp[minIndex];
            temp[minIndex] = auxP;

            int auxI = idx[i];
            idx[i] = idx[minIndex];
            idx[minIndex] = auxI;
        }
    }

    int inicio = 0, fin = temp.getSize() - 1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        int codMedio = temp[medio].getCodigo();

        if (codMedio == codigoBuscado) {
            return idx[medio];
        }
        if (codMedio < codigoBuscado) inicio = medio + 1;
        else fin = medio - 1;
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
        int acred1 = this->contarAcreditados(-1);
        int acred2 = p.contarAcreditados(-1);
        if (acred1 > acred2) return -1;
        if (acred1 < acred2) return 1;
        


        int total1 = this->contarProgramas(-1);
        int total2 = p.contarProgramas(-1);
        if (total1 < total2) return -1;
        if (total1 > total2) return 1;
        
        int est1 = this->totalEstudiantes(-1);
        int est2 = p.totalEstudiantes(-1);
        if (est1 > est2) return -1;
        if (est1 < est2) return 1;
        
        return 0;
    }
    
    void setOrdAtrib(int a){

        for(int i = 0; i < programas.getSize(); i++){
            programas[i].setOrdAtrib(a);
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
    Vector<Universidad> universidades;

public:
    void agregarUniversidad(int cod, const string& nom) {
        universidades.add(Universidad(cod, nom));
    }

    // Agrega programa a la universidad en posición idx
    void agregarProgramaAUniversidad(int idxUni, const Programa& p) {
        universidades[idxUni].addPrograma(p);
    }


    int getNumUniversidades()  { return universidades.getSize(); }

    // Acceso a universidad por índice
    Universidad getUniversidad(int idxUni) {
        return universidades[idxUni];
    }

    // Escribir de vuelta
    void setUniversidad(int idxUni, const Universidad& u) {
        if (idxUni >= 0 && idxUni < universidades.getSize()) {
            universidades[idxUni] = u;
        }
    }

    void print(){
        for(int i = 0; i < universidades.getSize(); i++){
            cout << universidades[i] << "\n";
        }
    }


    void setOrdUniversidades(int a){
        // Propagar a todas las universidades
        for(int i = 0; i < universidades.getSize(); i++){
            universidades[i].setOrdAtrib(a);
        }
    }

    void sort(){
        //por selection sort
        universidades.sort();
    }
    void buscarProgramasPorTipo(int tipoIngenieria){
        cout << "\n========================================\n";
        cout << "Programas de tipo " << tipoIngenieria << ":\n";
        cout << "========================================\n";
        
        bool encontrado = false;
        for(int i = 0; i < universidades.getSize(); i++){
            Vector<Programa>& progs = universidades[i].getProgramas();
            bool hayEnEstaUni = false;
            
            for(int j = 0; j < progs.getSize(); j++){
                if(progs[j].getTipoIngenieria() == tipoIngenieria){
                    if(!hayEnEstaUni){
                        cout << "\nEn " << universidades[i].getNombre() << ":\n";
                        hayEnEstaUni = true;
                        encontrado = true;
                    }
                    cout << "  - " << progs[j].to_string() << "\n";
                }
            }
        }
        
        if(!encontrado){
            cout << "No se encontraron programas de este tipo.\n";
        }
        cout << "========================================\n";
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

    cout << "=== listado inicialL ===\n";
    teba.print();

    // A) Ordenar universidades por criterios
    cout << "\n\n=== universidades ordenadas ===\n";
    teba.setOrdUniversidades(1);
    teba.sort();
    teba.print();

    // B) Búsqueda de programas por tipo
    int tipoBuscado = 2;
    teba.buscarProgramasPorTipo(tipoBuscado);

    // Búsqueda binaria por código en una universidad
    Universidad u = teba.getUniversidad(1);
    int n = u.getProgramas().getSize();
    int codigoBuscado = (n > 0) ? u.getProgramas()[n/2].getCodigo() : -1;
    //aqui podemos filtrar ingenieria 
    int posBin = u.buscarProgramaPorCodigoBinaria(codigoBuscado );
    cout << "\nBusqueda binaria por codigo " << codigoBuscado
         << " en " << u.getNombre()
         << " -> pos=" << posBin << (posBin>=0 ? " (ENCONTRADO)" : " (NO)") << "\n";

    return 0;
}