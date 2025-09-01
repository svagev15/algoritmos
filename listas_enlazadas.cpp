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
        if (p < 0 || p > size){
            cout << "Posición inválida" << endl;
            return;
        }
    
        Nodo<T> *nuevoNodo = new Nodo<T>(dato); // <-- corregido
    
        if (p == 0){
            nuevoNodo->setNext(ptr); // <-- ahora coincide
            ptr = nuevoNodo;
        }
        else {
            Nodo<T>* temp = ptr;
            int i = 0;
            while (i < p - 1) {
                temp = temp->getNext();
                i++;
            }
            nuevoNodo->setNext(temp->getNext());
            temp->setNext(nuevoNodo);
        }
        size++;
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
