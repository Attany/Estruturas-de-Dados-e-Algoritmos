#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node{
    int num;
    int altura;
    struct Node *esq;
    struct Node *dir;
};
typedef struct Node tree;

tree **descritorRaiz;
tree *node;

//funções
int menu(void);
void opcao(tree **descritorRaiz, int op);
int treeVazia(tree **descritorRaiz);
tree **alocaTree();
tree *alocaNode();
void rotacaoSimplesEsquerda(tree **descritorRaiz); // Interna
void rotacaoSimplesDireita(tree **descritorRaiz); // Interna
void rotacaoDuplaEsquerdaDireita(tree **descritorRaiz); // Interna
void rotacaoDuplaDireitaEsquerda(tree **descritorRaiz); // Interna
int insereNode(tree **descritorRaiz, int num); // Interna
int insereValor(tree **descritorRaiz); // API
int buscaTree(tree **descritorRaiz); // API
int removeValue(tree **descritorRaiz); // API
tree *removeNode(tree **descritorRaiz, int valor); // Interna
void liberaNode(tree *node); // Interna
void liberaTree(tree **descritorRaiz); // API
int alturaTree(tree *node); // API
int fatorBalanceamento(tree *node); // Interna
int maior(int x, int y);
tree * buscaMenor(tree *atual);
int totalNodes(tree **descritorRaiz);
void imprimeTree(tree **descritorRaiz);

int main(){
    tree **arvore = alocaTree();

    int opt;
    do{
        opt = menu();
        opcao(arvore,opt);
    }while(opt);

    free(arvore);
    return 0;
}

int menu(void){
    int opt;

    printf("\nEscolha a opcao\n");
    printf("0. Sair\n");
    printf("1. Imprimir árvore\n");
    printf("2. Exibir altura da árvore\n");
    printf("3. Exibir quantidade de nós da árvore\n");
    printf("4. Inserir nó na árvore\n");
    printf("5. Buscar valor na árvore\n");
    printf("6. Remover valor da árvore\n");
    printf("Opcao: "); scanf("%d", &opt);

    return opt;
}

void opcao(tree **descritorRaiz, int op){
    switch(op){
        case 0:
            liberaTree(descritorRaiz);
            break;

        case 1:
            imprimeTree(descritorRaiz);
            break;

        case 2:
            printf("A altura da árvore é: %d\n",alturaTree(node));
            break;

        case 3:
            printf("A árvore possui %d nós.\n",totalNodes(descritorRaiz));
            break;

        case 4:
            insereValor(descritorRaiz);
            break;

        case 5:
            buscaTree(descritorRaiz);
            break;

        case 6:
            removeValue(descritorRaiz);
            break;

        default:
            printf("Comando invalido\n\n");
    }
}


int treeVazia(tree **descritorRaiz){
    if(descritorRaiz == NULL){
        return 1;
    }
    if(*descritorRaiz == NULL){
        return 1;
    }
    return 0;
}

tree *alocaNode(){
    tree *novo = (tree*)malloc(sizeof(tree));
    if(!novo){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else{
        printf("\n");
        return novo;
    }
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

tree **alocaTree(){
    tree **descritorRaiz = (tree**)malloc(sizeof(tree**));
    if(descritorRaiz != NULL){
        *descritorRaiz = NULL;
        return descritorRaiz;
    }else{
        exit(0);
    }
}

void rotacaoSimplesDireita(tree **descritorRaiz){
    if(descritorRaiz != NULL){
        tree *no = (*descritorRaiz)->esq;

        (*descritorRaiz)->esq = no->dir;
        no->dir = *descritorRaiz;

        (*descritorRaiz)->altura = maior(alturaTree((*descritorRaiz)->esq), alturaTree((*descritorRaiz)->dir)) + 1;
        no->altura = maior(alturaTree(no->esq), (*descritorRaiz)->altura) + 1;

        *descritorRaiz = no;
    }
}

void rotacaoSimplesEsquerda(tree **descritorRaiz){
    if(descritorRaiz != NULL){
        tree *no = (*descritorRaiz)->dir;

        (*descritorRaiz)->dir = no->esq;
        no->esq = *descritorRaiz;

        (*descritorRaiz)->altura = maior(alturaTree((*descritorRaiz)->esq), alturaTree((*descritorRaiz)->dir)) + 1;
        no->altura = maior(alturaTree(no->dir), (*descritorRaiz)->altura) + 1;

        *descritorRaiz = no;
    }
}

void rotacaoDuplaEsquerdaDireita(tree **descritorRaiz){
    rotacaoSimplesDireita(&(*descritorRaiz)->dir);
    rotacaoSimplesEsquerda(descritorRaiz);
}

void rotacaoDuplaDireitaEsquerda(tree **descritorRaiz){
    rotacaoSimplesEsquerda(&(*descritorRaiz)->esq);
    rotacaoSimplesDireita(descritorRaiz);
}

int insereValor(tree **descritorRaiz){
    int num;
    printf("Novo elemento: ");
    scanf("%d", &num);
    insereNode(descritorRaiz, num);
    return num;
}

int insereNode(tree **descritorRaiz, int num){

    if(*descritorRaiz == NULL){//árvore vazia ou nó folha
        tree *novo = alocaNode();
        novo->num = num;
        *descritorRaiz = novo;
        return num;
    }

    tree *atual = *descritorRaiz;

    if(num < atual->num){
        insereNode(&(atual->esq), num);

        if(fatorBalanceamento(atual) >= 2){
            if(num < (*descritorRaiz)->esq->num){
                rotacaoSimplesDireita(descritorRaiz);
            }else{
                rotacaoDuplaDireitaEsquerda(descritorRaiz);
            }
        }
    }else{
        if(num > atual->num){
            insereNode(&(atual->dir), num);

            if(fatorBalanceamento(atual) >= 2){
                if((*descritorRaiz)->dir->num < num){
                    rotacaoSimplesEsquerda(descritorRaiz);
                }else{
                    rotacaoDuplaEsquerdaDireita(descritorRaiz);
                }
            }
        }else{
            printf("O número já está inserido na árvore!\n");
        }
    }
    atual->altura = maior(alturaTree(atual->esq), alturaTree(atual->dir)) + 1;
    return num;
}

int buscaTree(tree **descritorRaiz){
    tree *atual = *descritorRaiz;

    int valor;
    printf("Digite o número que deseja buscar na árvore: ");
    scanf("%d", &valor);

    while(atual != NULL){
        if(valor == atual->num){
            printf("O valor está na árvore.\n");
            return 1;
        }
        if(valor < atual->num){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    printf("O valor não foi encontrado na árvore.\n");
    return 0;
}


int removeValue(tree **descritorRaiz){
    int valor = 0;
    printf("Digite um valor para ser removido da árvore: ");
    scanf("%d", &valor);
    printf("\n");
    removeNode(descritorRaiz, valor);
}

tree *removeNode(tree **descritorRaiz, int valor){
    if(*descritorRaiz == NULL){// valor n�o existe
        printf("Valor não existe na árvore!\n");
        return;
    }

    if(valor < (*descritorRaiz)->num){
        removeNode(&(*descritorRaiz)->esq, valor);
        if(fatorBalanceamento(*descritorRaiz) >= 2){
            if(alturaTree((*descritorRaiz)->dir->esq) <= alturaTree((*descritorRaiz)->dir->dir)){
                rotacaoSimplesEsquerda(descritorRaiz);
            }else{
                rotacaoDuplaEsquerdaDireita(descritorRaiz);
            }

        }
    } else if((*descritorRaiz)->num < valor){
        removeNode(&(*descritorRaiz)->dir, valor);
        if(fatorBalanceamento(*descritorRaiz) >= 2){
            if(alturaTree((*descritorRaiz)->esq->dir) <= alturaTree((*descritorRaiz)->esq->esq) )
                rotacaoSimplesDireita(descritorRaiz);
            else
                rotacaoDuplaDireitaEsquerda(descritorRaiz);
        }
    } else if((*descritorRaiz)->num == valor){
        if(((*descritorRaiz)->esq == NULL || (*descritorRaiz)->dir == NULL)){// n� tem 1 filho ou nenhum
            tree *oldNode = (*descritorRaiz);
            if((*descritorRaiz)->esq != NULL){
                *descritorRaiz = (*descritorRaiz)->esq;
            } else {
                *descritorRaiz = (*descritorRaiz)->dir;
            }
            free(oldNode);
        }else{ // n� tem 2 filhos
            tree *temp = buscaMenor((*descritorRaiz)->dir);
            (*descritorRaiz)->num = temp->num;
            removeNode(&(*descritorRaiz)->dir, (*descritorRaiz)->num);
            if(fatorBalanceamento(*descritorRaiz) >= 2){
                if(alturaTree((*descritorRaiz)->esq->dir) <= alturaTree((*descritorRaiz)->esq->esq)){
                    rotacaoSimplesEsquerda(descritorRaiz);
                }else{
                    rotacaoDuplaEsquerdaDireita(descritorRaiz);
                }
            }
        }
        if(*descritorRaiz != NULL){
            (*descritorRaiz)->altura = maior(alturaTree((*descritorRaiz)->esq),alturaTree((*descritorRaiz)->dir)) + 1;
        }
        return descritorRaiz;
    }

    (*descritorRaiz)->altura = maior(alturaTree((*descritorRaiz)->esq),alturaTree((*descritorRaiz)->dir)) + 1;
    return descritorRaiz;
}

void liberaNode(tree *node){
    if(node == NULL){
        return;
    }else{
        liberaNode(node->esq);
        liberaNode(node->dir);
        free(node);
        node = NULL;
    }
}


void liberaTree(tree **descritorRaiz){
    if(descritorRaiz == NULL){
        return;
    }else{
        liberaNode(*descritorRaiz);
        *descritorRaiz = NULL;
    }
}

int alturaTree(tree *node){
    if(node == NULL){
        return -1;
    }else{
        return node->altura;
    }
}

int fatorBalanceamento(tree *node){
    return abs(alturaTree(node->esq)- alturaTree(node->dir));
}

int maior(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

tree * buscaMenor(tree *atual){
    tree *no1 = atual;
    tree *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int totalNodes(tree **descritorRaiz){
    if(descritorRaiz == NULL){
        return 0;
    }
    if(*descritorRaiz == NULL){
        return 0;
    }

    int alturaEsq = totalNodes(&((*descritorRaiz)->esq));
    int alturaDir = totalNodes(&((*descritorRaiz)->dir));

    return (alturaEsq + alturaDir + 1);
}

void imprimeTree(tree **descritorRaiz){
    if(*descritorRaiz != NULL){
        printf("R%d\n",(*descritorRaiz)->num);
        printf("esq\n");
        imprimeTree(&((*descritorRaiz)->esq));
        printf("dir\n");
        imprimeTree(&((*descritorRaiz)->dir));
    }else{
        return;
    }
}
