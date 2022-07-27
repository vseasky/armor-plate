#ifndef __HX711_1_H
#define __HX711_1_H

#include "sys.h"

#define HX711_1_SCK  PAout(3)// PA3
#define HX711_1_DOUT PAin(2)// PA2


extern void Init_1_HX711pin(void);
extern u32 HX711_1_Read(void);
extern void Get_Maopi1(void);
extern void Get_Weight1(void);

extern u32 HX711_Buffer1;
extern u32 Weight_Maopi1;
extern float Weight_Shiwu1;
extern u8 Flag_Error1;
#endif

