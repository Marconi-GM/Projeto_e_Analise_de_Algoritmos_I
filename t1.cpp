#include <iostream>
#include <array>
#include <string>
#include <cstdlib>
#include <cmath>

int pertinencia(int *S, int *set, int *pos, int numero) {
    /* Devolve 1 se numero ∈ S e zero caso contrário*/
    return 0;
}

void insere_valor(int *S, int *set, int *pos, int numero) {
    /* Insere numero em S caso ele ainda não esteja no subcojunto. Não faz nada
    caso contrário*/

}

void remove_valor(int *S, int *set, int *pos, int numero) {
    /* remove numero de S caso ele esteja no subconjunto. Não faz nada caso contrário*/
}

void reinicializa_S(int *S) {
    /* Reinicializa o subconjunto S tornando-o vazio*/
}


int main(void) {



    // vou receber um vetor N (devo oderná-lo?)     
    // esse vetor vai representar um conjunto
    // e vou usar um vetor de bits para representar um subconjunto desse vetor
    // nesse vetor Q[i] = 1 se i pertence a S e zero caso contrário

    /*  Quero realizar as seguintes operações
        1) devolver 1 se i estiver em [N]
        2) inserir um elemento i caso ele não esteja em N
        3) remover i caso ele esteja em N
        4) reiniciar S como um conjunto vazio


        teremos uma variável n que guarda o tamanho de S
        um vetor set que é uma lista contendo os elementos em S (em qualquer ordem)
        um vetor pos contendo a posição de cada elemento do vetor S
            Para i ∈ S, pos[i] indica a posi¸c˜ao de i no vetor set. Se i̸ ∈ S, ent˜ao
            pos[i] n˜ao tem significado nenhum.
        
        ou seja os vetores tem apontadores um para o outro

        para inserir em S

        set[n] <- i
        pos[i] <- n
        n <- n+1
    */
    std::string operacao;

    int N = 0,
        Q = 0,
        numero = 0;

    int *S = {},
        *set,
        *pos;

    
    
    // receber N (representando o conjunto) e Q (número de operações)
    std::cin >> N >> Q;

    for(int i = 0; i < Q; i++) {
        std::cin >> operacao >> numero;
        if(operacao == "p") {
            pertinencia(S, set, pos, numero);
        } else if(operacao == "i") {
            insere_valor(S, set, pos, numero);
        } else if(operacao == "r") {
            remove_valor(S, set, pos, numero);
        } else if(operacao == "l") {
            reinicializa_S(S);
        }
    }

    return 0;
}