#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

const float THRESHOLD[6] = {1.20, 1.10, 1.44, 1.45, 1.25, 1.44};

float test;
char res = 0;
   	
int main(void)
 { 
	u16 adc_infrared[6];
	float iv;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	Adc_Init();		  		//ADC��ʼ��    
	 
	//char res = 0;
	char newRes = 0;
	int cnt = 0;
	int numOfOne = 0;
	while(1)
	{
		adc_infrared[0] = Get_Adc_Average(ADC_Channel_13, 30);
		adc_infrared[1] = Get_Adc_Average(ADC_Channel_2, 30);
		adc_infrared[2] = Get_Adc_Average(ADC_Channel_3, 30);
		adc_infrared[3] = Get_Adc_Average(ADC_Channel_5, 30);
		adc_infrared[4] = Get_Adc_Average(ADC_Channel_15, 30);
		adc_infrared[5] = Get_Adc_Average(ADC_Channel_7, 30);
		
		newRes = 0;
		numOfOne = 0;
		for(int i = 0; i < 6; i++){
			iv = (float)adc_infrared[i]*(3.3/4096);
			if (i== 1) test = iv;
			if(iv > THRESHOLD[i]){
				newRes = newRes | (0 << i);
				//printf("%d, %d, %f\r\n", i, 0, iv);
			}else{
				newRes = newRes | (1 << i);
				//printf("%d, %d, %f\r\n", i, 1, iv);
				numOfOne++;
			}
		}
		
		if(newRes == res && numOfOne == 3){
			cnt++;
			//printf("cnt: %d\r\n", cnt);
		}else{
			res = newRes;
			cnt = 0;
		}
		
		if(cnt >= 3){
			printf("%c", res);
			LED1 = !LED1;
		}
		
		LED0 = !LED0;
		delay_ms(50);	
	}											    
}	
