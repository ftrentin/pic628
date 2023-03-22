#include <16F628A.h>
//#device ADC=16
//#device ICD=true

#FUSES NOBROWNOUT               //No brownout reset
#FUSES XT
#FUSES MCLR

//////// Fuses: NOWDT,WDT,PUT,NOPUT,LP,XT,HS,EC_IO,INTRC_IO,INTRC,RC_IO,RC
//////// Fuses: NOMCLR,MCLR,NOBROWNOUT,BROWNOUT,NOLVP,LVP,CPD,NOCPD,PROTECT
//////// Fuses: NOPROTECT

//!   ;    PORTB, 6     BOBINA DIREITA
//!   ;    PORTB, 5     BOBINA ESQUERDA
//!   ;    PORTB, 3     RETORNO E1 >S2
//!   ;    PORTB, 2     RETORNO E2 >S3  
//!   ;    PORTB, 1     BIP
//!   ;    PORTB, 4     RELÉ S4 P/ CONTADOR
//!   ;    PORTB, 7     COMANDO DIREITA
//!   ;    PORTA, 4     COMANDO ESQUERDA
//!   ;    PORTA, 0      OPTO DIREITA
//!   ;    PORTA, 1      OPTO ESQUERDA
//!   

//setup_oscillator(OSC_2MHz); 
#use delay(crystal=4000000)
//#use FIXED_IO( A_outputs=PIN_A1,PIN_A0 )
#use FIXED_IO( B_outputs=PIN_B6,PIN_B5,PIN_B4,PIN_B3,PIN_B2,PIN_B1 )

#define RELE_1   PIN_B3
#define RELE_2   PIN_B2

#define E1   PIN_A0
#define E2   PIN_A1
#define E3   PIN_A2
#define E4   PIN_A3
#define E5   PIN_A4
#define E6   PIN_B7

#define AUX   PIN_B0

#define BUZZER   PIN_B1

#define S1   PIN_B1
#define S2   PIN_B2
#define S3   PIN_B3
#define S4   PIN_B4
#define S5   PIN_B5
#define S6   PIN_B6

#define S8 PIN_B4
#define S9 PIN_B4
#define S10 PIN_B4
#define S11 PIN_B4


#define REPOUSO 0

////////////////
#define MOSTRA_X_H 1
#define MOSTRA_X_AH 2

///////////////////
#define AGUARDA_OPTO_1 3
#define AGUARDA_OPTO_2 4
#define AGUARDA_OPTO_1_menos 13
#define AGUARDA_OPTO_1_mais 14
#define AGUARDA_OPTO_2_menos 15
#define AGUARDA_OPTO_2_mais 16

#define AGUARDA_OPTO_1_N 5
#define AGUARDA_OPTO_2_N 6
///////////////////
#define AGUARDA_CONCLUIR_ACESSO_H 7


#define AGUARDA_OPTO_1_AH 8
#define AGUARDA_OPTO_2_AH 9
#define AGUARDA_OPTO_1_menos_AH 17
#define AGUARDA_OPTO_1_mais_AH 18
#define AGUARDA_OPTO_2_menos_AH 19
#define AGUARDA_OPTO_2_mais_AH 20

#define AGUARDA_OPTO_1_N_AH 10
#define AGUARDA_OPTO_2_N_AH 11
#define AGUARDA_CONCLUIR_ACESSO_AH 12

#define AGUARDA_DEFINIR_SENTIDO 21


