// Online C Compiler - Build, Compile and Run your C programs online in your favorite browser
//https://www.online-cpp.com/E8plckSIUj
#include<iostream>
using namespace std;

class Vector{
private:
    int* v;
    int capacidad;    
    int size;
    
public:
    Vector(){
        capacidad = 5;
        size = 0;
        v = new int[capacidad];
    }
    
    Vector(int t){
        if(t <= 0){
            t = 1;
        }
        capacidad = t;
        size = 0;
        v = new int[capacidad];
    }
    
    void add(int dato){
        if(size == capacidad){
            resize();
        }else{
            v[size++] = dato;
        }
    }
    
    void resize(){
        //Aumentar capacidad
        //Crear un nuevo Vector
        //Almacenar los datos del viejo
        //Borrar el vector viejo
    }
    
    void print(){
        for (int i = 0; i < size; i++) {
            cout<<v[i]<<"\t";
        }
        cout<<endl;
    }
    
    int getSize(){
        return size;
    }
    
    int getCapacidad(){
        return capacidad;
    }
    
    
};


class Matriz{
  
  int c;
  int f;
  int** m;
 
 public:
 
    Matriz(){
        crearMatriz(5, 5);
    }
    
    Matriz(int f1, int c1){
        crearMatriz(f1, c1);
    }
    
    Matriz(int f1, int c1, bool random){
        crearMatriz(f1, c1, random);
    }
    
    int** getM(){
        return m;
    }
    
    int getC(){
        return c;
    }
    
    int getF(){
        return f;
    }
    
    void crearMatriz(int f1, int c1){
        crearMatriz(f1, c1, false);
    }
    
    void crearMatriz(int f1, int c1, bool random){
        f = f1;
        c = c1;
        m = new int*[f];
        for (int i = 0; i < f; i++) {
            m[i] = new int[c];
            for (int j = 0; j < c; j++) {
                if(!random){
                    m[i][j] = 0;
                }else{
                    m[i][j] = rand()%1000;
                }
            }
        }
    }
    
    void addFila(){
        int** mtemp = new int*[f+1];
        for (int i = 0; i < f; i++) {
            mtemp[i] = m[i];
        }
        mtemp[f] = new int[c];
        for (int i = 0; i < c; i++) {
            mtemp[f][i] = 0;
        }
        f++;
        delete[] m;
        m = mtemp;
        
    }
    
    void addColum(){
    for (int i = 0; i < f; i++) {
        int* temp = new int[c + 1];
        for (int j = 0; j < c; j++) {
            temp[j] = m[i][j];
        }
        temp[c] = 0; 
        delete[] m[i]; 
        m[i] = temp;   
    }
    c++; 
}

    
    void print(){
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                cout<<m[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
  
    int sum(){
        int sum=0;
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                sum+=m[i][j];
            }
        }
        return sum;
    }
    
};


int sum(int** m){
    int sum=0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            sum+=m[i][j];
        }
    }
    return sum;
}

int sum(Matriz m){
    int sum=0;
    int** tempM = m.getM(); 
    int f = m.getF();
    int c = m.getC();
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            sum+=tempM[i][j];
        }
    }
    return sum;
}




int main()
{
    srand(1234);
    
    /*Vector v;
    
    for (int i = 0; i < 6; i++) {
        v.add(i*17);
    }
    
    v.print();*/
    
    Matriz m(6,6,true);
    
    m.print();
    
    cout<<sum(m.getM())<<endl;
    cout<<sum(m)<<endl;
    cout<<m.sum()<<endl;
    m.addFila();
    m.addColum();
    m.print();
    
    return 0;
}
