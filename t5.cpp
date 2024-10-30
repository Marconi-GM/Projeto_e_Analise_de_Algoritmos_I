#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>


void ordena_intervalos(std::vector<std::tuple<int, int>>& intervalos){
    std::sort(intervalos.begin(), intervalos.end(), [](const std::tuple<int, int>& a, const std::tuple<int, int>& b){
        return std::get<1>(a) < std::get<1>(b);
    });
}

// A ESCOLHA GULOSA É O INTERVALO COM O MAIOR NÚMERO DE TÉRMINO QUE COMEÇE EM 0 MAS TENHA
// O MAIOR NÚMERO DE TÉRMINO POIS A INTENÇÃO É ABRANGER O MAIOR INTERVALO POSSÍVEL  
/* A subestrutura  ́otima diz que se am pertence a uma solu ̧c ̃ao  ́otima A
de Sk , ent ̃ao A  ́ tamu  ́e uma solu ̧c ̃ao  ́otima de Sm.
*/

/* A PRIMEIRA LINHA DA SAÍDA É O NÚMERO MÍNIMO DE INTERVALOS

    AS T LINHAS SEGUINTES DEVEM CONTER CADA INTERVALO DA SOLUÇÃO ÓTIMA ORDENADOS
    PELO VALOR Li (OS DOIS VALORES DEVEM SER SEPARADOS POR UM ESPAÇO)
*/
void imprime_intervalos(std::vector<std::tuple<int, int>> intervalos, int n){
    for(int i = 0; i <= n; i++){
        std::cout << std::get<0>(intervalos[i]) <<" "<< std::get<1>(intervalos[i]) << std::endl; 
    }
}


int encontra_escolha_gulosa(std::vector<std::tuple<int, int>> intervalos, int indice_atual, int ini, int fim, int valor){
    int indice = -1,
        max = std::get<1>(intervalos[indice_atual]);

    for(long unsigned int i = indice_atual + 1 ; i < intervalos.size(); i++){
        if(ini <= std::get<0>(intervalos[i]) && std::get<0>(intervalos[i]) <= fim && fim <= std::get<1>(intervalos[i]) && std::get<1>(intervalos[i]) >= max){
            if(std::get<1>(intervalos[i]) == max){
                if(std::get<0>(intervalos[i]) < std::get<0>(intervalos[indice])){
                    indice = i;
                    max = std::get<1>(intervalos[i]);
                }
            } else{
                indice = i;
                max = std::get<1>(intervalos[i]);
            }
        }
    }

    return indice;
}

int encontra_primeiro_intervalo(std::vector<std::tuple<int, int>> intervalos){
    int indice = -1,
        max = -99999;

    for(long unsigned int i = 1; i < intervalos.size() && std::get<0>(intervalos[i]) <= 0; i++){
        if(std::get<0>(intervalos[i]) <= 0 && std::get<1>(intervalos[i]) >= max){
            if(std::get<1>(intervalos[i]) == max){
                if(std::get<0>(intervalos[i]) < std::get<0>(intervalos[indice])){
                    indice = i;
                    max = std::get<1>(intervalos[i]);
                }
            } else{
                indice = i;
                max = std::get<1>(intervalos[i]);
            }
        }
    }
    
    return indice;
}


std::vector<std::tuple<int, int>> encontra_solucao_otima(std::vector<std::tuple<int, int>> intervalos, int valor){
    int indice_escolha_gulosa = 0,
        inicio = 0,
        fim = 0;
    // vetor que contem os intervalos que compoem a resposta
    std::vector<std::tuple<int, int>> resposta;
    // tupla que contem o intervalo que é a escolha gulosa da iteração
    std::tuple<int, int> escolha_gulosa(0, 0);
    // encontra a primeira escolha gulosa
    indice_escolha_gulosa = encontra_primeiro_intervalo(intervalos);
    // caso a primeira escolha gulosa não seja um intervalo que não abrange o 0,
    // então é um intervalo inválido e logo recebe valor -1
    if(indice_escolha_gulosa != -1){
        // valor de início do intervalo
        // std::get<0> acessa o primeiro valor da tupla
        inicio = std::get<0>(intervalos[indice_escolha_gulosa]);
        // valor final do intervalo
        // std::get<1> acessa o segundo valor da tupla
        fim = std::get<1>(intervalos[indice_escolha_gulosa]);
        // append do intervalo no vetor de repostas
        resposta.push_back(intervalos[indice_escolha_gulosa]);
        // enquanto o intervalo for válido e seu valor final não ultrapassar V, faça
        while(indice_escolha_gulosa != -1 && std::get<1>(intervalos[indice_escolha_gulosa]) < valor){
            // encontra a escolha gulosa da iteração
            indice_escolha_gulosa = encontra_escolha_gulosa(intervalos, indice_escolha_gulosa, inicio, fim, valor);
            // se a escolha gulosa for inválida, ou seja, se a intersecção de
            // seu intervalo com o intervalo anterior é vazia
            if(indice_escolha_gulosa == -1){
                // zera o vetor de respostas
                resposta.clear();
            } else{
                // caso contrário atualiza os índices e armazena a resposta
                inicio = std::get<0>(intervalos[indice_escolha_gulosa]);
                fim = std::get<1>(intervalos[indice_escolha_gulosa]);
                resposta.push_back(intervalos[indice_escolha_gulosa]);
            }
        }
    }

    return resposta;
}


int main(void){
    // 1 <= V <= 50 000
    int V = 0;
    // 1 <= n <= 500 000
    int n = 0;
    // -10 000 <= L < R <= 10 000
    int L = 0,
        R = 0;
    std::vector<std::tuple<int, int>> solucao_otima;
    // recebe V e n 
    std::cin >> V >> n;
    // cria um vetor de tuplas, de tamanho n
    std::vector<std::tuple<int, int>> intervalos(n+1);
    intervalos[0] = std::tuple<int, int>(0, 0);
    // recebe cada intervalo e o armazena no vetor
    for(int i = 1; i <= n; i++){
        std::cin >> L >> R;
        std::tuple<int, int> intervalo(L, R);
        intervalos[i] = intervalo;
    }

    // ordena os intervalos em ordem crescente de término do intervalo
    ordena_intervalos(intervalos);
    //imprime_intervalos(intervalos, n);
    solucao_otima = encontra_solucao_otima(intervalos, V);

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