#include<stdio.h>
#include<string.h>

#define MAX_AGENT 50
#define TAM_NOME 80
#define TAM_SCRIPT 1000
#define NOTA_MAX 5

//funções de cadastro, salvamento, listagem e permanencia dos dados após o fechar o programa
int cadastrarAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int i);
int salvarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int a);
void listarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int a);
int carregarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents);

//funções de editar e excluir agente
int editarAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int maxnota, int posicao);
int excluirAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int total, int posicao);

//funções de busca
int buscarId(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents);
int buscarNome(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents);

//Menus
void exibirMenu();
void exibirMenuDeBusca();
void exibirMenuEditarOuExcluir();

void limparBuffer();

int main(){
    int ids[MAX_AGENT], notas[MAX_AGENT];
    char nomes[MAX_AGENT][TAM_NOME];
    char scripts[MAX_AGENT][TAM_SCRIPT];
    int acd = 0, opcao;

    //acd = Agentes Cadastrados
    acd = carregarAgentes(ids, nomes, scripts, notas, MAX_AGENT);
    if (acd > 0){
        printf("Arquivos carregados com sucesso\n");
    }
    

    do{
        exibirMenu();
        if (scanf("%d", &opcao) == 0){
            limparBuffer();
            opcao = 0;
        }

        switch(opcao){
    
        case 1:
            if (acd < MAX_AGENT){
                if (cadastrarAgente(ids, nomes, scripts, notas, acd) == 1){
                    acd++;
                    printf("Cadastro de Agente realizado com Sucesso\n");
                }
                else {
                    printf("Falhou, Cadastro não realizado\n");
                }
            }
            else {
                printf("Já possui %d Agentes cadastrados, Limite atingido\n", acd);
            }
            
    
            break;

        case 2:
            printf("Voce escolheu Listar os agentes\n");
            listarAgentes(ids, nomes, scripts, notas, acd);

            break;

        case 3:
            printf("Voce escolheu Buscar agentes cadastrados\n");
            exibirMenuDeBusca();
            if (scanf("%d", &opcao) == 0){
                limparBuffer();
                opcao = 0;
            }

            switch(opcao){
                
                case 1:
                    int posicao = buscarId(ids, nomes, scripts, notas, acd);

                    if (posicao == -1)break;

                    exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcao) == 0){
                        limparBuffer();
                        opcao = 0;
                    }

                    switch(opcao){
                        case 1:
                            editarAgente(ids, nomes, scripts, notas, acd, NOTA_MAX, posicao);
                            break;
                        
                        case 2:
                            if (posicao != 1){
                                acd = excluirAgente(ids, nomes, scripts, notas, acd, posicao);

                                salvarAgentes(ids, nomes, scripts, notas, acd);
                            }
                        break;
                        
                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;
                        
                        default:
                            printf("Opção Invalida...\n");
                    }
                break;
                
                case 2:
                    posicao = buscarNome(ids, nomes, scripts, notas, acd);

                    if (posicao == -1)break;

                    exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcao) ==0){
                        limparBuffer();
                        opcao = 0;
                    }

                    switch(opcao){
                        case 1:
                            editarAgente(ids, nomes, scripts, notas, acd, NOTA_MAX, posicao);
                        break;
                        
                        case 2:
                            if (posicao != 1){
                                acd = excluirAgente(ids, nomes, scripts, notas, acd, posicao);

                                salvarAgentes(ids, nomes, scripts, notas, acd);
                            }
                        break;

                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;
                        
                        default:
                            printf("Opção Invalida...\n");
                    }
                break;

                case 3:
                    posicao ;
                break;
            }
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
    printf("\n====== CATALOGO DE AGENTES =======");
    printf("\n _________________________________\n");
    printf("|1- Cadastrar novo agente         |\n");//concluido
    printf("|2- Listar os agentes cadastrados |\n");//concluido a parte de listagem, falta impletar edição e exclusão
    printf("|3- Buscar agentes já cadastrados |\n");
    printf("|0- Sair                          |\n");
    printf("Escolha uma opção: ");
}

void exibirMenuDeBusca(){
     printf("\n======= BUSCA DE AGENTES =========");
    printf("\n _________________________________\n");
    printf("|1- Buscar por Id                 |\n");
    printf("|2- Buscar por Nome               |\n");
    printf("|3- Buscar por Função             |\n");
    printf("|4- Buscar por Palavra chave      |\n");
    printf("|5- Buscar por Nota               |\n");
    printf("|0- Sair                          |\n");
    printf("Escolha uma opção: ");
}

void exibirMenuEditarOuExcluir(){
    printf("\nO que deseja fazer:\n");
    printf("|1- Editar\n");
    printf("|2- Excluir o agente\n");
    printf("|0- Voltar\n");
    printf("|Escolha uma opção: ");
}

int cadastrarAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int i){
    printf("\nInsira o ID do Agente: ");
    if (scanf("%d", &id[i]) == 0){
        limparBuffer();
        return 0;
    }
    limparBuffer();
    printf("Insira o nome do Agente: ");
    if (fgets(nome[i],TAM_NOME,stdin) == NULL)return 0;
    nome[i][strcspn(nome[i], "\n")] = '\0';

    printf("Insira o script do Agente: ");
    if (fgets(scpt[i],TAM_SCRIPT,stdin) == NULL)return 0;
    scpt[i][strcspn(scpt[i], "\n")] = '\0';

    printf("Insira a nota do Agente: ");
    if (scanf("%d", &nota[i]) == 0){
        limparBuffer();
        return 0;
    }

    if (salvarAgentes(id, nome, scpt, nota, i + 1) == 0){
        printf("Erro em salvar agente.\n");
        return 0;
    }
    limparBuffer();
    return 1;
}

int salvarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int a){
    FILE *arquivo = fopen("AgentesCadastrados.txt", "w");
    if (arquivo == NULL){
        printf("Arquivo de salvaAgentes não foi possivel ser aberto");
        return 0;
    }
    for (int i = 0; i < a; i++){
        fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%s\n", nome[i]);
        fprintf(arquivo, "%s\n", scpt[i]);
        fprintf(arquivo, "%d\n\n", nota[i]);
    }
    fclose(arquivo);
    return 1;
}

void listarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int a){
    printf("\n-----------------LISTA DE AGENTES------------------");
    for (int i = 0; i < a; i++){
        printf("\n============================================================================================\n");
        printf("|Id: %d|\n|Nome: %s|\n|Script: %s|\n|Nota: %d|", id[i], nome[i], scpt[i], nota[i]);
    }
    printf("\n============================================================================================\n");
}

int carregarAgentes(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents){
    FILE *arquivo = fopen("AgentesCadastrados.txt", "r");
    if (arquivo == NULL){
        printf("Arquivo de carregarAgentes não foi possivel ser aberto");
        return 0;
    }
    //ard = Agentes Recuperados do Arquivo
    int ard = 0;

    while(ard < maxagents && fscanf(arquivo, "%d", &id[ard]) == 1){

        int c;
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);

        if (fgets(nome[ard], TAM_NOME, arquivo) == NULL)break;
        nome[ard][strcspn(nome[ard], "\n")] = '\0';

        if (fgets(scpt[ard], TAM_SCRIPT, arquivo) == NULL)break;
        scpt[ard][strcspn(scpt[ard], "\n")] = '\0';

        if (fscanf(arquivo, "%d", &nota[ard]) != 1)break;
        ard++;
    }
    return ard;
}

int editarAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int maxnota, int posicao){
    int opcao;

    printf("\n====== O QUE DESEJA EDITAR =======");
    printf("\n _________________________________\n");
    printf("|1- Nome                          |\n");
    printf("|2- Script                        |\n");
    printf("|3- Nota                          |\n");
    printf("|4- Todas as informações          |\n");
    printf("|0- Cancelar                      |\n");
    printf("Escolha uma opção: ");

    if (scanf("%d", &opcao) != 1){
        limparBuffer();
        printf("Erro ao armazenar a opção escolhida...");
        return 0;
    }
    limparBuffer();

    switch(opcao){

    case 1:
        printf("Insira o novo nome do Agente: ");

        if (fgets(nome[posicao], TAM_NOME, stdin) == NULL)return 0;
        nome[posicao][strcspn(nome[posicao], "\n")] = '\0';

        break;
    
    case 2:
        printf("Insira o novo script do Agente: ");
        if (fgets(scpt[posicao], TAM_SCRIPT, stdin) == NULL)return 0;
        scpt[posicao][strcspn(scpt[posicao], "\n")] = '\0';

        break;

    case 3:
        printf("\nInsira a nova nota do Agente: ");
        if (scanf("%d", &nota[posicao]) != 1 || nota[posicao] < 0 || nota[posicao] > maxnota){
            limparBuffer();
            printf("Nota Invalida...\n");
            return 0;
        }
        limparBuffer();
        break;

    case 4:
        printf("\nInsira o novo nome do Agente: ");
        if (fgets(nome[posicao], TAM_NOME, stdin) == NULL)return 0;
        nome[posicao][strcspn(nome[posicao], "\n")] = '\0';

        printf("\nInsira o novo script do Agente: ");
        if (fgets(scpt[posicao], TAM_SCRIPT, stdin) == NULL)return 0;
        scpt[posicao][strcspn(scpt[posicao], "\n")] = '\0';

        printf("\nInsira a nova nota do Agente: ");
        if (scanf("%d", &nota[posicao]) != 1 || nota[posicao] < 0 || nota[posicao] > maxnota){
            limparBuffer();
            printf("Nota Invalida...\n");
            return 0;
        }
        limparBuffer();
        break;

    case 0:
        printf("Edição cancelada, Saindo...\n");
        return 0;
    
    default:
        printf("Opção Invalida...\n");
    }

    if (salvarAgentes(id, nome, scpt, nota, maxagents) == 0){
        printf("Erro ao salvar as alterações.\n");
        return 0;
    }

    printf("\n! Agente atualizado com sucesso !\n");

    return 1;

}

int buscarId(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents){
    int idBusca;
    int posicao = -1;

    printf("\nInsira o ID do agente que deseja editar: ");
    if (scanf("%d", &idBusca) != 1){
        limparBuffer();
        printf("ID solicitado invalido\n");
        return -1;
    }
    limparBuffer();

    for (int i = 0; i < maxagents; i++){
        if (id[i] == idBusca){
            posicao = i;
            break;
        }
    }

    if (posicao == -1){
        printf("Agente não encontrado...\n");
        return -1;
    }

    printf("\n======= AGENTE ENCONTRADO ========\n");
    printf("Id: %d\n", id[posicao]);
    printf("Nome: %s\n", nome[posicao]);
    printf("Script: %s\n", scpt[posicao]);
    printf("Nota: %d\n", nota[posicao]);

    return posicao;
}

int buscarNome(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int maxagents){
    char nomeBusca[TAM_NOME];
    int posicao = -1;

    limparBuffer();

    printf("\nInsira o Nome do agente que deseja buscar: ");
    if (fgets(nomeBusca, TAM_NOME, stdin) == NULL )return -1;

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < maxagents; i++){
        if (strcmp(nome[i], nomeBusca) == 0){
            posicao = i;
        }
    }

    if (posicao == -1){
        printf("Agente não encontrado...\n");
        return -1;
    }

    printf("\n======= AGENTE ENCONTRADO ========\n");
    printf("Id: %d\n", id[posicao]);
    printf("Nome: %s\n", nome[posicao]);
    printf("Script: %s\n", scpt[posicao]);
    printf("Nota: %d\n", nota[posicao]);

    return posicao;
}

int excluirAgente(int id[], char nome[][TAM_NOME], char scpt[][TAM_SCRIPT], int nota[], int total, int posicao){
    for (int i = posicao; i < total - 1; i++){
        id[i] = id[i + 1];
        strcpy(nome[i], nome[i +1]);
        strcpy(scpt[i], scpt[i + 1]);
        nota[i] = nota[i + 1];
    }

    total--;

    printf("! Agente excluido com sucesso !\n");

    return total;
}