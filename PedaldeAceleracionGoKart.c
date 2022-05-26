/*
 * PedaldeAceleracionGoKart.c
 *
 *  Created on: Apr 17, 2021
 *      Author: Alfredo Paz
 */


#include "derivative.h" /* include peripheral declarations */
#include "PedaldeAceleracionGoKart.h"
#include "ADC.h" //Para obtener valores del archivo ADC.c

unsigned short periodo;
unsigned char duty_cycle;	

void StartPedal_init(void){
	SIM_SCGC4|=(1<<10);                           //Habilitar pin 10 para UART0
	SIM_SCGC5|=(1<<13)+(1<<10)+(1<<9)+1;          //Habilitar puerto B para Pin A5 y A4 (nuestras entradas analogicas),habilitar puertos A y E, y habilitar LPTMR
		                                          //Habilitar Puerto A para PTA1 y PTA2 que son Tx y Rx respectivamente
	SIM_SCGC6|=(1<<31)+(1<<27)+(1<<25)+(1<<23);   //Habilitar clock gate DAC0, ADC0, TPM1 y PIT
	
	NVIC_ISER=(1<<28)+(1<<15);    //Habilitar Interrupciones para FTM1 y ADC0 (IRQ para utilizar 'libreria' I guess) - ID de interrupcion
	
	//Bloque PWM - Cambio de valores duty cycle con lo que lee ADC.c
	PORTA_PCR12=(3<<8);		    //TPM1_CH0	
	TPM1_SC=2;				    //preescaler de 4 y TPM deshabilitado
	TPM1_SC|=(1<<3);		    //Habilitar TPM1, que empieze conteo en base a clock LPTPM
	periodo=1000;			    //número de cuentas necesarias para el periodo, 1 cuenta 1 us
	duty_cycle=((mensaje_tablero[0])*(100/255));  //30% con 1 lógico, 70% con 0 lógico    
	TPM1_C0SC=(1<<6)+(5<<2);	//hab intr, Output compare toggle
	TPM1_C0V=(periodo-(100-duty_cycle)*100);
}


void FTM1_IRQHandler (void){	
	TPM1_C0SC|=(1<<7);		//Apaga bandera
	if (potenciometro_velocidad<75) TPM1_C0V=0;
	else TPM1_C0V+=potenciometro_velocidad;	  //Channel Value equivalente a la resistencia del potenciometro	
}

