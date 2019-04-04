#include <iostream>
#include "arvoreb.h"
#include "commands.h"
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
    mytree.inserir(20);
    mytree.imprimir();
    mytree.inserir(30);
    mytree.imprimir();
    mytree.inserir(40);
    mytree.imprimir();
    mytree.inserir(15);
    mytree.imprimir();
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

    cout << "====BUSCA====" << endl;
    cout << 11 << ((mytree.busca(11))?(" encontrado"):(" não")) << endl;
    cout << -1 << ((mytree.busca(-1))?(" encontrado"):(" não")) << endl;

    cout << 10 << ((mytree.busca(10))?(" encontrado"):(" não")) << endl;
    cout << 20 << ((mytree.busca(20))?(" encontrado"):(" não")) << endl;
    cout << 30 << ((mytree.busca(30))?(" encontrado"):(" não")) << endl;
    cout << 40 << ((mytree.busca(40))?(" encontrado"):(" não")) << endl;
    cout << 15 << ((mytree.busca(15))?(" encontrado"):(" não")) << endl;
    cout << 5 << ((mytree.busca(5))?(" encontrado"):(" não")) << endl;
    cout << 50 << ((mytree.busca(50))?(" encontrado"):(" não")) << endl;
    cout << 60 << ((mytree.busca(60))?(" encontrado"):(" não")) << endl;
    cout << 70 << ((mytree.busca(70))?(" encontrado"):(" não")) << endl;
    cout << 25 << ((mytree.busca(25))?(" encontrado"):(" não")) << endl;
    cout << 35 << ((mytree.busca(35))?(" encontrado"):(" não")) << endl;
    cout << 18 << ((mytree.busca(18))?(" encontrado"):(" não")) << endl;
    cout << 22 << ((mytree.busca(22))?(" encontrado"):(" não")) << endl;
    cout << 80 << ((mytree.busca(80))?(" encontrado"):(" não")) << endl;
    cout << 90 << ((mytree.busca(90))?(" encontrado"):(" não")) << endl;
    cout << 100 << ((mytree.busca(100))?(" encontrado"):(" não")) << endl;
    cout << 110 << ((mytree.busca(110))?(" encontrado"):(" não")) << endl;
    cout << 120 << ((mytree.busca(120))?(" encontrado"):(" não")) << endl;
    cout << 130 << ((mytree.busca(130))?(" encontrado"):(" não")) << endl;
    cout << 19 << ((mytree.busca(19))?(" encontrado"):(" não")) << endl;
    cout << 16 << ((mytree.busca(16))?(" encontrado"):(" não")) << endl;
    cout << 21 << ((mytree.busca(21))?(" encontrado"):(" não")) << endl;
    cout << 17 << ((mytree.busca(17))?(" encontrado"):(" não")) << endl;

    cout << 200 << ((mytree.busca(200))?(" encontrado"):(" não")) << endl;
    cout << 300 << ((mytree.busca(300))?(" encontrado"):(" não")) << endl;

    cout << "====RAIZ====" << endl;
    mytree.printRaiz();

    return 0;
}
