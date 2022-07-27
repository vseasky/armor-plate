#ifndef __HX711_2_H
#define __HX711_2_H

#include "sys.h"

#define HX711_2_SCK  PAout(5)// PA5
#define HX711_2_DOUT PAin(4)// PA4


extern void Init_2_HX711pin(void);
extern u32 HX711_2_Read(void);
extern void Get_Maopi2(void);
extern void Get_Weight2(void);

extern u32 HX711_Buffer2;
extern u32 Weight_Maopi2;
extern float Weight_Shiwu2;
extern u8 Flag_Error2;
#endif

