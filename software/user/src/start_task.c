#include "start_task.h"

#include "FreeRTOS.h"
#include "task.h"
#include "bsp_led.h"

#include "bsp_usart.h"
#include "bsp_hx711_1.h"
#include "bsp_hx711_2.h"
#include "bsp_hx711_3.h"
#include "bsp_hx711_4.h"

#define INFO_GET_TASK_PRIO 1
#define INFO_GET_TASK_STK_SIZE 128
TaskHandle_t Info_Get_Task_Handler;

#define START_TASK_PRIO 1
#define START_TASK_STK_SIZE 128
TaskHandle_t Start_Task_Handler;

#define Weight_TASK_PRIO 2
#define Weight_TASK_STK_SIZE 128
TaskHandle_t Weight_Task_Handler;

#define LED1_TASK_PRIO 3
#define LED1_TASK_STK_SIZE 128
TaskHandle_t Led1_Task_Handler;

#define OLED_TASK_PRIO 4
#define OLED_TASK_STK_SIZE 128
TaskHandle_t Oled_Task_Handler;

void create_start_task(void)
{
    xTaskCreate((TaskFunction_t)start_task,
                (char*         )"start_task",
                (uint16_t      )START_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )START_TASK_PRIO,
                (TaskHandle_t*)&Start_Task_Handler);
}

#define HIT_WIDGET 50
float all_widget;
const uint16_t timer_max = 500;
uint32_t count = 0;
uint32_t timer = 0;//统计倒计时10s内的次数，即10*1000/20 =500
uint8_t Effective_hit = 0; //有效击打统计，记录每0.1s内的超过次数
uint32_t hit_count = 0;
uint8_t timer_star_it = 0;
void Weight_task(void *pvParameters)
{

    while(1)
        {
            LED0 =~LED0;
//            Get_Weight1();
//            Get_Weight2();
//            Get_Weight3();
//            Get_Weight4();
//            all_widget = (Weight_Shiwu1+Weight_Shiwu2+Weight_Shiwu3+Weight_Shiwu4)/4;

            if(all_widget>HIT_WIDGET)
                {
                    count++;
//				timer_star_it=1;//开始倒计时
//				timer = timer_max;
                }
            if(Effective_hit<=5)
                {
                    Effective_hit++;
                }
            else
                {
                    if(count>3)//认为是一次击打
                        {
                            hit_count++;
                            timer_star_it=1;//开启倒计时
                            timer = timer_max;
                        }
                    Effective_hit=0;
                    count  =0;
                }
            if(timer_star_it==1)
                {
                    if(timer>0)
                        {
                            timer--;
                        }
                    if(timer==0)//倒计时结束,清空计数
                        {
                            if(hit_count==3)
                                {
                                    TIM_SetCompare1(TIM3,256);
                                    TIM_SetCompare2(TIM3,0);
                                    TIM_SetCompare3(TIM3,0);
                                    TIM_SetCompare1(TIM4,256);
                                    TIM_SetCompare2(TIM4,0);
                                    TIM_SetCompare3(TIM4,0);
                                }
                            if(hit_count==4)
                                {
                                    TIM_SetCompare1(TIM3,0);
                                    TIM_SetCompare2(TIM3,256);
                                    TIM_SetCompare3(TIM3,0);
                                    TIM_SetCompare1(TIM4,0);
                                    TIM_SetCompare2(TIM4,256);
                                    TIM_SetCompare3(TIM4,0);
                                }
                            if(hit_count==5)
                                {
                                    TIM_SetCompare1(TIM3,0);
                                    TIM_SetCompare2(TIM3,0);
                                    TIM_SetCompare3(TIM3,256);
                                    TIM_SetCompare1(TIM4,0);
                                    TIM_SetCompare2(TIM4,0);
                                    TIM_SetCompare3(TIM4,256);
                                }

                            timer_star_it = 2;
                            hit_count = 0;
                        }
                }
            vTaskDelay(20);
        }
}


void start_task(void *pvParameters)
{

    taskENTER_CRITICAL();
    xTaskCreate((TaskFunction_t)Weight_task,
                (char*         )"Weight_task",
                (uint16_t      )Weight_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )Weight_TASK_PRIO,
                (TaskHandle_t*)&Weight_Task_Handler);
    vTaskDelete(Start_Task_Handler);
    taskEXIT_CRITICAL();
}

