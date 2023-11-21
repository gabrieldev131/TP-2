#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logging.h"

#ifdef _WIN32 || _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

int main() {
  Lista *lista_controle = init_Lista(); //lista não ordenada
  Fila *fila_SE = init_Fila(); //fila da sala de espera (já ordenada)
  Fila *fila_raiox = init_Fila();
  Fila *fila_laudo = init_Fila();
  Hospital *h;
  int registro_pat[5][1];
  srand(time(NULL));
  for(register int i = 1;i<43201;i++){
    if(i&10 == 0){
      sleep(2);
      printa_metrica(lista_controle, registro_pat);
    }
    if(prob_pac()){  
      Paciente *paciente = gerarPaciente(i);
      append(lista_controle, paciente);
      //coloca já ordenado na fila, por ordem de gravidade da doença
      insere_ordenado(fila_SE, paciente);

    //sequência de verificações para olhar o tempo da consulta e as máquinas desocupadas
    atualiza_tempo_raiox(h);
    atualiza_tempo_laudo(h);
    verifica_raiox(h);
    verifica_laudo(h); 
    if(verica_raiox(h) == 1){
      //se tiver vaga no raiox, entra
      fila_atendimento_raiox(fila_SE, fila_raiox, h, i);
      if(verifica_laudo(h) == 1){
        //depois do raio x, entra pra ver o laudo, se tiver vaga
        fila_atendimento_laudo(fila_raiox, fila_laudo, h, i);
      }
    }
    void atualiza_lista_controle(fila_laudo, lista_controle);
    }
  }
  printf("%d\n", size(lista_controle));
  //print_list(lista_controle);
  //print_fila(fila_SE);
  freeLista(lista_controle);
  freeFila(fila_raiox);
  freeFila(fila_laudo);
  freeFila(fila_SE);
  free(h);
  return 0;
}
