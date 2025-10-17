#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Desafio Tetris Stack
//  Nível Aventureiro : Pilha de Peças 


#define MAX_TAMANHO 5
#define MAX_PILHA 3

const char *TIPOS_PECA[] = {"I", "O", "T", "L", "I"};
#define NUM_TIPOS 5


// Variável global para gerar IDs sequenciais   
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

typedef struct 
{
    tetris reserva[MAX_PILHA];
    int topo;
}Pilha;



// Protótipos
void InicializaFila(Fila *f);
int FilaCheia(Fila *f); 
int FilaVazia(Fila *f); 
void InserirFila(Fila *f, tetris p);
void RemoverFila(Fila *f, tetris *p);
void MostrarFila(Fila *f);
void InserirFilaFrente(Fila *f, tetris p);

void InicializarPilha(Pilha *p);
void MostrarPilha(Pilha *p);
void RemoverPilha(Pilha *p, tetris *t);
int PilhaVazia(Pilha *p);
int PilhaCheia(Pilha *p);
void InserirPilha(Pilha *p, tetris t);


void Menu();
tetris GerarPeca(); //  função para gerar uma nova peça


int main() {
    
    Fila f;
    Pilha p;
    InicializaFila(&f);
    InicializarPilha(&p);

    int resp;
    tetris removida;
  
    // Inicializa a fila com 5 peças geradas automaticamente
    printf("Inicializando Fila...\n");
    for (int i = 0; i < MAX_TAMANHO; i++) {
        InserirFila(&f, GerarPeca());
    }
    MostrarFila(&f);
    MostrarPilha(&p);

    
    
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
                InserirFila(&f, GerarPeca());
                
 
            }
            MostrarFila(&f);
            MostrarPilha(&p);
            break;
        }

        case 2: // 2 -  move a peca da frete da fila para o topo da pilha, se houver espaco
        { 
             if (FilaVazia(&f)){
                printf("[AVISO] Fila Vazia! Nenhuma peca para jogar.\n");
             } else if (PilhaCheia(&p)){
                 printf("[AVISO] Pilha Cheia! Não é possível reservar mais peças.\n");
             } else {
                RemoverFila(&f, &removida);
                InserirPilha(&p, removida);
                printf("[RESERVA] Peça movida para reserva: [%s, %d]\n", removida.tipo, removida.id);
                InserirFila(&f, GerarPeca());
             }
             MostrarFila(&f);
             MostrarPilha(&p);  
            break;

        }

        case 3: // usa a peca da pilha porem so joga fora
        {
            if (PilhaVazia(&p)){
                printf("[AVISO] Nenhuma peça reservada.\n");

            } else {
                RemoverPilha(&p, &removida);
                 printf("[USO] Peça usada da reserva: [%s, %d]\n", removida.tipo, removida.id);

            }
            MostrarFila(&f);
            MostrarPilha(&p);
            break;

        }

        case 4: // Trocar a peça da frente da FILA com o topo da PILHA
        {
            if (FilaVazia(&f)) {
                printf("[AVISO] Fila vazia! Nenhuma peça para trocar.\n");
            } else if (PilhaVazia(&p)) {
                printf("[AVISO] Pilha vazia! Nenhuma peça para trocar.\n");
            } else {
                tetris peca_fila, peca_pilha;

                // Remove da fila e da pilha
                RemoverFila(&f, &peca_fila);
                RemoverPilha(&p, &peca_pilha);

                // Troca: insere a peça da pilha na frente da fila
                InserirFilaFrente(&f, peca_pilha);

                // Insere a peça da fila no topo da pilha
                InserirPilha(&p, peca_fila);

                printf("[TROCA] Peça da FILA [%s, %d] trocada com PILHA [%s, %d]\n",
                    peca_fila.tipo, peca_fila.id,
                    peca_pilha.tipo, peca_pilha.id);
            }
            MostrarFila(&f);
            MostrarPilha(&p);
            break;
        }

case 5: // Trocar três peças da FILA com três da PILHA
{
    if (f.total < 3) {
        printf("[AVISO] Fila tem menos de 3 peças.\n");
    } else if (p.topo < 2) { // topo = 2 → 3 elementos (0,1,2)
        printf("[AVISO] Pilha tem menos de 3 peças.\n");
    } else {
        tetris fila3[3];
        tetris pilha3[3];

        // Remove as 3 primeiras da fila
        for (int i = 0; i < 3; i++) {
            RemoverFila(&f, &fila3[i]);
        }

        // Remove as 3 da pilha (topo primeiro)
        for (int i = 0; i < 3; i++) {
            RemoverPilha(&p, &pilha3[i]);
        }

        // Insere as 3 da pilha na FRENTE da fila (topo da pilha vira primeira)
        for (int i = 2; i >= 0; i--) {
            InserirFilaFrente(&f, pilha3[i]);
        }

        // Insere as 3 da fila na PILHA (primeira da fila vira topo)
        for (int i = 2; i >= 0; i--) {
            InserirPilha(&p, fila3[i]);
        }

        printf("[TROCA] 3 peças trocadas entre FILA e PILHA.\n");
    }
    MostrarFila(&f);
    MostrarPilha(&p);
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

void InserirFilaFrente(Fila *f, tetris p) {
    if (FilaCheia(f)) {
        printf("[AVISO] Fila Cheia. Impossivel inserir.\n");
        return;
    }
    f->inicio = (f->inicio - 1 + MAX_TAMANHO) % MAX_TAMANHO;
    f->itens[f->inicio] = p;
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
    printf("1 - Jogar peca da frente da FILA\n"); // remove uma peca da frente da fila
    printf("2 - Reservar Peca da FILA para PILHA\n"); // move a peca da frete da fila para o topo da pilha, se houver espaco
    printf("3 - Usar peca reservada da PILHA\n"); // remove a pe;a do topo da pilha e simula seu uso
    printf("4 - Trocar uma peca da FILA com a PILHA\n");//substitui a peça da frente da fila com o topo da pilha.
    printf("5 - Trocar tres pecas da FILA com a PILHA\n"); //alterna as três primeiras peças da fila com as três peças da pilha (caso ambas tenham, pelo menos, 3 peças).
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

/// @brief inicializa a pilha vazia
/// @param p ponteiro da pilha
void InicializarPilha(Pilha *p){
    p->topo = -1;
}

/// @brief mostra o estado da pilha com seus itens 
/// @param p ponteiro da pilha
void MostrarPilha(Pilha *p){
    printf("Pilha (Topo -> Base): \n");
    for (int i = p->topo; i >= 0; i--){
        printf("[%s, %d]\n", p->reserva[i].tipo, p->reserva[i].id);
    }
    printf("\n");
}

/// @brief remove item do topo da pilha
/// @param p ponteiro 
/// @param remove ponteiro da remocao
void RemoverPilha(Pilha *p, tetris *remove){
    if (PilhaVazia(p)){
        printf("[AVISO] Pilha Vazia");
        return;
    }
    *remove = p->reserva[p->topo];
    p->topo--;


}


/// @brief funcao verificacao se a pilha esta fazia
/// @param p ponteiro da pilha
/// @return retorna -1 se a pilha estiver vazia
int PilhaVazia(Pilha *p){ 
    return p->topo == -1;
}


/// @brief funcao verificacao se a pilha esta cheia
/// @param p ponteiro da pilha
/// @return retorna 0 se a pilha estiver cheia
int PilhaCheia(Pilha *p){
    return p->topo == MAX_PILHA -1;
}

/// @brief  inseri na pilha uma peca no final
/// @param p  passa o ponteiro da pilha
/// @param t  passa o ponteiro t
void InserirPilha(Pilha *p, tetris t) {
    if (PilhaCheia(p)) {
        printf("[AVISO] Pilha Cheia! Impossível inserir.\n");
        return;
    }
    p->reserva[++p->topo] = t;
}