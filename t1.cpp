#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>

int pertinencia(int *n, int *set, int *pos, int numero) {
    /* Devolve 1 se numero ∈ S e zero caso contrário*/
    if(*n > 0 && set[pos[numero]] == numero && *n > pos[numero]) {
        return 1;
    }

    return 0;
}

void insere_valor(int *n, int *set, int *pos, int numero) {
    /* Insere numero em S caso ele ainda não esteja no subcojunto. Não faz nada
    caso contrário*/
    if(*n == 0 || set[pos[numero]] != numero || pos[numero] > *n) {
        set[*n] = numero;
        pos[numero] = *n;
        *n += 1;
    }
}

void remove_valor(int *n, int *set, int *pos, int numero) {
    /* remove numero de S caso ele esteja no subconjunto. Não faz nada caso contrário*/
    if(set[pos[numero]] == numero && pos[numero] < *n) {
        // coloca o último elemento do vetor set na posição que teve seu elemento removido
        // -1 acrescentado pois o vetor começa em zero
        set[pos[numero]] = set[(*n) - 1];
        // atualiza a posição nova do elemento que foi movido
        pos[set[(*n) - 1]] = pos[numero];
        *n -= 1;
    }

    if(*n < 0) {
        *n = 0;
    }
}

void reinicializa_S(int *n, int *set, int *pos) {
    /* Reinicializa o subconjunto S tornando-o vazio*/
    *n = 0;
}


int main(void) {
    std::string operacao;

    int N = 0,
        Q = 0,
        numero = 0,
        pertence = 0;

    // recebe N (representando o conjunto) e Q (número de operações)
    std::cin >> N >> Q;

    int *set = new int[N],
        *pos = new int[N],
        *n = new int;

    *n = 0;

    for(int i = 0; i < Q; i++) {
        std::cin >> operacao;
        if(operacao == "p") {
            std::cin >> numero;
            pertence = pertinencia(n, set, pos, numero);
            if(pertence == 1) {
                std::cout << 1 << std::endl;
            } else {
                std::cout << 0 << std::endl;
            }
        } else if(operacao == "i") {
            std::cin >> numero;
            insere_valor(n, set, pos, numero);
        } else if(operacao == "r") {
            std::cin >> numero;
            remove_valor(n, set, pos, numero);
        } else if(operacao == "l") {
            reinicializa_S(n, set, pos);
        } 
    }

    delete set;
    delete pos;
    delete n;

    return 0;
}