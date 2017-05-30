#include <stdio.h>
#include <stdlib.h>

struct Node{
    int num;
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
tree insereNode(tree **descritorRaiz);
int buscaTree(tree **descritorRaiz);
tree removeTree(tree **descritorRaiz);
tree *removeNode(tree *atual);
void liberaNode(tree *node);
void liberaTree(tree **descritorRaiz);
int alturaTree(tree **descritorRaiz);
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
			printf("A altura da árvore é: %d\n",alturaTree(descritorRaiz));
			break;

        case 3:
			printf("A árvore possui %d nós.\n",totalNodes(descritorRaiz));
			break;

		case 4:
			insereNode(descritorRaiz);
			break;

        case 5:
			buscaTree(descritorRaiz);
			break;

		case 6:
			removeTree(descritorRaiz);
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
		printf("Novo elemento: ");
		scanf("%d", &novo->num);
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

tree insereNode(tree **descritorRaiz){
    tree *novo = alocaNode();

    if(treeVazia(descritorRaiz)){
        *descritorRaiz = novo;
    }else{
        tree *atual = *descritorRaiz;
        tree *ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(novo->num == atual->num){
                printf("Número já está na árvore!\n");
                free(novo);
                exit(1);
            }
            if(novo->num < atual->num){
                atual = atual->esq;
            }else{
                atual = atual->dir;
            }
        }
        if(novo->num < ant->num){
            ant->esq = novo;
        }else{
            ant->dir = novo;
        }
    }

    return *novo;

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

tree removeTree(tree **descritorRaiz){
    tree *atual = *descritorRaiz;
    tree *ant = NULL;

    int valor;
    printf("Digite o número que deseja remover da árvore: ");
    scanf("%d", &valor);

    while(atual != NULL){
        if(valor == atual->num){
            if(atual == *descritorRaiz){
                *descritorRaiz = removeNode(atual);
            }else{
                if(ant->esq == atual){
                    ant->esq = removeNode(atual);
                }else{
                    ant->dir = removeNode(atual);
                }
            }
            return *atual;
        }
        ant = atual;
        if(valor < atual->num){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    printf("Valor inserido não faz parte da árvore.\n");
}

tree *removeNode(tree *atual){
    tree *node1;
    tree *node2;

    if(atual == NULL) printf("DEBUG removeNode: try remove a NULL node\n");

    if(atual->esq == NULL){
        node2 = atual->dir;
        free(atual);
        return node2;
    }
    node1 = atual;
    node2 = atual->esq;

    while(node2->dir != NULL){
        node1 = node2;
        node2 = node2->dir;
    }

    if(node1 != atual){
        node1->dir = node2->esq;
        node2->esq = atual->esq;
    }
    node2->dir = atual->dir;
    free(atual);
    return node2;
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

int alturaTree(tree **descritorRaiz){
    if(descritorRaiz == NULL){
        return 0;
    }
    if(*descritorRaiz == NULL){
        return 0;
    }

    int alturaEsq = alturaTree(&((*descritorRaiz)->esq));
    int alturaDir = alturaTree(&((*descritorRaiz)->dir));

    if(alturaEsq > alturaDir){
        return (alturaEsq+1);
    }else{
        return (alturaDir+1);
    }
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
        imprimeTree(&((*descritorRaiz)->esq));
        imprimeTree(&((*descritorRaiz)->dir));
        printf("%d\n",(*descritorRaiz)->num);
    }else{
        return;
    }
}
