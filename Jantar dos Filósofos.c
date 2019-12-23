/*Trabalho ultima avaliação Programação paralela.
Engenharia da computação 2015
Discentes: Anselmo Mendes e Ellen Cris
Marabá 28 de abril de 2017
Problema: Jantar dos Filósofos*/

/*bibliotecas necessarias*/
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include "fila.h"
#define NFILOSOFOS 5

/*prototipos da função


/*Criar buffer*/
Fila hashi_direita;
Fila hashi_esquerda;

/*mutex*/
pthread_mutex_t a_trava_esquerda = PTHREAD_MUTEX_INITIALIZER;		// trava mutex
pthread_mutex_t a_trava_direita = PTHREAD_MUTEX_INITIALIZER;

/*threads*/
pthread_t filosofo[NFILOSOFOS];							//threads que representam os filosofos
pthread_t come;

/*variavel global*/
int estado[NFILOSOFOS] = {0,0,0,0,0};

/*função responsavel por pegar um hashi da fila da esquerda*/
int primeiro_hashi(void *filosofo){		
	long long x = (long long)filosofo;
	printf("O Filosofo %d Tentou pegar o hashi da Esquerda\n",x);
	if (!vaziaf(hashi_esquerda)){
			desenfileira(hashi_esquerda);
			printf("O Filosofo %d Pegou o hashi da Esquerda\n",x);
		return 1;
		}else{
			printf("O Filosofo %d Nao conseguiu pegar o hashi da Esquerda\n",x);
		return 0;
	}
}
/*função responsavel por pegar um hashi da fila da esquerda*/
int segundo_hashi(void *filosofo){
	long long x = (long long)filosofo;
	printf("O filosofo %d Tentou Pegar o hashi da Direita\n",x);
	if (!vaziaf(hashi_direita)){
			desenfileira(hashi_direita);
			printf("O filosofo %d Pegou o hashi da Direita\n",x);
		return 1;
		}else{
			printf("O Filosofo %d Nao conseguiu pegar o hashi da Direita\n",x);
		return 0;
	}
}

/*função responsavel por execultar a verificão dos hashis e registrar a variavel para representar
a coleta dos hashis*/
void ciclo_filosofo(void *filosofo){
	long long x = (long long)filosofo;
	pthread_mutex_lock(&a_trava_esquerda);			/*inicia a zona critica*/
		if(primeiro_hashi(filosofo)){	
			pthread_mutex_lock(&a_trava_direita);	/*inicia a zona critica*/
			if(segundo_hashi(filosofo)){
				estado[x] = 1;						//registra que o filosofo esta a comer,											//esse registro devera ser lido pela thread devolver
	}else{
		enfileira(x,hashi_esquerda);				// se ele nao consegue pegar o segundo hashi deve devolver o primeiro
	}}    			 
	else{
		enfileira(x,hashi_direita);					// se ele nao consegue pegar o segundo hashi deve devolver o segundo
	}
	pthread_mutex_unlock(&a_trava_esquerda);		/*encerra as região criticas*/
	pthread_mutex_unlock(&a_trava_direita);
}
/*função pensar*/
void pensar(void *filosofo){
	long long x = (long long)filosofo;
	srand(time(NULL));
	sleep(rand()%2+10);
	printf("O Filosofo %d Ja parou de Pensar\nO Filosofo %d esta Faminto\n",x,x);
}
/*essa função deve ficar eternaente verificando a presença dos estados das thread, caso encontre
o registro que indique a ação comendo deve esperar um tempo, depois empilhar na fila*/
void *comer(void *filosofo){
	long long x = (long long)filosofo;
	int i;
	while(1){
		for(i=0 ;i < NFILOSOFOS; i++){
		if(estado[i]==1){
		printf("O Filosofo %d Esta Comendo\n",i);
		srand(time(NULL));
		sleep(rand()%2+10);
		printf("O filosofo %d Terminou de Comer\nO Filosofo %d esta Pensando\n",i,i);
		pthread_mutex_lock(&a_trava_esquerda);							/*inicia região critica*/
		pthread_mutex_lock(&a_trava_direita);
		enfileira(x,hashi_esquerda);							/*enfileira, indicando a deovolução dos hashis*/
		enfileira(x,hashi_direita);
		estado[i] = 0;
		pthread_mutex_unlock(&a_trava_esquerda);						/*finaliza  aregião critica*/
		pthread_mutex_unlock(&a_trava_direita);
			}		
		}
	}
}
/*função responsavel por manter um loop dos filosofos pensando, faminto e comendo.*/
void *vida_do_filosofo(void *filosofo){
	
	while(1){
		pensar(filosofo);		//essa função é responsavel por indicar o estado do filosofo (pensando e faminto)
		ciclo_filosofo(filosofo);// função responsavel por verificar os hashis
	}
}
main(){
		
	long long i;
	printf("Jantar dos Filosofos\n\n");
		/*cria e inicializa os hashis*/
	hashi_direita = fila(3);		//cria a fila
	hashi_esquerda = fila(2);
	enfileira(1,hashi_direita);		/*cria os hashis*/
	enfileira(1,hashi_direita);
	enfileira(1,hashi_direita);
	enfileira(1,hashi_esquerda);
	enfileira(1,hashi_esquerda);
		/*criar as threads passando como argumento o numero do filosofo*/
	for(i=0 ; i<NFILOSOFOS ; i++){
		pthread_create(&filosofo[i],NULL,vida_do_filosofo,(void*)i);
	}
		pthread_create(&come,NULL,comer,(void*)i);
		/*função para fazer a função main aguarfar as threads */
	for(i=0 ; i<NFILOSOFOS ; i++){
		pthread_join(filosofo[i],NULL);
		}
}
