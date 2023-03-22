#include <Principal.h>

//int teste_entradas[8] = { E1, E2, E3, E4, E5, E6, E7, E8}; 

#type default=addressmodname
int tempo_buzzer = 0;
int tempo_RELE_1 = 0;
int tempo_RELE_2 = 0;
int tempo_buzzer2 = 0;

int32 timeOutAcesso = 0;

int32 timeOutAcesso2= 0;
 
int tempo_extra = 0;
int som_burla = 0;
  
int TEM_MEMORIA = 0;
int SENTIDO_E_LIBERADO = 0;
int SENTIDO_S_LIBERADO = 0;

int TEMPO_BUZZER_ =  10;
int TEMPO_RELE = 25;

int8 entrada = 0;
int8 saida = 0;

int ESTADO = 0;
int ESTADO_temp = 0;


#INT_TIMER1
void  TIMER1_isr(void) 
{

}

#INT_TIMER2
void  TIMER2_isr(void) 
{
   //set_timer2(195);
   if (tempo_buzzer == 1)
   {
      tempo_buzzer--;
      output_low(BUZZER);
   }
   else if (tempo_buzzer > 1)
   {
      tempo_buzzer--;
   }
   ///////////////////////////
   if (tempo_RELE_1 == 1)
   {
      tempo_RELE_1--;
      output_low(RELE_1);
      
      if (input_state(S1))
      {
         output_low(S1);
      }
      if (input_state(S3))
      {
         output_low(S3);
      }
      if (!input_state(S2))
      {
         output_high(S2);
      }

      if (!input_state(S4))
      {
         output_high(S4);
      }

   }
   else if (tempo_RELE_1 > 1)
   {
      tempo_RELE_1--;
   }

   ///////////////////////////
   if (tempo_RELE_2 == 1)
   {
      tempo_RELE_2--;
      output_low(RELE_2);
      
      if (input_state(S1))
      {
         output_low(S1);
      }
      if (input_state(S3))
      {
         output_low(S3);
      }
      if (!input_state(S2))
      {
         output_high(S2);
      }

      if (!input_state(S4))
      {
         output_high(S4);
      }
      
   }
   else if (tempo_RELE_2 > 1)
   {
      tempo_RELE_2--;
   }

   if (timeOutAcesso >= 1)
   {
      timeOutAcesso--;
   }

   if (tempo_buzzer2 >= 1)
   {
      tempo_buzzer2--;
   }
   //////////////////////////
   if (tempo_extra >= 1)
   {
      tempo_extra--;
   } 
   //////////////////////////
   //som burla
   /////////////////////////
   if ((ESTADO == MOSTRA_X_AH)||(ESTADO == MOSTRA_X_H)||(ESTADO == AGUARDA_CONCLUIR_ACESSO_AH)||(ESTADO == AGUARDA_CONCLUIR_ACESSO_H))
   {
      if(som_burla < 200)
      {
         som_burla++;
      }
      else
      {
         som_burla = 0;
      }
      
      if ((som_burla > 150)&&(som_burla % 5 == 0))
      {
         if (input_state(BUZZER))
         {
            output_low(BUZZER);
         }
         else
         {
            output_high(BUZZER);
         }
      
      }
   }
   else
   {
      som_burla = 0;
      if (tempo_buzzer == 0)
      {
         output_low(BUZZER);
      }
   }

}

int8 input_pin_state(int16 ccs_pin) 
{ 
    int16 io_port; 
    int8 bitmask; 
    int8 retval; 

    io_port = ccs_pin >> 3;                  // Get the i/o port address      
    bitmask = 1 << (ccs_pin & 7);            // get mask 
    retval = (*io_port & bitmask) ? 1 : 0;   // Read pin (ret. 0 or 1) 

    return retval; 
} 

short anti_ruido_alto(int16 PINO, int32 debouncing ) //NA - Retorna true quando a entrada ficar ATIVA ao menos o tempo de debounce
{
   short flag1=false;
   int32 cont1;
   cont1 = debouncing;
   while(cont1--)
   {
      if(input_pin_state(PINO))
         flag1=true;
      else
         return(false);     
      delay_ms(1);
   }
   //restart_wdt();
   return(flag1);
}

short anti_ruido_baixo(int16 PINO, int32 debouncing ) //NA - Retorna true quando a entrada ficar ATIVA ao menos o tempo de debounce
{
   short flag1=false;
   int32 cont1;
   cont1 = debouncing;
   while(cont1--)
   {
      if(!input_pin_state(PINO))
         flag1=true;
      else
         return(false);     
      delay_ms(1);
   }
   //restart_wdt();
   return(flag1);
}

void verifica_saidas(int padrao)
{
   if (padrao == 0)
   {
         if (input_state(S1))
         {
            output_low(S1);
         }
   
         if (!input_state(S2))
         {
            output_high(S2);
         }
      
         if (input_state(S3))
         {
            output_low(S3);
         }
         
         if (!input_state(S4))
         {
            output_high(S4);
         }


      
   }
   else if(padrao == 1)
   {
      if (!input_state(S1))
      {
         output_high(S1);
      }
      if (input_state(S2))
      {
         output_low(S2);
      }
      
      if (input_state(S3))
      {
         output_low(S3);
      }

      if (!input_state(S4))
      {
         output_high(S4);
      }
   }
   else if(padrao == 2)
   {
      if (input_state(S1))
      {
         output_low(S1);
      }
      if (!input_state(S2))
      {
         output_high(S2);
      }
      
      if (!input_state(S3))
      {
         output_high(S3);
      }

      if (input_state(S4))
      {
         output_low(S4);
      }
   }
   else if(padrao == 3)
   {
      if (!input_state(S1))
      {
         output_high(S1);
      }
      if (input_state(S2))
      {
         output_low(S2);
      }
      
      if (!input_state(S3))
      {
         output_high(S3);
      }

      if (input_state(S4))
      {
         output_low(S4);
      }
   }
}

void configura_tempo(int32 debouncing)
{
   short flag1=false;
   int32 cont1;
   cont1 = debouncing;
   
   int segundos = 0;
   while(cont1-- > 0)
   {
      if(input_state(AUX))
      {
         flag1=true;
      }
      else
      {
         return;
      }
      delay_ms(1);
      //restart_wdt();
   }


   while(input(AUX))
   {
      if (tempo_extra == 2)
      {
         output_high(BUZZER);
      }
      else if (tempo_extra == 0)
      {
         output_low(BUZZER);
         segundos++;
         tempo_extra = 41;
      }
      //restart_wdt();
   }
   if (segundos == 0)
   {
      segundos = 1;
   }
   write_eeprom(107, segundos);
   timeOutAcesso2 = segundos;
   timeOutAcesso2 *= 40;
   //restart_wdt();
}

#SEPARATE void burla(int Lado)
{
   if (Lado == 1)
   {
            if ((anti_ruido_alto(E5,5)) && (entrada == 0)&& (SENTIDO_E_LIBERADO == 0))
            {
               entrada = 1;
               saida = 0;
               if (TEM_MEMORIA == 1)
               {
                  timeOutAcesso = timeOutAcesso2;
               }
               ESTADO_temp = REPOUSO;
               ESTADO = AGUARDA_OPTO_2;
               output_high(BUZZER);
               if (anti_ruido_alto(E6,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(1);
               }
               tempo_buzzer = TEMPO_BUZZER_;
               output_low(S9);
               output_low(S5);

            }
            else if ((anti_ruido_alto(E6,5)) && (input(E2)) && (saida == 0)&& (SENTIDO_S_LIBERADO == 0))
            {
               saida = 1;
               entrada = 0;
               if (TEM_MEMORIA == 1)
               {
                  timeOutAcesso = timeOutAcesso2;
               }
               output_high(BUZZER);
               if (anti_ruido_alto(E6,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(2);         
               }
               tempo_buzzer = TEMPO_BUZZER_;
               ESTADO = AGUARDA_OPTO_2_AH;
               
            }
            else if ((anti_ruido_alto(E6,5)) && (saida == 0)&& (SENTIDO_S_LIBERADO == 0))
            {
               if (anti_ruido_alto(E5,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(2);         
               }
            }
   }
   else
   {
            if ((anti_ruido_alto(E5,5))  && (input(E1)) && (entrada == 0)&& (SENTIDO_E_LIBERADO == 0))
            {
               entrada = 1;
               saida = 0;
               if (TEM_MEMORIA == 1)
               {
                  timeOutAcesso = timeOutAcesso2;
               }
               ESTADO_temp = REPOUSO;
               ESTADO = AGUARDA_OPTO_2;
               output_high(BUZZER);
               if (anti_ruido_alto(E6,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(1);         
               }
               tempo_buzzer = TEMPO_BUZZER_;

            }
            else if ((anti_ruido_alto(E5,5))  && (input(E1)) && (entrada == 0)&& (SENTIDO_E_LIBERADO == 0))
            {
               if (anti_ruido_alto(E6,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(1);
               }
            }
            else if ((anti_ruido_alto(E6,5)) && (saida == 0)&& (SENTIDO_S_LIBERADO == 0))
            {
               saida = 1;
               entrada = 0;

               if (TEM_MEMORIA == 1)
               {
                  timeOutAcesso = timeOutAcesso2;
               }
               output_high(BUZZER);
               if (anti_ruido_alto(E5,5)){
                  verifica_saidas(3);         
               }
               else {
                  verifica_saidas(2);         
               }
               tempo_buzzer = TEMPO_BUZZER_;
               ESTADO = AGUARDA_OPTO_2_AH;
               output_low(S10);
               output_low(S5);

            }

   }
}



#SEPARATE void principal_ambos()
{
   switch (ESTADO)
   {
         case AGUARDA_DEFINIR_SENTIDO:
            
            if(!input(E1))
            {
               ESTADO = AGUARDA_OPTO_2;
               verifica_saidas(3);
            }
            if(!input(E2))
            {
               ESTADO = AGUARDA_OPTO_2_AH;
               verifica_saidas(3);
            }
            
            if(  ((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||
                  ((anti_ruido_baixo(E5,5)) && (anti_ruido_baixo(E6,5))&&(TEM_MEMORIA == 0))
            )
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;
            }
            else if((anti_ruido_alto(E5,5)) && (anti_ruido_baixo(E6,5)))
            {
               ESTADO = AGUARDA_OPTO_2;
               verifica_saidas(3);
            }
            else if((anti_ruido_baixo(E5,5)) && (anti_ruido_alto(E6,5)))
            {
               ESTADO = AGUARDA_OPTO_2_AH;
               verifica_saidas(3);
            }
         break;
            
         case MOSTRA_X_H:
         
            if (!input(E1))
            {
               if (!input_state(S9))
               {
                  output_high(S9);
                  output_low(S10);
               }
               if (!input_state(S5))
               {
                  output_high(S5);
               }
            }
            else
            {
               ESTADO = ESTADO_temp;
               output_low(S9);
               output_low(S5);
            }
            
            burla(1);
            
            
         break;

         case MOSTRA_X_AH:
         
            if(!input(E2))
            {
               if (!input_state(S10))
               {
                  output_high(S10);
                  output_low(S9);
               }
               if (!input_state(S5))
               {
                  output_high(S5);
               }
            }
            else
            {
               ESTADO = ESTADO_temp;
               output_low(S10);
               output_low(S5);
            }
             burla(2);
         
         break;

        
         //# liberação horario
         case AGUARDA_OPTO_1:
            
            if (!input(E1))
            {
               ESTADO = AGUARDA_OPTO_2;
               
            }
            else if(!input(E2))
            {
               if (saida == 0){
                  output_high(S10);
                  output_low(S9);
                  ESTADO_temp = ESTADO;
                  ESTADO = MOSTRA_X_AH;
               }
               else {
                  ESTADO = AGUARDA_DEFINIR_SENTIDO;
               }
            }
            
            else if((TEM_MEMORIA == 0) && (!input(E5)) ) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;
            }
            else if (((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||((SENTIDO_E_LIBERADO == 1) ))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;
            }
            else if(anti_ruido_alto(E6,5)) //sen memoria
            {
               ESTADO = AGUARDA_DEFINIR_SENTIDO;
               saida = 1;
               verifica_saidas(3);
            }
            
         break;
         
         case AGUARDA_OPTO_2:
            if (anti_ruido_baixo(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_1_N;
            }
            else if(anti_ruido_alto(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_1;
            }
            
            else if((TEM_MEMORIA == 0) && (!input(E5)) && (SENTIDO_E_LIBERADO == 0)) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
            else if ( ((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||((timeOutAcesso == 0) && (SENTIDO_E_LIBERADO == 1) ))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
        
         break;

         case AGUARDA_OPTO_1_N:

            if (anti_ruido_alto(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               //ESTADO = AGUARDA_OPTO_1_menos; // ERA AGUARDA_OPTO_2_N;
               ESTADO = AGUARDA_OPTO_2_N;
            }
            else if (anti_ruido_alto(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               // era ESTADO = AGUARDA_OPTO_2;
               // output_low(S10);
                  output_high(S10);
                  output_low(S9);
                  ESTADO_temp = ESTADO;
                  ESTADO = MOSTRA_X_AH;
            }
            
            else if((TEM_MEMORIA == 0) && (!input(E5)) &&(SENTIDO_E_LIBERADO == 0)) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
            else if (((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||((timeOutAcesso == 0) && (SENTIDO_E_LIBERADO == 1) ))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
        
         break;
         
         case AGUARDA_OPTO_2_N:
         
            if(anti_ruido_alto(E1, 4) && anti_ruido_alto(E2, 4))
            {
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);
            }
            else if (anti_ruido_baixo(E1, 4))
            {
               output_high(S9);
               output_low(S10);
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);            
            }
         
         break;
         
         case AGUARDA_OPTO_1_menos:
            if(anti_ruido_baixo(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_1_mais;
            }
            else if(anti_ruido_alto(E1, 4) && anti_ruido_alto(E2, 4))
            {
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);
            }
            
         break;

         case AGUARDA_OPTO_1_mais:
            if(anti_ruido_baixo(E1, 4) && anti_ruido_alto(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_2_menos;
            }
            else if(anti_ruido_alto(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               output_high(S9);
               output_low(S10);
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);            
            }
            
         break;
         
         case AGUARDA_OPTO_2_menos:
            if(anti_ruido_baixo(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_2_mais;
            }
            else if(anti_ruido_alto(E1, 4))
            {
               output_high(S9);
               output_low(S10);
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);            
            }
         break;

         case AGUARDA_OPTO_2_mais:
            if(anti_ruido_alto(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_2_N;
            }
            else if(anti_ruido_baixo(E1, 4) && anti_ruido_alto(E2, 4))
            {
               output_high(S9);
               output_low(S10);
               tempo_RELE_1 = TEMPO_RELE;
               output_high(RELE_1);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_H;
               delay_ms(2);            
            }
         break;
         
         case AGUARDA_CONCLUIR_ACESSO_H:
         
            if( (!input(E1)) && (!input_state(S9)))
            {
               output_high(S9);
               output_low(S10);
               //ESTADO_temp = AGUARDA_CONCLUIR_ACESSO_H;
               //ESTADO = MOSTRA_X_H;   
            }
            else if((!input(E2)) && (!input_state(S10)) )
            {
               output_high(S10);
               output_low(S9);
               //ESTADO_temp = AGUARDA_CONCLUIR_ACESSO_H;
               //ESTADO = MOSTRA_X_AH;
            }
            else if((input(E1)) && (input(E2)) && (input_state(S9)))
            {
               output_low(S9);
            }
            else if((input(E1)) && (input(E2)) && (input_state(S10)))
            {
               output_low(S10);
            }
            
            if ((tempo_RELE_1 == 0) && (!input(E5))&& (!input(E6)))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;
            }
         
         break;
         
         default:
            ESTADO = REPOUSO;
            entrada = 0;
            saida = 0;
         break;
   }
}

#SEPARATE void principal_ambos2()
{
   switch (ESTADO)
   {
         ///// Liberação ANTI_HORARIO
         case AGUARDA_OPTO_1_AH:
            
            if (!input(E2))
            {
               ESTADO = AGUARDA_OPTO_2_AH;
            }
            else if(!input(E1))
            {
               if (entrada == 0){
                  output_high(S9);
                  output_low(S10);
                  ESTADO_temp = ESTADO;
                  ESTADO = MOSTRA_X_H;
               }
               else {
                  ESTADO = AGUARDA_DEFINIR_SENTIDO;
               }
            }
            
            else if((TEM_MEMORIA == 0) && (!input(E6))  ) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
            else if (((timeOutAcesso == 0) && (TEM_MEMORIA == 1)) || (SENTIDO_S_LIBERADO == 1)) 
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;
            }
            else if(anti_ruido_alto(E5,5)) //sen memoria
            {
               ESTADO = AGUARDA_DEFINIR_SENTIDO;
               entrada = 1;
               verifica_saidas(3);
            }
         break;
         
         case AGUARDA_OPTO_2_AH:
            if (anti_ruido_baixo(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_1_N_AH;
            }
            else if(anti_ruido_alto(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_1_AH;
            }
            
            else if((TEM_MEMORIA == 0) && (!input(E6)) && (SENTIDO_S_LIBERADO == 0)) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
            else if (((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||((timeOutAcesso == 0) && (SENTIDO_S_LIBERADO == 1) ))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
        
         break;

         case AGUARDA_OPTO_1_menos_AH:
            if(anti_ruido_baixo(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_1_mais_AH;
            }
            else if(anti_ruido_alto(E1, 4) && anti_ruido_alto(E2, 4))
            {
               ESTADO = AGUARDA_OPTO_2_N_AH;
            }
            
         break;

         case AGUARDA_OPTO_1_mais_AH:
            if(anti_ruido_baixo(E2, 4) && anti_ruido_alto(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_2_menos_AH;
            }
            else if(anti_ruido_alto(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               output_high(S10);
               output_low(S9);
               tempo_RELE_2 = TEMPO_RELE;
               output_high(RELE_2);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_AH;
               delay_ms(2);           
            }
            
         break;
         
         case AGUARDA_OPTO_2_menos_AH:
            if(anti_ruido_baixo(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_2_mais_AH;
            }
            else if(anti_ruido_alto(E2, 4))
            {
               output_high(S10);
               output_low(S9);
               tempo_RELE_2 = TEMPO_RELE;
               output_high(RELE_2);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_AH;
               delay_ms(2);           
            }
         break;

         case AGUARDA_OPTO_2_mais_AH:
            if(anti_ruido_alto(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               ESTADO = AGUARDA_OPTO_2_N_AH;
            }
            else if(anti_ruido_baixo(E2, 4) && anti_ruido_alto(E1, 4))
            {
               output_high(S10);
               output_low(S9);
               tempo_RELE_2 = TEMPO_RELE;
               output_high(RELE_2);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_AH;
               delay_ms(2);           
            }
         break;

     
     
         case AGUARDA_OPTO_1_N_AH:

            if (anti_ruido_alto(E2, 4) && anti_ruido_baixo(E1, 4))
            {
               //ESTADO = AGUARDA_OPTO_1_menos_AH; //AGUARDA_OPTO_2_N_AH;
               ESTADO = AGUARDA_OPTO_2_N_AH;
            }
            else if (anti_ruido_alto(E1, 4) && anti_ruido_baixo(E2, 4))
            {
               //era ESTADO = AGUARDA_OPTO_2_AH;
               // output_low(S9);
               output_high(S9);
               output_low(S10);
               ESTADO_temp = ESTADO;
               ESTADO = MOSTRA_X_H;

            }
            
            else if((TEM_MEMORIA == 0) && (!input(E6)) && (SENTIDO_S_LIBERADO == 0) ) //sen memoria
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
            else if (((timeOutAcesso == 0) && (TEM_MEMORIA == 1) )||((timeOutAcesso == 0) && (SENTIDO_S_LIBERADO == 1) ))
            {
               ESTADO = REPOUSO;
               entrada = 0;
               saida = 0;

            }
        
         break;
         
         case AGUARDA_OPTO_2_N_AH:
         
            if(anti_ruido_alto(E2, 4) && anti_ruido_alto(E1, 4))
            {
               tempo_RELE_2 = TEMPO_RELE;
               output_high(RELE_2);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_AH;
               delay_ms(2);
            }
            else if (anti_ruido_baixo(E2, 4))
            {
               output_high(S10);
               output_low(S9);
               tempo_RELE_2 = TEMPO_RELE;
               output_high(RELE_2);
               verifica_saidas(0);
               ESTADO = AGUARDA_CONCLUIR_ACESSO_AH;
               delay_ms(2);            
            }
         
         break;

         /////////
        
         case AGUARDA_CONCLUIR_ACESSO_AH:
         
         if( (!input(E1)) && (!input_state(S9)))
         {
            output_high(S9);
            output_low(S10);
            //ESTADO_temp = AGUARDA_CONCLUIR_ACESSO_H;
            //ESTADO = MOSTRA_X_H;   
         }
         else if((!input(E2)) && (!input_state(S10)) )
         {
            output_high(S10);
            output_low(S9);
            //ESTADO_temp = AGUARDA_CONCLUIR_ACESSO_H;
            //ESTADO = MOSTRA_X_AH;
         }
         else if( (input(E1)) && (input(E2)) && (input_state(S9)) )
         {
            output_low(S9);
         }
         else if( (input(E1)) && (input(E2)) && (input_state(S10)) )
         {
            output_low(S10);
         }
         
         if ((tempo_RELE_2 == 0) && (!input(E5))&& (!input(E6)))
         {
            ESTADO = REPOUSO;
            entrada = 0;
            saida = 0;
         }
         
         break;
   }
}

#SEPARATE void rotina_principal()
{
   while (TRUE)
   {
   
      delay_ms(3); // deboucing;
      //restart_wdt();
      principal_ambos();
      principal_ambos2();
      
      switch (ESTADO)
      {
               case REPOUSO:
               
               verifica_saidas(0); 
               
               if ((!input(E1)))
               {
                  if ( (input(E2)) && (SENTIDO_E_LIBERADO == 1))
                  {
                     ESTADO_temp = REPOUSO;
                     ESTADO = AGUARDA_OPTO_2;
                     //output_high(BUZZER);
                     verifica_saidas(1);   
                     timeOutAcesso = timeOutAcesso2;
                     entrada = 1;
                     saida = 0;
                     
                  }
                  else
                  {
                     ESTADO_temp = REPOUSO;
                     ESTADO = MOSTRA_X_H;
                     output_high(S9);
                     output_low(S10);
                  }
               }
               else if (!input(E2))
               {
                  if ( (input(E1)) && (SENTIDO_S_LIBERADO == 1))
                  {
                     ESTADO_temp = REPOUSO;
                     ESTADO = AGUARDA_OPTO_2_AH;
                     verifica_saidas(2);   
                     timeOutAcesso = timeOutAcesso2;
                     entrada = 0;
                     saida = 1;
                     
                  }
                  else
                  {
                     ESTADO_temp = REPOUSO;
                     ESTADO = MOSTRA_X_AH;
                     output_high(S10);
                     output_low(S9);
                  }
                  
               }
               else if (input(E1)&&input(E2)&&input_state(S9))
               {
                     output_low(S9);
                     output_low(S5);
               }
               else if (input(E1)&&input(E2)&&input_state(S10))
               {
                     output_low(S10);
                     output_low(S5);
               }
               
               //COMANDO LIBERACAO H
               if ((anti_ruido_alto(E5,5)) && (SENTIDO_E_LIBERADO == 0))
               {
                  entrada = 1;   
                  delay_ms(10);
               }
               
               if ((anti_ruido_alto(E6,5))&& (SENTIDO_S_LIBERADO == 0))
               {
                  saida = 1;   
               }
               
               if((entrada == 1) && (saida == 0))
               {
                  if (TEM_MEMORIA == 1)
                  {
                     timeOutAcesso = timeOutAcesso2;
                  }
                  ESTADO_temp = REPOUSO;
                  ESTADO = AGUARDA_OPTO_1;
                  if (SENTIDO_E_LIBERADO == 0)
                     output_high(BUZZER);
                  verifica_saidas(1);         
                  tempo_buzzer = TEMPO_BUZZER_;
                  
               }
               else if( (entrada == 0) && (saida == 1))
               {
                  if (TEM_MEMORIA == 1)
                  {
                     timeOutAcesso = timeOutAcesso2;
                  }
                  ESTADO_temp = REPOUSO;
                  ESTADO = AGUARDA_OPTO_1_AH;
                  if (SENTIDO_S_LIBERADO == 0)
                    output_high(BUZZER);
                  verifica_saidas(2);         
                  tempo_buzzer = TEMPO_BUZZER_;
                  
               }
               else if((entrada == 1) && (saida == 1))
               {
                  if (TEM_MEMORIA == 1)
                  {
                     timeOutAcesso = timeOutAcesso2;
                  }
                  ESTADO_temp = REPOUSO;
                  ESTADO = AGUARDA_DEFINIR_SENTIDO;
                  output_high(BUZZER);
                  verifica_saidas(3);         
                  tempo_buzzer = TEMPO_BUZZER_;
               }
               
            //////////////////
            configura_tempo(5000);
         break;
         

      }
      
   }
}

#SEPARATE void setup()
{
   int teste_saidas[12] =  { S1, S2, S3, S4, S5, S6, S9, S10, RELE_1, RELE_2}; 

   int i, valor_eprom; 
   int tempi;
   
   for (i = 0; i<= 11; i++)
   {
      output_low(teste_saidas[i]);
   }
   
   valor_eprom = read_eeprom(7);
   if (valor_eprom == 0xFF)
   {
      write_eeprom(7, 0);   
   }
   
   if (anti_ruido_alto(AUX,200))
   {
      valor_eprom = read_eeprom(7);
      
      if (valor_eprom == 0)
      {
         write_eeprom(7, 1);   
      }
      else 
      {
         write_eeprom(7, 0);
      }
   
   }
   
  TEM_MEMORIA = read_eeprom(7);
  
  
  tempi = read_eeprom(17);
   
  if ((tempi == 0)||(tempi == 0xFF))
  {
    write_eeprom(107, 15);
    tempi = 15;
  }
   
  timeOutAcesso2 = (tempi);
  timeOutAcesso2 *= 40;
  
  ////////////
  //restart_wdt();
   if (TEM_MEMORIA == 0)
   {
      output_high(BUZZER);
      delay_ms(300); // Rotina de Delay com Restart do WDT
      output_low(BUZZER);
   }
   else 
   {
      TEM_MEMORIA = 1;
      output_high(BUZZER);
      delay_ms(300); // Rotina de Delay com Restart do WDT
      output_low(BUZZER);
      delay_ms(300); // Rotina de Delay com Restart do WDT
      output_high(BUZZER);
      delay_ms(300); // Rotina de Delay com Restart do WDT
      output_low(BUZZER);
   }
   
   //restart_wdt();
   if (anti_ruido_baixo(E3, 20))
   {
      SENTIDO_E_LIBERADO = 1;
   }
   if (anti_ruido_baixo(E4, 20))
   {
      SENTIDO_S_LIBERADO = 1;
   }
  
  
  if ((SENTIDO_E_LIBERADO == 1)&& (SENTIDO_S_LIBERADO == 1))
  {
      verifica_saidas(3);
      while(true)
      {
         //restart_wdt();
      }
  }
}

#SEPARATE void main()
{
   setup_timer_2(T2_DIV_BY_16,97,16);      //1,5 ms overflow, 25,0 ms interrupt
   //setup_wdt(WDT_ON);
   //setup_wdt(WDT_2304MS|WDT_DIV_16);      //~2,3 s reset
   //restart_wdt();
   
   set_timer2(0);
   
   setup();
  
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);

   rotina_principal();
}
