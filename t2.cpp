#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>

class Arvore {
    public: Arvore *esq;
    public: Arvore *dir;
    public: int peso;
};


Arvore *cria_arvore(Arvore *arv) {
    int peso;
    char dir, esq;

    std::cin >> peso;
    arv->peso = peso;

    std::cin >> esq;
    if(esq == 'T') {
        Arvore *arv_aux = new Arvore;
        arv->esq = cria_arvore(arv_aux);
    } else {
        arv->esq = NULL;
    }

    std::cin >> dir;
    if(dir == 'T') {
        Arvore *arv_aux = new Arvore;
        arv->dir = cria_arvore(arv_aux);
    } else {
        arv->dir = NULL;
    }

    return arv;
}

void printa_arvore(Arvore *arv) {
    std::cout << arv->peso << " ";
    if(arv->esq != NULL)
        printa_arvore(arv->esq);
    if(arv->dir != NULL)
        printa_arvore(arv->dir);
}


int main(void) {
    Arvore *arv = new Arvore;

    arv = cria_arvore(arv);
    
    printa_arvore(arv);
    std::cout << std::endl;
    // criar uma função para apagar os nós da arvore antes de
    delete arv;

    return 0;
}

