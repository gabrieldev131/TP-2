#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logging.h"

int main(){
  Lista *lista_controle = inicia_Lista(); //lista não ordenada
  Fila *fila_SE = inicia_Fila(); //fila da sala de espera (já ordenada)
  Fila *fila_raiox = inicia_Fila();//fila de quem vai fazer/está fazendo raiox (já ordenado)
  Fila *fila_laudo = inicia_Fila();//fila de quem vai fazer/está fazendo raiox (já ordenado)
  Hospital *hospital = inicia_Hospital();//váriavel que controla os equipamentos e funcionários do hospital
  srand(time(NULL));
  
  for(int Unidade_de_tempo = 1;Unidade_de_tempo<43200;Unidade_de_tempo++){
    if(probabilidade_paciente()){  
      Paciente *paciente = gerarPaciente(Unidade_de_tempo);
      insere_Lista(lista_controle, paciente);

      //coloca já ordenado na fila, por ordem de gravidade da doença
      insere_ordenado(fila_SE, paciente);
    }
    //sequência de verificações para olhar o tempo da consulta e as máquinas desocupadas
    atualiza_tempo_raiox(hospital);
    atualiza_tempo_laudo(hospital);
    atualiza_raiox(hospital, fila_raiox, Unidade_de_tempo);
    atualiza_laudo(hospital, fila_laudo, Unidade_de_tempo);

    if(verifica_raiox(hospital)){
      //se tiver vagas no raiox, entra no raiox
      fila_atendimento_raiox(fila_SE, fila_raiox, hospital, Unidade_de_tempo);
    }
    if(verifica_laudo(hospital)){
      //se tiver feito raiox e o consultório de consulta estiver vazio, entra no consutório
      fila_atendimento_laudo(fila_raiox, fila_laudo, hospital, Unidade_de_tempo);
    }
    //atualiza a lista que controla em que momento o paciente entrou ou saiu de alguma ala do hospital
    atualiza_lista_controle(fila_laudo, lista_controle);
    if((Unidade_de_tempo%10) == 0){
      //função que printam as médias de tempo
      printa_metrica(lista_controle, hospital);
    }
  }

  //liberando memória
  liberaLista(lista_controle);
  liberaFila(fila_raiox);
  liberaFila(fila_laudo);
  liberaFila(fila_SE);
  liberaHospital(hospital);
  return 0;
}
