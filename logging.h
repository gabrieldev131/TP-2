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
// Função para adicionar um elemento ao final da lista encadeada
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
// Função que remove um valor da fila
void remove_dados_fila(Fila *fila);
// Função para liberar a memória alocada para a fila
void liberaFila(Fila *fila);

/*-----------------------------------------------------------------
                             TAD
-----------------------------------------------------------------*/

Hospital *inicia_Hospital();
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
 // Função para inserir paciente ordenadamente na fila pela gravidade
void insere_ordenado(Fila *lista, Paciente *novo_paciente);
//coloca na fila do raiox
void fila_atendimento_raiox(Fila *fila_SE, Fila *raiox, Hospital *h, int i);
//função que atualiza o tempo para terminar o raio x
void fila_atendimento_laudo(Fila *fila_raiox, Fila *laudo, Hospital *h, int i);
//função que atualiza o tempo para terminar o raio x
void atualiza_tempo_raiox(Hospital *h);
//função que atualiza o tempo para terminar o laudo
void atualiza_tempo_laudo(Hospital *h);
//função que atualiza o raio x caso o tempo seje 0
void atualiza_raiox(Hospital *h, Fila *fila_raiox, int j);
//função que atualiza o laudo caso o tempo seje 0
void atualiza_laudo(Hospital *h, Fila *fila_laudo, int j);
//função que verifica se tem máquina de raio x disponivel
int verifica_raiox(Hospital *h);
//função que verifica se tem médico disponivel e se o paciente já passou no raio x
int verifica_laudo(Hospital *h);
//função que atualiza a contagem de tempo dos pacientes
void atualiza_lista_controle(Fila *fila_laudo, Lista *lista_controle);
//pega a média de tempo para se ter o laudo
float media_laudo(Lista *controle);
//pega a média de tempo para se ter o laudo por patologia
void media_patologias(Lista *controle, Hospital *h);
//função que retorna o número de exames que demoraram mais de 7200U.T
int exames_apos_tempo(Lista *controle, int unidade_de_tempo);
//função que printa as métricas
void printa_metrica(Lista *controle, Hospital *h, int j);
//função que libera a estrutura Hospital
void liberaHospital(Hospital *hospital);
#endif
