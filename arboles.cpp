#include <iostream>
#include <string>
using namespace std;
class Nodo{
    int dato;
    Nodo* izq;
    Nodo* der;
public:
    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
    int getDato() const { return dato; }
    Nodo* getIzq() const { return izq; }
    Nodo* getDer() const { return der; }
    void setIzq(Nodo* nodo) { izq = nodo; }
    void setDer(Nodo* nodo) { der = nodo; }
    bool esHoja() const { return izq == nullptr && der == nullptr; }
    string to_string() const {
        return std::to_string(dato);
    }
    void print(){
        cout<<to_string();
    }
    friend ostream& operator<<(ostream& os, const Nodo& nodo) {
        os << nodo.to_string();
        return os;
    }
};
class Arbol{
    Nodo* raiz;
public:
    Arbol() : raiz(nullptr) {}
    void addRec(Nodo* nodo, int dato) {
        if(nodo->getDato() != dato){
            if(nodo->getDato() > dato){
                if(nodo->getIzq() == nullptr){
                    nodo->setIzq(new Nodo(dato));
                }else{
                    addRec(nodo->getIzq(), dato);
                }
            }else{
                if(nodo->getDer() == nullptr){
                    nodo->setDer(new Nodo(dato));
                }else{
                    addRec(nodo->getDer(), dato);
                }
            }
        }
    }
    void add(int dato){
        if(!raiz){
            raiz = new Nodo(dato); 
        }
        else{
            addRec(raiz, dato);
        }
    }
    // Método auxiliar para buscar un nodo por su valor
    Nodo* buscarNodoRec(Nodo* nodo, int valor) {
        if(nodo == nullptr || nodo->getDato() == valor) {
            return nodo;
        }
        if(valor < nodo->getDato()) {
            return buscarNodoRec(nodo->getIzq(), valor);
        } else {
            return buscarNodoRec(nodo->getDer(), valor);
        }
    }
    // Método auxiliar recursivo para buscar el padre
    Nodo* getPadreRec(Nodo* nodo, int valor) {
        if(nodo == nullptr) {
            return nullptr; // No se encontró
        }
        
        // Verificar si alguno de los hijos tiene el valor buscado
        if((nodo->getIzq() != nullptr && nodo->getIzq()->getDato() == valor) ||
           (nodo->getDer() != nullptr && nodo->getDer()->getDato() == valor)) {
            return nodo; // Este es el padre
        }
        
        // Buscar en el subárbol correspondiente según BST
        if(valor < nodo->getDato()) {
            return getPadreRec(nodo->getIzq(), valor);
        } else {
            return getPadreRec(nodo->getDer(), valor);
        }
    }

    // Método público para obtener el padre de un nodo con valor dado
    Nodo* getPadre(int valor) {
        // Si el valor es la raíz, no tiene padre
        if(raiz == nullptr || raiz->getDato() == valor) {
            return nullptr;
        }
        
        return getPadreRec(raiz, valor);
    }

    // Método para obtener el hijo izquierdo de un nodo
    Nodo* getHijoIzquierdo(int valor) {
        Nodo* nodo = buscarNodoRec(raiz, valor);
        
        if(nodo == nullptr) {
            return nullptr; // El nodo no existe
        }
        
        return nodo->getIzq(); // Puede ser nullptr si no tiene hijo izquierdo
    }

    // Método para obtener el hijo derecho de un nodo
    Nodo* getHijoDerecho(int valor) {
        Nodo* nodo = buscarNodoRec(raiz, valor);
        
        if(nodo == nullptr) {
            return nullptr; // El nodo no existe
        }
        
        return nodo->getDer(); // Puede ser nullptr si no tiene hijo derecho
    }

    // Método auxiliar recursivo para calcular la altura
    int getAlturaRec(Nodo* nodo) {
        if(nodo == nullptr) {
            return -1; // Altura de árbol vacío es -1
        }
        
        int alturaIzq = getAlturaRec(nodo->getIzq());
        int alturaDer = getAlturaRec(nodo->getDer());
        
        // La altura es 1 + la máxima altura de sus subárboles
        return 1 + max(alturaIzq, alturaDer);
    }

    // Método público para obtener la altura del árbol
    int getAltura() {
        return getAlturaRec(raiz);
    }

    // Sobrecarga: obtener altura desde un nodo específico
    int getAltura(int valor) {
        Nodo* nodo = buscarNodoRec(raiz, valor);
        if(nodo == nullptr) {
            return -1; // Nodo no existe
        }
        return getAlturaRec(nodo);
    }

    void preordenRec(Nodo* nodo){
        if(nodo){
            cout<<nodo->getDato()<<", ";
            preordenRec(nodo->getIzq());
            preordenRec(nodo->getDer());
        }
    }

    void preorden(){
        preordenRec(raiz);
        cout<<endl;
    }

    void inordenRec(Nodo* nodo){
        if(nodo){
            inordenRec(nodo->getIzq());
            cout<<nodo->getDato()<<", ";
            inordenRec(nodo->getDer());
        }
    }

    void inorden(){
        inordenRec(raiz);
        cout<<endl;
    }

    void posordenRec(Nodo* nodo){
        if(nodo){
            posordenRec(nodo->getIzq());
            posordenRec(nodo->getDer());
            cout<<nodo->getDato()<<", ";
        }
    }

    void posorden(){
        posordenRec(raiz);
        cout<<endl;
    }
    
    // Función que equilibra el árbol si es necesario
    void balance(AvlNode *&t) {
        if (!t) return; // Si el nodo está vacío, no hace nada

        // Si el árbol está desequilibrado hacia el subárbol izquierdo
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            // Si el subárbol izquierdo está desequilibrado hacia la izquierda
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            // Si el subárbol izquierdo está desequilibrado hacia la derecha
            else doubleWithLeftChild(t);
        }
        // Si el árbol está desequilibrado hacia el subárbol derecho
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            // Si el subárbol derecho está desequilibrado hacia la derecha
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            // Si el subárbol derecho está desequilibrado hacia la izquierda
            else doubleWithRightChild(t);
        }

        // Actualiza la altura del nodo
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    // Rotación simple hacia la izquierda (para corregir desequilibrio)
    void rotateWithLeftChild(AvlNode *&k2) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    // Rotación simple hacia la derecha (para corregir desequilibrio)
    void rotateWithRightChild(AvlNode *&k2) {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    // Rotación doble hacia la izquierda (para corregir desequilibrio)
    void doubleWithLeftChild(AvlNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    // Rotación doble hacia la derecha (para corregir desequilibrio)
    void doubleWithRightChild(AvlNode *&k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }
};

int main(){
    srand(1234);
    Arbol arbol;
    int t;
    cout << "Valores insertados: ";
    for(int i = 0; i<10;i++){
        t = rand()%100;
        cout<<t<<", ";
        arbol.add(t);
    }
    cout<<endl;
    cout<<"Recorrido en preorden: "<<endl;
    arbol.preorden();
    cout<<endl;
    cout<<"Recorrido en inorden: "<<endl;
    arbol.inorden();
    cout<<endl;
    cout<<"Recorrido en posorden: "<<endl;
    arbol.posorden();
    // Probar el método getPadre
    cout<<endl;
    cout<<"===== Pruebas de metodos ====="<<endl;
    int valorBuscar = 41;
    Nodo* padre = arbol.getPadre(valorBuscar);
    if(padre != nullptr) {
        cout<<"El padre de "<<valorBuscar<<" es: "<<padre->getDato()<<endl;
    } else {
        cout<<"El nodo "<<valorBuscar<<" no tiene padre (es raiz o no existe)"<<endl;
    }
    // Probar getHijoIzquierdo
    cout<<endl;
    int valorPadre = 41;
    Nodo* hijoIzq = arbol.getHijoIzquierdo(valorPadre);
    if(hijoIzq != nullptr) {
        cout<<"El hijo izquierdo de "<<valorPadre<<" es: "<<hijoIzq->getDato()<<endl;
    } else {
        cout<<"El nodo "<<valorPadre<<" no tiene hijo izquierdo"<<endl;
    }
    // Probar getHijoDerecho
    Nodo* hijoDer = arbol.getHijoDerecho(valorPadre);
    if(hijoDer != nullptr) {
        cout<<"El hijo derecho de "<<valorPadre<<" es: "<<hijoDer->getDato()<<endl;
    } else {
        cout<<"El nodo "<<valorPadre<<" no tiene hijo derecho"<<endl;
    }
    // Probar getAltura
    cout<<endl;
    cout<<"La altura del arbol completo es: "<<arbol.getAltura()<<endl;
    
    cout<<"La altura desde el nodo "<<valorPadre<<" es: "<<arbol.getAltura(valorPadre)<<endl;

    return 0;
}
