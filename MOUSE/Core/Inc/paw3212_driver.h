// paw3212_driver.h
#ifndef PAW3212_DRIVER_H
#define PAW3212_DRIVER_H

#include "stm32f1xx_hal.h"

// SPI 和 GPIO 外设定义
extern SPI_HandleTypeDef hspi1;
#define PAW3212_NCS_GPIO_Port    GPIOA
#define PAW3212_NCS_Pin          GPIO_PIN_3
#define PAW3212_MOTION_GPIO_Port GPIOA
#define PAW3212_MOTION_Pin       GPIO_PIN_4

// 寄存器地址
#define PAW3212_REG_PRODUCT_ID1    0x00
#define PAW3212_REG_PRODUCT_ID2    0x01
#define PAW3212_REG_MOTION_STATUS  0x02
#define PAW3212_REG_DELTA_X        0x03
#define PAW3212_REG_DELTA_Y        0x04
#define PAW3212_REG_CONFIG      0x06
#define PAW3212_REG_WRITE_PROTECT  0x09
#define PAW3212_REG_SLEEP1         0x0A
#define PAW3212_REG_SLEEP2         0x0B
#define PAW3212_REG_SLEEP3         0x0C
#define PAW3212_REG_CPI_X          0x0D
#define PAW3212_REG_CPI_Y          0x0E
#define PAW3212_REG_DELTA_XY_HI    0x12
#define PAW3212_REG_IQC            0x13
#define PAW3212_REG_SHUTTER        0x14
#define PAW3212_REG_FRAME_AVG      0x17
#define PAW3212_REG_MOUSE_OPTION   0x19
#define PAW3212_REG_SPI_MODE       0x26
// … 可根据需求补充其他寄存器

// 接口声明
void     PAW3212_Select(void);
void     PAW3212_Deselect(void);

HAL_StatusTypeDef PAW3212_WriteReg(uint8_t reg, uint8_t data);
HAL_StatusTypeDef PAW3212_ReadReg(uint8_t reg, uint8_t *pData);

uint8_t  PAW3212_Init(void);
uint8_t  PAW3212_DPI(uint8_t DPI);
void     PAW3212_SoftwarePowerDown(void);
void 		 PAW3212_Wakeup(void);
void 		 PAW3212_SoftwareReset(void);

void     PAW3212_ReadMotion(int8_t *dx, int8_t *dy, uint8_t *motion);
void     PAW3212_IRQHandler(void);




#endif // PAW3212_DRIVER_H
