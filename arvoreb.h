#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include <limits.h>
using namespace std;

class Nodo
{
    private:
        int* chaves; //#chaves[2t]
        Nodo** filhos; //#filhos[2t+1] - vetor de ponteiros
        int ivc; //indice vetor de chaves
        int ivf; //indice vetor de filhos
        
        bool insertChave(int* v, int tam, int value)
        {
            int item=value;
            for(int i=0; i<tam; i++)
            {
                if(item<v[i])
                {
                    int temp=v[i];
                    v[i]=item;
                    item=temp;
                }
                else if(item==v[i])
                    return false;
            }
            ivc += 1;
            return true;
        }

    public:
        bool isRaiz=false;
        bool isFolha=false;
        int quant_chaves;
        int quant_filhos;

        Nodo(int t) //t --> grau maximo
        {
            chaves = new int[t];
            filhos = new Nodo*[t+1];
            quant_chaves=t;
            quant_filhos=t+1;
            isRaiz=false;
            isFolha=true;
            ivc=0;
            ivf=0;
            for(int i=0; i<quant_chaves; i++)
                chaves[i] = INT_MAX;
            for(int i=0; i<quant_chaves; i++)
                filhos[i] = NULL;
        }

        bool isFolha()
        {
            for(int i=0; i<quant_chaves; i++)
            {
                if(filhos[i]!=NULL)
                    return false;
            }
            return true;
        }

        void breakNode(int* v, int tam)
        {
            int mediana=0; //indice da mediana;
            Nodo* esq = new Nodo(quant_chaves);
            Nodo* dir = new Nodo(quant_chaves);
            //Nodo<TIPO>* new_node = new Nodo<TIPO>(quant_chaves);
            //new_node->filhos[0]=esq;
            //new_node->filhos[1]=dir;

            if(tam%2==0) //numero par de chaves
                mediana=(tam/2)-1;
            else //numero impar de chaves
                mediana=tam/2;

            for(int i=0; i<mediana; i++)//copia chaves (valores) antes da mediana do nodo atual, para o novo nodo filho esq;
            {
                esq->chaves[i]=chaves[i];
                esq->ivc += 1;
            }
            for(int i=mediana+1, j=0; i<tam; i++, j++)//copia chaves (valores) depois da mediana do nodo atual, para o novo nodo filho dir;
            {
                dir->chaves[j]=chaves[i];
                dir->ivc += 1;
            }

            v[0]=v[mediana]; //reposicionar a medina no nodo atual
            ivc=1;
            for(int i=1; i<tam; i++)
                v[i]=INT_MAX;
            
            //redirecionar os ponteiros filhos do nodo atual, para esq e dir
            filhos[0]=esq;
            filhos[1]=dir;
        }
        
        void print()
        {
            cout << "[";
            for(int i=0; i<ivc; i++)
            {
                if(chaves[i] != INT_MAX)
                    cout << chaves[i];
                if(i<(ivc-1)) cout << ",";
            }
            cout << "]";
        }

    friend class ArvoreB;
};

class ArvoreB
{
    private:
        Nodo* raiz;
        bool inserir(int valor, Nodo* n);
        bool pesquisar(int value, Nodo* n)
        {
            Nodo* f = NULL; //nodo auxiliar, para salvar o filho, que será verificado, na proxima chamada.
            for(int i=0; i<grau_max; i++)
            {
                if(value==n->chaves[i]) //se achar o valor, retorna a confirmação.
                    return true;
            }
            if(n->isFolha) //se o NÓ for FOLHA, o elemento não está na arvore.
                return false;

            for(int i=0; i<grau_max; i++) //verica qual filho, será o proximo a ser verificado.
            {
                if(value < n->chaves[i])
                {
                    if(n->filhos[i] != NULL)
                        f = n->filhos[i];
                    else
                        return false;
                    break;
                }
            }
            if(f==NULL) //verifica se o ultimo filho, é proximo a ser verificado.
            {
                if(value > n->chaves[grau_max-1])
                    f = n->filhos[grau_max-1];
            }
            return pesquisar(value,f);
        }
    public:
        int grau_max=0;
        ArvoreB(int arg_grau_max)
        {
            raiz=NULL;
            grau_max=arg_grau_max;
        }
        void inserir(int valor)
        {
            if(raiz==NULL)
            {
                raiz = new Nodo(grau_max);
                raiz->isRaiz=true;
                inserir(valor,raiz);
            }
            else
            {
                inserir(valor,raiz);
            }
        }
        void remover(int valor);
        bool pesquisar(int valor)
        {
            return pesquisar(valor,raiz);
        }
        void preencherPorAtacado();
        void clear();
        void print();
};

bool ArvoreB::inserir(int valor, Nodo* n)
{
    if(n->isFolha)
    {
        return n->insertChave(n->chaves,grau_max,valor);
    }
    //Buscar
    //verificar intervalo para decidir o proximo filho a ser analizado.

}

void ArvoreB::remover(int valor)
{
    
}

void ArvoreB::clear()
{
    
}

void ArvoreB::print()
{
    cout << "(";
    raiz->print();
    for(int i=0; i<grau_max; i++)
    {
        if(raiz->filhos[i] != NULL)
            raiz->filhos[i]->print();
    }
    cout << ")"<<endl;
}

#endif