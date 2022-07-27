#ifndef __HX711_4_H
#define __HX711_4_H

#include "sys.h"

#define HX711_4_SCK  PBout(5) // PB5
#define HX711_4_DOUT PBin(4)  // PB4


extern void Init_4_HX711pin(void);
extern u32 HX711_4_Read(void);
extern void Get_Maopi4(void);
extern void Get_Weight4(void);

extern u32 HX711_Buffer4;
extern u32 Weight_Maopi4;
extern float Weight_Shiwu4;
extern u8 Flag_Error4;
#endif

