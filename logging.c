#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "logging.h"

#define MAX_QUANTIDADE_RAIOX 5
#define MAX_QUANTIDADE_LAUDO 3
#define MAX_QUANTIDADE_PATOLOGIAS 5

struct hospital{
  int raioX[MAX_QUANTIDADE_RAIOX][3]; //col1 = se está disponivel, col2 = tempo que será usada, col3 = id do paciente
  int laudo[MAX_QUANTIDADE_LAUDO][3]; //col1 = se está disponivel, col2 = tempo que será usada, col3 = id do paciente
  float **registro_pacientes;//patologia, tempo
};
struct paciente {
  char nome[50];
  char cpf[15];
  int idade;
  int id;
  int patologia[2]; //id da patologia e a gravidade
  int entrada, entrada_raiox, saida_raiox, entrada_laudo, saida;
};
struct node {
  void *dados;
  Node *proximo;
  Node *anterior;
};
struct lista {
  Node *Primeiro;
  Node *Ultimo;
  int tamanho;
};

struct fila {
  Node *Primeiro;
  Node *Ultimo;
  int tamanho;
};

/*-----------------------------------------------------------------
                            Lista
-----------------------------------------------------------------*/

Lista *inicia_Lista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->Primeiro = NULL;
    lista->Ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

void insere_Lista(Lista *lista, void *dados) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->dados = dados;
    newNode->proximo = lista->Primeiro;
    newNode->anterior = NULL;
    if(lista->tamanho != 0) {
      lista->Primeiro->anterior = newNode;
    }
    else{
      lista->Ultimo = newNode;
    }
    lista->Primeiro = newNode;
    lista->tamanho++;
}

void remove_dados_lista(Lista *l, void *val) {
  Node *temp = l->Primeiro;
  Node *anterior = NULL;
  Node *auxiliar;
  while (temp != NULL) {
    if (temp->dados == val) {
      auxiliar = temp;
      if (anterior != NULL) {
        anterior->proximo = temp->proximo;
        if (temp->proximo == NULL) {
          l->Ultimo = anterior;
        }
      } else {
        l->Primeiro = temp->proximo;
        if (temp->proximo == NULL) {
          l->Ultimo = NULL;
        }
      }
      temp = temp->proximo;
      free(auxiliar);
    } 
    else {
      anterior = temp;
      temp = temp->proximo;
    }
  }
  l->tamanho--;
}

void liberaLista(Lista *lista) {
    Node *primeiro = lista->Primeiro;
    Node *proximo;
    while (primeiro != NULL) {
        proximo = primeiro->proximo;
        free(primeiro);
        primeiro = proximo;
    }
    free(lista);
}

/*----------------------------------------------------------------
                            Fila
-----------------------------------------------------------------*/

Fila *inicia_Fila(){
  Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->Ultimo = NULL;
    fila->Primeiro = NULL;
    fila->tamanho = 0;
    return fila;
}

void remove_dados_fila(Fila *fila) {
    if (fila->Primeiro == NULL) {
        fprintf(stderr, "Erro: Fila vazia\n");
        return;
    }
    Node *temp = fila->Primeiro;
    fila->Primeiro = fila->Primeiro->proximo;
    // Se a fila ficar vazia após a remoção
    if (fila->Primeiro == NULL) {
        fila->Ultimo = NULL;
    } 
    else {
        fila->Primeiro->anterior = NULL;
    }
    free(temp);              // Liberar o nó removido
    fila->tamanho--;
}

void liberaFila(Fila *fila) {
    Node *primeiro = fila->Primeiro;
    Node *proximo;
    while (primeiro != NULL) {
        proximo = primeiro->proximo;
        free(primeiro);
        primeiro = proximo;
    }
    free(fila);
}

/*---------------------------------------------------------------
                              TAD
---------------------------------------------------------------*/

Hospital *inicia_Hospital() {
  Hospital *hospital = (Hospital *)malloc(sizeof(Hospital));
  //confere se conseguiu alocar
  if (hospital == NULL) {
    printf("Erro: falha ao alocar memória para Hospital.\n");
    exit(EXIT_FAILURE);
  }
  hospital->registro_pacientes = (float**)malloc(MAX_QUANTIDADE_PATOLOGIAS * sizeof(int*));
  //conferindo se alocou os ponteiros de ponteiros
  if (hospital->registro_pacientes == NULL) {
      printf("Erro: falha ao alocar memória.\n");
      exit(EXIT_FAILURE);
  }
  for (int i = 0; i < MAX_QUANTIDADE_PATOLOGIAS; i++) {
    hospital->registro_pacientes[i] = (float *)malloc(sizeof(float) * 2);
    //conferindo se alocou cada elemento da matriz
    if (hospital->registro_pacientes[i] == NULL) {
      printf("Erro: falha ao alocar memória para registro_pacientes[%d].\n", i);
      // Liberar memória anterioriamente alocada
      liberaHospital(hospital);
      exit(EXIT_FAILURE);
    }
    hospital->registro_pacientes[i][0] = i+1;
    hospital->registro_pacientes[i][1] = 0;
  }
  return hospital;
}

void liberaHospital(Hospital *hospital) {
  if (hospital != NULL) {
    for (int i = 0; i < MAX_QUANTIDADE_PATOLOGIAS; i++) {
      free(hospital->registro_pacientes[i]);
    }
    free(hospital->registro_pacientes);
    free(hospital);
  }
}

int probabilidade_paciente(){
  int probabilidade_paciente = rand() % 100;
  if(probabilidade_paciente < 20){
    return 1;
  }
  return 0;
}

int *probabilidade_patologia(){
  int probabilidade_patologia = rand() % 100;
  int *patologia = (int*)malloc(sizeof(int)*2); //váriavel que será retornada tem 2 valores
  int SAUDE_NORMAL = 1;
  int BRONQUITE = 2;
  int PNEUMONIA = 3;
  int FRATURA_DE_FEMUR = 4;
  int APENDICITE = 4;

  if(probabilidade_patologia < 30 ){
    patologia[0] = 1;
    patologia[1] = SAUDE_NORMAL;
  }
  else if (probabilidade_patologia >= 30 && probabilidade_patologia < 50){
    patologia[0] = 2;
    patologia[1] = BRONQUITE;
  }
  else if (probabilidade_patologia >= 50 && probabilidade_patologia < 70){
    patologia[0] = 3;
    patologia[1] = PNEUMONIA;
  }
  else if (probabilidade_patologia >= 70 && probabilidade_patologia < 85){
    patologia[0] = 4;
    patologia[1] = FRATURA_DE_FEMUR;
  }
  else if (probabilidade_patologia >= 85){
    patologia[0] = 5;
    patologia[1] = APENDICITE;
  }
  return patologia;
}

int probabilidade_raiox(){
  int probabilidade_raiox = 5 + (rand() % 6);
  return probabilidade_raiox;
}

int probabilidade_laudo(){
  int probabilidade_laudo = 10 + rand() % 21;
  return probabilidade_laudo;
}
char* gerarNome() {
    char* nomes[] = {"joao", "Maria", "Carlos", "Ana", "Pedro", "jlia", "Lucas", "Mariana", "Guilherme"};
    // Gera um índice aleatório para escolher um nome da lista
    int indice = rand() % (sizeof(nomes) / sizeof(nomes[0]));
    // copia e cola o nome na váriavel nome
    char* nome = strdup(nomes[indice]);
    return nome;
}
char* gerarCPF() {
    char cpf[15];
    // Gera números aleatórios para o CPF
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
    // copia e cola o cpf na váriavel resultado
    char* resultado = strdup(cpf);
    return resultado;
}

int gerarIdade() {
  return rand() % 100;
}
Paciente *gerarPaciente(int ID){
  Paciente *paciente = (Paciente *)malloc(sizeof(Paciente));
  if (paciente == NULL) {
    fprintf(stderr, "Erro ao alocar memória para Paciente\n");
    exit(EXIT_FAILURE);
  }
  int *patologia = (int*)malloc(sizeof(int)*2);
  patologia = probabilidade_patologia();
  // Gera aleatoriamente o nome, CPF e idade
  strcpy(paciente->nome, gerarNome());
  strcpy(paciente->cpf, gerarCPF());
  paciente->idade = gerarIdade();
  paciente->id = ID;
  paciente->patologia[0] = patologia[0];
  paciente->patologia[1] = patologia[1];
  paciente->entrada = ID;
  free(patologia);
  return paciente;
}

void fila_atendimento_raiox(Fila *fila_sala_de_entrada, Fila *raiox, Hospital *hospital, int unidade_de_tempo){
  //verifica se tem algum paciente na entrada do hospital
  if(fila_sala_de_entrada->Primeiro == NULL){
    return;
  }
  Paciente *auxiliar = (Paciente*)fila_sala_de_entrada->Primeiro->dados;
  for (int i = 0;i<MAX_QUANTIDADE_RAIOX;i++){
    if(hospital->raioX[i][0] == 0){
      hospital->raioX[i][0] = 1;
      hospital->raioX[i][1] = probabilidade_raiox();
      hospital->raioX[i][2] = auxiliar->id;
      auxiliar->entrada_raiox = unidade_de_tempo;
      remove_dados_fila(fila_sala_de_entrada);
      insere_ordenado(raiox, auxiliar);
      return; //termina o loop e retorna
    }
  }
}

void fila_atendimento_laudo(Fila *fila_raiox, Fila *laudo, Hospital *hospital, int unidade_de_tempo){
  if (fila_raiox->Primeiro == NULL) {
    return; // Não há pacientes no raio-x, portanto, não é possível ir para o laudo
  }

  Paciente *auxiliar = (Paciente *)fila_raiox->Primeiro->dados;
  if (auxiliar->saida_raiox == 0) {
    return; // O paciente ainda não passou pelo raio-x, então não pode ir para o laudo
  }

  for (int i = 0; i < MAX_QUANTIDADE_LAUDO; i++) {
    if (hospital->laudo[i][0] == 0) {
      hospital->laudo[i][0] = 1;
      hospital->laudo[i][1] = probabilidade_laudo();
      hospital->laudo[i][2] = auxiliar->id;
      auxiliar->entrada_laudo = unidade_de_tempo;
      remove_dados_fila(fila_raiox);
      insere_ordenado(laudo, auxiliar);
      return; //termina o loop e retorna
    }
  }
}

void atualiza_tempo_raiox(Hospital *hospital){
  for(int i = 0;i<MAX_QUANTIDADE_RAIOX;i++){
    if(hospital->raioX[i][1] != 0){
      hospital->raioX[i][1]--;
    }
    if(hospital->raioX[i][1] == 0){
      hospital->raioX[i][0] = 0;
    }
  }
}

void atualiza_tempo_laudo(Hospital *hospital){
  for(int i = 0;i<MAX_QUANTIDADE_LAUDO;i++){
    if(hospital->laudo[i][1] != 0){
      hospital->laudo[i][1]--;
    }
    if(hospital->laudo[i][1] == 0){
      hospital->laudo[i][0] = 0;
    }
  }
}

void atualiza_raiox(Hospital *hospital, Fila *fila_raiox, int unidade_de_tempo){
  for(int i = 0;i<MAX_QUANTIDADE_RAIOX;i++){
    if(hospital->raioX[i][1] == 0){
      Node *Auxiliar = fila_raiox->Primeiro;
      Paciente *paciente;
      while (Auxiliar != NULL) {
        paciente = (Paciente *)Auxiliar->dados;
        if (paciente->id == hospital->raioX[i][2]) {
          paciente->saida_raiox = unidade_de_tempo;
          hospital->raioX[i][2] = 0;
          return;
        }
        Auxiliar = Auxiliar->proximo;
      }
    }
  }
}

void atualiza_laudo(Hospital *hospital, Fila *fila_laudo, int unidade_de_tempo){
  for(int i = 0;i<MAX_QUANTIDADE_LAUDO;i++){
    if(hospital->laudo[i][1] == 0){
      Node *Auxiliar = fila_laudo->Primeiro;
      while (Auxiliar != NULL) {
        Paciente *paciente = (Paciente *)Auxiliar->dados;
        if (paciente->id == hospital->laudo[i][2]) {
          paciente->saida = unidade_de_tempo;
          hospital->laudo[i][2] = 0;
          return;
        }
        Auxiliar = Auxiliar->proximo;
      }
    }
  }
}

int verifica_raiox(Hospital *hospital){
  for (int i = 0; i < MAX_QUANTIDADE_RAIOX; i++) {
    if (hospital->raioX[i][0] == 0) {
      return 1;  // Encontrou uma vaga no raio-x
    }
  }
  return 0; // Não encontrou vaga no raio-x
}

int verifica_laudo(Hospital *hospital){
  for (int i = 0; i < MAX_QUANTIDADE_LAUDO; i++) {
    if (hospital->laudo[i][0] == 0) {
      return 1;  // Encontrou uma vaga no laudo
    }
  }
  return 0; // Não encontrou vaga no laudo
}

void atualiza_lista_controle(Fila *fila_laudo, Lista *lista_controle){
  if(fila_laudo->Primeiro == NULL || lista_controle->Primeiro == NULL){
    return;
  }
  Node *auxiliar = fila_laudo->Primeiro;
  if(((Paciente*)auxiliar->dados)->saida == 0) return;
  for(Node *Dados_atualizados = lista_controle->Primeiro;Dados_atualizados != NULL; Dados_atualizados = Dados_atualizados->proximo){
    if(((Paciente*)Dados_atualizados->dados)->id == ((Paciente*)auxiliar->dados)->id){
      lista_controle->Primeiro->dados = Dados_atualizados->dados; //troca apenas os dados
      remove_dados_fila(fila_laudo);//tira da fila, o paciente já foi atendido
      return;
    }
  }
}

float media_laudo(Lista *controle){
  float Soma_Tempo = 0.0;
  int Ocorrencias = 0;
  Node *paciente = controle->Primeiro;
  for (int i = 0; i < controle->tamanho; i++) {
      if (((Paciente *)paciente->dados)->saida != 0) {
        Soma_Tempo += ((Paciente *)paciente->dados)->saida - ((Paciente *)paciente->dados)->entrada;
        Ocorrencias++;
      }
      paciente = paciente->proximo;
  }
  // Evita divisão por zero
  if (Ocorrencias != 0) {
    return Soma_Tempo / Ocorrencias;
  } 
  return 0.0;
}

void media_patologias(Lista *controle, Hospital *hospital) {
    if (controle->Primeiro == NULL) {
        return;
    }
    Node *auxiliar = controle->Primeiro;
    for (int i = 0; i < MAX_QUANTIDADE_PATOLOGIAS; i++) {
        float soma_tempos = 0.0;
        int contador = 0;
        // Percorre a lista
        while (auxiliar != NULL) {
            Paciente *paciente = (Paciente *)auxiliar->dados;
            // Verifica se o paciente possui a patologia e unidade_de_tempoá foi atendido
            if (paciente->saida != 0 && paciente->patologia[0] == hospital->registro_pacientes[i][0]) {
                soma_tempos += paciente->saida - paciente->entrada;
                contador++;
            }
            auxiliar = auxiliar->proximo;
        }
        // Calcula a média se houver pacientes
      hospital->registro_pacientes[i][1] = (contador != 0) ? (soma_tempos / contador) : 0.0;
        // Reinicia o ponteiro para o início da lista
        auxiliar = controle->Primeiro;
    }
}

int exames_apos_tempo(Lista *controle){
  float Soma_Tempo = 0.0;
  int contador = 0;
  Node *auxiliar = (Node *)malloc(sizeof(Node));
  auxiliar = controle->Primeiro;

  for (int i = 0; i < controle->tamanho; i++) {
      if (((Paciente *)auxiliar->dados)->saida != 0) {
        Soma_Tempo = ((Paciente *)auxiliar->dados)->saida - ((Paciente *)auxiliar->dados)->entrada;
        if(Soma_Tempo>7200){
          contador++;
        }
      }
      auxiliar = auxiliar->proximo;
  }
  return contador;
} 

void printa_metrica(Lista *controle, Hospital *hospital){
  media_patologias(controle,  hospital);
  printf("laudo: %f\npatologias:\nSaúde normal: %f\nBronquite: %f\nPneumonia: %f\nFratura de fêmur: %f\nApendicite: %f\nFora do tempo: %d\n\n", media_laudo(controle),  hospital->registro_pacientes[0][1], hospital->registro_pacientes[1][1], hospital->registro_pacientes[2][1], hospital->registro_pacientes[3][1], hospital->registro_pacientes[4][1], exames_apos_tempo(controle));
  sleep(1);
}

void insere_ordenado(Fila *fila, Paciente *novo_paciente) {
  // Aloca memória para o novo nó
  Node *novo_node = (Node*)malloc(sizeof(Node));
  // Configuração do novo nó
  novo_node->dados = novo_paciente;
  novo_node->anterior = NULL;
  novo_node->proximo = NULL;
  // Caso especial: fila vazia
  if (fila->Primeiro == NULL) {
      fila->Primeiro = novo_node;
      fila->Ultimo = novo_node;
      fila->tamanho++;
      return;
  }
  if(novo_paciente->patologia[0]<=2){
    // Procura a posição correta para inserir o novo paciente
    Node *atual = fila->Ultimo;
    while (atual != NULL && novo_paciente->patologia[1] <= ((Paciente *)atual->dados)->patologia[1]) {
      atual = atual->anterior;
    }
    // Insere o novo_node na posição correta
    if (atual != NULL) {
      Node *anterior = atual->anterior;
      novo_node->proximo = atual;
      novo_node->anterior = anterior;
      if (anterior != NULL) {
          anterior->proximo = novo_node;
      } 
      else {
        // Se anterior é nulo, então o novo_node se torna o novo Primeiro
        fila->Primeiro = novo_node;
      }
      atual->anterior = novo_node;
    } 
    else {
      // Se chegou ao final da fila, insere no final
      Node *ultimo = fila->Ultimo;
      novo_node->anterior = ultimo;
      ultimo->proximo = novo_node;
      fila->Ultimo = novo_node; // Atualiza o Ultimo
    }
  }
  else{
    // Procura a posição correta para inserir o novo paciente
    Node *atual = fila->Primeiro;
    while (atual != NULL && novo_paciente->patologia[1] <= ((Paciente *)atual->dados)->patologia[1]) {
      atual = atual->proximo;
    }
    // Insere o novo_node na posição correta
    if (atual != NULL) {
      Node *anterior = atual->anterior;
      novo_node->proximo = atual;
      novo_node->anterior = anterior;
      if (anterior != NULL) {
        anterior->proximo = novo_node;
      } 
      else {
        // Se anterior é nulo, então o novo_node se torna o novo Primeiro
        fila->Primeiro = novo_node;
      }
      atual->anterior = novo_node;
    } 
    else {
      // Se chegou ao final da fila, insere no final
      Node *ultimo = fila->Ultimo;
      novo_node->anterior = ultimo;
      ultimo->proximo = novo_node;
      fila->Ultimo = novo_node; // Atualiza o Ultimo
    }

  }
  fila->tamanho++;
}
