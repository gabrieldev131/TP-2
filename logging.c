#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logging.h"

/*
struct máquina_raioX{
  unsigned máquina1: 1;
  unsigned máquina2: 1;
  unsigned máquina3: 1;
  unsigned máquina4: 1;
  unsigned máquina5: 1;
}raioX;
struct laudos{
  unsigned medico1: 1;
  unsigned medico2: 1;
  unsigned medico3: 1;
}laudos;
*/
struct hospital{
  int raioX[5][2]; //col1 = se está disponivel, col2 = tempo que será usada
  int laudo[3][2]; //col1 = se está disponivel, col2 = tempo que será usada
};
struct paciente {
  char nome[50];
  char cpf[15];
  int idade;
  int id;
  int doença[2]; //id da doença e a gravidade
  int entrada, entrada_raiox, saida_raiox, entrada_laudo, saida;
};
struct node {
  void *data;
  Node *next;
  Node *prev;
};
struct lista {
  Node *First;
  Node *Last;
  int size;
};

struct fila {
  Node *Front;
  Node *Rear;
  int size;
};

/*-----------------------------------------------------------------
                            Lista
-----------------------------------------------------------------*/


Lista *init_Lista(){
    Lista *list = (Lista *)malloc(sizeof(Lista));
    list->First = NULL;
    list->Last = NULL;
    list->size = 0;
    return list;
}

int size(Lista *list){
  return list->size;
}

void append(Lista *list, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = list->Last;
    newNode->next = NULL;
    if(list->size != 0) {
      list->Last->next = newNode;
    }
    else{
      list->First = newNode;
    }
    list->Last = newNode;
    list->size++;

}

int is_in(Lista *l, void *val){
  Node *temp = l->First;
  for(;temp->next != NULL;){
    if (temp->data == val) {  
      return 1;
    }
    temp = temp->next;
  }
   return 0;
}

void remove_data(Lista *l, void *val) {
  Node *temp = l->First;
  Node *prev = NULL;
  Node *aux;

  while (temp != NULL) {
    if (temp->data == val) {
      aux = temp;
      if (prev != NULL) {
        prev->next = temp->next;
        if (temp->next == NULL) {
          l->Last = prev;
        }
      } else {
        l->First = temp->next;
        if (temp->next == NULL) {
          l->Last = NULL;
        }
      }
      temp = temp->next;
      free(aux);
    } 
    else {
      prev = temp;
      temp = temp->next;
    }
  }
  l->size--;
}

void freeLista(Lista *list) {
    Node *current = list->First;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void insert(Lista *l, void *data){
   Node *node = (Node *)malloc(sizeof(Node)); 
   node->data = data; 
   node->next = l->First;
   if (l->size != 0){
      l->First->prev = node; 
   }
   else {
      l->Last = node;
   }
   l->First = node; 
   l->size++; 
}

void print_list(Lista *l){
   for (Node *p = l->First; p != NULL; p = p->next)
   {
     void *a = p->data;
      print_p(a); 
   }
   printf("\n"); 
}

/*----------------------------------------------------------------
                            Fila
-----------------------------------------------------------------*/

Fila *init_Fila(){
  Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->Rear = NULL;
    fila->Front = NULL;
    fila->size = 0;
    return fila;
}
int size_f(Fila *fila){
  return fila->size;
}

void append_f(Fila *fila, void *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = fila->Rear;
    newNode->next = NULL;
    if(fila->size != 0) {
      fila->Rear->next = newNode;
    }
    else{
      fila->Front = newNode;
    }
    fila->Rear = newNode;
    fila->size++;

}

int is_in_f(Fila *f, void *val){
  Node *temp = f->Front;
  for(;temp->next != NULL;){
    if (temp->data == val) {  
      return 1;
    }
    temp = temp->next;
  }
   return 0;
}

void remove_data_f(Fila *f) {
    if (f->Front == NULL) {
        fprintf(stderr, "Erro: Fila vazia\n");
        return;
    }
    Node *temp = f->Front;
    f->Front = f->Front->next;
    // Se a fila ficar vazia após a remoção
    if (f->Front == NULL) {
        f->Rear = NULL;
    } 
    else {
        f->Front->prev = NULL;
    }
    free(temp);              // Liberar o nó removido
    f->size--;
}

void freeFila(Fila *fila) {
    Node *current = fila->Front;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(fila);
}

void print_fila(Fila *f){
   for (Node *p = f->Front; p != NULL; p = p->next)
   {
     void *a = p->data;
      print_p(a); 
   }
   printf("\n"); 
}

/*---------------------------------------------------------------
                              TAD
---------------------------------------------------------------*/

int prob_pac(){
  int prob = rand() % 100;
  if(prob < 20){
    return 1;
  }
  return 0;
}
int prob_pat(){
  int prob = rand() % 100;
  int SAUDE_NORMAL = 1;
  int BRONQUITE = 2;
  int PNEUMONIA = 3;
  int FRATURA_DE_FEMUR = 4;
  int APENDICITE = 4;

  if(prob < 30 ){
    return SAUDE_NORMAL;
  }
  else if (prob >= 30 && prob < 50){
    return BRONQUITE;
  }
  else if (prob >= 50 && prob < 70){
    return PNEUMONIA;
  }
  else if (prob >= 70 && prob < 85){
    return FRATURA_DE_FEMUR;
  }
  else if (prob >= 85){
    return APENDICITE;
  }
  return 0;
}
int prob_raiox(){
  int k = rand() % 11;
  if(k >= 5){
    return k;
  }
  return 0;
}
int prob_laudo(){
  int k = rand() % 31;
  if(k >= 10){
    return k;
  }
  return 0;
}
char* gerarNome() {
    char* nomes[] = {"Joao", "Maria", "Carlos", "Ana", "Pedro", "Julia", "Lucas", "Mariana", "Guilherme"};
    // Gera um índice aleatório para escolher um nome da lista
    int indice = rand() % (sizeof(nomes) / sizeof(nomes[0]));
    // Aloca memória para o nome
    char* nome = strdup(nomes[indice]);
    return nome;
}
char* gerarCPF() {
    char cpf[15];
    // Gera números aleatórios para o CPF
    sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
    // Aloca memória para o CPF
    char* resultado = strdup(cpf);
    return resultado;
}
int gerarIdade() {
  return rand() % 100;
}
Paciente *gerarPaciente(register int ID) {
  Paciente *paciente = (Paciente *)malloc(sizeof(Paciente));
  if (paciente == NULL) {
    fprintf(stderr, "Erro ao alocar memória para Paciente\n");
    exit(EXIT_FAILURE);
  }
  // Gera aleatoriamente o nome, CPF e idade
  strcpy(paciente->nome, gerarNome());
  strcpy(paciente->cpf, gerarCPF());
  paciente->idade = gerarIdade();
  paciente->id = ID;
  paciente->doença[1] = prob_pat();
  paciente->entrada = ID;
  return paciente;
}
void print_p(Paciente *p){
  printf("Nome: %-9s ", p->nome);
  printf("CPF: %-15s ", p->cpf);
  printf("Idade: %-3d ", p->idade);
  printf("Id: %-5d ", p->id);
  printf("Gravidade: %-1.d\n", p->doença[1]);
}
void appendf(Lista *list, Paciente *p){
  Node *newNode = (Node*)malloc(sizeof(Node));
  int *aux = (int*)malloc(sizeof(int));
  *aux = p->id;
  newNode->data = aux;
  newNode->prev = list->Last;
  newNode->next = NULL;
  if(list->size != 0) {
    list->Last->next = newNode;
  }
  else{
    list->First = newNode;
  }
  list->Last = newNode;
  list->size++;
}
void swap(Node *a, Node *b) {
    if (a == NULL || b == NULL || a == b) {
        return;  
    }
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
}
void ordena_fila(Lista *list, Lista *fila, Paciente *k) {
    Node *aux1 = list->First;
    Node *aux2 = fila->First;

    while (aux1 != NULL) {
        Paciente *p = (Paciente*)aux1->data;
        if (k->doença[1] > p->doença[1]) {
            Node *temp = aux2;
            while (temp != NULL) {
                Paciente *paciente_na_fila = (Paciente*)temp->data;
                if (paciente_na_fila->id == p->id) {
                    swap(aux1, temp);
                    return;
                }
                temp = temp->next;
            }
        }
        aux1 = aux1->next;
        aux2 = aux2->next;
    }
}
void insere_ordenado(Fila *fila, Paciente *novo_paciente) {
    Node *novo_node = (Node *)malloc(sizeof(Node));
    if (novo_node == NULL) {
        fprintf(stderr, "Erro ao alocar memória para novo_node\n");
        exit(EXIT_FAILURE);
    }
    novo_node->data = novo_paciente;
    novo_node->prev = NULL;
    novo_node->next = NULL;
    Node *atual = fila->Front;
    // Procura a posição correta para inserir o novo paciente
    while (atual != NULL && novo_paciente->doença[1] >= ((Paciente *)atual->data)->doença[1]){
        atual = atual->next;
    }
    // Insere o novo_node na posição correta
    if(atual != NULL){
        Node *anterior = atual->prev;
        novo_node->next = atual;
        novo_node->prev = anterior;
        anterior->next = novo_node;
        atual->prev = novo_node;
    } 
    else{
        // Se chegou ao final da fila, insere no final
        Node *ultimo = fila->Rear;
        if (ultimo == NULL) {
            // Se a fila estiver vazia, ajusta o Front
            fila->Front = novo_node;
        } 
        else {
            novo_node->prev = ultimo;
            ultimo->next = novo_node;
        }
        fila->Rear = novo_node;  // Atualiza o Rear
    }
    fila->size++;
}
//coloca na fila do raiox
void fila_atendimento_raiox(Fila *fila_SE, Fila *raiox, Hospital *h, int j){
  for (register int i = 0;i<5;i++){
    if(h->raioX[i][0] == 0){
      h->raioX[i][0] = 1;
      h->raioX[i][1] = prob_raiox();
      Paciente *aux = (Paciente*)fila_SE->Front->data;
      aux->entrada_raiox = j;
      remove_data_f(fila_SE);
      insere_ordenado(raiox, aux);
      return;
    }
  }
}
void append_consulta(Lista *l, Lista *j){
  Node *k = (Node *)malloc(sizeof(Node));
  k = j->First;
  append(l, k);
  freeLista(j);
}
void fila_atendimento_laudo(Fila *fila_raiox, Fila *laudo, Hospital *h, int j){
  for (register int i = 0;i<3;i++){
    if(h->laudo[i][0] == 0){
      h->laudo[i][0] = 1;
      h->raioX[i][1] = prob_laudo();
      Paciente *aux = (Paciente*)fila_raiox->Front->data;
      aux->entrada_laudo = j;
      remove_data_f(fila_raiox);
      insere_ordenado(laudo, aux);
      return;
    }
  }
}

void atualiza_tempo_raiox(Hospital *h){
  for(register int i = 0;i<5;i++){
    if(h->raioX[i][1] != 0){
      h->raioX[i][1]--;
    }
  }
}
void atualiza_tempo_laudo(Hospital *h){
  for(register int i = 0;i<3;i++){
    if(h->laudo[i][1] != 0){
      h->laudo[i][1]--;
    }
  }
}
void atualiza_raiox(Hospital *h){
  for(register int i = 0;i<5;i++){
    if(h->raioX[i][1] == 0){
      h->raioX[i][0] == 0;
    }
  }
}
void atualiza_laudo(Hospital *h){
  for(register int i = 0;i<3;i++){
    if(h->laudo[i][1] == 0){
      h->laudo[i][0] == 0;
    }
  }
}
int verifica_raiox(Hospital *h){
  for(register int i = 0;i<5;i++){
    if(h->raioX[i][1] == 0){
      return 1;
    }
  }
  return 0;
}
int verifica_laudo(Hospital *h){
  for(register int i = 0;i<3;i++){
    if(h->laudo[i][1] == 0){
      return 1;
    }
  }
  return 0;
}
void atualiza_lista_controle(Fila *fila_laudo, Lista *lista_controle){
  Node *aux = fila_laudo->Front;
  for(Node *j = lista_controle->First;j != NULL; j = j->next){
    if(((Paciente*)j->data)->id == ((Paciente*)aux->data)->id){
      swap(j,aux); //troca apenas os dados
      remove_data_f(fila_laudo);//tira da fila, já foi atendido
      return;
    }
  }
}
float media_laudo(Lista *controle){
  float k = 0.0;
  int count = 0;
  Node *z = controle->First;

  for (register int i = 0; i < controle->size; i++) {
      if (((Paciente *)z->data)->saida != 0) {
        // Converte para segundos e calcula a diferença
        k += ((Paciente *)z->data)->saida, ((Paciente *)z->data)->entrada;
        count++;
      }
      z = z->next;
  }
  // Evita divisão por zero
  if (count != 0) {
    return k / count;
  } 
  else {
    // Retorna um valor indicando que não há dados suficientes para calcular a média
    return 0.0;
  }
  // Retorna um valor indicando que a média não foi calculada nesta chamada
  return 0.0;
}
float media_patologias(Lista *controle, float registro_pat[][2]){
  float k = 0.0;
  int count_sn = 0;
  int count_b = 0;
  int count_p = 0;
  int count_ff = 0;
  int count_a = 0;
  Node *z = controle->First;

  for (register int i = 0; i < controle->size; i++) {
      if (((Paciente *)z->data)->saida != 0) {
        if(((Paciente *)z->data)->doença[0] == 1){
          // Converte para segundos e calcula a diferença
          k += ((Paciente *)z->data)->saida - ((Paciente *)z->data)->entrada;
          count_sn++;
        }
        else if(((Paciente *)z->data)->doença[0] == 2){
          // Converte para segundos e calcula a diferença
          k += ((Paciente *)z->data)->saida - ((Paciente *)z->data)->entrada;
          count_b++;
        }
        else if(((Paciente *)z->data)->doença[0] == 3){
          // Converte para segundos e calcula a diferença
          k += ((Paciente *)z->data)->saida - ((Paciente *)z->data)->entrada;
          count_p++;
        }
        else if(((Paciente *)z->data)->doença[0] == 4){
          // Converte para segundos e calcula a diferença
          k += ((Paciente *)z->data)->saida - ((Paciente *)z->data)->entrada;
          count_ff++;
        }
        else if(((Paciente *)z->data)->doença[0] == 5){
          // Converte para segundos e calcula a diferença
          k += ((Paciente *)z->data)->saida - ((Paciente *)z->data)->entrada;
          count_a++;
        }
      }
      z = z->next;
  }
  // Evita divisão por zero
  if (count_sn != 0){
    registro_pat[0][1] =  k / count_sn;
  } 
  if (count_b != 0){
    registro_pat[1][1] =  k / count_sn;
  }
  if (count_p != 0){
    registro_pat[2][1] =  k / count_sn;
  }
  if (count_ff != 0){
    registro_pat[3][1] =  k / count_sn;
  }
  if (count_a != 0){
    registro_pat[4][1] =  k / count_sn;
  }
  // Retorna um valor indicando que a média não foi calculada nesta chamada
  return 0.0;
}
int exames_pos_tempo(Lista *controle){
  float k = 0.0;
  int count = 0;
  Node *z = controle->First;

  for (register int i = 0; i < controle->size; i++) {
      if (((Paciente *)z->data)->saida != 0) {
        k = ((Paciente *)z->data)->saida, ((Paciente *)z->data)->entrada;
        if(k>7200){
          count++;
        }
      }
      z = z->next;
  }
  // Evita divisão por zero
  if (count != 0) {
    return count;
  } 
  
  // Retorna um valor indicando que não não há gargalos na chamada
  return 0.0;
} 
/*
void escreve_log(Lista *eventos, const char *filename){
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
      printf("Erro: não foi possível criar o arquivo %s.\n", filename);
      exit(EXIT_FAILURE);
  }
  fprintf(file, "chegada: %f inicio/fim do raio-x: %f/%f inicio/fim do laudo: %f/%f", chegada(), inicio_raiox(),fim_raiox(), inicio_laudo(),fim_laudo());
  fclose(file);
}*/

void printa_metrica(Lista *controle, float registro_pat[][2]){
  printf("Tempo médio do laudo: %f tempo médio por patologia: %f Exames após o limite de tempo: %d", media_laudo(controle), media_patologias(controle, registro_pat), exames_pos_tempo(controle));
}
