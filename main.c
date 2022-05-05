#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){
    Job *jobs = NULL;
    Operation * operacoes = NULL; 


    int opcao;
    int qtOpCiclo;
    int idCountOp=0;
    int idCountJb=0;
    int qt=0;
    int aa[MAXOPERATION]={};
    

    
    do{
        opcao = menu();
        switch(opcao){
            case 1:
                
                //inserir Job
                printf("####Inserir Job####\n");
                idCountJb=quantidadeJobs(jobs);
                printf("Job nº%d\n",idCountJb);


                //condicao se nao houver operacoes nao deixar adicionar job
                if(quantidadeOperacoes(operacoes)==0){
                    printf("Não existe operações insira operações \npara poder inserir um job \n\n");
                    break;
                }
                printf("Quantas operações deseja?\n");
                scanf("%d",&qtOpCiclo);
                for(int i=0; i<qtOpCiclo; i++){
                    listarOperations(operacoes);
                    printf("Qual operação deseja:");
                    scanf("%d",&aa[i]);
                }
                //inserir com tudo 
                jobs=inserirJobs(jobs,idCountJb,aa);
                idCountJb++;
                //operacoes= inserirOperacoes(operacoes,1,bb,cc,3);
                //operacoes= inserirOperacoes(operacoes,2,rr,tt,3);   
                //operacoes= inserirOperacoes(operacoes,3,kk,ii,1);
                printf("Job predefenido inserido com sucesso!\n");
                break;
            case 2:
                printf("Quantidade: %d\n", quantidadeJobs(jobs));
                break;
            case 3:
                system("clear");
                listarJobs(jobs);
                break;
            case 4:{
                int idRemover=0;
                system("clear");
                printf("###### remover operação #####\n\n");
                printf("Qual id da operação:");
                scanf("%d",&idRemover);
                removerOperacoes(operacoes,idRemover);
                break;
            }    
            case 5:{
                int idAlterar=0;
                system("clear");
                printf("###### Alterar Operação #####\n\n");
                printf("###Inserir operações###\n");
                printf("Qual id da operação:");
                scanf("%d",&idAlterar);
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
                alteraOperacao(operacoes,idAlterar,maq,temp,qt);
                break;
            }
            case 6:
                system("clear");
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
                system("clear");
                printf("###### tempo minimo do job ######\n");
                medMinJob(jobs,operacoes);
                break;
            case 9:
                system("clear");
                printf("###### tempo maximo do job ######\n");
                medMaxJob(jobs,operacoes);
                break;
            case 10:
                system("clear");
                // vai ler ao ficheiro
                printf("Puxa os dados do ficheiro\n");
                operacoes = pullFicheiro(operacoes, idCountOp);
                break; 
            case 11:{
                //ve quantas operacoes tem inseridas para ter o id correto
                
                //inserir operacoes e ver a quantidade de maquinas
                system("clear");
                printf("###Inserir operações###\n");
                
                //para ir buscar a quantidade de op
                idCountOp=quantidadeOperacoes(operacoes);
                idCountOp++;

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
                
                operacoes=inserirOperacoes(operacoes,idCountOp,maq,temp,qt);

                break; 
            }  
            default:
                break;
        }
    }while(opcao != 0);

    return 0;
}
