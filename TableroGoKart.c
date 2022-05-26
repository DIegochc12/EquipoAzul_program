/*
 * TableroGoKart.c
 *
 *  Created on: Apr 21, 2021
 *      Author: Alfredo Paz
 */
//UART1 - Comucniacion con tablero via Bluetooth

#include "derivative.h" /* include peripheral declarations */
#include "TableroGoKart.h"
#include "PedaldeAceleracionGoKart.h"
#include "UART0.h"
#include "ADC.h"


void UART1_init (void)//funcion para la UART para enviar toda la info al volante 
{
	SIM_SCGC4|=(1<<11);  // ENCENDER UART1
	SIM_SCGC5|=(1<<11);  //PTC ENABLE
	PORTC_PCR4=(3<<8);   //MUX por A Seleccionamos la función 3 ****** TRANSMITIR
	//PORTC_PCR3=(3<<8);  //MUX por A Seleccionamos la función 3 ****** RECIBIR
	
	UART1_BDH=0;
	UART1_BDL=26;			  //Baud rate de 9600 bps. usando un UART clk de 4 MHz
	UART1_C2|=(1<<7)+(1<<3);  //Hab Intr de Recepción, Hab TE 
	
	NVIC_ISER=(1<<13);		  //hab. interrupcion UART1	

}


void UART1_IRQHandler (void)
{
	if ((UART1_S1 & (1<<7))==(1<<7))   //TDRE (THRE)
	{
		UART1_D=mensaje_tablero[i++];
		if (mensaje_tablero[i]==0)
		{
			UART1_C2=12;			//Desh interrupcion asociada a TDRE
			i=0;
		}
	}	
}


