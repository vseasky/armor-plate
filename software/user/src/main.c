#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "start_task.h"
#include "bsp_led.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_rgb.h"
#include "bsp_hx711_1.h"
#include "bsp_hx711_2.h"
#include "bsp_hx711_3.h"
#include "bsp_hx711_4.h"

RCC_ClocksTypeDef RCC_Clocks;//检验时钟

/*
	RCC_Clocks.SYSCLK_Frequency = 72000000
	RCC_Clocks.PCLK1_Frequency = 36000000
	RCC_Clocks.PCLK2_Frequency  = 72000000
	RCC_Clocks.ADCCLK_Frequency = 36000000
	RCC_Clocks.HCLK_Frequency = 72000000
*/
int main()
{
    RCC_GetClocksFreq(&RCC_Clocks);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);		//JTAG&SWD DISABLE
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	//JTAG DISABLE,SWD ENABLE
    delay_init();
	mx_tim3_init();
	mx_tim4_init();
    mx_led_init();
    mx_uart_init();
    Init_1_HX711pin();
//    Get_Maopi1();//重新获取毛皮重量
//    Init_2_HX711pin();
//    Get_Maopi2();//重新获取毛皮重量
//    Init_3_HX711pin();
//    Get_Maopi3();//重新获取毛皮重量
//    Init_4_HX711pin();
//    Get_Maopi4();//重新获取毛皮重量
	TIM_SetCompare1(TIM3,256);
//	TIM_SetCompare2(TIM3,256);
//	TIM_SetCompare3(TIM3,256);
	TIM_SetCompare1(TIM4,256);
//	TIM_SetCompare2(TIM4,256);
//	TIM_SetCompare3(TIM4,256);
    create_start_task();	//创建开始任务
    vTaskStartScheduler();  //开启任务调度
    while(1) {}
}
