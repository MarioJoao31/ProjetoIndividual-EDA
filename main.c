#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
    Job *jobs = NULL;
    Operation * operacoes = NULL; 


    int opcao;
    int idCount=0;
    int qt=0;
    int aa[MAXOPERATION]={1,2,3};
    int bb[3]={1,2,3};
    int cc[5]={7,4,9};
    int rr[3]={2,6,5};
    int tt[3]={6,5,5};
    int kk[1]={3};
    int ii[1]={5};
    int hh[2]={6,6};

    
    do{
        opcao = menu();
        switch(opcao){
            case 1:
                //inserir Job
                printf("A inserir jobs...\n");
                jobs=inserirJobs(jobs,1,aa);

                operacoes= inserirOperacoes(operacoes,1,bb,cc,3);
                operacoes= inserirOperacoes(operacoes,2,rr,tt,3);   
                operacoes= inserirOperacoes(operacoes,3,kk,ii,1);
                
                break;
            case 2:
                printf("Quantidade: %d\n", quantidadeJobs(jobs));
                break;
            case 3:
                listarJobs(jobs);
                break;
            case 4:
                printf("###### remover operação #####\n\n");
                removerOperacoes(operacoes,2);
                break;
            case 5:
                printf("###### Alterar Operação #####\n\n");
                alteraOperacao(operacoes,3,hh,bb);
                break;
            case 6:
                //insere e depois lista
                //tenho de passar arrays no parametros para maquinas e tempo 
                listarOperations(operacoes);
                break;
            case 7:
                //guardar ainda nao fiz
                //TODO:Ainda não fiz e nao funciona
                //
                break;
            case 8:
                printf("###### tempo minimo do job ######\n");
                medMinJob(jobs,operacoes);
                break;
            case 9:
                printf("###### tempo minimo do job ######\n");
                medMaxJob(jobs,operacoes);
                break;
            case 10:
                // vai ler ao ficheiro
                printf("Puxa os dados do ficheiro\n");
                operacoes = pullFicheiro(operacoes, idCount);
                break; 
            case 11:{
                //ve quantas operacoes tem inseridas para ter o id correto
                idCount=quantidadeOperacoes(operacoes);
                idCount++;
                //inserir operacoes e ver a quantidade de maquinas
                system("clear");
                printf("###Inserir operações###\n");
                printf("Quantas maquinas:");
                scanf("%d",&qt);

                int maq[qt];
                int temp[qt];
                for(int i=0; i<qt; i++){
                    printf("\nMaquina numero:");
                    scanf("%d",&maq[i]);
                    printf("tempo da maquina %d:",i+1);
                    scanf("%d",&temp[i]);
                }
                
                operacoes=inserirOperacoes(operacoes,idCount,maq,temp,qt);

                break; 
            }  
            default:
                break;
        }
    }while(opcao != 0);

    return 0;
}
