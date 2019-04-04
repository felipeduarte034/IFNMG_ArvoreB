#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
using namespace std;

class Nodo
{
private:
    int* chaves; //#chaves[t-1, 2t-1]
    Nodo** filhos; //#filhos[2t+1] - vetor de ponteiros
    int len; //quantidade de chaves no nodo
    int maxf; //quantidade maxima de filhos
public:
    bool isFolha=false;
    Nodo(int t) //t --> grau minimo
    {
        maxf = 2*t;
        chaves = new int[2*t-1];
        filhos = new Nodo*[2*t];
        len=0;
        for(int i=0; i<maxf; i++)
            filhos[i]=NULL;
    }
    bool is_folha()
    {
        for(int i=0; i<maxf; i++)
        {
            if(filhos[i]!=NULL)
                return false;
        }
        return true;
    }
    
    void print() //printa as chaves em sequencia separadas por virgula
    {
        for(int i=0; i<len; i++)
        {
            cout << chaves[i];
            if(i<(len-1)) cout << ",";
        }
    }
friend class ArvoreB;
};

class ArvoreB
{
private:
    Nodo* raiz;
    void CreateRoot()
    {
        raiz = new Nodo(t);
        raiz->isFolha=true;
        raiz->len=0;
    }
    bool Search(Nodo* n, int k)
    {
        int i=0;
        while(i<n->len && k>n->chaves[i]) //ajusta o indice do filho
        {
            i+=1;
        }
        if(i<n->len && k==n->chaves[i]) //verica se a valor buscado está nas chaves do nodo
        {
            return true;
        }
        else if(n->is_folha()) //se for folha o elemento não está contido na arvore
        {
            return false;
        }
        return Search(n->filhos[i],k);
    }
    void SplitRaiz(Nodo* n, int i, Nodo* esq)
    {
        /*cout << "  SplitRaiz  i: " << i << endl;
        cout << "  1: "; printNodoAndChild(n);
        cout << "  2: "; printNodoAndChild(esq);*/
        Nodo* dir = new Nodo(t);
        dir->isFolha=esq->isFolha;
        for(int j=1; j<=(t-1); j++) //passa para dir as maiores chaves
        {
            InsertNoFull(dir,esq->chaves[j+(t-1)]);
        }
        if(!esq->is_folha())
        {
            //cout << "    j: " <<  dir->len << "  t: " << t << "  (j<=t)" << endl;
            for(int j=dir->len, m=0; m<(dir->len+1); j--,m++)
            {
                //cout << "    j: " << j << "  t: " << t << "    esq->filhos[j+t]: "; printNodoAndChild(esq->filhos[j+t]);
                dir->filhos[j] = esq->filhos[j+t];
                esq->filhos[j+t] = NULL;
            }
        }
        esq->len=t-1; //ajusta a contagem de chaves para o nodo com as menores chaves

        for(int j=n->len+1; j<(i+1); j++)
        {
            n->filhos[j+1] = n->filhos[j]; //empurra os filhos para direita
        }
        /*cout << "  esq: "; printNodoAndChild(esq);
        cout << "  dir: "; printNodoAndChild(dir);
        cout << "  3: "; printRaiz();*/
        n->filhos[i]=dir; //inserem dir como filho de n
        //cout << "  4: "; printRaiz();
        for(int j=n->len; j<i; j++)
        {
            n->chaves[j+1] = n->chaves[j];
        }
        n->chaves[i-1] = esq->chaves[t-1];//move a chave mediana de esq para n
        //cout << "    MEDIANA  n->chaves[i-1] i-1: " << i-1 << "  esq->chaves[t-1]: " << esq->chaves[t-1] << endl;
        n->len = n->len+1; //ajusta a contagem de chaves de n
        /*cout << "  5: "; imprimir();
        cout << "  6: "; printRaiz();
        cout << "  7: "; printNodoAndChild(n);*/
    }
    void SplitChild(Nodo* n, int i, Nodo* esq)
    {
        /*cout << "  SplitChild  i: " << i << endl;
        cout << "  1: "; printNodoAndChild(n);
        cout << "  2: "; printNodoAndChild(esq);*/
        Nodo* dir = new Nodo(t);
        dir->isFolha=esq->isFolha;
        for(int j=1; j<=(t-1); j++) //passa para dir as maiores chaves
        {
            InsertNoFull(dir,esq->chaves[j+(t-1)]);
        }
        if(!esq->is_folha())
        {
            //cout << "    j: " <<  dir->len << "  t: " << t << "  (j<=t)" << endl;
            for(int j=dir->len, m=0; m<(dir->len+1); j--,m++)
            {
                //cout << "    j: " << j << "  t: " << t << "    esq->filhos[j+t]: "; printNodoAndChild(esq->filhos[j+t]);
                dir->filhos[j] = esq->filhos[j+t];
                esq->filhos[j+t] = NULL;
            }
        }
        esq->len=t-1; //ajusta a contagem de chaves para o nodo com as menores chaves
        //cout << "    n->len+1: " <<  n->len+1 << "  i: " << i << "  (j<(i+1))" << endl;
        for(int j=n->len+1; j>i; j--) //inserem dir como filho de n
        {
            n->filhos[j+1] = n->filhos[j]; //empurra os filhos para direita
        }
        /*cout << "  esq: "; printNodoAndChild(esq);
        cout << "  dir: "; printNodoAndChild(dir);
        cout << "  3: "; printNodoAndChild(n);*/
        n->filhos[i+1] = dir; //inserem dir como filho de n
        //cout << "  4: "; printNodoAndChild(n);
        //cout << "    n->len: " <<  n->len << "  i: " << i << "  (j<i)" << endl;
        for(int j=n->len-1; j>=i; j--)
        {
            n->chaves[j+1] = n->chaves[j];
        }
        n->chaves[i] = esq->chaves[t-1];//move a chave mediana de esq para n
        //cout << "    MEDIANA n->chaves[i] i: " << i << "  esq->chaves[t-1]: " << esq->chaves[t-1] << endl;
        n->len = n->len+1; //ajusta a contagem de chaves de n
        //cout << "  5: "; printNodoAndChild(n);
    }
    void InsertNoFull(Nodo* n, int k)
    {
        int i=n->len; //quantidade de chaves no nodo
        if(n->is_folha())
        {
            while(i>=1 && k<n->chaves[i-1]) //enquanto k < chave na ultima posiçao
            {
                n->chaves[i] = n->chaves[i-1]; //mover a chave para a direita
                i = i-1;
            }
            n->chaves[i]=k;
            n->len = n->len+1;
        }
        else
        {
            //cout << "    -  InsertNoFull i: " << i << "  k: " << k << endl;
            while(i>=1 && k<n->chaves[i-1]) //determina o filho de n
            {
                i-=1;
            }
            //i+=1;
            //cout << "    -  InsertNoFull 2  i: " << i << "  k: " << k << endl;
            if(n->filhos[i]->len == (2*t-1)) //verifica se a recursão desceria até um filho completo
            {
                /*cout << "  n->filhos[i]->len == (2*t-1): " << (2*t-1) << endl;
                cout << "    dividir nodo: ";
                n->filhos[i]->print();
                cout << endl;*/
                SplitChild(n,i,n->filhos[i]); //dividi esse filho em 2 filhos não-completos
                if(k > n->chaves[i]) //determina qual dos 2 filhos é agora o correto para descer
                    i+=1;
            }
            /*cout << "    -  InsertNoFull 3  i: " << i << "  k: " << k << endl;
            cout << "    inserir k no nodo: ";
            n->filhos[i]->print();
            cout<<endl;*/
            InsertNoFull(n->filhos[i],k); //utiliza recursão para inserir na sub-arvore apropriada
        }
        
    }
    void Insert(int k)
    {
        if(raiz->len==(2*t-1)) //a raiz está cheia
        {
            //cout << "  COMPLETO: raiz->len==(2*t-1) " << (2*t-1) << "  k: " << k << endl;
            Nodo* r = raiz;
            Nodo* s = new Nodo(t);
            raiz=s;
            s->isFolha=false;
            s->len=0;
            s->filhos[0]=r;
            SplitRaiz(s,1,r);
            InsertNoFull(s,k);
        }
        else
            InsertNoFull(raiz,k);
    }
    void Print(Nodo* n)
    {
        if(n->is_folha())
            n->print();
        for(int i=0; i<n->maxf; i++)
        {
            if(n->filhos[i] != NULL)
            {
                cout << "(";
                Print(n->filhos[i]);
                cout << ")";
                if(i < n->len)
                    cout << " " << n->chaves[i] << " ";
            }
        }
    }
public:
    int t; //grau minimo
    ArvoreB(int arg_grau_min)
    {
        t=arg_grau_min;
        CreateRoot();
        //cout << "(grau min) t = " << arg_grau_min << endl;
    }
    bool buscar(int valor)
    {
        if(raiz==NULL)
        {
            cout << "BUSCA não pode ser executada, RAIZ == NULL"<<endl;
            return false;
        }
        return Search(raiz,valor);
    }
    void inserir(int valor)
    {
        Insert(valor);
    }
    void imprimir()
    {
        cout << "(";
        Print(raiz);
        cout << ")"<<endl;
    }
    void printRaiz()
    {
        cout << "[";
        raiz->print();
        cout << "]";
        cout << " ---> ";
        for(int i=0; i<raiz->maxf; i++)
        {
            cout << "(";
            if(raiz->filhos[i] != NULL)
                raiz->filhos[i]->print();
            cout << ")";
        }
        cout<<endl;
    }
    void printNodoAndChild(Nodo* n)
    {
        cout << "Nodo: [";
        n->print();
        cout << "]";
        cout << " ---> ";
        for(int i=0; i<n->maxf; i++)
        {
            cout << "(";
            if(n->filhos[i] != NULL)
                n->filhos[i]->print();
            cout << ")";
        }
        cout<<endl;
    }
};

#endif