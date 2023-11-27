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
Lista *inicia_Lista();

// Função para adicionar um elemento no inicio da lista encadeada
void insere_Lista(Lista *lista, void *dados);

// Função que remove um valor da lista
void remove_dados_lista(Lista *l, void *val);

// Função para liberar a memória alocada para a lista encadeada
void liberaLista(Lista *lista);

/*------------------------------------------------------------------
                            Fila
------------------------------------------------------------------*/

// Função para inicializar uma fila vazia
Fila *inicia_Fila();

//append não foi usado, foi adaptada para uma função mais complexa que já insere ordenadamente chamada "insere_ordenado()" 

// Função que remove um valor da fila
void remove_dados_fila(Fila *fila);

// Função para liberar a memória alocada para a fila
void liberaFila(Fila *fila);

/*-----------------------------------------------------------------
                             TAD
-----------------------------------------------------------------*/

//função para inicializar o hispital
Hospital *inicia_Hospital();

//função que libera a estrutura Hospital
void liberaHospital(Hospital *hospital);

//função que diz se haverá paciente
int probabilidade_paciente();

//função que diz a patologia do paciente
int *probabilidade_patologia();

//pega um número entre 5 e 10, em unidades de tempo para pegar o raio-x
int probabilidade_raiox();

//pega um número entre 10 e 30, em unidades de tempo para pegar o laudo
int probabilidade_laudo();

// Função para gerar aleatoriamente um nome
char *gerarNome();

// Função para gerar aleatoriamente um CPF
char *gerarCPF();

// Função para gerar aleatoriamente uma idade entre 18 e 99 anos
int gerarIdade();

// Função para criar aleatoriamente um paciente
Paciente *gerarPaciente(int ID);

//coloca na fila do raiox
void fila_atendimento_raiox(Fila *fila_SE, Fila *raiox, Hospital *hospital, int unidade_de_tempo);

//função que atualiza o tempo para terminar o raio x
void fila_atendimento_laudo(Fila *fila_raiox, Fila *laudo, Hospital *hospital, int unidade_de_tempo);

//função que atualiza o tempo para terminar o raio x e verifica se o exame terminou
void atualiza_tempo_raiox(Hospital *hospital);

//função que atualiza o tempo para terminar o laudo e verifica se terminou o atendimento
void atualiza_tempo_laudo(Hospital *hospital);

//função que atualiza o tempo de saida do paciente no raio-x e o tira do raio-x
void atualiza_raiox(Hospital *hospital, Fila *fila_raiox, int unidade_de_tempo);

//função que atualiza o tempo de saida do paciente da sala de laudo e o tira da sala de laudo
void atualiza_laudo(Hospital *hospital, Fila *fila_laudo, int unidade_de_tempo);

//função que verifica se tem máquina de raio x disponivel
int verifica_raiox(Hospital *hospital);

//função que verifica se tem médico disponivel e se o paciente já passou no raio x
int verifica_laudo(Hospital *hospital);

//função que atualiza a contagem de tempo dos pacientes
void atualiza_lista_controle(Fila *fila_laudo, Lista *lista_controle);

//pega a média de tempo para se ter o laudo
float media_laudo(Lista *controle);

//pega a média de tempo para se ter o laudo por patologia
void media_patologias(Lista *controle, Hospital *hospital);

//função que retorna o número de exames que demoraram mais de 7200U.T(Unidades de Tempo)
int exames_apos_tempo(Lista *controle);

//função que printa as métricas
void printa_metrica(Lista *controle, Hospital *hospital);

// Função para inserir paciente ordenadamente na fila pela gravidade
void insere_ordenado(Fila *lista, Paciente *novo_paciente);
#endif
