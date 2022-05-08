#include <iostream>
#include <fstream>

using namespace std;
ifstream in("abce.in");
ofstream out("abce.out");

struct node
{
    int valoare;
    node *parent;
    node *leftChild;
    node *rightChild;
    node(int);
};

node::node(int val)
{
    this->valoare = val;
    this->parent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

node *rad = nullptr;

void inserare(int val)
{
    node *newNode = new node(val);
    node *y = nullptr;
    node *x = rad;

    while(x != nullptr)
    {
        y = x;
        if(newNode->valoare < x->valoare)
            x = x->leftChild;
        else
            x = x->rightChild;
    }

    newNode->parent = y;
    if(y == nullptr)
        rad = newNode;
    else if(newNode->valoare < y->valoare)
        y->leftChild = newNode;
    else
        y->rightChild = newNode;

}

node* cautare(int val)    //cauta daca exista un node cu valoarea val
{
    node *nodActual = rad;

    while(nodActual != nullptr && val != nodActual->valoare)
        if(val < nodActual->valoare)
            nodActual = nodActual->leftChild;
        else
            nodActual = nodActual->rightChild;

    return nodActual;
}

node* minimLocal(node *nodActual)     //cauta minimul de dupa nodul dat !NU E MINIMUL GLOBAL DIN ARBORE
{
    while(nodActual->leftChild != nullptr)
        nodActual = nodActual->leftChild;

    return nodActual;
}

node* succesor(int val)  //cauta si returneaza un pointer catre nodul care este succesor nodului cu valoarea val
{
    node *nodDeCautatSuccesor = cautare(val); //nodul caruia ii cauti succesor

    if(nodDeCautatSuccesor->rightChild != nullptr)
        return minimLocal(nodDeCautatSuccesor->rightChild);

    node *y = nodDeCautatSuccesor->parent;

    while(y != nullptr && nodDeCautatSuccesor == y->rightChild)
    {
        nodDeCautatSuccesor = y;
        y = y->parent;
    }

    return y;

}
void sterge(int val)
{
    node *nodDeSters = cautare(val);

    if(nodDeSters != nullptr)
    {
        node *y = nullptr;
        node *x = nullptr;

        if(nodDeSters->leftChild == nullptr || nodDeSters->rightChild == nullptr)
            y = nodDeSters;
        else
            y = succesor(nodDeSters->valoare);

        if(y->leftChild != nullptr)
            x = y->leftChild;
        else
            x = y->rightChild;

        if(x != nullptr)
            x->parent = y->parent;

        if(y->parent == nullptr)
            rad = x;
        else if(y == y->parent->leftChild)
            y->parent->leftChild = x;
        else
            y->parent->rightChild = x;

        if(y != nodDeSters)
            nodDeSters->valoare = y->valoare;
    }
}

void afis(node *nodAfis)
{
    if(nodAfis != nullptr)
    {
        cout<<nodAfis->valoare<<" "<<nodAfis<<endl;
        afis(nodAfis->leftChild);
        afis(nodAfis->rightChild);
    }
}

int main()
{
    int q, i, x, op;
    in>>q;

    for(i = 1; i <= q; i++)
    {
        in>>op;
        if(op == 1)
        {
            in>>x;
            inserare(x);
        }
        else if(op == 2)
        {
            in>>x;
            sterge(x);
        }
        else if(op == 3)
        {
            in>>x;
            if(cautare(x) != nullptr)
                out<<1<<'\n';
            else
                out<<0<<'\n';
        }
    }

   // cout<<cautare(5)<<endl;
    // cout<<rad->leftChild<<" "<<rad->rightChild;
   // sterge(6);
   //  afis(rad);

   return 0;
}
