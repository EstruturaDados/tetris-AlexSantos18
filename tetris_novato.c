#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Desafio Tetris Stack
//  Nível Novato: Fila de Peças Futuras


#define MAX_TAMANHO 5
// Tipos de peças disponíveis
const char *TIPOS_PECA[] = {"I", "O", "T", "L", "I"};
#define NUM_TIPOS 5

// Variável global para gerar IDs sequenciais (simplificação para o desafio)
int proximo_id = 0;

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


// Protótipos
void InicializaFila(Fila *f);
int FilaCheia(Fila *f); 
int FilaVazia(Fila *f); 
void InserirFila(Fila *f, tetris p);
void RemoverFila(Fila *f, tetris *p);
void MostrarFila(Fila *f);
void Menu();
tetris GerarPeca(); //  função para gerar uma nova peça


int main() {
    
    Fila f;
    InicializaFila(&f);
    int resp;

    // Inicializa a fila com 5 peças geradas automaticamente
    printf("Inicializando Fila...\n");
    for (int i = 0; i < MAX_TAMANHO; i++) {
        InserirFila(&f, GerarPeca());
    }
    MostrarFila(&f);


    tetris removida;
    do
    {
        Menu();
        if (scanf("%d", &resp) != 1) {
           // checagem de numero
            while(getchar() != '\n');
            resp = -1; // Opção inválida
        }

        switch (resp)
        {
        case 1: // 1 - Jogar peça (remover da frente e repor no final)
        { 
            if (FilaVazia(&f)) {
                printf("[AVISO] Fila Vazia! Nenhuma peca para jogar.\n");
            } else {
                RemoverFila(&f, &removida);
                printf("[JOGAR] Peca jogada: [%s, %d]\n", removida.tipo, removida.id);
                
 
            }
            MostrarFila(&f);
            break;
        }

        case 2:
        {
             // Repõe uma nova peça ao final, mantendo o tamanho
            tetris novaPeca = GerarPeca();
            InserirFila(&f, novaPeca);
            printf("[REPOSICAO] Inserida nova peca: [%s, %d]\n", novaPeca.tipo, novaPeca.id);
            printf("\n");
            MostrarFila(&f);
            break;

        }

        case 0: // 0 - Sair
        {
            printf("Saindo do sistema.\n");
            break;
        }
        
        default:
            printf("[ERRO] Opcao invalida. Tente novamente.\n");
            break;
        }

    } while (resp != 0);

    return 0;
}

/// @brief Gera uma nova peça com tipo aleatório e ID sequencial
/// @return Struct tetris com as informações da nova peça
tetris GerarPeca(){
    tetris novaPeca;
    
    // Escolhe um tipo de peça aleatoriamente
    int indice = rand() % NUM_TIPOS;
    strcpy(novaPeca.tipo, TIPOS_PECA[indice]);

    // Atribui e incrementa o ID sequencial
    novaPeca.id = proximo_id++;

    return novaPeca;
}


// Implementações das Funções de Fila

/// @brief Inicializa a fila vazia
/// @param f ponteiro para a fila
void InicializaFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

/// @brief Verifica se a fila esta cheia 
/// @param f ponteiro para a fila
/// @return 1 se cheia, 0 caso contrário
int FilaCheia(Fila *f){
    return f->total == MAX_TAMANHO;
}

/// @brief Vefifica se a fila esta vazia
/// @param f ponteiro para a fila
/// @return 1 se vazia, 0 caso contrário
int FilaVazia(Fila *f){ 
    return f->total == 0;
}

/// @brief Inseri as peças na Fila (Enqueue)
/// @param f ponteiro para a fila
/// @param p struct tetris a ser inserida
void InserirFila(Fila *f, tetris p){
    if (FilaCheia(f)){ 
        printf("[AVISO] Fila Cheia. Impossivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_TAMANHO;
    f->total++;
}

/// @brief Remove as peças da Fila (Dequeue)
/// @param f ponteiro para a fila
/// @param p ponteiro para a struct que receberá a peça removida
void RemoverFila(Fila *f, tetris *p){
    if (FilaVazia(f)){ 
        printf("[AVISO] Fila Vazia. Impossivel remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_TAMANHO;
    f->total--;
}
/// @brief Mostra a fila na ordem de retirada
/// @param f ponteiro para a struct 
void MostrarFila(Fila *f){
    printf("\n--- Fila de Pecas (%d/%d) ---\n", f->total, MAX_TAMANHO);
    printf("Proxima: ");
    
    if (FilaVazia(f)) {
        printf("[Vazia]\n");
        return;
    }

    for (int i = 0, id = f->inicio; i < f->total; i++, id = (id + 1) % MAX_TAMANHO){
        // Mostra a peça da frente (inicio)
        if (i == 0) {
            printf("|[%s, %d]|", f->itens[id].tipo, f->itens[id].id);
        } else {
            // Mostra as peças futuras
            printf(" -> [%s, %d]", f->itens[id].tipo, f->itens[id].id);
        }
    }
    printf("\n---------------------------\n");
}
/// @brief Menu com as opcoes 
void Menu(){
    printf("\n=========TETRIS STACK=======\n");
    printf("1 - Jogar peca\n");
    printf("2 - Inserir nova peca\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}