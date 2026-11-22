#include<stdio.h>
#include<string.h>

#define ADMIN_USER "admin"
#define ADMIN_SENHA "admin123"

#define MAX_AGENT 50
#define MAX_USERS 50
#define TAM_NOME 80
#define TAM_NOME_USER 80
#define TAM_FUNCIONALIDADE 1000
#define TAM_PALAVRA_CHAVE 80
#define TAM_SCRIPT 1000
#define NOTA_MAX 5
#define TAM_SENHA 80

//funções de cadastro, salvamento, listagem e permanencia dos dados após o fechar o programa - Agentes
int cadastrarAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int i, int *proximoId, char criador[][TAM_NOME_USER], char usuarioLogado[], char ultimaModificacao[][TAM_NOME_USER]);
int salvarAgentes(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int agentesCadastrados, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
void listarAgentes(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int agentesCadastrados, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
int carregarAgentes(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);

//funções de cadastro, salvamento e permanencia de dados - Usuarios
int cadastrarUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int i, int *proximoIdUser);
int salvarUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int usuariosCadastrados);
int carregarUsuarios(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int maxusers);
int loginUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int usuariosCadastrados, char usuarioLogado[], char senhaLogado[]);

//funções de editar e excluir agente
int editarAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int maxnota, int posicao, char criador[][TAM_NOME_USER], char usuarioLogado[], char ultimaModificacao[][TAM_NOME_USER]);
int excluirAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int posicao, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);

//funções de busca
int buscarId(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
int buscarNome(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
int buscarFuncao(int id[], char nome [][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
int buscarPalavraChave(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);
int buscarNota(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]);

//Menus
void exibirMenu();
void exibirMenuDeBusca();
void exibirMenuEditarOuExcluir();
void exibirMenuCadastro();

//Limpar o Buffer de Entrada
void limparBuffer();

int main(){
    //Agentes
    int ids[MAX_AGENT], notas[MAX_AGENT];
    char nomes[MAX_AGENT][TAM_NOME];
    char funcionalidades[MAX_AGENT][TAM_FUNCIONALIDADE];
    char scripts[MAX_AGENT][TAM_SCRIPT];
    char criadores[MAX_AGENT][TAM_NOME_USER];
    //Usuarios
    int idsUsuarios[MAX_USERS];
    char usuarios[MAX_USERS][TAM_NOME_USER];
    char senhas[MAX_USERS][TAM_SENHA];
    char usuarioLogado[TAM_NOME_USER];
    char senhaLogado[TAM_SENHA];
    char ultimaModificacao[MAX_USERS][TAM_NOME_USER];
    //Gestão
    int acd = 0, ucd = 0, opcao, opcaoCadastro;
    int proximoId = 1, proximoIdUsuario = 1;

    //acd = Agentes Cadastrados
    acd = carregarAgentes(ids, nomes, funcionalidades, scripts, notas, MAX_AGENT, criadores, ultimaModificacao);
    if (acd > 0){
        printf("Arquivos carregados com sucesso\n");
    }
    for (int i = 0; i < acd; i++){
        if (ids[i] >= proximoId){
            proximoId = ids[i] + 1;
        }
    }
    
    ucd = carregarUsuarios(idsUsuarios, usuarios, senhas, MAX_USERS);
    if (ucd > 0){
        printf("Arquivos Usuarios carregados com sucesso\n");
    }
    for (int i = 0; i < ucd; i++){
        if (idsUsuarios[i] >= proximoIdUsuario){
            proximoIdUsuario = idsUsuarios[i] + 1;
        }
    }

    do{
        exibirMenuCadastro();
        if (scanf("%d", &opcaoCadastro) != 1){
            limparBuffer();
            opcaoCadastro = -1;
        }

        switch(opcaoCadastro){
        
        case 1:
            if (ucd < MAX_USERS){
                if (cadastrarUsuario(idsUsuarios, usuarios, senhas, ucd, &proximoIdUsuario) == 1){
                    ucd++;
                    printf("Cadastro de Usuario realizado com Sucesso\n");
                }
                else{
                    printf("Cadastro não realizado\n");
                }
            }
            else{
                printf("Já possui %d Usuarios cadastrados, Limite atingido\n", ucd);
            }

            break;
            
        case 2:
            printf("Voce escolheu fazer login\n");
            if (loginUsuario(idsUsuarios, usuarios, senhas, ucd, usuarioLogado, senhaLogado)){
                printf("Acesso autorizado!\n");

        do{
        exibirMenu();
        if (scanf("%d", &opcao) != 1){
            limparBuffer();
            opcao = -1;
        }

        switch(opcao){
    
        case 1:
            if (acd < MAX_AGENT){
                if (cadastrarAgente(ids, nomes, funcionalidades, scripts, notas, acd, &proximoId, criadores, usuarioLogado, ultimaModificacao) == 1){
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
            listarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

            break;

        case 3:
            int opcaoBusca;
            printf("Voce escolheu Buscar agentes cadastrados\n");
            do{
                exibirMenuDeBusca();
            if (scanf("%d", &opcaoBusca) != 1){
                limparBuffer();
                opcaoBusca = -1;
            }

            switch(opcaoBusca){
                
                case 1:
                    int opcaoEditar;
                    int posicao = buscarId(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    if (posicao == -1)break;
                    
                    do{
                        exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcaoEditar) != 1){
                        limparBuffer();
                        opcaoEditar = -1;
                    }

                    switch(opcaoEditar){
                        case 1:
                            editarAgente(ids, nomes, funcionalidades, scripts, notas, acd, NOTA_MAX, posicao, criadores, usuarioLogado, ultimaModificacao);
                            break;
                        
                        case 2:
                            if (strcmp(usuarioLogado, ADMIN_USER) == 0 && strcmp(senhaLogado, ADMIN_SENHA) == 0){
                                if (posicao >= 0 && posicao < acd){
                                    acd = excluirAgente(ids, nomes, funcionalidades, scripts, notas, acd, posicao, criadores, ultimaModificacao);

                                    salvarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                                    opcaoEditar = 0;
                                }
                            }
                            else{
                                printf("Acesso Negado, somente o administrador pode excluir Agentes\n");
                            }
                        break;
                        
                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;
                        
                        default:
                            printf("Opção Invalida...\n");
                    }
                    }while(opcaoEditar != 0);
                break;
                
                case 2:
                    int opcaoNome;
                    posicao = buscarNome(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    if (posicao == -1)break;

                    do{
                        exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcaoNome) != 1){
                        limparBuffer();
                        opcaoNome = -1;
                    }

                    switch(opcaoNome){
                        case 1:
                            editarAgente(ids, nomes, funcionalidades, scripts, notas, acd, NOTA_MAX, posicao, criadores, usuarioLogado, ultimaModificacao);
                        break;
                        
                        case 2:
                            if (strcmp(usuarioLogado, ADMIN_USER) == 0 && strcmp(senhaLogado, ADMIN_SENHA) == 0){
                                if (posicao >= 0 && posicao < acd){
                                    acd = excluirAgente(ids, nomes, funcionalidades, scripts, notas, acd, posicao, criadores, ultimaModificacao);

                                    salvarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                                    opcaoNome = 0;
                                }
                            }
                            else{
                                printf("Acesso Negado, somente o administrador pode excluir Agentes\n");
                            }
                        break;

                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;
                        
                        default:
                            printf("Opção Invalida...\n");
                    }
                    }while(opcaoNome != 0);
                break;

                case 3:
                    int opcaoFuncao;
                    posicao = buscarFuncao(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    if (posicao == -1)break;

                    do{
                        exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcaoFuncao) != 1){
                        limparBuffer();
                        opcaoFuncao = -1;
                    }

                    switch(opcaoFuncao){
                        case 1:
                            editarAgente(ids, nomes, funcionalidades, scripts, notas, acd, NOTA_MAX, posicao, criadores, usuarioLogado, ultimaModificacao);
                        break;
                        
                        case 2:
                            if (strcmp(usuarioLogado, ADMIN_USER) == 0 && strcmp(senhaLogado, ADMIN_SENHA) == 0){
                                if (posicao >= 0 && posicao < acd){
                                    acd = excluirAgente(ids, nomes, funcionalidades, scripts, notas, acd, posicao, criadores, ultimaModificacao);

                                    salvarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                                    opcaoFuncao = 0;
                                }
                            }
                            else{
                                printf("Acesso Negado, somente o administrador pode excluir Agentes\n");
                            }

                        break;

                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;
                        
                        default:
                            printf("Opção Invalida...\n");
                    }
                    }while(opcaoFuncao != 0);

                break;

                case 4:
                    int opcaoPalavraChave;
                    posicao = buscarPalavraChave(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    if (posicao == -1)break;

                    buscarId(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    do{
                        exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcaoPalavraChave) != 1){
                        limparBuffer();
                        opcaoPalavraChave = -1;
                    }

                    switch(opcaoPalavraChave){
                        case 1:
                            editarAgente(ids, nomes, funcionalidades, scripts, notas, acd, NOTA_MAX, posicao, criadores, usuarioLogado, ultimaModificacao);
                        break;

                        case 2:
                            if (strcmp(usuarioLogado, ADMIN_USER) == 0 && strcmp(senhaLogado, ADMIN_SENHA) == 0){
                                if (posicao >= 0 && posicao < acd){
                                    acd = excluirAgente(ids, nomes, funcionalidades, scripts, notas, acd, posicao, criadores, ultimaModificacao);

                                    salvarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                                    opcaoPalavraChave = 0;
                                }
                            }
                            else{
                                printf("Acesso Negado, somente o administrador pode excluir Agentes\n");
                            }
                        break;

                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;

                        default:
                            printf("Opção Invalida...\n");
                    }
                    }while(opcaoPalavraChave != 0);

                    
                break;

                case 5:
                    int opcaoNota;
                    posicao = buscarNota(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    if (posicao == -1)break;

                    buscarId(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                    do{
                        exibirMenuEditarOuExcluir();
                    if (scanf("%d", &opcaoNota) != 1){
                        limparBuffer();
                        opcaoNota = -1;
                    }

                    switch(opcaoNota){
                        case 1:
                            editarAgente(ids, nomes, funcionalidades, scripts, notas, acd, NOTA_MAX, posicao, criadores, usuarioLogado, ultimaModificacao);
                        break;

                        case 2:
                            if (strcmp(usuarioLogado, ADMIN_USER) == 0 && strcmp(senhaLogado, ADMIN_SENHA) == 0){
                                if (posicao >= 0 && posicao < acd){
                                    acd = excluirAgente(ids, nomes, funcionalidades, scripts, notas, acd, posicao, criadores, ultimaModificacao);

                                    salvarAgentes(ids, nomes, funcionalidades, scripts, notas, acd, criadores, ultimaModificacao);

                                    opcaoNota = 0;
                                }
                            }
                            else{
                                printf("Acesso Negado, somente o administrador pode excluir Agentes\n");
                            }
                        break;

                        case 0:
                            printf("Voce escolheu voltar\n");
                        break;

                        default:
                            printf("Opção Invalida...\n");
                    }
                    }while(opcaoNota != 0);

                break;

                case 0:
                    printf("Voltando...\n");
                break;

                default:
                    printf("Opção Invalida\n");

            }
            }while(opcaoBusca != 0);
            break;

        case 0:
            printf("Encerrando o programa...\n");

        break;
    
        default:
            printf("Opção Invalida...\n");
    }
        

        }while(opcao != 0);

            }
            break;
        
        case 0:
            printf("Saindo...\n");
            opcaoCadastro = 0;
            opcao = 0;
            break;

        default:
            printf("Opção Invalida\n");
                
        }

        
    }while(opcaoCadastro != 0);


    

}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenuCadastro(){
    printf("\n====== CATALOGO DE AGENTES =======");
    printf("\n _________________________________\n");
    printf("|1- Cadastrar uma nova conta      |\n");
    printf("|2- Fazer login                   |\n");
    printf("|0- Sair                          |\n");
    printf("Escolha uma opção: ");
}

void exibirMenu(){
    printf("\n====== CATALOGO DE AGENTES =======");
    printf("\n _________________________________\n");
    printf("|1- Cadastrar novo agente         |\n");//concluido
    printf("|2- Listar os agentes cadastrados |\n");//concluido
    printf("|3- Buscar agentes já cadastrados |\n");//concluido
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
    printf("|0- Voltar                        |\n");
    printf("Escolha uma opção: ");
}

void exibirMenuEditarOuExcluir(){
    printf("\nO que deseja fazer:\n");
    printf("|1- Editar\n");
    printf("|2- Excluir o agente\n");
    printf("|0- Voltar\n");
    printf("|Escolha uma opção: ");
}

int cadastrarUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int i, int *proximoIdUser){
    id[i] = *proximoIdUser;

    limparBuffer();
    printf("Insira o nome de Usuario: ");
    if (fgets(nome[i],TAM_NOME_USER,stdin) == NULL)return 0;
    nome[i][strcspn(nome[i], "\n")] = '\0';

    for (int u = 0; u < i; u++){
        if (strcmp(nome[i], nome[u]) == 0){
            printf("Nome de usuario ja registrado, escolha outro\n");
            return 0;
        }
    }

    printf("Insira a senha: ");
    if (fgets(senha[i],TAM_SENHA,stdin) == NULL)return 0;
    senha[i][strcspn(senha[i], "\n")] = '\0';

    if (salvarUsuario(id, nome, senha, i + 1) == 0){
        printf("Erro em salvar Usuario.\n");
        return 0;
    }
    (*proximoIdUser)++;

    return 1;
}

int salvarUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int usuariosCadastrados){
    FILE *arquivo = fopen("UsuariosCadastrados.txt", "w");
    if (arquivo == NULL){
        printf("Arquivo de cadastro de Usuarios Não foi possivel ser aberto");
        return 0;
    }
    for (int i = 0; i < usuariosCadastrados; i++){
        fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%s\n", nome[i]);
        fprintf(arquivo, "%s\n", senha[i]);
    }
    fclose(arquivo);
    return 1;
}

int loginUsuario(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int usuariosCadastrados, char usuarioLogado[], char senhaLogado[]){
    char usuario[TAM_NOME_USER];
    char senhaLocal[TAM_SENHA];

    limparBuffer();
    printf("\n=============  LOGIN  ============");
    printf("\n _________________________________\n");
    printf("|Usuario: ");
    if (fgets(usuario, TAM_NOME_USER, stdin) == NULL)return 0;
    usuario[strcspn(usuario, "\n")] = '\0';

    printf("|Senha: ");
    if (fgets(senhaLocal, TAM_SENHA, stdin) == NULL)return 0;
    senhaLocal[strcspn(senhaLocal, "\n")] = '\0';

    for (int i = 0; i < usuariosCadastrados; i++){
        if (strcmp(usuario, nome[i]) == 0 && strcmp(senhaLocal, senha[i]) == 0){
            printf("\n======= LOGIN REALIZADO =========\n");
            printf("Id: %d\n", id[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Senha: %s\n", senha[i]);
            strcpy(usuarioLogado, nome[i]);
            strcpy(senhaLogado, senha[i]);
            return 1;
        }
        else{
            printf("Usuario ou senha incorreto!\n");
        }
    }
    
    return 0;

}

int cadastrarAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int i, int *proximoId, char criador[][TAM_NOME_USER], char usuarioLogado[], char ultimaModificacao[][TAM_NOME_USER]){
    id[i] = *proximoId;
    strcpy(criador[i], usuarioLogado);
    strcpy(ultimaModificacao[i], usuarioLogado);

    limparBuffer();
    printf("Insira o nome do Agente: ");
    if (fgets(nome[i],TAM_NOME,stdin) == NULL)return 0;
    nome[i][strcspn(nome[i], "\n")] = '\0';

    printf("Insira a funcionalidade do Agente: ");
    if (fgets(funcao[i], TAM_FUNCIONALIDADE, stdin) == NULL)return 0;
    funcao[i][strcspn(funcao[i], "\n")] = '\0';

    printf("Insira o script do Agente: ");
    if (fgets(scpt[i],TAM_SCRIPT,stdin) == NULL)return 0;
    scpt[i][strcspn(scpt[i], "\n")] = '\0';

    printf("Insira a nota do Agente: ");
    if (scanf("%d", &nota[i]) == 0){
        limparBuffer();
        return 0;
    }

    if (salvarAgentes(id, nome, funcao, scpt, nota, i + 1, criador, ultimaModificacao) == 0){
        printf("Erro em salvar agente.\n");
        return 0;
    }
    (*proximoId)++;

    limparBuffer();
    return 1;
}

int salvarAgentes(int id[], char nome[][TAM_NOME],char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int agentesCadastrados, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    FILE *arquivo = fopen("AgentesCadastrados.txt", "w");
    if (arquivo == NULL){
        printf("Arquivo de salvaAgentes não foi possivel ser aberto");
        return 0;
    }
    for (int i = 0; i < agentesCadastrados; i++){
        fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%s\n", nome[i]);
        fprintf(arquivo, "%s\n", funcao[i]);
        fprintf(arquivo, "%s\n", scpt[i]);
        fprintf(arquivo, "%d\n", nota[i]);
        fprintf(arquivo, "%s\n", criador[i]);
        fprintf(arquivo, "%s\n\n", ultimaModificacao[i]);
    }
    fclose(arquivo);
    return 1;
}

void listarAgentes(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int agentesCadastrados, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    printf("\n-----------------LISTA DE AGENTES------------------");
    for (int i = 0; i < agentesCadastrados; i++){
        printf("\n============================================================================================\n");
        printf("|Id: %d|\n|Nome: %s|\n|Funcionalidade: %s|\n|Script: %s|\n|Nota: %d|\n|Cadastrado por: %s|\n|Ultima Modificação: %s|\n", id[i], nome[i], funcao[i], scpt[i], nota[i], criador[i], ultimaModificacao[i]);
    }
    printf("\n============================================================================================\n");
}

int carregarAgentes(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    FILE *arquivo = fopen("AgentesCadastrados.txt", "r");
    if (arquivo == NULL){
        printf("Arquivo de carregarAgentes não foi possivel ser aberto");
        return 0;
    }
    //ard = Agentes Recuperados do Arquivo "AgentesCadastrados.txt"
    int ard = 0;

    while(ard < maxagents && fscanf(arquivo, "%d", &id[ard]) == 1){

        int c;
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);

        if (fgets(nome[ard], TAM_NOME, arquivo) == NULL)break;
        nome[ard][strcspn(nome[ard], "\n")] = '\0';

        if (fgets(funcao[ard], TAM_FUNCIONALIDADE, arquivo) == NULL)break;
        funcao[ard][strcspn(funcao[ard], "\n")] = '\0';

        if (fgets(scpt[ard], TAM_SCRIPT, arquivo) == NULL)break;
        scpt[ard][strcspn(scpt[ard], "\n")] = '\0';

        if (fscanf(arquivo, "%d", &nota[ard]) != 1)break;
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);

        if (fgets(criador[ard], TAM_NOME_USER, arquivo) == NULL)break;
        criador[ard][strcspn(criador[ard], "\n")] = '\0';

        if (fgets(ultimaModificacao[ard], TAM_NOME_USER, arquivo) == NULL)break;
        ultimaModificacao[ard][strcspn(ultimaModificacao[ard], "\n")] = '\0';
        ard++;
    }
    fclose(arquivo);
    return ard;
}

int carregarUsuarios(int id[], char nome[][TAM_NOME_USER], char senha[][TAM_SENHA], int maxusers){
    FILE *arquivo = fopen("UsuariosCadastrados.txt", "r");
    if (arquivo == NULL){
        printf("Arquivo de carregarUsuarios não foi possivel ser aberto");
        return 0;
    }
    //urd = Usuarios Recuperados do Arquivo "UsuariosCadastrados.txt"
    int urd = 0;

    while(urd < maxusers && fscanf(arquivo, "%d", &id[urd]) == 1){
        
        int c;
        while ((c = fgetc(arquivo)) != '\n' && c != EOF);

        if (fgets(nome[urd], TAM_NOME_USER, arquivo) == NULL)break;
        nome[urd][strcspn(nome[urd], "\n")] = '\0';

        if (fgets(senha[urd], TAM_SENHA, arquivo) == NULL)break;
        senha[urd][strcspn(senha[urd], "\n")] = '\0';
        urd++;
    }
    fclose(arquivo);
    return urd;
}

int editarAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int maxnota, int posicao, char criador[][TAM_NOME_USER], char usuarioLogado[], char ultimaModificacao[][TAM_NOME_USER]){
    int opcao;

    printf("\n====== O QUE DESEJA EDITAR =======");
    printf("\n _________________________________\n");
    printf("|1- Nome                          |\n");
    printf("|2- Funcionalidade                 |\n");
    printf("|3- Script                        |\n");
    printf("|4- Nota                          |\n");
    printf("|5- Todas as informações          |\n");
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
        strcpy(ultimaModificacao[posicao], usuarioLogado);

        break;
    
    case 2:
        printf("Insira a nova funcionalidade do Agente: ");

        if (fgets(funcao[posicao], TAM_FUNCIONALIDADE, stdin) == NULL)return 0;
        funcao[posicao][strcspn(funcao[posicao], "\n")] = '\0';
        strcpy(ultimaModificacao[posicao], usuarioLogado);

        break;
    
    case 3:
        printf("Insira o novo script do Agente: ");
        if (fgets(scpt[posicao], TAM_SCRIPT, stdin) == NULL)return 0;
        scpt[posicao][strcspn(scpt[posicao], "\n")] = '\0';
        strcpy(ultimaModificacao[posicao], usuarioLogado);

        break;

    case 4:
        printf("\nInsira a nova nota do Agente: ");

        if (scanf("%d", &nota[posicao]) != 1 || nota[posicao] < 0 || nota[posicao] > maxnota){
            limparBuffer();
            printf("Nota Invalida...\n");
            return 0;
        }
        strcpy(ultimaModificacao[posicao], usuarioLogado);
        limparBuffer();
        break;

    case 5:
        printf("\nInsira o novo nome do Agente: ");
        if (fgets(nome[posicao], TAM_NOME, stdin) == NULL)return 0;
        nome[posicao][strcspn(nome[posicao], "\n")] = '\0';

        printf("Insira a nova funcionalidade do Agente: ");
        if (fgets(funcao[posicao], TAM_FUNCIONALIDADE, stdin) == NULL)return 0;
        funcao[posicao][strcspn(funcao[posicao], "\n")] = '\0';

        printf("\nInsira o novo script do Agente: ");
        if (fgets(scpt[posicao], TAM_SCRIPT, stdin) == NULL)return 0;
        scpt[posicao][strcspn(scpt[posicao], "\n")] = '\0';

        printf("\nInsira a nova nota do Agente: ");
        if (scanf("%d", &nota[posicao]) != 1 || nota[posicao] < 0 || nota[posicao] > maxnota){
            limparBuffer();
            printf("Nota Invalida...\n");
            return 0;
        }
        strcpy(ultimaModificacao[posicao], usuarioLogado);
        limparBuffer();
        break;

    case 0:
        printf("Edição cancelada, Saindo...\n");
        return 0;
    
    default:
        printf("Opção Invalida...\n");
    }

    if (salvarAgentes(id, nome, funcao, scpt, nota, maxagents, criador, ultimaModificacao) == 0){
        printf("Erro ao salvar as alterações.\n");
        return 0;
    }

    printf("\n! Agente atualizado com sucesso !\n");

    return 1;

}

int buscarId(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
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
    printf("Funcionalidade: %s\n", funcao[posicao]);
    printf("Script: %s\n", scpt[posicao]);
    printf("Nota: %d\n", nota[posicao]);
    printf("Cadastrado por: %s\n", criador[posicao]);
    printf("Ultima modificação foi feita por: %s\n", ultimaModificacao[posicao]);

    return posicao;
}

int buscarNome(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
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
    printf("Funcionalidade: %s\n", funcao[posicao]);
    printf("Script: %s\n", scpt[posicao]);
    printf("Nota: %d\n", nota[posicao]);
    printf("Cadastrado por: %s\n", criador[posicao]);
    printf("Ultima modificação foi feita por: %s\n", ultimaModificacao[posicao]);

    return posicao;
}

int buscarFuncao(int id[], char nome [][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    char funcaoBusca[TAM_FUNCIONALIDADE];
    int posicao = -1;

    limparBuffer();

    printf("\nInsira a Funcionalidade do Agente que deseja buscar: ");
    if (fgets(funcaoBusca, TAM_FUNCIONALIDADE, stdin) == NULL)return -1;

    funcaoBusca[strcspn(funcaoBusca, "\n")] = '\0';

    for (int i = 0; i < maxagents; i++){
        if (strcmp(funcao[i], funcaoBusca) == 0){
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
    printf("Funcionalidade: %s\n", funcao[posicao]);
    printf("Script: %s\n", scpt[posicao]);
    printf("Nota: %d\n", nota[posicao]);
    printf("Cadastrado por: %s\n", criador[posicao]);
    printf("Ultima modificação foi feita por: %s\n", ultimaModificacao[posicao]);

    return posicao;

}

int buscarPalavraChave(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    char palavraBusca[TAM_PALAVRA_CHAVE];
    int agentesencontrados = 0;

    limparBuffer();

    printf("\nInsira a Palavra-Chave que deseja buscar: ");
    if (fgets(palavraBusca, TAM_PALAVRA_CHAVE, stdin) == NULL)return -1;

    palavraBusca[strcspn(palavraBusca, "\n")] = '\0';

    for (int i = 0; i < maxagents; i++){

        if (strstr(nome[i], palavraBusca) != NULL || strstr(funcao[i], palavraBusca) != NULL || strstr(scpt[i], palavraBusca) != NULL){
        
            printf("\n======= AGENTE ENCONTRADO ========\n");
            printf("Id: %d\n", id[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Funcionalidade: %s\n", funcao[i]);
            printf("Script: %s\n", scpt[i]);
            printf("Nota: %d\n", nota[i]);
            printf("Cadastrado por: %s\n", criador[i]);
            printf("Ultima modificação foi feita por: %s\n", ultimaModificacao[i]);

            agentesencontrados++;
        }
    }

    if (agentesencontrados == 0){
        printf("Nenhum Agente Encontrado\n");
        return -1;
    }

}

int buscarNota(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    int notaBusca;
    int agentescadastrados;

    printf("\nInsira a Nota que deseja buscar: ");
    if (scanf("%d", &notaBusca) != 1){
        limparBuffer();
        printf("Nota Invalida\n");
        return -1;
    }
    limparBuffer();

    for (int i = 0; i < maxagents; i++){
        if (nota[i] == notaBusca){

            printf("\n======= AGENTE ENCONTRADO ========\n");
            printf("Id: %d\n", id[i]);
            printf("Nome: %s\n", nome[i]);
            printf("Funcionalidade: %s\n", funcao[i]);
            printf("Script: %s\n", scpt[i]);
            printf("Nota: %d\n", nota[i]);
            printf("Cadastrado por: %s\n", criador[i]);
            printf("Ultima modificação foi feita por: %s\n", ultimaModificacao[i]);

            agentescadastrados++;
        }
    }

    if (agentescadastrados == 0){
        printf("Nenhum Agente encontrado...\n");
    }
}

int excluirAgente(int id[], char nome[][TAM_NOME], char funcao[][TAM_FUNCIONALIDADE], char scpt[][TAM_SCRIPT], int nota[], int maxagents, int posicao, char criador[][TAM_NOME_USER], char ultimaModificacao[][TAM_NOME_USER]){
    
    int opcaoConfirmar = 0;

    do{
        printf("\nTem certeza que deseja excluir o Agente:\n");
        printf("|1- Sim, Excluir o Agente\n");
        printf("|2- Não, Voltar\n");
        printf("|Escolha uma opção: ");
        
        if (scanf("%d", &opcaoConfirmar) != 1){
            limparBuffer();
            printf("Opção Invalida...\n");
            opcaoConfirmar = -1;
        }
        else{
            limparBuffer();
        }
    }while(opcaoConfirmar != 1 && opcaoConfirmar != 2);

    if (opcaoConfirmar == 1){
        for (int i = posicao; i < maxagents - 1; i++){
            id[i] = id[i + 1];
            strcpy(nome[i], nome[i +1]);
            strcpy(funcao[i], funcao[i + 1]);
            strcpy(scpt[i], scpt[i + 1]);
            nota[i] = nota[i + 1];
            strcpy(criador[i], criador[i + 1]);
            strcpy(ultimaModificacao[i], ultimaModificacao[i + 1]);
        }

        maxagents--;

        printf("! Agente excluido com sucesso !\n");

    }
    else if (opcaoConfirmar == 2){
        printf("Agente mantido, voltando...\n");
    }

    return maxagents;
}