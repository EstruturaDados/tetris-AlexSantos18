#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


#define MAX_TAMANHO 5

// Estrutura das peças 
typedef struct 
{
    char tipo[20];
    int id;
}tetris;

// Estrutura da Fila
typedef struct 
{
    tetris itens[MAX_TAMANHO];
    int inicio;
    int fim;
    int total;
}Fila;



void InicializaFila(Fila *f);
void FilaCheia(Fila *f);
void FilaVazia(Fila *f);
void InserirFila(Fila *f, Peca p);
void RemoverFila(Fila *f, Peca p);



int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

/// @brief Inicializa a fila vazia
/// @param f passa o ponteiro dos itens
void InicializaFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/// @brief Verifica se a fila esta cheira 
/// @param f 
void FilaCheia(Fila *f){
    return f->total == MAX_TAMANHO;
}

/// @brief Vefifica se a fila esta vazia
/// @param f 
void FilaVazia(Fila *f){
    return f->total == 0;
}

/// @brief Inseri as peças da Fila
/// @param f ponteiro dos itens 
/// @param p parametro aonde recebe as informaçoes
void InserirFila(Fila *f, Peca p){
    if (f->total == MAX_TAMANHO){
        printf("[AVISO] Fila Cheia.");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_TAMANHO;
    f->total++;
}

/// @brief Remove as peças da Fila
/// @param f ponteiro dos itens
/// @param p paramentro aonde recebe as informaçoes pelo ponteiro
void RemoverFila(Fila *f, Peca *p){
    if (FilaVazia(f)){
        printf("[AVISO] Fila Vazia.");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio +1) % MAX_TAMANHO;
    f->total--;

}