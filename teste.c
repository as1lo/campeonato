#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NTIME 4

//OBS: terminar oitavas
//adicionar o sistema de retirada da lista baseado nos maiores saldos
//ocorre erro na contagem de saldo

//OBS: adicionar a troca de fase: todos os times, de cada grupo, se enfrentam no sistema ida e volta
		//o 2 melhores times, com melhor saldo, se enfrentam nas 4 de finais.
		//1° colocado A x 2° colocado de B
		//1° colocado B x 2° colocado de C
		//1° colocado C x 2° colocado de D
		//1° colocado D x 2° colocado de A
		
//OBS: mostrar a contagem de pontos feitos, sofridos e saldo de cada fase
//OBS: declarar o vencedor final como campeão

typedef struct time{
	char nome[30];
	int etiqueta;
	int pontos_feitos;
	int pontos_sofridos;
	int saldo;
}time;

typedef struct lista{
	struct time dados;
	struct lista *proximo;
}lista;

void inserir(lista **fim, time dados){
	lista *novalista = (lista *)malloc(sizeof(lista));

	novalista->dados = dados;
	novalista->proximo = NULL;

	if(*fim == NULL){
		*fim = novalista;
	}else{
		lista *aux = *fim;

		while(aux->proximo != NULL){
			aux = aux->proximo;
		}
	
		aux->proximo = novalista;
	}
}

void buscar_e_tirar(lista **node, int inicio, int fim, int segundo_maior){
	lista *atual = *node;
	lista *prox = NULL;
	
	while(inicio != atual->dados.etiqueta){
		atual = atual->proximo;
	}

	while(atual->dados.etiqueta != fim && atual->dados.saldo < segundo_maior){
		prox = atual;
		atual = atual->proximo;
	}

	if(atual != NULL || atual->dados.etiqueta != fim ){
		if(prox != NULL || prox->dados.etiqueta != fim ){
			prox->proximo = atual->proximo;
		}else{
			*node = atual->proximo;
		}
	}
	
	free(atual);

}

char *buscar_imprimir(lista *node, int etiq){
	lista *atual = node;
	
	while(atual->dados.etiqueta != etiq){
		atual = atual->proximo;
	}

	return atual->dados.nome;
}

void recebe_pontos_sofridos(lista **node, int etiq, int pontos){
	lista *aux = *node;

	while(aux->dados.etiqueta != etiq){
		aux = aux->proximo;
	}

	aux->dados.pontos_sofridos = aux->dados.pontos_sofridos + pontos;

	if(aux->dados.pontos_sofridos >= aux->dados.pontos_feitos){
		aux->dados.saldo = aux->dados.saldo + (aux->dados.pontos_sofridos - aux->dados.pontos_feitos);
	}else{
		aux->dados.saldo = aux->dados.saldo + (aux->dados.pontos_feitos - aux->dados.pontos_sofridos);
	}
}

int buscar_selecionar_pontos(lista **node, int etiq){
	lista *aux = *node;
	
	while(aux->dados.etiqueta != etiq){
		aux = aux->proximo;
	}

	int pontos;

	scanf("%d", &pontos);

	aux->dados.pontos_feitos = aux->dados.pontos_feitos + pontos;

	//para retornar os pontos feitos de um determinado time para pontos sofridos de outrem.
	return aux->dados.pontos_feitos;
}

void selecionar_pontos(lista **no, int etiq1, int etiq2){
	lista *node = *no;

	printf("%s -VS- %s\n", buscar_imprimir(node, etiq1), buscar_imprimir(node, etiq2));

	printf("PONTOS de %s: ", buscar_imprimir(node, etiq1));
	int pontos1 = buscar_selecionar_pontos(no, etiq1);

	printf("PONTOS de %s: ", buscar_imprimir(node, etiq2));
	int pontos2 = buscar_selecionar_pontos(no, etiq2);

	recebe_pontos_sofridos(no, etiq2, pontos1);
	recebe_pontos_sofridos(no, etiq1, pontos2);

	system("cls");
}

void sistema_oitavas(lista **no, int etiq1, int etiq2, int etiq3, int etiq4, int oitavas, int limite){

	while(oitavas <= limite){
		if(etiq1 == oitavas){
			selecionar_pontos(no, etiq1, etiq2);
			selecionar_pontos(no, etiq1, etiq3);
			selecionar_pontos(no, etiq1, etiq4);
		}
			
		if(etiq2 == oitavas){
			selecionar_pontos(no, etiq2, etiq1);
			selecionar_pontos(no, etiq2, etiq3);
			selecionar_pontos(no, etiq2, etiq4);
		}

		if(oitavas == etiq3){
			selecionar_pontos(no, etiq3, etiq1);
			selecionar_pontos(no, etiq3, etiq2);
			selecionar_pontos(no, etiq3, etiq4);
		}

		if(oitavas == etiq4){
			selecionar_pontos(no, etiq4, etiq1);
			selecionar_pontos(no, etiq4, etiq2);
			selecionar_pontos(no, etiq4, etiq3);
		}
	
	oitavas++;
	}
}

void inicializar_pontos(lista **node){
	lista *aux = *node;

	while(aux != NULL){
		aux->dados.pontos_feitos = 0;
		aux->dados.pontos_sofridos = 0;
		aux->dados.saldo = 0;

		aux = aux->proximo;
	}
}

void mostra_contagem(lista *node, int inicio, int fim){
	lista *aux = node;
	
	while(aux->dados.etiqueta != inicio){
		aux = aux->proximo;
	}

	while(aux->dados.etiqueta != fim + 1){
		printf("\n| %s (%d)|\nPONTOS FEITOS: %d\nPONTOS SOFRIDOS: %d\nSALDO: %d\n", aux->dados.nome, aux->dados.etiqueta, aux->dados.pontos_feitos, aux->dados.pontos_sofridos, aux->dados.saldo);

		aux = aux->proximo;
	}	
}

int main(){
	char r;
	
	do{
		lista *node = NULL;
		time ally;

		int i = 1, etiq = 1;

		//seleção dos grupos
		while(i <= 4){
			int j = 1;
			printf("=======| CAMPEONATO |=======\n");
			printf("INSIRA OS NOMES DOS TIMES:\n");
			switch(i){
				case 1: printf("\n| GRUPO A |\n"); break;
				case 2: printf("\n| GRUPO B |\n"); break;
				case 3: printf("\n| GRUPO C |\n"); break;
				case 4: printf("\n| GRUPO D |\n"); break;
			};

			while(j <= NTIME){
				printf("Nome do %do time: ", j);
				
				scanf(" %s", ally.nome);

				ally.etiqueta = etiq;

				etiq++;

				inserir(&node, ally);
				//printime(node);
				j++;
			}
			system("cls");
			i++;
		}

		inicializar_pontos(&node);

		i = 1;

		//oitavas
		while(i <= 4){

			switch(i){
				case 1: printf("\n| GRUPO A |\n\n"); sistema_oitavas(&node, 1, 2, 3, 4, 1, 4); 
					mostra_contagem(node, 1, 4); break;
				case 2: printf("\n| GRUPO B |\n\n"); sistema_oitavas(&node, 5, 6, 7, 8, 5, 8); mostra_contagem(node, 5, 8); break;
				case 3: printf("\n| GRUPO C |\n\n"); sistema_oitavas(&node, 9, 10, 11, 12, 9, 12); mostra_contagem(node, 9, 12); break;
				case 4: printf("\n| GRUPO D |\n\n"); sistema_oitavas(&node, 13, 14, 15, 16, 13, 16); mostra_contagem(node, 13, 16); break;
			};
			
			i++;
		}

		printf("\nDeseja criar um novo campeonato?[s/n]\n");
		scanf(" %c", &r);

	}while(r == 's' || r == 'S');
		
	return 0;
}