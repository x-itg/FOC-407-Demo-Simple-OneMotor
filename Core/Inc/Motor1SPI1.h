#ifndef Motor1SPI1_h
#define Motor1SPI1_h

#include "stdint.h"


void Motor1SPI1WriteData(uint16_t data);
uint16_t Motor1SPI1ReadData(void);
void Motor1SPI1SetCS(uint8_t leave);
float ReadTLE5012BAngle(float fTLE5012B);

#endif /* Motor1SPI1_h */
