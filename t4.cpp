#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

#define INFINITO 99999


int calcula_numero_de_colunas(int *notas, int tamanho, int valor){
    for(int i = 0; i < tamanho - 1; i++){
        // se existe nota com valor menor que o valor que desejamos computar
        if(notas[i] < valor){
            return 2*valor;
        }
    }
    // caso não exista, ou seja, todos os valores são das notas são maiores que
    // o valor que desejamos computar
    return notas[0];
}


int inicializa_matriz(int **matriz, int linhas, int *notas, int valor_item){

    int colunas = 0;
    colunas = calcula_numero_de_colunas(notas, linhas, valor_item) + 1;

    for(int linha = 0; linha < linhas; linha++){
        int *coluna = new int[colunas];
        matriz[linha] =  coluna;
    }

    return colunas;
}


int preenche_matriz(int **matriz, int i, int U, int *notas){
    /*  matriz[i][U] --> menor número de notas usando as i primeiras notas que de
        exatamente U

        matriz[i - 1][U] --> se não usou a i-ésima nota
        matriz[i][U - notas[i]] + 1 --> se usou a moeda i
    */
    // se o valor é zero
    if(U == 0){
        return 0;
    // se o número de notas é zero
    } else if(i == 0){
        return INFINITO;
    } else{
        // se U - notas[i] < 0 então não se pode pagar, com as i primeiras notas
        // EXATAMENTE U, então retorna-se infinito
        if(U - notas[i] < 0 ){
            return INFINITO;
        } else{
            return std::min(matriz[i - 1][U], matriz[i][U - notas[i]] + 1);
        }
    }
}

std::tuple<int, int> encontra_solucao_otima(int **matriz, int linhas, int colunas, int valor_item, int *notas){
    int solucao = 0,
        nota = -1,
        k = -1,
        valor = valor_item;

    if(colunas == (2 * valor_item) + 1){
        nota = notas[linhas - 1];
        k = linhas - 1;
        /* encontra a maior nota que ainda assim é menor que o valor do item */
        for(int i = linhas - 1; i > 0 && nota > valor_item; i--){
            nota = notas[i];
            k = i;
        }
        /* encontra o maior valor que é EXATAMENTE pago com as k primeiras notas*/
        for(int i = valor_item; i < colunas && matriz[k][i] == INFINITO; i++){
            valor = i + 1;
        }

        solucao = matriz[k][valor];
    } else {
        /* se tivermos apenas notas maiores que o valor que desejamos calcular*/
        for(int i = 0; i < linhas && solucao == 0; i++){
            for(int j = 0; j < colunas && solucao == 0; j++){
                /* então encontre o primeiro valor que não é infinito */
                if(matriz[i][j] < INFINITO){
                    solucao = matriz[i][j];
                    valor = j;
                }
            }
        }
    }

    return std::tuple<int, int>(solucao, valor);
}


int main(void){
    int valor_item = 0,
        num_tipo_notas = 0,
        colunas = 0;
    
    std::tuple<int, int> solucao_otima(0, 0);

    // recebe o valor do item e o número de tipos de notas
    std::cin >> valor_item >> num_tipo_notas;
    // recebe o número total de notas
    int *notas = new int[num_tipo_notas + 1];
    // valor dummy para a posição 0 do vetor de notas já que não teremos 0 notas
    // se temos notas é porque ela é no mínimo uma nota
    notas[0] = -1;
    for(int i = 1; i <= num_tipo_notas; i++){
        // armazena o valor de cada nota no vetor
        std::cin >> notas[i];
    }

    int **matriz = new int* [num_tipo_notas + 1];
    colunas = inicializa_matriz(matriz, num_tipo_notas + 1, notas, valor_item);

    for(int i = 0; i < num_tipo_notas + 1; i++){
        for(int j = 0; j < colunas; j++){
            matriz[i][j] = preenche_matriz(matriz, i, j, notas); 
        }
    }
    
    solucao_otima = encontra_solucao_otima(matriz, num_tipo_notas + 1, colunas, valor_item, notas);
    std::cout << std::get<1>(solucao_otima) << " " << std::get<0>(solucao_otima) << std::endl;

    delete notas;

    return 0;
}