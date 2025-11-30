#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// ---------------------------
//      CONFIGURAÇÕES
// ---------------------------
#define TAM_FILA 5
#define TAM_PILHA 3

// ---------------------------
//      STRUCT PEÇA
// ---------------------------
typedef struct {
    char tipo;
    int id;
} Peca;

// ---------------------------
//      FILA (CIRCULAR)
// ---------------------------
typedef struct {
    Peca vet[TAM_FILA];
    int inicio, fim, qtd;
} Fila;

// ---------------------------
//      PILHA
// ---------------------------
typedef struct {
    Peca vet[TAM_PILHA];
    int topo;
} Pilha;

// ---------------------------
//   PROTÓTIPOS - FILA
// ---------------------------
void inicializarFila(Fila *f);
bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void mostrarFila(Fila *f);

// ---------------------------
//   PROTÓTIPOS - PILHA
// ---------------------------
void inicializarPilha(Pilha *p);
bool pilhaCheia(Pilha *p);
bool pilhaVazia(Pilha *p);
void push(Pilha *p, Peca x);
Peca pop(Pilha *p);
void mostrarPilha(Pilha *p);

// ---------------------------
//   FUNÇÕES AUXILIARES
// ---------------------------
Peca gerarPeca();
void mostrarEstruturas(Fila *f, Pilha *p);
void trocar1(Fila *f, Pilha *p);
void trocar3(Fila *f, Pilha *p);

// -----------------------------------------------------------
//                       MAIN
// -----------------------------------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preencher a fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++)
        enqueue(&fila, gerarPeca());

    int op;

    do {
        printf("\n\n=== DESAFIO TETRIS STACK ===\n");
        mostrarEstruturas(&fila, &pilha);

        printf("\nMenu:\n");
        printf("1 - Jogar peça (remover da fila)\n");
        printf("2 - Enviar peça da fila para a pilha (reserva)\n");
        printf("3 - Usar peça da pilha (pop)\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            if (filaVazia(&fila)) {
                printf("A fila está vazia!\n");
            } else {
                Peca jogada = dequeue(&fila);
                printf("Peça jogada: %c%d\n", jogada.tipo, jogada.id);
                enqueue(&fila, gerarPeca());
            }
        }

        else if (op == 2) {
            if (filaVazia(&fila)) {
                printf("Fila vazia!\n");
            } else if (pilhaCheia(&pilha)) {
                printf("Pilha cheia!\n");
            } else {
                Peca frente = dequeue(&fila);
                push(&pilha, frente);
                enqueue(&fila, gerarPeca());
                printf("Peça enviada pra reserva.\n");
            }
        }

        else if (op == 3) {
            if (pilhaVazia(&pilha)) {
                printf("Pilha vazia!\n");
            } else {
                Peca usada = pop(&pilha);
                printf("Usou peça da reserva: %c%d\n", usada.tipo, usada.id);
            }
        }

        else if (op == 4) {
            trocar1(&fila, &pilha);
        }

        else if (op == 5) {
            trocar3(&fila, &pilha);
        }

    } while (op != 0);

    return 0;
}

// -----------------------------------------------------------
//                   IMPLEMENTAÇÃO DA FILA
// -----------------------------------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

bool filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

bool filaVazia(Fila *f) {
    return f->qtd == 0;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;

    f->vet[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->qtd++;
}

Peca dequeue(Fila *f) {
    Peca removido = f->vet[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return removido;
}

void mostrarFila(Fila *f) {
    printf("FILA: ");
    if (filaVazia(f)) {
        printf("[vazia]");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->qtd; c++) {
        printf("%c%d ", f->vet[i].tipo, f->vet[i].id);
        i = (i + 1) % TAM_FILA;
    }
}

// -----------------------------------------------------------
//                   IMPLEMENTAÇÃO DA PILHA
// -----------------------------------------------------------
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

bool pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

bool pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->vet[p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca x = p->vet[p->topo];
    p->topo--;
    return x;
}

void mostrarPilha(Pilha *p) {
    printf("PILHA: ");
    if (pilhaVazia(p)) {
        printf("[vazia]");
        return;
    }

    for (int i = 0; i <= p->topo; i++) {
        printf("%c%d ", p->vet[i].tipo, p->vet[i].id);
    }
}

// -----------------------------------------------------------
//                GERAÇÃO AUTOMÁTICA DE PEÇAS
// -----------------------------------------------------------
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L', 'S'};
    p.tipo = tipos[rand() % 5];

    static int contador = 1;
    p.id = contador++;
    return p;
}

// -----------------------------------------------------------
//               EXIBIR ESTRUTURAS JUNTAS
// -----------------------------------------------------------
void mostrarEstruturas(Fila *f, Pilha *p) {
    printf("\n------------------------------\n");
    mostrarFila(f);
    printf("\n");
    mostrarPilha(p);
    printf("\n------------------------------\n");
}

// -----------------------------------------------------------
//               TROCA 1x1 (fila ↔ pilha)
// -----------------------------------------------------------
void trocar1(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Impossível trocar (falta peça).\n");
        return;
    }

    int idx = f->inicio;
    Peca temp = f->vet[idx];
    f->vet[idx] = p->vet[p->topo];
    p->vet[p->topo] = temp;

    printf("Troca realizada!\n");
}

// -----------------------------------------------------------
//               TROCA 3x3 (fila ↔ pilha)
// -----------------------------------------------------------
void trocar3(Fila *f, Pilha *p) {
    if (f->qtd < 3 || p->topo != 2) {
        printf("Não é possível trocar 3 peças!\n");
        return;
    }

    for (int k = 0; k < 3; k++) {
        int idx = (f->inicio + k) % TAM_FILA;
        Peca temp = f->vet[idx];
        f->vet[idx] = p->vet[k];
        p->vet[k] = temp;
    }

    printf("Troca de 3 peças realizada!\n");
}
