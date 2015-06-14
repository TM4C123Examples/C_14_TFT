


#include "TM4C123.h"                    // Device header
#include "retarget_tm4c.h"
#include "serial_stdio.h"

void delay_ms(int delay);

void TFT_Init();
void TFT_Fill(unsigned short color);

Serial_t USART0_serial = {UART0_getChar, UART0_sendChar}; 
#define BufferSize 80

int main(){
	char buffer[BufferSize];
	int counter=1;
	UART0_init(9600);
	serial_printf(USART0_serial,"\nIngrese comando\n");
	TFT_Init();
	while(1){
		TFT_Fill(2016);
		delay_ms(1000);
		TFT_Fill(63488);
		delay_ms(1000);
	}
}

void delay_ms(int delay){
	delay=delay*1000;
	for(int i=0; i<delay; i++){

	}
}
