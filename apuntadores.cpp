#include<iostream>
using namespace std;
int main()
{
    srand(1234);
    int a;
    a=5;
    cout<<&a<<" "<<a<<endl;
    
    //el simbolo * apunta y me da el valor 
    int* b = new int(3);
    cout<<&b<<" "<<b<<" "<<*b<<endl;
    delete b;
    cout<<&b<<" "<<b<<" "<<*b<<endl;
    b = &a;
    cout<<&b<<" "<<b<<" "<<*b<<endl;
    *b = 12;
    cout<<&a<<" "<<a<<endl;
    cout<<&b<<" "<<b<<" "<<*b<<endl;
    
    int tam = 5;
    int* v = new int[tam];
    
    for (int i = 0; i < tam; i++) {
        v[i] = rand()%100;
    }
    
    for (int i = 0; i < tam; i++) {
        cout<<v[i]<<"\t";
    }
    cout<<endl;



    //redimensionar un vector manualmente
    int* v_temp = new int[tam*2];//con new guardamos el espacio de memoria del vector inicial, se pone tam*2 para que sea el doble de tamano del vector 1
    
    //llenamos el nuevo vector con los datos del vector anterior en la misma posicion
    for (int i = 0; i < tam; i++) {
        v_temp[i] = v[i];
    }

    //subimnos la capacidad del vector 1
    tam *= 2;

    //liberamos la memoria del arreglo nuevo, se eliminan los elementos pero ya tenemos la capacidad al doble
    delete[] v;

    //ahora hacemos que apuine hacia el nuevo vector
    v = v_temp;

    //llenamos la parte del vector nuevo con numero aleatorios, como el vector inicial tenia la mitad de capacidad, por eso comienza desde la posicion tam/2
    for (int i = tam/2; i < tam; i++) {
        v[i] = rand()%100;
    }

    //se imprime el nuevo vector
    for (int i = 0; i < tam; i++) {
        cout<<v[i]<<"\t";
    }
    
    cout<<endl;

    //toca eliminar la memoria al final, es como si luego de que comes en el restaurante te vas si avisar y el mesero cree que la mesa isuge ocupada
    delete[] v;
    
    
    return 0;
}
