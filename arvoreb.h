#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include <limits.h>
using namespace std;

class Nodo;

class ReturnInfo
{
    public:
        bool isBreak;
        bool isInsert;
        Nodo* esq;
        Nodo* dir;
        int mediana;
        ReturnInfo()
        {
            isBreak=false;
            isInsert=false;
            esq=NULL;
            dir=NULL;
            mediana=INT_MAX;
        }
        ReturnInfo(bool is_break,bool is_insert,Nodo* p_esq,Nodo* p_dir,int chave_mediana)
        {
            isBreak=is_break;
            isInsert=is_insert;
            esq=p_esq;
            dir=p_dir;
            mediana=chave_mediana;
        }
};

class Nodo
{
    private:
        int* chaves; //#chaves[2t]
        Nodo** filhos; //#filhos[2t+1] - vetor de ponteiros
        int ivc; //indice vetor de chaves
        int ivf; //indice vetor de filhos
        
        bool insertChave(int* v, int tam, int value) //insere ordenadamente o valor no vetor de chaves
        {
            int item=value;
            for(int i=0; i<tam && i<=ivc; i++)
            {
                if(item<v[i])
                {
                    int temp=v[i];
                    v[i]=item;
                    item=temp;
                }
            }
            ivc += 1;
            return true;
        }

        bool insertMediana(Nodo* n, int value, Nodo* dir)
        {
            int item=value;
            Nodo* itemNodo=dir;

            for(int i=0; i<quant_chaves; i++) //inseri o valor ordenadamente
            {
                if(item<n->chaves[i])
                {
                    int temp=n->chaves[i];
                    n->chaves[i]=item;
                    item=temp;
                }
            }
            ivc += 1;
            /*
            //if(value==2)
            {
                cout << "VALORES NODO: ";
                n->printNode();
                cout << endl;
            }
            */
            /*
            //if(value==2)
            {
                cout << "dir: ";
                dir->printNode();
                cout << "\n\nPRINT 1: ";
                for(int j=0; j<quant_filhos; j++)
                {
                    if(filhos[j] != NULL)
                        filhos[j]->printNode();
                    else
                        cout << " NULL ";
                }
                cout << endl;
            }
            */

            //inseri o novo Nodo Filho no intervalo correto, empurrando os demais
            for(int i=0; i<quant_filhos; i++) //inseri o valor ordenadamente
            {
                if(n->filhos[i] == NULL)
                {
                    n->filhos[i]=itemNodo;
                    break;
                }
                if(itemNodo->chaves[0] < n->filhos[i]->chaves[0])
                {
                    Nodo* temp=n->filhos[i];
                    n->filhos[i]=itemNodo;
                    itemNodo=temp;
                }
            }
            /*
            //if(value==2)
            {
                cout << "PRINT 2: ";
                for(int j=0; j<quant_filhos; j++)
                {
                    if(filhos[j] != NULL)
                        filhos[j]->printNode();
                    else
                        cout << " NULL ";
                }
                cout << endl;
            }
            */
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

        bool is_folha()
        {
            for(int i=0; i<quant_chaves; i++)
            {
                if(filhos[i]!=NULL)
                    return false;
            }
            return true;
        }

        ReturnInfo* breakNode(Nodo* n, int tam)
        {
            int mediana=0; //indice da mediana;
            Nodo* irmao = new Nodo(quant_chaves);
            ReturnInfo* rinfo = new ReturnInfo();

            if(tam%2==0) //numero par de chaves
                mediana=(tam/2)-1;
            else //numero impar de chaves
                mediana=tam/2;
            rinfo->mediana = n->chaves[mediana];

            for(int i=mediana+1, j=0; i<tam; i++, j++)//copia chaves (valores) depois da mediana do nodo atual, para o novo nodo filho;
            {
                irmao->chaves[j]=chaves[i];
                irmao->ivc += 1;
            }
            for(int i=mediana; i<tam; i++)
            {
                n->chaves[i]=INT_MAX;
                n->ivc -= 1;
            }

            rinfo->esq = n;
            rinfo->dir = irmao;
            rinfo->isBreak = true;
            return rinfo;
        }

        void breakNodeRaiz(Nodo* n, int tam)
        {
            int mediana=0; //indice da mediana;
            Nodo* esq = new Nodo(quant_chaves);
            Nodo* dir = new Nodo(quant_chaves);

            if(tam%2==0) //numero par de chaves
                mediana=(tam/2)-1;
            else //numero impar de chaves
                mediana=tam/2;

            for(int i=0; i<mediana; i++)//copia chaves (valores) antes da mediana do nodo atual, para o novo nodo filho esq;
            {
                esq->chaves[i]=n->chaves[i];
                esq->ivc += 1;
            }
            for(int i=mediana+1, j=0; i<tam; i++, j++)//copia chaves (valores) depois da mediana do nodo atual, para o novo nodo filho dir;
            {
                dir->chaves[j]=n->chaves[i];
                dir->ivc += 1;
            }

            n->chaves[0]=n->chaves[mediana]; //reposicionar a medina no nodo atual
            n->ivc=1;
            for(int i=1; i<tam; i++)
                n->chaves[i]=INT_MAX;

            if(!n->is_folha()) //se RAIZ tiver filhos, é feito o redirecionamento dos apontadores.
            {
                bool first=true;
                for(int i=0,e=0,d=0; i<quant_filhos; i++)
                {
                    if(first) //inicia pelo nodo esq
                    {
                        if(esq->chaves[e] == INT_MAX)
                        {
                            first=false;
                            esq->filhos[e] = n->filhos[i];
                            e++;
                        }
                        else if(n->filhos[i]->chaves[0] < esq->chaves[e])
                        {
                            esq->filhos[e] = n->filhos[i];
                            e++;
                        }
                    }
                    else //termina no nodo dir
                    {
                        if(n->filhos[i]->chaves[0] < dir->chaves[d])
                        {
                            dir->filhos[d] = n->filhos[i];
                            d++;
                        }
                    }
                }

                for(int i=2; i<quant_filhos; i++)
                {
                    if(n->filhos[i] != NULL)
                    {
                        n->filhos[i]=NULL;
                    }
                }
            }
            
            //redirecionar os ponteiros filhos do nodo atual, para esq e dir
            n->filhos[0]=esq;
            n->filhos[1]=dir;
        }

        void breakNodeRaizOld(Nodo* n, int tam)
        {
            int mediana=0; //indice da mediana;
            Nodo* esq = new Nodo(quant_chaves);
            Nodo* dir = new Nodo(quant_chaves);

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

            chaves[0]=chaves[mediana]; //reposicionar a medina no nodo atual
            ivc=1;
            for(int i=1; i<tam; i++)
                chaves[i]=INT_MAX;
            
            //redirecionar os ponteiros filhos do nodo atual, para esq e dir
            filhos[0]=esq;
            filhos[1]=dir;
        }
        
        void print()
        {
            //cout << "(";
            for(int i=0; i<ivc; i++)
            {
                if(chaves[i] != INT_MAX)
                    cout << chaves[i];
                if(i<(ivc-1)) cout << ",";
            }
            //cout << ")";
        }
        void printNode()
        {
            cout << "[";
            for(int i=0; i<quant_chaves; i++)
            {
                if(chaves[i] != INT_MAX)
                    cout << chaves[i];
                else
                    cout << "x";
                
                if(i<(quant_chaves-1)) cout << ",";
            }
            cout << "]";
        }

    friend class ArvoreB;
    friend class ReturnInfo;
};

class ArvoreB
{
    private:
        Nodo* raiz;
        ReturnInfo* inserir(int value, Nodo* n);
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
        bool inserir(int valor)
        {
            ReturnInfo* rInfo;
            if(raiz==NULL)
            {
                raiz = new Nodo(grau_max);
                raiz->isRaiz=true;
                rInfo = inserir(valor,raiz);
                return rInfo->isInsert;
            }
            else
            {
                rInfo = inserir(valor,raiz);
                return rInfo->isInsert;
            }
        }
        void remover(int valor);
        bool pesquisar(int valor)
        {
            return pesquisar(valor,raiz);
        }
        void preencherPorAtacado();
        void clear();
        void print(Nodo* n)
        {
            if(n->is_folha())
            {
                n->print();
            }

            for(int i=0; i<grau_max; i++)
            {
                if(n->filhos[i] != NULL)
                {
                    cout << "(";
                    print(n->filhos[i]);
                    cout << ")";
                    if(n->chaves[i] != INT_MAX)
                        cout << " " << n->chaves[i] << " ";
                }
            }
        }
        void print()
        {
            cout << "(";
            print(raiz);
            cout << ")"<<endl;
        }
        void printTree(Nodo* n)
        {
            //cout << "(";
            if(n->is_folha())
            {
                n->printNode();
            }

            for(int i=0; i<grau_max; i++)
            {
                if(n->filhos[i] != NULL)
                {
                    cout << "(";
                    printTree(n->filhos[i]);
                    cout << ")";
                    if(n->chaves[i] != INT_MAX)
                        cout << " " << n->chaves[i] << " ";
                    else
                        cout << " NULL ";
                }
            }
            //cout << ")";
        }
        void printTree()
        {
            cout << "{ ";
            printTree(raiz);
            cout << " }"<<endl;
        }

        ReturnInfo* inserirMediana(int value, Nodo* n, Nodo* dir)
        {
            ReturnInfo* rInfo;
            bool isInsert = n->insertMediana(n,value,dir);

            if(n->ivc==grau_max) //breakNode - sobe a mediana(posição) - nodo deixa de ser folha
            {
                if(n->isRaiz)
                {
                    n->breakNodeRaiz(n,grau_max);
                    if(n->isFolha) n->isFolha=false;
                    rInfo = new ReturnInfo();
                    rInfo->isInsert=isInsert;
                    return rInfo;
                }
                else
                {
                    rInfo = n->breakNode(n,grau_max);
                    rInfo->isInsert=isInsert;
                    return rInfo;
                }
            }
            rInfo = new ReturnInfo();
            return rInfo;
        }

        void printTest(Nodo* n)
        {
            n->printNode();
            cout << " ---> ";
            for(int i=0; i<=grau_max; i++)
            {
                if(n->filhos[i] != NULL)
                {
                    n->filhos[i]->printNode();
                }
            }
        }
        void printTest()
        {
            cout << "{ ";
            printTest(raiz);
            cout << " }"<<endl;
        }

        friend class ReturnInfo;
};

ReturnInfo* ArvoreB::inserir(int value, Nodo* n)
{
    ReturnInfo* rInfo;
    if(n->is_folha())
    {
        for(int i=0; i<grau_max; i++)
        {
            if(value==n->chaves[i]) //Não inserir valor repetido.
            {
                cout << "ALERT! "<< value << " ja existe na TREE." << endl;
                rInfo = new ReturnInfo();
                rInfo->isInsert=false;
                return rInfo;
            }   
        }

        bool isInsert = n->insertChave(n->chaves,grau_max,value);
        //cout<<"isInsert: "<<isInsert<<endl;
        /*
        if(value==2)
        {
            cout << "Nodo apos o INSERT 2: ";
            n->printNode();
            cout << endl;
        }
        */
        
        //2º recursão - vericar se o noco está cheio
        //if(n->ivc==grau_max){} //breakNode - sobe mediana - nodo deixa de ser folha

        if(n->ivc==grau_max) //breakNode - sobe a mediana(posição) - nodo deixa de ser folha
        {
            if(n->isRaiz)
            {
                n->breakNodeRaiz(n,grau_max);
                if(n->isFolha) n->isFolha=false;
                rInfo = new ReturnInfo();
                rInfo->isInsert=isInsert;
                return rInfo;
            }
            else
            {
                rInfo = n->breakNode(n,grau_max);
                /*
                cout << "Nodo apos o break: ";
                n->printNode();
                cout << endl;
                cout << "Nodo esq: ";
                rInfo->esq->printNode();
                cout << endl;
                cout << "Nodo dir: ";
                rInfo->dir->printNode();
                cout << endl;
                cout << "Mediana: "<<rInfo->mediana<<endl;
                */

                rInfo->isInsert=isInsert;
                return rInfo;
            }
        }
        rInfo = new ReturnInfo();
        rInfo->isInsert=isInsert;
        return rInfo;
    }

    rInfo = new ReturnInfo();
    //BUSCAR o valor nas chaves do nodo atual
    Nodo* f = NULL; //nodo auxiliar, para salvar o filho, que será verificado, na proxima chamada.

    for(int i=0; i<grau_max; i++) //proibido inserir valores repetidos
    {
        if(value==n->chaves[i]) //Não inserir valor repetido.
        {
            cout << "ALERT! "<< value << " ja existe na ARVORE." << endl;
            rInfo->isInsert=false;
            return rInfo;
        }   
    }

    for(int i=0; i<grau_max; i++) //verica qual filho, será o proximo a ser verificado.
    {
        if(value < n->chaves[i])
        {
            if(n->filhos[i] != NULL)
                f = n->filhos[i];
            else
            {
                cout << "ALERT! n->filhos[i] == NULL" << endl;
                rInfo->isInsert=false;
                return rInfo;
            }
            break;
        }
    }
    if(f==NULL) //verifica se o ultimo filho, é proximo a ser verificado.
    {
        if(value > n->chaves[grau_max-1])
            f = n->filhos[grau_max-1];
    }

    ReturnInfo* retinfo = inserir(value,f);
    if(retinfo->isBreak)
    {
        return inserirMediana(retinfo->mediana,n,retinfo->dir);
    }
    return rInfo;
}

void ArvoreB::remover(int valor)
{
    
}

void ArvoreB::clear()
{
    
}

#endif