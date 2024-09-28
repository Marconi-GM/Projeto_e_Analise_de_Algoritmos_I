#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <tuple>


class Arvore {
    public: Arvore *esq;
    public: Arvore *dir;
    public: int peso;
};


Arvore *cria_arvore(Arvore *arv) {
    int peso = 0;
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


std::tuple<int, int> encontra_caminhos(Arvore *arv) {
    /*  
        Entradas:
            *arv --> uma arvore binária, do tipo Arvore
        Saídas:
            uma tupla, contendo dois valores, um referente ao maior caminho da 
            árvore, considerando que esse caminho inclui a raiz. O segundo 
            valor é o maior caminho da árvore, considerando que a raiz pode não
            estar no caminho
    */
    int caminho_max = 0,
        subcaminho = 0;

    std::tuple<int, int> caminho_esq {0, 0},
                         caminho_dir {0, 0};
    
    // se o nó em questão é NULL retorna 0 nos valores da tupla
    if(arv == NULL) {
        return std::tuple<int, int>(0, 0);
    }
    // se o nó é uma folha, então apenas retorna o peso do nó
    if(arv->esq == NULL && arv->dir == NULL) {
        // se o peso do nó for menor que zero arv->peso = 0
        if(arv->peso < 0) {
            arv->peso = 0;
        }
        // retorna a tupla com o peso do nó como valores
        return std::tuple<int, int>(arv->peso, arv->peso);
    // se o nó não é folha, nem NULL
    } else {
        /*  as variáveis abaixo armazenarão as tuplas do caminho esquerdo e
            direito, nas tuplas teremos os caminhos já citados */
        caminho_esq = encontra_caminhos(arv->esq);
        caminho_dir = encontra_caminhos(arv->dir);
        // o caminho_max leva em consideração que a raiz está no maior caminho
        caminho_max = std::max(std::get<0>(caminho_esq), std::get<0>(caminho_dir)) + arv->peso;
        // o subcaminho leva em consideração que a raiz pode não estar incluida
        // ou seja, abaixo da raiz pode ter um subcaminho maior 
        subcaminho = arv->peso + std::get<0>(caminho_esq) + std::get<0>(caminho_dir);
    }

    // se houver um subcaminho maior do que o já encontrado, atualiza
    if(std::get<1>(caminho_esq) > subcaminho) {
        subcaminho = std::get<1>(caminho_esq);
    } else if(std::get<1>(caminho_dir) > subcaminho) {
        subcaminho = std::get<1>(caminho_dir);
    }

    return std::tuple<int, int>(caminho_max, subcaminho);
}


int main(void) {
    /*  A tupla abaixo (caminhos) receberá dois valores, o da primeria posição
        é referente ao maior camino da árvore, considerando que esse caminho
        inclui a raiz. O segundo valor é o maior caminho da árvore, considerando
        que a raiz pode não estar no caminho.
    */
    std::tuple<int, int> caminhos(0, 0);
    Arvore *arv = new Arvore;

    arv = cria_arvore(arv);
    caminhos = encontra_caminhos(arv);
    /*  Caso só tenha nós negativos na árvore, então os caminhos serão negativos
        nesse caso queremos que os caminhos sejam nulos
    */
    if(std::get<0>(caminhos) < 0 && std::get<1>(caminhos) < 0) {
        std::get<0>(caminhos) = 0;
        std::get<1>(caminhos) = 0;
    }
    /*  a resposta é o maior caminho da tupla */
    std::cout << std::max(std::get<0>(caminhos), std::get<1>(caminhos));
    std::cout << std::endl;

    delete arv;

    return 0;
}

