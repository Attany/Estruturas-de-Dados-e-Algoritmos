#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node *prox;
    int num;
};
typedef struct Node node;

struct Lista{
    node *primeiro;
    int qtde;
    node *ultimo;

};
typedef struct Lista lista;

void inicia(lista *Lista);
int menu(void);
void opcao(lista *Lista, int op);
void inserePosicao(lista *Lista);
void insereFim(lista *Lista);
void insereInicio(lista *Lista);
void insereAntesValor(lista *Lista);
void exibe(lista *Lista);
void libera(lista *Lista);
node *retiraInicio(lista *Lista);
node *retiraFim(lista *Lista);
node *retiraPosicao(lista *Lista);
node *retiraValor(lista *Lista);


int main(){
    //alocando espaço de memória para o nó que será a cabeça da lista
    lista *Lista = (lista*)malloc(sizeof(lista));

    //verifica se o espaço foi alocado
    if(!Lista){
		printf("Sem memoria disponivel!\n");
		exit(1);
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
    node->prox = NULL;
}

int menu(void){
	int opt;

	printf("Escolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Zerar lista\n");
	printf("2. Exibir lista\n");
	printf("3. Adicionar node no inicio\n");
	printf("4. Adicionar node no final\n");
	printf("5. Escolher posição para inserir\n");
	printf("6. Escolher inserir antes de um elemento\n");
	printf("7. Retirar do inicio\n");
	printf("8. Retirar do fim\n");
	printf("9. Escolher de onde tirar\n");
	printf("10. Retirar valor\n");
	printf("Opcao: "); scanf("%d", &opt);

	return opt;
}

void opcao(lista *Lista, int op){
	switch(op){
		case 0:
			libera(Lista);
			break;

		case 1:
			libera(Lista);
			iniciaLista(Lista);
			break;

		case 2:
			exibe(Lista);
			break;

		case 3:
			insereInicio(Lista);
			break;

		case 4:
			insereFim(Lista);
			break;

		case 5:
			inserePosicao(Lista);
			break;

		case 6:
			insereAntesValor(Lista);
			break;

        case 7:
			retiraInicio(Lista);
			break;

		case 8:
			retiraFim(Lista);
			break;

		case 9:
            retiraPosicao(Lista);
			break;

        case 10:
            retiraValor(Lista);
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



    printf("Lista:");
    printf("%5d", Lista->primeiro->num);

    node *aux = Lista->primeiro->prox;
	while( aux != Lista->primeiro){
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
	if(!vazia(Lista)){

		while(Lista->qtde>0){
            retiraInicio(Lista);
		}
	}
}

void insereInicio(lista *Lista){
    node *novo = aloca();

    if(vazia(Lista)){
        novo->prox = novo;
        Lista->primeiro = novo;
        Lista->ultimo = novo;
    }else{
        novo->prox = Lista->primeiro;
        Lista->primeiro = novo;
        Lista->ultimo->prox = novo;
    }

    Lista->qtde++;
}

void insereFim(lista *Lista){
	node *novo = aloca();

	if(vazia(Lista)){
		novo->prox = novo;
        Lista->primeiro = novo;
        Lista->ultimo = novo;
    }else{
		Lista->ultimo->prox = novo;
		Lista->ultimo = novo;
		novo->prox = Lista->primeiro;
	}
	Lista->qtde++;
}

void inserePosicao(lista *Lista){
	int pos,count;
	printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", Lista->qtde);
	scanf("%d", &pos);

	if(pos>0 && pos <= Lista->qtde){
		if(pos==1){
			insereInicio(Lista);
		}else{
            if(pos==Lista->qtde){
                insereFim(Lista);
            }else{
                node *atual = Lista->primeiro;
                node *anterior = Lista->primeiro;
                node *novo = aloca();

                for(count = 1; count<pos; count++){
                        anterior = atual;
                        atual = atual->prox;
                }
                anterior->prox = novo;
                novo->prox = atual;
                Lista->qtde++;
            }
		}

	}else
		printf("Elemento invalido\n\n");
}

void insereAntesValor(lista *Lista){
    if(vazia(Lista)){
		printf("Lista está vazia!\n\n");
	}else{
        int numero;
        node *novo = aloca();
        if(Lista->qtde==1){
            insereInicio(Lista);
            return;
        }
        printf("Inserir elemento antes do elemento: ");
        scanf("%d",&numero);

        node *aux = Lista->primeiro;

        while(aux->prox != Lista->primeiro && aux->prox->num != numero ){
            aux = aux->prox;
        }
        if(aux->prox == Lista->primeiro){
            printf("Número não está lista!\n");
        }else{
            novo->prox = aux->prox;
            aux->prox = novo;
        Lista->qtde++;
        }
    }
}

node *retiraInicio(lista *Lista){
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}else{
        node *aux = Lista->primeiro;
        if(Lista->qtde==1){
            free(aux);
            Lista->primeiro = NULL;
            Lista->ultimo = NULL;
        }else{
            Lista->primeiro = aux->prox;
            printf("Retirado: %3d\n\n", aux->num);
            Lista->ultimo->prox = Lista->primeiro;
        }
        Lista->qtde--;
        return aux;
	}
}

node *retiraFim(lista *Lista){
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}else{
        if(Lista->qtde==1){
            node *aux = Lista->primeiro;
            free(aux);
            Lista->primeiro = NULL;
            Lista->ultimo = NULL;
        }else{
            node *ultimo = Lista->ultimo;
            node *penultimo = Lista->primeiro;

            while(penultimo->prox != ultimo){
                penultimo = penultimo->prox;
            }
            penultimo->prox = Lista->primeiro;
            Lista->ultimo = penultimo;
            printf("Retirado: %3d\n\n", ultimo->num);
            Lista->qtde--;
            return ultimo;
        }
	}
}

node *retiraPosicao(lista *Lista){
	int opt, count;
	printf("Que posicao, [de 1 ate %d] voce deseja retirar: ", Lista->qtde);
	scanf("%d", &opt);

	if(opt>0 && opt <= Lista->qtde){
		if(opt==1){
			return retiraInicio(Lista);
        }
        if(Lista->qtde==1){
            node *aux = Lista->primeiro;
            free(aux);
            Lista->primeiro = NULL;
            Lista->ultimo = NULL;
            return NULL;
        }
        if(Lista->qtde==opt){
            retiraFim(Lista);
        }
        node *anterior = Lista->primeiro;
        node *atual = Lista->primeiro;

        for(count=1 ; count < opt ; count++){
            anterior = atual;
            atual = atual->prox;
        }

        anterior->prox = atual->prox;
        Lista->qtde--;
        return atual;
        }else{
            printf("Elemento invalido\n\n");
            return NULL;
        }
}

node *retiraValor(lista *Lista){
    //verifica se a lista esta vazia
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}
	if(Lista->qtde==1){
        node *aux = Lista->primeiro;
        free(aux);
        Lista->primeiro = NULL;
        Lista->ultimo = NULL;
        return NULL;
    }
    int numero;
    printf("Digite o número que deseja excluir: ");
    scanf("%d", &numero);

    if(Lista->qtde==numero){
        retiraFim(Lista);
    }

    node *anterior = Lista;
    node *proximo = Lista->primeiro;

    while(anterior->prox != NULL && anterior->prox->num !=numero){
        anterior = anterior->prox;
    }
    if(anterior->prox == NULL){
        printf("Número não consta na lista!\n");
        return NULL;
    }
    proximo = anterior->prox->prox;
    free(anterior->prox);
    anterior->prox = proximo;
    printf("Número retirado: %d\n", numero);
    Lista->qtde--;
    return Lista;
}

