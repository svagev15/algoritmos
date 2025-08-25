#include <iostream>

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


class Cita {
private:
    int paciente;
    int medico;
    int enfermedad;
public:
    Cita() {
        paciente = -1; 
        medico = -1;
        enfermedad = -1;
    }
    Cita(int p, int m, int e) {
        paciente = p;
        medico = m;
        enfermedad = e;
    }
    
    //Getters
    int getPaciente() const { 
        return paciente; 
    }
    void setPaceinte(int p) { 
        paciente = p; 
    }
    int getMedico() const { 
        return medico; 
    }
    void setMedico(int m) { 
        medico = m; 
    }

    int getEnfermedad() const { 
        return enfermedad; 
    }
    void setProducto(int e) { 
        enfermedad = e; 
    }

    Cita& operator=(const Cita& f) {
        paciente = f.paciente;
        medico = f.medico;
        enfermedad = f.enfermedad;
        return *this;
    }

    string to_string() {
	    string s = std::to_string(paciente)+", "+std::to_string(medico)+", "+std::to_string(enfermedad);
	    return s;
	}

	friend std::ostream& operator<<(std::ostream& os, Cita& b) {
		return os << b.to_string();
	}
	
	friend std::ostream& operator<<(std::ostream& os, Cita b) {
		return os << b.to_string();
	}

};

// Clase nodo con plantilla
template<typename T>
class Nodo{
private:
  T dato;
  Nodo* next;

public:

 Nodo(T d){
     dato = d;
     next =  NULL;
 }
 
 ~Nodo(){
 }
 
 T get_dato(){
     return dato;
 }
 
 void set_dato(T d){
     dato = d;
 }
 
 Nodo* get_next(){
     return next;
 }
 
 void set_next(Nodo* n){
     next = n;
 }
 
 
    
};


// Clase lista enlazada con plantilla
template <typename T>
class Lista {
private:
    Nodo<T>* ptr;
    int size;
public:
    Lista(){
        ptr = NULL;
        size = 0;
    }
  
    ~Lista(){
        Nodo<T>* temp = ptr;
        if(ptr != NULL){
            Nodo<T>* temp_next = ptr->get_next();
            while(temp_next != NULL){
                delete temp;
                temp = temp_next;
                temp_next = temp->get_next();
            }
            delete temp; //Borrar el último nodo
        }
    }
    void add(T d){
        Nodo<T>* nodo = new Nodo<T>(d);
        
        if(ptr == NULL){//La lista está vacía
            ptr  = nodo;
        }else{//La lista no está vacía
            Nodo<T>* temp =  ptr;
            while(temp->get_next() != NULL){
                temp = temp->get_next();
            }
            temp->set_next(nodo);
        }
        size++;
    }
    
    void insert(T d, int i){
        if(i<=size && i>=0 && ptr != NULL){
            Nodo<T>* nodo = new Nodo<T>(d);
            if(i == 0){
                nodo->set_next(ptr);
                ptr = nodo;
            }else{
                int j = 0;
                Nodo<T>* temp =  ptr;
                while(j<i-1){
                    temp = temp->get_next();
                    j++;
                }
                nodo->set_next(temp->get_next());
                temp->set_next(nodo);
            }
            size++;
        }else{//Si el índice es incorrecto o la lista está vacía, se añade al final
            add(d);
        }
        
    }
    
    int get_size(){
        return size;
    }
    
    void print(){
        if(ptr == NULL){//La lista está vacía
            cout<<"La lista está vacía"<<endl;
        }else{//La lista no está vacía
            Nodo<T>* temp =  ptr;
            while(temp != NULL){
                cout<<temp->get_dato()<<"\t";
                temp = temp->get_next();
            }
            cout<<endl;
        }
    }
    
    void println(){
        if(ptr == NULL){//La lista está vacía
            cout<<"La lista está vacía"<<endl;
        }else{//La lista no está vacía
            Nodo<T>* temp =  ptr;
            while(temp != NULL){
                cout<<temp->get_dato()<<endl;
                temp = temp->get_next();
            }
            cout<<endl;
        }
    }
    
    Nodo<T>* get(int i){
        if(i>=0 && i<size){
          int j=0;
          Nodo<T>* temp = ptr;
          while(j<i){
              temp = temp->get_next();
              j++;
          }
          return temp;
        }
        return NULL;
    }
    
};


class EPSUrsa {
private:
    Lista <Cita> Citas;
    int** matriz;
    int* arreglo; 
    int np;
    int nm; 
    int ne; 
    int nc; 

public:
    EPSUrsa(int p = 100, int m = 100, int e = 100, int c = 100): np(p), nm(m), ne(e), nc(c) {
        matriz = crear_mat(nm, ne);
        arreglo = crear_arreglo(nc);
    }

    ~EPSUrsa() {
        destruir_mat(matriz, nm);
        destruir_arreglo(arreglo);
    }

    void init_lista() {
        Cita* t;
        int p; 
        int m;
        int e;
        for(int i = 0; i<nc; i++){
            p = rand()%np;
            m = rand()%nm;
            e = rand()%ne;
            t = new Cita(p,m,e);
            Citas.add(*t);
        }
        cout<<"Fueron creadas "<<Citas.get_size()<<" en la plataforma"<<endl;
        println();   
    }

    void print() {
        Citas.print();
    }

    void println(){
        Citas.println();
    }

    void calc_mat() {
        Nodo<Cita>* ptr = Citas.get(0);
        for (int i = 0; i < nc; i++) {
            matriz[ptr->get_dato().getMedico()][ptr->get_dato().getEnfermedad()]++;
            ptr = ptr->get_next();
        }
        cout << "Matriz de medicos por enfermdedad: " << endl;
        print_mat(matriz, nm, ne);
    }

    void generar_arreglo() {
        Nodo<Cita>* ptr = Citas.get(0);
        while (ptr != nullptr) {
            arreglo[ptr->get_dato().getEnfermedad()]++;  
            ptr = ptr->get_next();
        }
        cout << "Arreglo de Citas " << endl;
        print_arreglo(arreglo, nc);  
    }

    int enfermedad_mayor() {
        int max = 0;
        int enfermedad = -1;
        for (int i = 0; i < ne; i++) {
            int total = 0;
            for (int j = 0; j < nm; j++) {
                total += matriz[j][i];
            }
            if (total > max) {
                max = total;
                enfermedad = i;
            }
        }
        return enfermedad;
    }

    
    int enfermedad_menor() {
        int min = 1000000;
        int enfermedad = -1;
        for (int i = 0; i < ne; i++) {
            int total = 0;
            for (int j = 0; j < nm; j++) {
                total += matriz[j][i];
            }
            if (total < min) {
                min = total;
                enfermedad = i;
            }
        }
        return enfermedad;
    }
    
        // Devuelve el índice del médico con más citas en general
    int medico_mayor() {
        int max = -1;
        int doctor = -1;
        for (int j = 0; j < nm; j++) {
            int total = 0;
            for (int i = 0; i < ne; i++) {
                total += matriz[j][i];
            }
            if (total > max) {
                max = total;
                doctor = j;
            }
        }
        return doctor;
    }

    int medico_menor() {
        int min = 1000000;
        int doctor = -1;
        for (int j = 0; j < nm; j++) {
            int total = 0;
            for (int i = 0; i < ne; i++) {
                total += matriz[j][i];
            }
            if (total < min) {
                min = total;
                doctor = j;
            }
        }
        return doctor;
    }

    double promedio_citas() {
        int total_citas = 0;
        for (int j = 0; j < nm; j++) {
            for (int i = 0; i < ne; i++) {
                total_citas += matriz[j][i];
            }
        }
        return (double) total_citas / nm;
    }

    int medico_mayor_e(int enfermedad) {
        int max = -1;
        int doctor = -1;
        for (int j = 0; j < nm; j++) {
            if (matriz[j][enfermedad] > max) {
                max = matriz[j][enfermedad];
                doctor = j;
            }
        }
        return doctor;
    }

    
};

int main()
{
    srand(1234);
    int p = 10;
    int m = 10;
    int e = 10;
    int c = 100;
    EPSUrsa eps = EPSUrsa(p,m,e,c);
    eps.init_lista();
    
    cout<<endl;
    eps.calc_mat();
    
    cout<<"La enfermedad con mayor prevalencia es "<<eps.enfermedad_mayor()<<endl;
    cout<<"La enfermedad con menor prevalencia es "<<eps.enfermedad_menor()<<endl;
    cout<<"El medico con mayor numero de citas es "<<eps.medico_mayor()<<endl;
    cout<<"El medico con menor numero de citas es "<<eps.medico_menor()<<endl;
    cout<<"El promedio de citas por medico es "<<eps.promedio_citas()<<endl;

for(int i=0; i<e; i++){
    cout<<"La enfermedad "<<i<<" fue atendida con mayor frecuencia por el medico "<<eps.medico_mayor_e(i)<<endl;
}

    
    return 0;
}
