#include "TM4C123.h"                    // Device header
#include "tft_driver.h"
void delay_ms(int delay);

int main(){
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
