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
    
    treeInd.inserir(15);
    treeInd.inserir(7);
    treeInd.inserir(1);
    treeInd.print();

    cout << "contem 5: " << treeInd.pesquisar(5) << endl;
    cout << "contem 15: " << treeInd.pesquisar(15) << endl;
    cout << "contem 7: " << treeInd.pesquisar(7) << endl;
    cout << "contem 1: " << treeInd.pesquisar(1) << endl;
    
   

    return 0;
}
