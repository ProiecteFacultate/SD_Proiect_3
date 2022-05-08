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

node* succesor(int val)  //cauta si returneaza un pointer catre nodul care este succesor nodului cu valoarea val !VAL TREBUIE SA EXISTE IN ARBORE DACA NU EXISTA NU FUNCTIONEAZA DE ASRA NE TRB FCT
//SEPARATE PT CERINTELE 4 SI 5 PT CA ACOLO NI SE POT DA NUMERE CARE SA NU FIE ARBORE
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


node* cerinta4(int val)
{
    node *nodActual = rad;
    node *nodMaximal = rad;

    while(nodActual != nullptr)
    {
        if(nodActual->valoare == val)
            return nodActual;
        else if(nodActual->valoare < val)     //se duce pe ramura dreapta
        {
            if(nodActual->rightChild == nullptr) //nu mai exista copil in dr si nodu actual e mai mic decat val cautata deci asta va fi cea mai mare val mai mica decat val cautata
            {
                if(nodActual->valoare > val)
                    return nodMaximal;
                else
                    return nodActual;
            }
            else if(nodActual->rightChild->valoare <= val)  //nodu viitor e si el mai mica sau egal decat val cautata deci ne ducem pe el
                nodActual = nodActual->rightChild;
            else  //nodu asta are val mai mica decat val cautata dar urm e mai mare asa ca trb sa verf daca gasim pe ramura st a urm nod o val mai mare ca asta dar mai mica decat val cautata
            {
                nodMaximal = nodActual;
                nodActual = nodActual->rightChild;
            }
        }
        else //se duce pe st
        {
            if(nodActual->leftChild == nullptr)  //am fost odata pe dr desi nodul urm era mai mare si am mers dupa pe ramura st sperand ca gasim cv ok dar n am gasit nmk mai mic decat val si acum am ajuns la baza arborelui
            {
                if(nodActual->valoare > val)  //nu am gasit o valoare mai mica pe arborele stang cand am facut ce scire mai sus
                    return nodMaximal;
                else    //am gasit o val mai mica adica asta
                    return nodActual;
            }
            else
                nodActual = nodActual->leftChild;
        }

    }
}


node* cerinta5(int val)
{
    node *nodActual = rad;
    node *nodMinimal = rad;

    while(nodActual != nullptr)
    {
        if(nodActual->valoare == val)
            return nodActual;
        else if(nodActual->valoare > val)   //se duce pe st
        {
            if(nodActual->leftChild == nullptr)
            {
                if(nodActual->valoare < val)
                    return nodMinimal;
                else
                    return nodActual;
            }
            else if(nodActual->leftChild->valoare >= val)
                nodActual = nodActual->leftChild;
            else
            {
                nodMinimal = nodActual;
                nodActual = nodActual->leftChild;
            }
        }
        else  //e mai mic nodu actual decat val deci trb neaparat sa creasca asa ca se duce pe dr
        {
            if(nodActual->rightChild == nullptr)
            {
                if(nodActual->valoare < val)
                    return nodMinimal;
                else
                    return nodActual;
            }
            else
                nodActual = nodActual->rightChild;
        }

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
    int q, i, x, y, z, zUltim, op;
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
        else if(op == 4)
        {
            in>>x;
            out<<cerinta4(x)->valoare<<'\n';
        }
        else if(op == 5)
        {
            in>>x;
            out<<cerinta5(x)->valoare<<'\n';
        }
        else if(op == 6)
        {
            in>>x>>y;

            z = cerinta5(x)->valoare;
            zUltim = cerinta4(y)->valoare;
            while(z < zUltim)
            {
                out<<z<<" ";
                z = cerinta5(z + 1)->valoare;
            }
            out<<zUltim<<'\n';
        }
    }

    // cout<<cautare(5)<<endl;
    // cout<<rad->leftChild<<" "<<rad->rightChild;
    // sterge(6);
    //  afis(rad);

    return 0;
}
