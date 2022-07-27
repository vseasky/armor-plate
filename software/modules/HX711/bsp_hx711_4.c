/************************************************************************************

*************************************************************************************/
#include "bsp_hx711_4.h"
#include "delay.h"

u32 HX711_Buffer4;
u32 Weight_Maopi4;
float Weight_Shiwu4;
u8 Flag_Error4 = 0;
//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue4 106.5
void Init_4_HX711pin(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PF端口时钟
//#define HX711_4_SCK  PBout(5) // PB5
//#define HX711_4_DOUT PBin(4)  // PB4
    //HX711_SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		 // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);			 //根据设定参数初始化GPIOB

    //HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //输入上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	//HX711_SCK
    GPIO_SetBits(GPIOB,GPIO_Pin_5);					//初始化设置为0
}
//****************************************************
//读取HX711
//****************************************************
u32 HX711_4_Read(void)	//增益128
{
    unsigned long count;
    unsigned char i;
    HX711_4_DOUT=1;
    delay_us(5);
    HX711_4_SCK=0;
    count=0;
    while(HX711_4_DOUT);
    for(i=0; i<24; i++)
        {
            HX711_4_SCK=1;
            count=count<<1;
            delay_us(5);
            HX711_4_SCK=0;
            if(HX711_4_DOUT)
                count++;
            delay_us(5);
        }
    HX711_4_SCK=1;
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
    delay_us(5);
    HX711_4_SCK=0;
    return(count);
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi4(void)
{
    Weight_Maopi4 = HX711_4_Read();
}

//****************************************************
//称重
//****************************************************
void Get_Weight4(void)
{
    HX711_Buffer4 = HX711_4_Read();
    if(HX711_Buffer4 > Weight_Maopi4)
        {
            Weight_Shiwu4 = HX711_Buffer4 - Weight_Maopi4;		//获取实物的AD采样数值。
            Weight_Shiwu4 = ((float)Weight_Shiwu4/GapValue4); 	//计算实物的实际重量
            //因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
            //当发现测试出来的重量偏大时，增加该数值。
            //如果测试出来的重量偏小时，减小改数值。
        }
}
