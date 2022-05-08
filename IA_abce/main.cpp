#include <iostream>
#include <fstream>

using namespace std;
ifstream in("abce.in");
ofstream out("abce.out");

struct nod
{
    int valoare;
    nod *leftChild;
    nod *rightChild;
};

nod *rad = nullptr;

void inserare(int val)
{
    nod *newNod = new nod;
    nod *y = nullptr;
    nod *x = rad;

    while(x != nullptr)
    {
        y = x;
        if(val < x->valoare)
            x = x->leftChild;
        else
            x = x->rightChild;
    }

  //  newNod->parent = y;
    if(y == nullptr)
        rad = newNod;
    else if(newNod->valoare < y->valoare)
        y->leftChild = newNod;
    else
        y->rightChild = newNod;

}

void afis(nod *nodAfis)
{
    while(rad != nullptr)
    {
        cout<<nodAfis->valoare<<endl;
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
    }

    //cout<<rad->valoare;
  //  afis(rad);
}
