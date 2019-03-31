#include <iostream>
#include "arvoreb.h"
using namespace std;

int main(int argc, char const *argv[])
{
    //const int TAM = 10;
    //int v[] = {5, 2, 7, 1, 4, 6, 9, 3, 8, 10};
    ArvoreB treeInd(3);
    cout << "====ARVORE B====" << endl;
    /*
    for(int i=0; i<TAM; i++)
        treeInd.inserir(v[i]);
    */
    cout << "t: " << treeInd.grau_max << endl;
    cout << "INSERIR---------------------------------------"<<endl;
    /*
    treeInd.inserir(10);
    treeInd.print();
    treeInd.inserir(20);
    treeInd.print();
    treeInd.inserir(30);
    treeInd.print();
    treeInd.inserir(40);
    treeInd.print();
    treeInd.inserir(1);
    treeInd.print();
    treeInd.inserir(50);
    treeInd.print();
    */
    treeInd.inserir(10);
    treeInd.printTree();
    treeInd.inserir(20);
    treeInd.printTree();
    treeInd.inserir(30);
    treeInd.printTree();
    treeInd.inserir(40);
    treeInd.printTree();
    treeInd.inserir(1);
    treeInd.printTree();
    treeInd.inserir(50);
    treeInd.printTree();

    cout << "\nBUSCA---------------------------------------"<<endl;
    cout << 5 << ((treeInd.pesquisar(5))?" encontrado. ":" nao ") << endl;
    cout << 1 << ((treeInd.pesquisar(30))?" encontrado. ":" nao ") << endl;
    cout << 10 << ((treeInd.pesquisar(10))?" encontrado. ":" nao ") << endl;
    cout << 20 << ((treeInd.pesquisar(20))?" encontrado. ":" nao ") << endl;
    cout << 30 << ((treeInd.pesquisar(30))?" encontrado. ":" nao ") << endl;
    cout << 40 << ((treeInd.pesquisar(30))?" encontrado. ":" nao ") << endl;
    cout << 50 << ((treeInd.pesquisar(30))?" encontrado. ":" nao ") << endl;

    
    return 0;
}
