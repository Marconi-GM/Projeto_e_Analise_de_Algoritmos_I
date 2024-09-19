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

int magic(Arvore *arv) {
    int peso_esq = 0,
        peso_dir = 0;

    int caminho_max = 0;

    if(arv->esq == NULL && arv->dir == NULL) {
        return arv->peso;
    } else {
        peso_esq = magic(arv->esq);
        peso_dir = magic(arv->dir);
    }

    if(peso_esq >= peso_dir) {
        caminho_max = arv->peso + peso_esq; 
    } else {
        caminho_max = arv->peso + peso_dir;
    }

    return caminho_max;
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
    
    // printa_arvore(arv);
    std::cout << (magic(arv));
    std::cout << std::endl;
    // criar uma função para apagar os nós da arvore antes de
    delete arv;

    return 0;
}

