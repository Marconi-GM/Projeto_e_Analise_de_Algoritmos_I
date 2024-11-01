#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>


void troca(int *L, int *R, int i, int j) {
    int temp = R[i];
    R[i] = R[j];
    R[j] = temp;

    temp = L[i];
    L[i] = L[j];
    L[j] = temp;
}


int particiona(int *L, int *R, int inicio, int fim) {
    int pivo = R[fim];
    int i = (inicio - 1);

    for (int j = inicio; j < fim; j++) {
        if (R[j] <= pivo) {
            i++;
            troca(L, R, i, j);
        }
    }

    troca(L, R, i + 1, fim);
    return (i + 1);
}


void quickSort(int *L, int *R, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(L, R, inicio, fim);

        quickSort(L, R, inicio, pivo - 1);
        quickSort(L, R, pivo + 1, fim);
    }
}


void ordena_intervalos(int *L, int *R, int n) {
    quickSort(L, R, 0, n - 1);
}


int encontra_escolha_gulosa(int *L, int *R, int n, int indice_atual, int ini, int fim, int valor){
    int indice = -1,
        max = R[indice_atual];

    // percorre todos os intervalos
    for(int i = indice_atual + 1; i <= n; i++){
        /*
            ini <= L[i] && L[i] <= fim ---> se o intervalo atual abrange o intervalo
            anterior

            fim <= R[i] ---> se o intervalo atual tem ponto final maior que o 
            intervalo anterior

            R[i] => max ---> se o intervalo atual é o intervalo que maximiza a 
            computação
        */
        if(ini <= L[i] && L[i] <= fim && fim <= R[i] && R[i] >= max){
            if(R[i] == max){
                if(L[i] < L[indice]){
                    indice = i;
                    max = R[i];
                }
            } else{
                indice = i;
                max = R[i];
            }
        }
    }

    return indice;
}

int encontra_primeiro_intervalo(int *L, int *R, int n){
    //  A função encontra o intervalo que tem menor valor em L[i] e maior em R[i]
    int indice = -1,
        max = -99999;

    for(int i = 1; i <= n; i++){
        if(L[i] <= 0 && R[i] >= max){
            if(R[i] == max){
                if(L[i] < L[indice]){
                    indice = i;
                    max = R[i];
                }
            } else{
                indice = i;
                max = R[i];
            }
        }
    }
    
    return indice;
}


std::vector<std::tuple<int, int>> encontra_solucao_otima(int *L, int *R, int n, int valor){
    int indice_escolha_gulosa = 0,
        inicio = 0,
        fim = 0;
    // vetor que contem os intervalos que compoem a resposta
    std::vector<std::tuple<int, int>> resposta;

    // encontra a primeira escolha gulosa
    indice_escolha_gulosa = encontra_primeiro_intervalo(L, R, n);

    // caso a primeira escolha gulosa não seja um intervalo que não abrange o 0,
    // então é um intervalo inválido e logo recebe valor -1
    if(indice_escolha_gulosa != -1){
        // valores de início e fim do intervalo
        inicio = L[indice_escolha_gulosa];
        fim = R[indice_escolha_gulosa];
        resposta.push_back(std::make_tuple(L[indice_escolha_gulosa], R[indice_escolha_gulosa]));

        // enquanto o intervalo for válido e seu valor final não ultrapassar V, faça
        while(indice_escolha_gulosa != -1 && R[indice_escolha_gulosa] < valor){
            // encontra a escolha gulosa da iteração
            indice_escolha_gulosa = encontra_escolha_gulosa(L, R, n, indice_escolha_gulosa, inicio, fim, valor);
            // se a escolha gulosa for inválida, ou seja, se a intersecção de
            // seu intervalo com o intervalo anterior é vazia
            if(indice_escolha_gulosa == -1){
                // zera o vetor de respostas
                resposta.clear();
            } else{
                // caso contrário atualiza os índices e armazena a resposta
                inicio = L[indice_escolha_gulosa];
                fim = R[indice_escolha_gulosa];
                resposta.push_back(std::make_tuple(L[indice_escolha_gulosa], R[indice_escolha_gulosa]));
            }
        }
    }

    return resposta;
}


int main(void){
    int V = 0;
    int n = 0;

    std::cin >> V >> n;

    int *L = new int[n+1],
        *R = new int[n+1];
    L[0] = 0;
    R[0] = 0;

    std::vector<std::tuple<int, int>> solucao_otima;

    for(int i = 1; i <= n; i++){
        std::cin >> L[i] >> R[i];

    }
    // ordena os intervalos em ordem crescente de término do intervalo
    ordena_intervalos(L, R, n);

    solucao_otima = encontra_solucao_otima(L, R , n, V);
    // imprime a saída
    if(solucao_otima.empty()){
        std::cout << 0 << std::endl;
    } else{
        std::cout << solucao_otima.size() << std::endl;
        for(long unsigned int i = 0; i < solucao_otima.size(); i++){
            std::cout << std::get<0>(solucao_otima[i]) <<" "<<std::get<1>(solucao_otima[i]) << std::endl;
        }
    }

    return 0;
}