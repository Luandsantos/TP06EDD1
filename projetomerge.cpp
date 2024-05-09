#include <iostream>
#include <locale.h>
using namespace std;

#define MAX 30

struct Pilha {
    int qtde;
    float elementos[MAX];
};

Pilha* init() {
    Pilha *p = new Pilha;
    p->qtde = 0;
    return p;
}

int isEmpty(Pilha *p) {
    return (p->qtde == 0);
}

int count(Pilha *p) {
    return (p->qtde);
}

void freePilha(Pilha *p) {
    free(p);
}

int push(Pilha *p, float v) {
    int podeEmpilhar = (p->qtde < MAX);
    if (podeEmpilhar) {
        p->elementos[p->qtde++] = v;
    }
    return podeEmpilhar;
}

float pop(Pilha *p) {
    int podeDesempilhar = (p->qtde > 0);
    float v;
    if (podeDesempilhar) {
        v = p->elementos[--(p->qtde)];
    } else {
        v = -1;
    }
    return v;
}

void print(Pilha *p) {
    cout << "Qtde de elementos: " << count(p) << endl;
    for(int i = p->qtde - 1; i >= 0; --i) {
        cout << p->elementos[i] << endl;
    }
    cout << "--------------------" << endl;
}

bool checkIncreasing(float current, float previous) {
    return current > previous;
}

bool insertInOrder(Pilha *p, float v) {
    if (p->qtde == 0 || checkIncreasing(v, p->elementos[p->qtde - 1])) {
        return push(p, v);
    }
    return false;
}

void separatePiles(Pilha *evenStack, Pilha *oddStack, float v) {
    if ((int)v % 2 == 0) {
        push(evenStack, v);
    } else {
        push(oddStack, v);
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    Pilha *pilhaFloat;
    pilhaFloat = init();

    cout << "Digite 30 números inteiros maiores que os anteriores:" << endl;
    float previous = -1;
    for (int i = 0; i < 30; ++i) {
        float num;
        cout << "Número " << i + 1 << ": ";
        cin >> num;
        if (checkIncreasing(num, previous)) {
            insertInOrder(pilhaFloat, num);
            previous = num;
        } else {
            cout << "Número digitado não é maior que o anterior. Insira um número maior." << endl;
            --i; 
        }
    }

    Pilha *pilhaPar = init();
    Pilha *pilhaImpar = init();

    for (int i = 0; i < count(pilhaFloat); ++i) {
        separatePiles(pilhaPar, pilhaImpar, pop(pilhaFloat));
    }

    cout << "Números pares em ordem decrescente:" << endl;
    print(pilhaPar);

    cout << "Números ímpares em ordem decrescente:" << endl;
    print(pilhaImpar);

    freePilha(pilhaFloat);
    freePilha(pilhaPar);
    freePilha(pilhaImpar);

    return 0;
}