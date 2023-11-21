#ifndef LOGGING_H
#define LOGGING_H

typedef struct node Node;
typedef struct lista Lista;
typedef struct fila Fila;
typedef struct paciente Paciente;
typedef struct hospital Hospital;

/*------------------------------------------------------------------
                            Lista
------------------------------------------------------------------*/

// Função para inicializar uma lista encadeada vazia
Lista *init_Lista();
// Função para adicionar um elemento ao final da lista encadeada
void append(Lista *list, void *data);
// função que retorna o tamanho da lista
int size(Lista *list);
// Função que verifica se uma valor está na lista
int is_in(Lista *l, void *val);
// Função que remove um valor da lista
void remove_data(Lista *l, void *val);
// Função para liberar a memória alocada para a lista encadeada
void freeLista(Lista *list);
//função que insere no inicio
void insert(Lista *l, void *data);
//função que printa os elementos da lista
void print_list(Lista *l);
/*------------------------------------------------------------------
                            Fila
------------------------------------------------------------------*/

// Função para inicializar uma fila vazia
Fila *init_Fila();
// Função para adicionar um elemento na fila
void append_f(Fila *fila, void *data);
// Função que verifica se uma valor está na fila
int is_in_f(Fila *f, void *val);
// Função que remove um valor da fila
void remove_data_f(Fila *f);
// Função para liberar a memória alocada para a fila
void freeFila(Fila *fila);
//printa os elementos da fila
void print_fila(Fila *f);

/*-----------------------------------------------------------------
                             TAD
-----------------------------------------------------------------*/

//função que diz se haverá paciente
int prob_pac();
//função que diz a patologia do paciente
int prob_pat();
//pega um número entre 5 e 10, em unidades de tempo para pegar o raio-x
int prob_raiox();
//pega um número entre 10 e 30, em unidades de tempo para pegar o laudo
int prob_laudo();
// Função para gerar aleatoriamente um nome
char *gerarNome();
// Função para gerar aleatoriamente um CPF
char *gerarCPF();
// Função para gerar aleatoriamente uma idade entre 18 e 99 anos
int gerarIdade();
// Função para criar aleatoriamente um paciente
Paciente *gerarPaciente();
//função que printa s informações do paciente/nó
void print_p(Paciente *p);
//insere na frente
void appendf(Lista *list, Paciente *p); //append para fila do id
//função que troca dois nós
void swap(Node *a, Node *b);
//função que ordena a fila de pacientes em ordem crescente de gravidade
void ordena_fila(Lista *list, Lista *fila, Paciente *k);
 // Função para inserir paciente ordenadamente na fila pela gravidade
void insere_ordenado(Fila *lista, Paciente *novo_paciente);
//coloca na fila do raiox
void fila_atendimento_raiox(Fila *fila_SE, Fila *raiox, Hospital *h, int i);
//coloca na fila de laudo
void append_consulta(Lista *l, Lista *j);
//função que atualiza o tempo para terminar o raio x
void fila_atendimento_laudo(Fila *fila_raiox, Fila *laudo, Hospital *h, int i);
//função que atualiza o tempo para terminar o raio x
void atualiza_tempo_raiox(Hospital *h);
//função que atualiza o tempo para terminar o laudo
void atualiza_tempo_laudo(Hospital *h);
//função que atualiza o raio x caso o tempo seje 0
oid atualiza_raiox(Hospital *h);
//função que atualiza o laudo caso o tempo seje 0
void atualiza_laudo(Hospital *h);
//função que verifica se tem máquina de raio x disponivel
int verifica_raiox(Hospital *h);
//função que verifica se tem médico disponivel e se o paciente já passou no raio x
int verifica_laudo(Hospital *h);
//função que atualiza a contagem de tempo dos pacientes
void atualiza_lista_controle(Fila *fila_laudo, Lista *lista_controle)
//pega a média de tempo para se ter o laudo
float media_laudo(Lista *controle);
//pega a média de tempo para se ter o laudo por patologia
float media_patologias(Lista *controle, float registro_pat[][2]);
//função que retorna o número de exames que demoraram mais de 7200U.T
int exames_pos_tempo(Lista *controle);
//função que coloca as informações no arquivo
void escreve_log(Lista *eventos, const char *filename);
//função que printa as métricas
void printa_metrica();
#endif
