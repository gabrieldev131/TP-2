#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hospital.h"

int main() {
  List *listGeral = cria_lista();
  Fila *Entrada = cria_fila();
  Fila *Raiox = cria_fila();
  Fila *Laudo = cria_fila();
  Hospital *H = cria_hospital();
  srand(time(NULL));
  
  for(int UT = 1;UT<43200;UT++){
    if(gera_pessoa()){  
      Pessoa *paciente = gera_paciente(UT);
      inserir_lista(listGeral, paciente);
      ordenado(Entrada, paciente);
    }
    atualizacao_geral(H, Raiox, Laudo, UT);
    if(verifica_raiox(H)){
      raiox(Entrada, Raiox, H, UT);
    }
    if(verifica_laudo(H)){
      laudo(Raiox, Laudo, H, UT);
    }
    atualiza_tempo(Laudo, listGeral);
    if((UT%10) == 0){
      sleep(1);
      printa_metrica(listGeral, H);
    }
  }
  libera_lista(listGeral);
  libera_fila(Raiox);
  libera_fila(Laudo);
  libera_fila(Entrada);
  libera_hospital(H);
  return 0;
}
