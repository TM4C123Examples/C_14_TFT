#include "TM4C123.h"                    // Device header
#include "tft_driver.h"
void delay_ms(int delay);

int main(){
	TFT_Init();
	TFT_Fill(Black);
	while(1){
		TFT_Fill(Black);
		delay_ms(1000);
		TFT_Text("Hello",100,0,8,Green,Black);
		TFT_Text("World",100,310,8,Green,Black);
		delay_ms(5000);
	}
}

void delay_ms(int delay){
	delay=delay*8000;
	for(int i=0; i<delay; i++){

	}
}
