/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include "LPTimer.h"
#include "ADC.h"
#include "UART0.h"
#include "PedaldeAceleracionGoKart.h"

void clk_init (void){
// FIRC = 4 MHz. BusClk = 4 MHz
// UART0: FIRC. UART1: BusClk. UART2: BusClk. TPM: FIRC. IIC: BusClk. PIT:
MCG_C1|=(1<<6) + (1<<1);	//MCGOUTCLK : IRCLK. CG: Clock gate, MCGIRCLK enable pag 116
MCG_C2|=1;					//Mux IRCLK : FIRC (4 MHz) pag 116
MCG_SC=0;					//Preescaler FIRC 1:1 pag 116

SIM_CLKDIV1=0;				//OUTDIV4=OUTDIV1= 1:1 pag 116. Busclk 4 MHz
SIM_SOPT2|=15<<24;			//Seleccion MCGIRCLK tanto para UART0 como para TPM

}


int main(void)
{
	clk_init();
	
	ADC0_init();
	UART1_init();
	LPTimer_init();
	StartPedal_init();
	
	while(1);
	return 0;
}
