#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "header.h"

//ligar ao header para tudo que eu fazer aqui 
//fica aqui ligado ao main 
int quantidadeJobs(Job * jp) {
  int soma = 0;
  while (jp != NULL) {
    jp = jp -> seguinte;
    soma++;
  }
  return (soma);
}

int quantidadeOperacoes(Operation * op) {
  int soma = 0;
  while (op != NULL) {
    op = op -> seguinte;
    soma++;
  }
  return (soma);
}

//INSERIR

Job* inserirJobs(Job * jp, int id, int* operacao, int size){

  Job *jb = (Job*) malloc(sizeof(Job));

  if (jb!=NULL)
  {
    jb->id = id;
    //copiar array 
    int sizearrayoperacao=sizeof(operacao);
    for(int h=0;h<sizearrayoperacao;h++){
      jb->operacao[h] = operacao[h] ;
    }
    jb->sizeOP = size;
    jb->seguinte = jp;
    return(jb);
  }
  else return(jp);
}

//BUG: chekar se esta a funcionar se eliminar o primeiro
Job *removerJobs(Job *jp, Operation *op, int id){
  //se a lista ficar vazia 
  //remove so o job 
  if( jp == NULL) return NULL;

  if(jp->id == id){
    Job* aux = jp;
    jp=jp->seguinte;
    free(aux);
  }else{
    Job *aux=jp;
    Job *auxAnt = aux;
    while(aux && aux->id != id){
      auxAnt=aux;
      aux = aux->seguinte;
    }
    if(aux != NULL){
      auxAnt->seguinte= aux->seguinte;
      free(aux);
    }
  }
  
  //retorna a lista job 
  return jp;
}

//operação 
Operation* inserirOperacoes(Operation * op, int id, int* maq, int* temp, int size){
  Operation *ot = (Operation*) malloc(sizeof(Operation));
  ot->id=id;
  
  // passa de um arrey para o outro /maquina/
  for(int i=0; i<size;i++){
    if(maq[i]!=0){
      ot->maquina[i]=maq[i]; 
    } 
  }

  // passa de um arrey para o outro /tempo/
  for(int j=0; j<size;j++){
    if(temp[j]!=0){
      ot->tempo[j]=temp[j];

    } 
  }

  ot->sizeMT=size;
  ot->seguinte=NULL;
  if(op == NULL){
    op= ot;
  }else{
    Operation* lastnode = op;
    while(lastnode->seguinte != NULL){
      lastnode = lastnode->seguinte;
    }
    lastnode->seguinte = ot;
  }
  return op;
}



//BUG:erro se remover o primeiro 
Operation* removerOperacoes(Operation *op, int id){
  printf(" IDDDD :%d",id);
  if(id == 1 ){
    //cria uma variavel temporiaria 
    //aponta o inicio da lista para o apontador seguinte 
    Operation* aux = op;
    aux = op->seguinte;
    
    return aux;
  }
  if( op == NULL) return NULL;

  //remover primeiro posição
  

  if(op->id == id){
    Operation* aux = op;
    op=op->seguinte;
    free(aux);
  }
  else{
    Operation *aux=op;
    Operation *auxAnt = aux;
    while(aux && aux->id != id){
      auxAnt=aux;
      aux = aux->seguinte;
    }
    if(aux != NULL){
      auxAnt->seguinte= aux->seguinte;
      free(aux);
    }

  }
  return op;
}

Operation* procuraOperacoes(Operation* op, int id){
  if(op==NULL) return NULL;
  else{
    Operation* aux = op;
    while(aux != NULL){
      if(aux->id == id){
        return aux;
      }
      aux= aux->seguinte;
    }
    return NULL;
  }
}



Operation* alteraOperacao(Operation* op, int id,int* maq,int* temp,int size){
  Operation* aux = procuraOperacoes(op, id);
  if(aux != NULL){
    aux->sizeMT=size;
    // insere as maquinas de novo
    // passa de um arrey para o outro /maquina/
    for(int i=0; i<size;i++){
    aux->maquina[i]=maq[i];
    }

    // passa de um arrey para o outro /maquina/
    for(int j=0; j<size;j++){
    aux->tempo[j]=temp[j];
    }

  }
  return op;
}



//LISTAR

void listarJobs(Job *jp){
  while (jp!=NULL)
 {
    printf("Job nº%d\n",jp->id );
    for(int j=0; j<7;j++){
      if(jp->operacao[j]==0) break;
      printf(" Lista de operações:%d\n", jp->operacao[j]);
      
    }
    jp = jp->seguinte;
 }
}


void listarOperations(Operation *op){
  while (op!=NULL)
 {
    printf("Operação nº%d\n",op->id );

    //lista as maquinas que se pode usar 
    printf(" Lista   de  Maquinas:(");
    for(int j=0; j<op->sizeMT;j++){  
      if(j+2 > op->sizeMT){
        printf("%d", op->maquina[j]);
        break;
      }else
          printf("%d,", op->maquina[j]); 
    }
    printf(")\n");



    //lista o tempo que cada maquina demora

    printf("Tempo de cada Maquina:[");
    for(int j=0; j<op->sizeMT;j++){  
      if(op->tempo[j+1]==0){
        printf("%d", op->tempo[j]);
        break;
      }else
        printf("%d,", op->tempo[j]); 
    }
    printf("]\n");
    printf("Size:%d\n",op->sizeMT);

    op = op->seguinte;
 }
}



//BUG: tenho de deixar um linha em branco no final do ficheiro
//ARMAZENAMENTO
void saveFicheiro(Job *jp, Operation *op){
  FILE *f_SAVE= fopen("table.html","a");
  if(! f_SAVE) printf("O Ficheiro não abriu corretamente!");
  //TODO: acabar de fazer o guardar com o fputs
  char data[10]="olaaa";
  fputs(data, f_SAVE);

  //fecha o ficheiro
  fclose(f_SAVE);

}

Operation* pullFicheiro(Operation *op, int idCont) {
	Operation *opP;
	FILE *f_JOB = fopen("data.txt","r");
	char symb ;
  unsigned char symbI;
	int i = 0, cont = 0, success = 0, arrayM[100], arrayT[100];
  

    if(f_JOB != NULL) {
		do {
			if((symb = getc(f_JOB)) != EOF) {
				i = cont = 0;
        Operation *ot=(Operation *)malloc(sizeof(Operation));

				//primeira linha le as maquinas
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayM[i] = symbI - '0';
						cont++;
						i++;
					}
				}

				i=0;

        //segunda linha le os tempos
        //BUG: tem de ter uma linha sem nada no ficheiro pq senao o ficheiro nao funciona
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayT[i] = symbI - '0';
						i++;
					}
				}
        idCont = quantidadeOperacoes(op);
        
				idCont++;
				ot->id = idCont;
        ot->sizeMT = cont;
        for(i=0; i < cont; i++) {
					ot->maquina[i] = arrayM[i];
					ot->tempo[i] = arrayT[i];
				}
				ot->seguinte = NULL;
        
				if(op == NULL){
          op= ot;
        }else{
          Operation* lastnode = op;
          while(lastnode->seguinte != NULL){
            lastnode = lastnode->seguinte;
          }
          lastnode->seguinte = ot;
        }
        
        success = 0;
        
        listarOperations(ot);
			}
			else{
				success = 1;
        
			}
		}while(success == 0);
	}
    
    return (op);
    fclose(f_JOB);
}



//MENU
int menu(){
    int opcao;

    do{
        printf("-------------------------------MENU--------------------------------\n");
        printf("1 - Inserir job com operações      \t11 - Inserir so operações\n");
        printf("2 - Quantidade de jobs             \t12 - Eliminar job\n");
        printf("3 - Listar jobs                    \t13 - Inserir operação num job\n");
        printf("4 - Remover operação\n");
        printf("5 - Alterar operação\n");
        printf("6 - Listar operações\n");
        printf("7 - Guardar no ficheiro\n");
        printf("8 - Media minima por job\n");
        printf("9 - Media maxima por job\n");
        printf("10 - Pull dados do ficheiro\n");
        printf("0 - Sair\n");
        printf("Opcao:");
        scanf("%d",&opcao); 
    }
    while ((opcao>20)||(opcao<0));
    return(opcao);
}

//CALCULOS
void medMinJob(Job *jp,Operation *op){
  int min;
  int incre=0;
  while (jp!=NULL){

    printf("Job nº%d tempo minino:\n",jp->id );
    for(int j=0; j<8;j++){
      if(jp->operacao[j]==0) break;
      printf("Operação nº:%d\n",jp->operacao[j]);

     //inserir aqui a funcao de retornar a operacao min 
      min = minOperacao(op,jp->operacao[j]);
      incre += min;
    }
    printf("O minimo de tempo é de %d minutos\n",incre+1);
    jp = jp->seguinte;
 }
}

void medMaxJob(Job *jp,Operation *op){
  int max;
  int incre=0;
  while (jp!=NULL){

    printf("Job nº%d tempo maximo:\n",jp->id );
    for(int j=0; j<8;j++){
      if(jp->operacao[j]==0) break;
      printf("Operação nº:%d\n",jp->operacao[j]);

       //inserir aqui a funcao de retornar a operacao max 
      max = maxOperacao(op,jp->operacao[j]);
      incre += max;
    }
    printf("O maximo de tempo é de %d minutos\n",incre-1);
    jp = jp->seguinte;
 }
}

int minOperacao(Operation *op, int id){
  Operation* aux = procuraOperacoes(op, id);
  int min=100;
  int temp=0;
  //verifica se é null
  if(aux!=NULL){
    //le todos os tempos e guarda o maximo
    for(int i=0;i<op->sizeMT;i++){
      if(aux->tempo[i] < min){
        min=aux->maquina[i];
        temp=aux->tempo[i];
      }

    }
  } 

  printf("Maquina nº%d é a mais rapida\n",min+1);
  return (temp);  
}
 

int maxOperacao(Operation *op, int id){
  Operation* aux = procuraOperacoes(op, id);
  int max=0;
  int temp=0;
  
  //ler todos os tempos 

  if(aux!=NULL){
    for(int i=0;i<op->sizeMT;i++){
      if(aux->tempo[i] > max){
        max=aux->maquina[i];
        temp=aux->tempo[i];
      }

    }
  } 

  printf("Maquina nº%d é a mais lenta\n",max+1);
  return (temp);  
} 



int procuraOperacoesInt(Operation *op, int id){
  if(op==NULL) return 0;
  else{
    Operation* aux = op;
    while(aux != NULL){
      if(aux->id == id){
        return 1;
      }
      aux= aux->seguinte;
    }
    return 0;
  }
}

Job* procuraJob(Job* jp, int id){
  if(jp==NULL) return NULL;
  else{
    Job* aux = jp;
    while(aux != NULL){
      if(aux->id == id){
        return aux;
      }
      aux= aux->seguinte;
    }
    return NULL;
  }
}


//inserir operação em job 
Job *insOpJp(Job * jp,int idOp,int idJp ){
  Job *aux = procuraJob(jp, idJp);

  //incrementa o tamanho 
  aux->sizeOP++;
  aux->operacao[jp->sizeOP-1]=idOp;

  return jp;
}


Job *rmOpJp(Job * jp,int idOp,int idJp ){
  Job *aux = procuraJob(jp, idJp);

  for(int i=0;i<jp->sizeOP;i++){
    if(idOp==aux->operacao[i]){
      //TODO: ACABAR ESTA MERDA 
      for(int f=i-1;f<jp->sizeOP-1;f++){
        aux->operacao[i]=aux->operacao[i+1];
      }
    }
  }
  aux->sizeOP -=1;

  return jp;
}
