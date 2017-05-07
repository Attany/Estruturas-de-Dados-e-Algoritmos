#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node *ant;
    int num;
    struct Node *prox;
};
typedef struct Node node;

struct Lista{
    node *primeiro;
    int qtde;
    node *ultimo;

};
typedef struct Lista lista;

void iniciaLista(lista *Lista);
void iniciaNode(node *node);
int menu(void);
void opcao(lista *Lista, int op);
int vazia(lista *Lista);
node *aloca();
void exibe(lista *Lista);
void libera(lista *Lista);
void insereInicio(lista *Lista);
node *retiraInicio(lista *Lista);
node *desempilha(lista *Lista);
void empilha(lista *Lista);

int main(){
    //alocando espaço de memória para o nó que será a cabeça da lista
    lista *Lista = (lista*)malloc(sizeof(lista));

    //verifica se o espaço foi alocado
    if(!Lista){
		printf("Sem memoria disponivel!\n");
		exit(EXIT_FAILURE);
	}else{
        //função inicia lista
        iniciaLista(Lista);

        int opt;
        do{
            opt = menu();
            opcao(Lista,opt);
        }while(opt);

        free(Lista);
        return 0;
    }
}

void iniciaLista(lista *Lista){
    //aponta pra null porque a lista ta vazia
    Lista->primeiro = NULL;
    Lista->ultimo = NULL;
    Lista->qtde = 0;
}

void iniciaNode(node *node){
    node->ant = NULL;
    node->prox = NULL;
}

int menu(void){
	int opt;

	printf("Escolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Exibir lista\n");
	printf("2. Empilha\n");
	printf("3. Desempilha\n");
	printf("Opcao: "); scanf("%d", &opt);

	return opt;
}

void opcao(lista *Lista, int op){
	switch(op){
		case 0:
			libera(Lista);
			break;

		case 1:
			exibe(Lista);
			break;

		case 2:
			empilha(Lista);
			break;

        case 3:
            desempilha(Lista);
			break;

		default:
			printf("Comando invalido\n\n");
	}
}

int vazia(lista *Lista){
	if(Lista->qtde == 0)
		return 1;
	else
		return 0;
}

node *aloca(){
	node *novo = (node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
        iniciaNode(novo);
		printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}

void exibe(lista *Lista){
    system("clear");
	if(vazia(Lista)){
		printf("Lista vazia!\n\n");
		return ;
	}

	node *aux = Lista->primeiro;

    printf("Lista:");
	while( aux != NULL){
		printf("%5d", aux->num);
		aux = aux->prox;
	}
    printf("\n        ");
	int count;
	for(count=0 ; count < Lista->qtde ; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for(count=0 ; count < Lista->qtde ; count++)
		printf("%5d", count+1);

	printf("\n\n");
}

void libera(lista *Lista){
    while(!vazia(Lista)){
		free(retiraInicio(Lista));
	}
}
void empilha(lista *Lista){
    insereInicio(Lista);
}
void insereInicio(lista *Lista){
    node *novo = aloca();

    if(vazia(Lista)){
        novo->prox = NULL;
        novo->ant = NULL;
        Lista->primeiro = novo;
        Lista->ultimo = novo;
    }else{
        novo->ant = NULL;
        novo->prox = Lista->primeiro;
        Lista->primeiro->ant = novo;
        Lista->primeiro = novo;
    }
    Lista->qtde++;
}

node *desempilha(lista *Lista){
    node *elemento = retiraInicio(Lista);
    if(elemento == NULL){
        printf("Fila vazia");
    }else{
        printf("Retirado: %3d\n\n", elemento->num);
    }
    return elemento;
}

node *retiraInicio(lista *Lista){
    if(vazia(Lista)){
        return NULL;
	}else{
        node *aux = Lista->primeiro;
        if(Lista->qtde == 1){
            Lista->primeiro = NULL;
            Lista->ultimo = NULL;
        }else{
            Lista->primeiro = aux->prox;
            aux->prox->ant = NULL;
        }
        Lista->qtde--;
        return aux;
	}
}

