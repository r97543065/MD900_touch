#include "stm32f4xx.h"
#include "ff.h"	

uint32_t LoadBmpToRam(uint32_t PSRamIndex,const TCHAR *path,uint32_t *Width,uint32_t *Height);
uint32_t LoadBmpMaskToRam(uint32_t PSRamIndex,const TCHAR *path,uint32_t *Width,uint32_t *Height);
void CopyRam2Layer(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t Heigh,uint32_t DesRam,uint32_t SouRam);
void CopyLayer2Ram(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t Heigh,uint32_t DesRam,uint32_t SouRam);

