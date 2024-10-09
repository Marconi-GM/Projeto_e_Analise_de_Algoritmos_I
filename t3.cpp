#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>

class Dados{
    public: int numero_de_inversoes = 0;
    public: std::string sequencia;
};


int calcula_numero_de_inversoes(std::string sequencia){
    /*
        Para cada elemento da string, compara os códigos ascii dos elementos,
        caso o elemento posterior tenha um ascii maior que o anterior então isso
        é uma inversão e incrementa-se o contador de inversões
    */
    int numero_de_inversoes = 0,
        tamanho_string = 0;
    tamanho_string = sequencia.length();
    // para cada elemento da string
    for(int i = 0; i < tamanho_string - 1; i++){
        // percorra o resto da string
        for(int k = i; k < tamanho_string; k++){
            // comparando os ascii de cada caracter caso ele não seja o fim da string  
            if(int(sequencia[i]) > int(sequencia[k+1]) && int(sequencia[k+1] != 0)){
                numero_de_inversoes += 1;
            }
        }
    }

    return numero_de_inversoes;
}


void imprime_estringues(Dados *estringues, int m){
    for(int i = 0; i < m; i++){
        std::cout << estringues[i].sequencia << std::endl;
    }
}


void intercala(Dados *A, int p, int q, int r) {
    /*
        Caro ped/pad, os comentários abaixo não tem a intenção de explicar o código
        apenas a intenção de, quando eu revisitá-lo, lembrar onde e porque estava
        errando. Por isso, por favor, desconsidere-os
    */
    Dados *B = new Dados[r];
    int i = 0,
        j = 0,
        k = 0;
    
    for(i = p; i < q; i++){
        B[i] = A[i];
    }
    /*
        Aqui ao preencher a segunda parte do vetor estava dando erro. Isso porque
        ao preencher a segunda parte do vetor, de trás pra frente acarretava em
        uma perda a estabilidade do algoritmo, por isso a segunda metade do
        vetor B deve ser preenchida na ordem normal do vetor
    */
    for(j = q; j < r; j++){
        B[j] = A[j];
    }

    i = p;
    j = q;

    /*  
        aqui na hora de intercalar também dava erro. No caso erro de segmentation
        fault. Isso porque tentava-se acessar indices do vetor B que não existiam
        para isso coloquei as condições a mais no if.
        i < q é para que i não tente acessar uma posição além da primeira metade
        do vetor.
        j >= r é para quando se j for maior que r, ou seja, acabar a segunda metade
        do vetor, então continue preenchendo o vetor mas com os elementos de A
    */
    for(k = p; k < r; k++){
        if(i < q && (j >= r || B[i].numero_de_inversoes <= B[j].numero_de_inversoes)){
            A[k] = B[i];
            i += 1;
        } else {
            A[k] = B[j];
            j += 1;
        }
    }
    // CUIDADO COM A CONFUSÃO NOS INDÍCES
}


void merge_sort(Dados *A, int p, int r){
    int q = 0;
    if(p < r - 1){
        q = std::floor((p+r)/2);
        merge_sort(A, p, q);
        merge_sort(A, q, r);
        intercala(A, p, q, r);
    }
}

int main(void){
    /*
        M -> quantidade de conjunto de dados (rodadas)
        n -> tamanho de cada string
        m -> quantidade de strings de tamanho n
    */
    int M = 0,
        m = 0,
        n = 0;

    std::cin >> M;

    for(int i = 0; i < M; i++){
        // m strings de tamanho n
        std::cin >> n >> m;
        // vetor contendo os m dados ou seja, as strings que serão lidas e
        // o seus respectivos números de inversões
        Dados *estringues = new Dados[m];
        for(int k = 0; k < m; k++){
            Dados novo_dado;
            // recebe a string
            std::cin >> novo_dado.sequencia;
            novo_dado.numero_de_inversoes = calcula_numero_de_inversoes(novo_dado.sequencia);
            estringues[k] = novo_dado;
        }
        // ordena o vetor de strings
        merge_sort(estringues, 0, m);
        imprime_estringues(estringues, m);
        if(i < M - 1){
            std::cout << std::endl;
        }
    }

    return 0;
}