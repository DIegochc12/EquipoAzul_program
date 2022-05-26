/*
 * VoltimetroBateriaGoKart.c
 *
 *  Created on: Apr 20, 2021
 *      Author: Alfredo Paz
 */

#include "derivative.h" /* include peripheral declarations */
#include "VoltimetroBateriaGoKart.h"

unsigned char i=0;
unsigned char temp=0;
unsigned char valor_recibido_UART=0;

unsigned char mensaje1[]={"Hola mundo \n\r"};
unsigned char voltaje_ASCII[]={"#.### V\n\r"};

unsigned char valor_ADC;

void UART0_IRGHandler (void){
	if((UART0_S1&(1<<5))==(1<<5)){  //port bandera data ready (RDRF)
		i=UART0_D;
		if(i!=13) temp=temp*10+(i-0x30);
		else{
			valor_recibido_UART=1;
			temp=0;
			//desh intr UART rx
				}
			}
			if ((UART0_S1&(1<<7))==(1<<7))	//por bandera de TDRE 
			{
				UART0_D=voltaje_ASCII[i++];
				if (voltaje_ASCII[i]==0)
				{
					NVIC_ISER=(1<<15)+(1<<28);     //ADC0, LPTimer
					i=0;
				}
			}
}

void ADC0_IRQHandler(){
	unsigned short voltaje_mV;
	
	valor_ADC=ADC0_RA;     //leo el resultado de la conversion y se apaga la bandera
	voltaje_mV=(valor_ADC*3300)/255;
	
	//"itoa"
    voltaje_ASCII[4]=(voltaje_mV%10)+0x30;  //mV
	voltaje_mV=voltaje_mV/10;
	voltaje_ASCII[3]=(voltaje_mV%10)+'0';   //cV
	voltaje_mV/=10;
	voltaje_ASCII[2]=(voltaje_mV%10)+'0';   //dV
	voltaje_ASCII[0]=(voltaje_mV/10)+'0';	//V
	
	NVIC_ISER=(1<<28)+(1<<15)+(1<<12);  //UART0, ADC0, LPTimer
		
}

void LPTimer_IRQHandler(){
	LPTMR0_CSR=(1<<7)+(1<<6)+1;  //Apaga la bandera TCF y mantiene la configuracion
	ADC0_SC1A=(1<<6)+8;          //b6 es AIEN, 8 es el selector de MUX para seleccionar PT
}

