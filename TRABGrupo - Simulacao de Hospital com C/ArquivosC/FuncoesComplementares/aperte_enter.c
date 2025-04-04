#include <stdio.h>
#include "../../CabecalhosC/FuncoesComplementares/aperte_enter.h"

void AperteEnter(){
    while(1){
      while( getchar() != '\n');
      printf("\nAperte ENTER para continuar: ");
      if(getchar() == '\n'){
        break;
      }
      else{
        printf("\nErro!\n");
      }
    }
}
