#include<stdio.h>
#include<string.h>

#define MAX_AGENT 50
#define TAM_NOME 80
#define TAM_SCRIPT 1000
#define VALOR_NOTA 5

int cadastrarAgente(int id[], int nota[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int i);

void exibirMenu();

void limparBuffer();

int main(){
    int ids[MAX_AGENT], notas[MAX_AGENT];
    char nomes[MAX_AGENT][TAM_NOME];
    char scripts[MAX_AGENT][TAM_SCRIPT];
    int acd = 0, opcao;


    do{
        exibirMenu();
        if(scanf("%d", &opcao) == 0){
            limparBuffer();
            opcao = 0;
        }

        switch(opcao){
    
        case 1:
            // if (acd < MAX_AGENT){
            //     if (cadastrarAgente(ids, nomes, scripts, notas, acd) == 1){
            //         acd++;
            //         printf("Cadastro de Agente realizado com Sucesso\n");
            //     }
            //     else {
            //         printf("Falhou, Cadastro não realizado\n");
            //     }
            // }
            // else {
            //     printf("Já possui %d Agentes cadastrados, Limite atingido\n", acd);
            // }
            
    
            break;

        case 2:
            printf("Voce escolheu Listar os agentes\n");

            break;

        case 3:
            printf("Voce escolheu Buscar agentes cadastrados\n");

            break;

        case 0:
            printf("Voce escolheu Sair\n");

            break;
    
        default:
            printf("Opção Invalida...\n");
    }
        

    }while(opcao != 0);

    

}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu(){
    printf("\n===== CATALOGO DE AGENTES =====\n");
    printf("1- Cadastrar novo agente\n");
    printf("2- Listar os agentes cadastrados\n");
    printf("3- Buscar agentes já cadastrados\n");
    printf("0- Sair\n");
    printf("Escolha uma opção: ");
}

// int cadastrarAgente(int id[], int nota[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int i){
//     printf("\nInsira o ID do Agente: ");
//     if (scanf("%d", &id[i]) == 0){
//         limparBuffer();
//         return 0;
//     }
//     limparBuffer();
//     printf("Insira o nome do Agente: ");
//     if (fgets(nome[i],TAM_NOME,stdin) == NULL)return 0;
//     nome[i][strcspn(nome[i], "\n")] = '\0';

//     printf("Insira o script do Agente: ");
//     if (fgets(scpt[i],TAM_SCRIPT,stdin) == NULL)return 0;
//     scpt[i][strcspn(scpt[i], "\n")] = '\0';

//     printf("Insira a nota do Agente: ");
//     if (scanf("%d", &nota[i]) == 0){
//         limparBuffer();
//         return 0;
//     }
//     limparBuffer();
//     return 1;

    

// }