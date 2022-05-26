/*
 * ADC.c
 *
 *  Created on: Apr 20, 2021
 *      Author: Alfredo Paz
 */


#include "derivative.h" /* include peripheral declarations */
#include "ADC.h"

unsigned char mens1[]={"#.### V \r\n"};
unsigned char i=0;                                        //Toggle entre los canales
unsigned char channels[4]={(1<<6)+8,(1<<6)+9,(1<<6)+12,(1<<6)+13};  //ADC0 - PTB0(Pedal A), PTB1(Pedal F), PTB2(Volante), PTB3(Bateria) entradas analogicas 
unsigned char potenciometro_velocidad;
unsigned char potenciometro_frendao;
unsigned char potenciometro_volante;
unsigned char results[3];

unsigned char mensaje_tablero[3];  //UART0 - Tablero y Antena

void ADC0_init (void){
	SIM_SCGC6|=0x08000000;	   //clk interfaz ADC
	SIM_SCGC5|=(1<<10)+1;      //Habilitar PORT B y LPTMR
	
	
	NVIC_ISER=(1<<28)+(1<<15);  //Interrupciones LPTMR y ADC0
}

void ADC0_IRQHandler (void){
	unsigned short voltaje_mV;
	results[i]=ADC0_RA;      //Lectura
	
	//Canales 
	if(i==0){  //results[0]=canal para pedal de aceleracion
		       //if i=0 entonces dirijimos a channel (1<<6)+8 - PTB0 
		mensaje_tablero[i]=results[i];
	}
	if(i==1){  //results[1]=canal para pedal de frenado
		mensaje_tablero[i]=results[i];
		
	}
	if(i==2){
		mensaje_tablero[i]=results[i];
	}
	
	if(i==3){
		mensaje_tablero[i]=results[i];
	}
	i++;
	if(i==3){
		i=0;
	}
	UART1_C2=(1<<7)+12;			// TEN=REN=1, Hab Intr TDRE
}

