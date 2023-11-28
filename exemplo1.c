#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pessoa{
    int id;
    char nome[30];
    int idade;
    struct Pessoa *prox;
}Pessoa;

//funcao que cria a lista vazia
Pessoa* criarListaVazia(){
    return NULL;
}

//criar uma nova pessoa
//retorna o enderecoda nova pessoa
Pessoa* criarPessoa(){
    Pessoa *novaPessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if(novaPessoa == NULL){
        //memoria insuficiente
        printf("Erro de alocacao");
        exit(EXIT_FAILURE);
    }
    novaPessoa->prox = NULL;
    return novaPessoa;//endereco de memoria alocacado para a nova pessoa
}

Pessoa* cadastrar(Pessoa *lista){
    Pessoa *novaPessoa = criarPessoa();
    //inserir as informacoes
    srand(time(NULL));
    novaPessoa->id = rand() % 100;
    printf("Digite o nome: ");
    fflush(stdin);
    fgets(novaPessoa->nome, sizeof(novaPessoa), stdin);
    fflush(stdin);
    printf("Digite a idade: ");
    fflush(stdin);
    scanf("%d", &novaPessoa->idade);
    fflush(stdin);                                            

    //duas situacoes 1 - lista é vazia 2 já tem alguem na lista
    if(lista == NULL){
        return novaPessoa;
    }else{
        //percorrer a lista eté encontrar a pessoa que aponta para NULL
        Pessoa *atual = lista;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = novaPessoa;
        return lista;
    }
}

void mostrar(Pessoa *lista){
    if(lista == NULL){
        printf("Lista NULA");
        return;
    } else{
        Pessoa *atual = lista;
        while(atual != NULL){
            printf("NOme: %s", atual->nome);
            printf("\nIdade: %d", atual->idade);
            printf("\nId: %d", atual->id);
            atual = atual->prox;
        }
    }
}

Pessoa* buscarPessoa(Pessoa *lista, int idBusca){
    if(lista == NULL){
        printf("Lista NULA");
        return;
    } else{
        Pessoa *atual = lista;
        while(atual != NULL){
            if(atual->id == idBusca){
                printf("NOme: %s", atual->nome);
                printf("Idade: %d", atual->idade);
                printf("\nId: %d", atual->id);
                return atual;
            }
            atual = atual->prox;
        }
        printf("Pessoa nao encontrada");
        return NULL;
    }
}

void alterar(Pessoa *encontrada){
    printf("Alteracao dos campos");
    printf("\nDigite o nome: ");
    fflush(stdin);
    fgets(encontrada->nome, sizeof(encontrada->nome), stdin);
    fflush(stdin);
    printf("Digite a idade: ");
    fflush(stdin);
    scanf("%d", &encontrada->idade);
    fflush(stdin);         
}

Pessoa* excluir(Pessoa *lista, int idBusca){
    Pessoa *anterior = NULL;
    Pessoa *atual = lista;

    while(atual != NULL && atual->id != idBusca){
        anterior = atual;
        atual = atual->prox;

    }
    if(atual != NULL){
        //logica de exclusao
        if(anterior != NULL){
            //excluir alguem que nao esta no inicio da lista
            anterior->prox = atual->prox;

        } else {
            //excluir o primeiro da lista 
            lista = atual->prox;
        }
        free(atual);
        printf("Excluido com sucesso");

    } else{
        printf("Pessoa nao encontrada");
    }
    return lista;

}

main(){
    int opcao, idBusca;
    Pessoa *lista = criarListaVazia();
    Pessoa *encontrada;
    do{
        printf("\n1 - Cadastrr");
        printf("\n2 - Mostrar");
        printf("\n3 - Buscar");
        printf("\n4 - Alterar");
        printf("\n5 - Excluir");
        printf("\n0 - Sair");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                lista = cadastrar(lista);
                break;

            case 2:
                mostrar(lista);
                break;

            case 3:
                printf("Digite o id para buscar");
                scanf("%d", &idBusca);
                encontrada = buscarPessoa(lista, idBusca);
                break;

            case 4:
                printf("Digite o id para buscar");
                scanf("%d", &idBusca);
                encontrada = buscarPessoa(lista, idBusca);
                if(encontrada != NULL){
                    alterar(encontrada);
                }
                break;

            case 5:
                printf("Digite o id para buscar");
                scanf("%d", &idBusca);
                lista = excluir(lista, idBusca);
                break;
        }
    }while(opcao != 0);
    
}
