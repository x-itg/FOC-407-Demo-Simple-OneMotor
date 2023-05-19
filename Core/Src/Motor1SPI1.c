#include "Motor1SPI1.h"
#include "main.h"
#include "Timer.h"

// 磁编码器型号TLE5012B.h
extern SPI_HandleTypeDef hspi1;

/*************************************************************
** Function name:       Motor1SPI1WriteData
** Descriptions:        SPI1写数据
** Input parameters:    data：要发送的数据
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1SPI1WriteData(uint16_t data)
{
	HAL_SPI_Transmit(&hspi1, (uint8_t *)&data, 1, 1000);
}
/*************************************************************
** Function name:       Motor1SPI1ReadData
** Descriptions:        SPI1读数据
** Input parameters:    None
** Output parameters:   None
** Returned value:      读取到的数据
** Remarks:             None
*************************************************************/
uint16_t Motor1SPI1ReadData(void)
{
	uint16_t data;
	HAL_SPI_Receive(&hspi1, (uint8_t *)&data, 1, 1000);
	return data;
}
/*************************************************************
** Function name:       Motor1SPI1SetCS1
** Descriptions:        设置SPI1 片选1引脚电平
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void Motor1SPI1SetCS(uint8_t leave)
{
	HAL_GPIO_WritePin(M1_SPI_CS_GPIO_Port, M1_SPI_CS_Pin, (GPIO_PinState)leave);
}
/*************************************************************
** Function name:       ReadTLE5012BAngle
** Descriptions:        获取MS730角度值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
float ReadTLE5012BAngle(float fTLE5012B)
{
	uint16_t data = 0xffff;
	float angle;
	Motor1SPI1SetCS(0);
	rt_hw_us_delay(1);
	Motor1SPI1WriteData(0x8021);
	data = Motor1SPI1ReadData();
	Motor1SPI1SetCS(1);
	data &= 0x7fff;
	angle = data / 32767.0f * 360.0f;
	// printf("pre:%f\r\n",angle);
	angle = angle - fTLE5012B;
	if (angle < 0)
	{
		angle = angle + 360.0f;
	}
	return angle;
}
