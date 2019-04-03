#include <iostream>
#include "arvoreb.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int grau_min=0;

    if(argc<2)
    {
        cout << "Ops! informe o parametro GRAU_MIN." << endl;
        return 0;
    }

    grau_min = atoi(argv[1]);
    if(grau_min<2)
    {
        cout << "Ops! o parametro GRAU_MIN tem q ser MAIO ou IGUAL a 2." << endl;
        return 0;
    }

    cout << "====ARVORE B====" << endl;
    ArvoreB mytree(grau_min);

    ///*
    mytree.inserir(10);
    mytree.imprimir();
    cout << "raiz: ";
    mytree.printRaiz();
    mytree.inserir(20);
    mytree.imprimir();
    cout << "raiz: ";
    mytree.printRaiz();
    mytree.inserir(30);
    mytree.imprimir();
    cout << "raiz: ";
    mytree.printRaiz();
    mytree.inserir(40);
    mytree.imprimir();
    cout << "raiz: ";
    mytree.printRaiz();
    mytree.inserir(15);
    mytree.imprimir();
    cout << "raiz: ";
    mytree.printRaiz();
    mytree.inserir(5);
    mytree.imprimir();
    mytree.inserir(50);
    mytree.imprimir();
    mytree.inserir(60);
    mytree.imprimir();
    mytree.inserir(70);
    mytree.imprimir();
    mytree.inserir(25);
    mytree.imprimir();
    mytree.inserir(35);
    mytree.imprimir();
    mytree.inserir(18);
    mytree.imprimir();
    mytree.inserir(22);
    mytree.imprimir();
    mytree.inserir(80);
    mytree.imprimir();
    mytree.inserir(90);
    mytree.imprimir();
    mytree.inserir(100);
    mytree.imprimir();
    mytree.inserir(110);
    mytree.imprimir();
    mytree.inserir(120);
    mytree.imprimir();
    mytree.inserir(130);
    mytree.imprimir();
    mytree.inserir(19);
    mytree.imprimir();
    mytree.inserir(16);
    mytree.imprimir();
    mytree.inserir(21);
    mytree.imprimir();
    mytree.inserir(17);
    mytree.imprimir();
    //*/

    cout << "====RAIZ====" << endl;
    mytree.printRaiz();

    return 0;
}
