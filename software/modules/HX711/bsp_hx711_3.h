#ifndef __HX711_3_H
#define __HX711_3_H

#include "sys.h"

#define HX711_3_SCK  PBout(3) // PB3
#define HX711_3_DOUT PAin(15) // PA15


extern void Init_3_HX711pin(void);
extern u32 HX711_3_Read(void);
extern void Get_Maopi3(void);
extern void Get_Weight3(void);

extern u32 HX711_Buffer3;
extern u32 Weight_Maopi3;
extern float Weight_Shiwu3;
extern u8 Flag_Error3;
#endif

