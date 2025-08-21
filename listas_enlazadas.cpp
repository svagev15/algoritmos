//poner remove, find, removeall


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
    
    
    void insert(int p, int dato){
        if (p <0 || p>size){//si la posicion es mayor al tamaño o menos a cero no se puede insertar
            cout<<"posicion invalida " << endl;
            return ;
        }
        Nodo<T> *nodonuevo = new Nodo<T>(dato); //se crea el nuevo nodo en donde se alamcena el elemtneo que inserte el usuario
        
        if (p==0){//si quiereo insertar el dato al inicio 
            nuevoNodo -> setNext(ptr);
            ptr = nuevoNodo;
        }
        else {
            Nodo<T>* temp = ptr; // se crea un nodo ¿temporal para recorreer y empezamos desde el primero
            int i =0;

            while(i< p-1 ){ // mientras no lleguemos al final
                temp = temp->getNext(); // avanzamos al siguiente
            }
            nuevoNodo->setNext(temp->getNext());//el nuevo nodo apunta al que estaba despues de temp
            temp->setNext(nuevoNodo);//el anterior a temp apunta al nuevo nodo
        }
            
        }
    }

    
    void print(){
        Nodo<T>* temp = ptr; // empezamos desde el primero
        while(temp != nullptr){ // mientras no lleguemos al final
            cout << temp->getDato() << " "; // imprimimos el dato
            temp = temp->getNext(); // avanzamos al siguiente
        }
        cout << endl; // salto de línea al final
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
    l.insert(2,40);
    
    return 0;
}
