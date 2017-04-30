#include <stdio.h>
#include <stdlib.h>

struct Node{
    int num;
    struct Node *prox;

};
typedef struct Node node;

int tam;

void inicia(node *Lista);
int menu(void);
void opcao(node *Lista, int op);
void inserePosicao(node *Lista);
void insereFim(node *Lista);
void insereInicio(node *Lista);
void insereAntesValor(node *Lista);
void exibe(node *Lista);
void libera(node *Lista);
node *retiraInicio(node *Lista);
node *retiraFim(node *Lista);
node *retira(node *Lista);
node *retiraValor(node *Lista);


int main(){
    //alocando espaço de memória para o nó que será a cabeça da lista
    node *Lista = (node*)malloc(sizeof(node));

    //verifica se o espaço foi alocado
    if(!Lista){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
        //função inicia lista
        inicia(Lista);

        int opt;
        do{
            opt = menu();
            opcao(Lista,opt);
        }while(opt);

        free(Lista);
        return 0;
    }

}

void inicia(node *Lista){
    //aponta pra null porque a lista ta vazia
    Lista->prox = NULL;
    tam = 0;
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

void opcao(node *Lista, int op){
	node *tmp;
	switch(op){
		case 0:
			libera(Lista);
			break;

		case 1:
			libera(Lista);
			inicia(Lista);
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
            retira(Lista);
			break;

        case 10:
            retiraValor(Lista);
            break;

		default:
			printf("Comando invalido\n\n");
	}
}

int vazia(node *Lista){
	if(Lista->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca(){
	node *novo=(node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}

void insereFim(node *Lista){
	node *novo = aloca();
	novo->prox = NULL;

	if(vazia(Lista))
		Lista->prox=novo;
	else{
		node *tmp = Lista->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	tam++;
}

void insereInicio(node *Lista){
    //a lista pode estar vazia
	node *novo=aloca();
	node *oldHead = Lista->prox;

	Lista->prox = novo;
	novo->prox = oldHead;

	tam++;
}

void exibe(node *Lista){
    system("clear");
	if(vazia(Lista)){
		printf("Lista vazia!\n\n");
		return ;
	}

	node *tmp;
	tmp = Lista->prox;

    printf("Lista:");
	while( tmp != NULL){
		printf("%5d", tmp->num);
		tmp = tmp->prox;
	}
    printf("\n        ");
	int count;
	for(count=0 ; count < tam ; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for(count=0 ; count < tam ; count++)
		printf("%5d", count+1);

	printf("\n\n");
}

void libera(node *Lista){
	if(!vazia(Lista)){
		node *proxNode,*atual;

		atual = Lista->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void inserePosicao(node *Lista){
	int pos,count;
	printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
	scanf("%d", &pos);

	if(pos>0 && pos <= tam){
		if(pos==1)
			insereInicio(Lista);
		else{
			node *atual = Lista->prox,
				 *anterior=Lista;
			node *novo=aloca();

			for(count=1 ; count < pos ; count++){
					anterior=atual;
					atual=atual->prox;
			}
			anterior->prox=novo;
			novo->prox = atual;
			tam++;
		}

	}else
		printf("Elemento invalido\n\n");
}

void insereAntesValor(node *Lista){
    if(vazia(Lista)){
		printf("Lista está vazia!\n\n");
	}else{
        int numero;
        node *novo = aloca();
        printf("Inserir elemento antes do elemento: ");
        scanf("%d",&numero);

        node *aux = Lista;

        while(aux->prox != NULL && aux->prox->num != numero ){
            aux = aux->prox;
        }
        if(aux->prox == NULL){
            printf("Número não está lista!\n");
        }else{
            novo->prox = aux->prox;
        aux->prox = novo;
        tam++;
        }
    }
}

node *retiraInicio(node *Lista){
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}else{
        node *tmp = Lista->prox;
        Lista->prox = tmp->prox;
        printf("Retirado: %3d\n\n", tmp->num);
        tam--;
        return tmp;
	}
}

node *retiraFim(node *Lista){
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}else{
        node *ultimo = Lista->prox;
        node *penultimo = Lista;

        while(ultimo->prox != NULL){
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }
        penultimo->prox = NULL;
        printf("Retirado: %3d\n\n", ultimo->num);
        tam--;
        return ultimo;
	}
}

node *retira(node *Lista){
	int opt, count;
	printf("Que posicao, [de 1 ate %d] voce deseja retirar: ", tam);
	scanf("%d", &opt);

	if(opt>0 && opt <= tam){
		if(opt==1)
			return retiraInicio(Lista);
		else{
			node *atual = Lista->prox;
            node *anterior = Lista;

			for(count=1 ; count < opt ; count++){
				anterior = atual;
				atual = atual->prox;
			}

		anterior->prox = atual->prox;
		tam--;
		return atual;
		}

	}else{
		printf("Elemento invalido\n\n");
		return NULL;
	}
}

node *retiraValor(node *Lista){
    //verifica se a lista esta vazia
    if(vazia(Lista)){
		printf("Lista já está vazia!\n\n");
		return NULL;
	}else{
        int numero;
        printf("Digite o número que deseja excluir: ");
        scanf("%d", &numero);

        node *anterior = Lista;
        node *proximo = Lista->prox;

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
        tam--;
        return Lista;
    }
}



