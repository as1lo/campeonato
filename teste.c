#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NTIME 4


//OBS: adicionar a troca de fase: todos os times, de cada grupo, se enfrentam no sistema ida e volta
		//o 2 melhores times, com melhor saldo, se enfrentam nas 4 de finais.
		//1° colocado A x 2° colocado de B
		//1° colocado B x 2° colocado de C
		//1° colocado C x 2° colocado de D
		//1° colocado D x 2° colocado de A
		
//OBS: declarar o vencedor final como campeão

typedef struct time{
	char nome[30];
	int etiqueta;
	int gols_feitos;
	int gols_sofridos;
	int saldo;
	int pontos;
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

/*
int verifica_menor_ponto(lista **no){
	lista *aux = *no;
	
	int etiq = aux->dados.etiqueta;
	int verifica = aux->dados.pontos;

	while(aux != NULL){
		printf("%d\n", etiq);
		
		if(aux->dados.pontos < verifica){
			etiq = aux->dados.etiqueta;
			verifica = aux->dados.pontos;
		}
		
		aux = aux->proximo;
	
	}
	
	return etiq;
}
*/

void buscar_tirar_menor_ponto(lista **node){
    lista *anterior = NULL;
    lista *atual = *node;
    lista *menorAnterior = NULL;
    lista *menor = *node;

    while (atual != NULL) {
        if (atual->dados.pontos < menor->dados.pontos) {
            menorAnterior = anterior;
            menor = atual;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    if (menorAnterior != NULL) {
        menorAnterior->proximo = menor->proximo;
    } else {
        *node = menor->proximo;
    }

    free(menor);
}

void buscar_tirar(lista **node, int etiq){
    lista *anterior = NULL;
    lista *atual = *node;

    while (atual->dados.etiqueta != etiq) {
    
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior != NULL) {
        anterior->proximo = atual->proximo;
    } else {
        *node = atual->proximo;
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


void recebe_gols_sofridos(lista **node, int etiq, int gols){
	lista *aux = *node;

	while(aux->dados.etiqueta != etiq){
		aux = aux->proximo;
	}

	aux->dados.gols_sofridos += gols;
}


int recebe_gols_feitos(lista **node, int etiq){
	lista *aux = *node;
	
	while(aux->dados.etiqueta != etiq){
		aux = aux->proximo;
	}

	int pontos;

	scanf("%d", &pontos);

	aux->dados.gols_feitos += pontos;

	//para retornar os pontos feitos de um determinado time para pontos sofridos de outrem.
	return pontos;
}


void calcula_saldo(lista **node){
	lista *aux = *node;

	while(aux != NULL){
		aux->dados.saldo = aux->dados.gols_feitos - aux->dados.gols_sofridos;

		aux = aux->proximo;
	}
}


void buscar_selecionar_pontos(lista **no, lista **nod, int etiq1, int etiq2, int gols1, int gols2){
	lista *aux1 = *no;
	lista *aux2 = *nod;

	while(aux1->dados.etiqueta != etiq1){
		aux1 = aux1->proximo;
	}

	while(aux2->dados.etiqueta != etiq2){
		aux2 = aux2->proximo;
	}

	if(gols1 > gols2){
		aux1->dados.pontos += 3;
	}else if(gols1 < gols2){
		aux2->dados.pontos += 3;
	}else{
		aux1->dados.pontos += 1;
		aux2->dados.pontos += 1;
	}
}


void selecionar_pontos_e_gols(lista **no, lista **nod, int etiq1, int etiq2){
	lista *node = *no;
	lista *nodee = *nod;

	printf("|%s| x |%s|\n", buscar_imprimir(node, etiq1), buscar_imprimir(nodee, etiq2));

	printf("GOLS de %s: ", buscar_imprimir(node, etiq1));
	int pontos1 = recebe_gols_feitos(no, etiq1);

	printf("GOLS de %s: ", buscar_imprimir(nodee, etiq2));
	int pontos2 = recebe_gols_feitos(nod, etiq2);

	recebe_gols_sofridos(nod, etiq2, pontos1);
	recebe_gols_sofridos(no, etiq1, pontos2);

	buscar_selecionar_pontos(no, nod, etiq1, etiq2, pontos1, pontos2);
	system("cls");
}


void sistema_oitavas(lista **no, int etiq1, int etiq2, int etiq3, int etiq4, int oitavas, int limite){

	while(oitavas <= limite){
		if(etiq1 == oitavas){
			selecionar_pontos_e_gols(no, no, etiq1, etiq2);
			selecionar_pontos_e_gols(no, no, etiq1, etiq3);
			selecionar_pontos_e_gols(no, no, etiq1, etiq4);
		}
			
		if(etiq2 == oitavas){
			selecionar_pontos_e_gols(no, no, etiq2, etiq1);
			selecionar_pontos_e_gols(no, no, etiq2, etiq3);
			selecionar_pontos_e_gols(no, no, etiq2, etiq4);
		}

		if(etiq3  == oitavas){
			selecionar_pontos_e_gols(no, no, etiq3, etiq1);
			selecionar_pontos_e_gols(no, no, etiq3, etiq2);
			selecionar_pontos_e_gols(no, no, etiq3, etiq4);
		}

		if(etiq4 == oitavas){
			selecionar_pontos_e_gols(no, no, etiq4, etiq1);
			selecionar_pontos_e_gols(no, no, etiq4, etiq2);
			selecionar_pontos_e_gols(no, no, etiq4, etiq3);
		}
	
		oitavas++;
	}

	calcula_saldo(no);
}


void inicializar_pontos(lista **node){
	lista *aux = *node;

	while(aux != NULL){
		aux->dados.gols_feitos = 0;
		aux->dados.gols_sofridos = 0;
		aux->dados.saldo = 0;
		aux->dados.pontos = 0;
		aux = aux->proximo;
	}
}


void mostra_contagem_oitavas(lista *node){
	lista *aux = node;

	while(aux != NULL){
		printf("\n| %s | (%d)\nGOLS FEITOS: %d\nGOLS SOFRIDOS: %d\nSALDO: %d\nPONTOS: %d\n", aux->dados.nome, aux->dados.etiqueta, aux->dados.gols_feitos, aux->dados.gols_sofridos, aux->dados.saldo, aux->dados.pontos);

		aux = aux->proximo;
	}	
}


void mostra_contagem(lista *node, int etiq){
	lista *aux = node;

	while(aux->dados.etiqueta != etiq){
		aux = aux->proximo;
	}	

	printf("\n| %s | (%d)\nGOLS FEITOS: %d\nGOLS SOFRIDOS: %d\nSALDO: %d\nPONTOS: %d\n", aux->dados.nome, aux->dados.etiqueta, aux->dados.gols_feitos, aux->dados.gols_sofridos, aux->dados.saldo, aux->dados.pontos);
}


void printar(lista *node){
	lista *aux = node;

	while(aux != NULL){
		printf("%s, ", aux->dados.nome);
		aux = aux->proximo;
	}
	printf("\n");
}


int retorna_maior(lista *node){
	lista *aux = node;
	lista *prox;

	prox = aux->proximo;

	if(aux->dados.pontos > prox->dados.pontos){
		return aux->dados.etiqueta;
	}
	
	return prox->dados.etiqueta;

}


int retorna_menor(lista *node){
	lista *aux = node;
	lista *prox;

	prox = aux->proximo;

	if(aux->dados.pontos < prox->dados.pontos){
		return aux->dados.etiqueta;
	}
	
	return prox->dados.etiqueta;

}


void inserir_nome(lista **node, time ally, int etiq){
	int j = 1;

	while(j <= NTIME){
		printf("Nome do %do time: ", j);

		scanf(" %s", ally.nome);

		ally.etiqueta = etiq;

		inserir(node, ally);
		etiq++;
		j++;
	}
}


void sistema_quartas(lista **maior, lista **menor, int etiq_maior, int etiq_menor){
	printf("\n | QUARTAS DE FINAL |\n\n");
	lista *ma = *maior;
	lista *me = *menor;

	selecionar_pontos_e_gols(maior, menor, etiq_maior, etiq_menor);
	
	calcula_saldo(maior);
	calcula_saldo(menor);
	mostra_contagem(ma, etiq_maior);
	mostra_contagem(me, etiq_menor);
	int gols_do_maior = 
	int gols_do_menor = 
	 
	printar(ma);

	if(gols_do_maior > gols_do_menor){
		buscar_tirar(menor, etiq_menor);
	}else{
		buscar_tirar(maior, etiq_maior);
	}
	
}


int main(){
	char r;
	
	do{
		lista *ga = NULL, *gb = NULL, *gc = NULL, *gd = NULL;
		time ta, tb, tc, td;

		int i = 1, etiq = 1;

		//seleção dos grupos
		while(i <= 4){
			
			printf("=======| CAMPEONATO |=======\n");
			printf("INSIRA OS NOMES DOS TIMES:\n");
			switch(i){
				case 1: printf("\n| GRUPO A |\n"); 
					inserir_nome(&ga, ta, etiq); 				
					etiq += 4;
					break;

				case 2: printf("\n| GRUPO B |\n"); 
					inserir_nome(&gb, tb, etiq); 				
					etiq += 4;
					break;

				case 3: printf("\n| GRUPO C |\n"); 
					inserir_nome(&gc, tc, etiq); 				
					etiq += 4;
					break;

				case 4: printf("\n| GRUPO D |\n");
					inserir_nome(&gd, td, etiq); 				
					etiq += 4;
					break;
			};

			
			system("cls");
			i++;
		}

		inicializar_pontos(&ga);
		inicializar_pontos(&gb);
		inicializar_pontos(&gc);
		inicializar_pontos(&gd);

		i = 1;

		//oitavas
		while(i <= 4){

			switch(i){
				case 1: printf("\n| GRUPO A |\n\n"); 
				sistema_oitavas(&ga, 1, 2, 3, 4, 1, 4); 
				mostra_contagem_oitavas(ga); 
				printar(ga); 
				buscar_tirar_menor_ponto(&ga); 
				buscar_tirar_menor_ponto(&ga); 
				printar(ga); 
				break;
				

				case 2: printf("\n| GRUPO B |\n\n"); 
				sistema_oitavas(&gb, 5, 6, 7, 8, 5, 8); 
				mostra_contagem_oitavas(gb); 
				buscar_tirar_menor_ponto(&gb); 
				buscar_tirar_menor_ponto(&gb); 
				printar(gb); 
				break;
				

				case 3: printf("\n| GRUPO C |\n\n"); 
				sistema_oitavas(&gc, 9, 10, 11, 12, 9, 12); 
				mostra_contagem_oitavas(gc); 
				buscar_tirar_menor_ponto(&gc); 
				buscar_tirar_menor_ponto(&gc);
				printar(gc); 
				break;
				
				
				case 4: printf("\n| GRUPO D |\n\n"); 
				sistema_oitavas(&gd, 13, 14, 15, 16, 13, 16); 
				mostra_contagem_oitavas(gd);  
				buscar_tirar_menor_ponto(&gd); 
				buscar_tirar_menor_ponto(&gd); 
				printar(gd); 
				break;
				
				
			};
			
			i++;
		}

		//quartas
		sistema_quartas(&ga, &gb, retorna_maior(ga), retorna_menor(gb));
		sistema_quartas(&gb, &gc, retorna_maior(gb), retorna_menor(gc));
		sistema_quartas(&gc, &gd, retorna_maior(gc), retorna_menor(gd));
		sistema_quartas(&gd, &ga, retorna_maior(gd), retorna_menor(ga));

		printf("\nDeseja criar um novo campeonato?[s/n]\n");
		scanf(" %c", &r);

	}while(r == 's' || r == 'S');
		
	return 0;
}
