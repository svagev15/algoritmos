#include<iostream>
using namespace std;

template <typename T>
class Nodo{
  T dato;
  Nodo* next;
public:
    
    Nodo(){
        next = nullptr;
    }
    
    Nodo(T d){
        dato = d;
        next = nullptr;
    }
    
    T getDato(){
        return dato;
    }
    
    Nodo* getNext(){
        return next;
    }
    
    void setDato(T da){
        dato = da;
    }
    
    void setNext(Nodo<T>* n){
        next = n;
    }
    
    string to_string(){
        return std::to_string(dato);
    }

};

template <typename T>
class Lista{
  Nodo<T>* ptr;
  int size;
public:
    Lista(){
        ptr = nullptr;//se crea el puntero vacio
        size = 0;
    }
    
    void add(T dato){ 
        Nodo<T>* nuevoNodo = new Nodo<T>(dato);
        if(ptr == nullptr){//verificar si el vector esta vacio, si apunta a nulo esta vacio
            ptr = nuevoNodo;//crear un nuevo Nodo
        }else{//si no esta vacio
            Nodo<T>* temp = ptr;//un nodo temporal, comienza apuntadno al primero
            //while((*temp).getNext() != nullptr){
            while(temp->getNext() != nullptr){//mientras que el next no apunte a nulo quiere decir que no es el ultimo
                temp = temp->getNext();//que apunte al siguiente
            }
            temp->setNext(nuevoNodo);//para ponerlo al final
        }
        size++;
    }
    
    void print(){
        
    }
    
};

int main()
{
    srand(1234);
    
    Lista<int> l;
    
    for (int i = 0; i < 10; i++) {
        l.add(rand()%100);
    }
    
    l.print();
    
    return 0;
}
