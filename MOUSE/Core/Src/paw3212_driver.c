// paw3212_driver.c
#include "paw3212_driver.h"
#include "usart.h"

// 拉低 NCS，开启 SPI 事务, 上电时候最小低电平时间1ms仅调用一次 HAL_Delay(1)
void PAW3212_Select(void) {
    HAL_GPIO_WritePin(PAW3212_NCS_GPIO_Port, PAW3212_NCS_Pin, GPIO_PIN_RESET);
    // 小延时确保 NCS 建立时间 ≥ tNCS-LEAD
    __NOP(); __NOP(); __NOP();
}

// 拉高 NCS，结束 SPI 事务
void PAW3212_Deselect(void) {
    HAL_GPIO_WritePin(PAW3212_NCS_GPIO_Port, PAW3212_NCS_Pin, GPIO_PIN_SET);
    // 小延时确保 NCS 保持时间 ≥ tNCS-LAG
    __NOP(); __NOP();
}

// 写寄存器：MSB=1 表示写操作，若出现不稳定，可在 HAL_SPI_Transmit 和 HAL_SPI_Receive 之间插入几条 __NOP() 做微小延时。
HAL_StatusTypeDef PAW3212_WriteReg(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = { (uint8_t)(0x80 | reg), data };
    PAW3212_Select();
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, buf, 2, HAL_MAX_DELAY);
    PAW3212_Deselect();
    return status;
}

// 读寄存器：MSB=0 表示读操作，若出现不稳定，可在 HAL_SPI_Transmit 和 HAL_SPI_Receive 之间插入几条 __NOP() 做微小延时。
HAL_StatusTypeDef PAW3212_ReadReg(uint8_t reg, uint8_t *pData) {
    uint8_t cmd = reg & 0x7F;
    PAW3212_Select();
    // 发送地址
    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    if (status != HAL_OK) { PAW3212_Deselect(); return status; }
    // 读取数据
    status = HAL_SPI_Receive(&hspi1, pData, 1, HAL_MAX_DELAY);
    PAW3212_Deselect();
    return status;
}

// 初始化：示例读取 Product ID，并设置 CPI 为 800
uint8_t PAW3212_Init(void) {
	
	    //上电后，拉低 NCS 至少 1ms
    PAW3212_Select();
    HAL_Delay(1);  // 确保 t_NCSPU >= 1ms

    //之后释放 NCS，准备常规 SPI 事务
    PAW3212_Deselect();
		HAL_Delay(1); 
	
	
    uint8_t pid;
    if (PAW3212_ReadReg(PAW3212_REG_PRODUCT_ID1, &pid) != HAL_OK) return 0;
    if (pid != 0x30) return 0; // 校验 ID 是否正确 (0x30)
    // 禁用写保护
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x5A);
    // 设置 CPI_X = CPI_Y = (800/38) ≈ 21
    PAW3212_WriteReg(PAW3212_REG_CPI_X, 21);
    PAW3212_WriteReg(PAW3212_REG_CPI_Y, 21);
    // 恢复写保护
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x00);
		printf("PAW3212 Init OK\r\n");
    return 1;
}
uint8_t PAW3212_DPI(uint8_t DPI) {
    // 禁用写保护
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x5A);
    // 设置 CPI_X = CPI_Y = (800/38) ≈ 21
    PAW3212_WriteReg(PAW3212_REG_CPI_X, DPI);
    PAW3212_WriteReg(PAW3212_REG_CPI_Y, DPI);
    // 恢复写保护
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x00);

}
// 进入软件掉电
void PAW3212_SoftwarePowerDown(void) {
    uint8_t cfg;
    PAW3212_ReadReg(PAW3212_REG_CONFIG, &cfg);
    cfg |= (1 << 3);               // PD_enh = 1
    PAW3212_WriteReg(PAW3212_REG_CONFIG, cfg);
}

// 退出掉电（唤醒）
void PAW3212_Wakeup(void) {
    uint8_t cfg;
    PAW3212_ReadReg(PAW3212_REG_CONFIG, &cfg);
    cfg &= ~(1 << 3);              // PD_enh = 0
    PAW3212_WriteReg(PAW3212_REG_CONFIG, cfg);
    HAL_Delay(3);                  // 等待 ≥3ms，保证运动数据准确
}

// 软件复位(调试用)
void PAW3212_SoftwareReset(void) {
    uint8_t cfg;
    PAW3212_ReadReg(PAW3212_REG_CONFIG, &cfg);
    cfg |= (1 << 7);               // Reset = 1
    PAW3212_WriteReg(PAW3212_REG_CONFIG, cfg);
    // Reset 完成后所有寄存器恢复默认，需重新调用 PAW3212_Init()
}

// 连续模式测功率
void PAW3212_LED_ContinuousMode(void) {
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x5A);
    PAW3212_WriteReg(0x5B, 0x63);
    PAW3212_WriteReg(PAW3212_REG_WRITE_PROTECT, 0x00);
}
// 读取一次运动数据
void PAW3212_ReadMotion(int8_t *dx, int8_t *dy, uint8_t *motion) {
    uint8_t s;
    PAW3212_ReadReg(PAW3212_REG_MOTION_STATUS, &s);//依次读
    *motion = s & 0x80;  // Motion bit (bit7)
    PAW3212_ReadReg(PAW3212_REG_DELTA_X, (uint8_t*)dx);//依次读
    PAW3212_ReadReg(PAW3212_REG_DELTA_Y, (uint8_t*)dy);//依次读
}

// 中断处理
void PAW3212_IRQHandler(void) {
    int8_t dx, dy;
    uint8_t motion;
    PAW3212_ReadMotion(&dx, &dy, &motion);
    if (motion) {
        printf("dx=%d, dy=%d\r\n", dx, dy);
    }
    // 读取完成后 MOTION 会拉高，等待下一次中断
}

