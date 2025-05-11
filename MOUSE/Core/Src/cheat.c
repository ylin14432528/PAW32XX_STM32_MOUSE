#include "cheat.h"


//振刀示意
void Parry(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    HID_Mouse_Buffer[1] = 0x08;  // 设置鼠标缓冲区的第二个字节为 0x08
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送数据
    HAL_Delay(1000);  // 延时 1000ms
}


//左键抓
void catch_Left(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 左键按下
    HID_Mouse_Buffer[1] = 0x01;  // 设置鼠标缓冲区的第二个字节为 0x01（左键按下）
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送数据
    HAL_Delay(200);  // 延时 200ms

    // 左键释放
    HID_Mouse_Buffer[1] = 0x00;  // 设置鼠标缓冲区的第二个字节为 0x00（左键释放）
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送数据
    HAL_Delay(200);  // 延时 200ms
}

//升龙
void rise(uint8_t* HID_Keyboard_Buffer, uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 'C' 键下蹲
    HID_Keyboard_Buffer[3] = 0x06;  // 'C' 键的 HID 键码
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(200);  // 延时 200ms

    // 升龙
    HID_Mouse_Buffer[1] = 0x02;  // 设置鼠标缓冲区的第二个字节为 0x02（右键按下）
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
    HAL_Delay(100);  // 延时 100ms

    // 升龙取消
    HID_Mouse_Buffer[1] = 0x00;  // 设置鼠标缓冲区的第二个字节为 0x00（右键释放）
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
    HAL_Delay(100);  // 延时 100ms
}

//双刀抽搐铁马残红
void convulsion(uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    for (int i = 0; i < 5; i++)
    {
        // Ctrl静步
        HID_Keyboard_Buffer[1] = 0x01; // Ctrl键按下
        HID_Keyboard_Buffer[3] = 0x00; // 'Q' 键取消
        HID_Keyboard_Buffer[3] = 0x1A; // 'W' 键按下
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9); // 发送键盘数据
        HAL_Delay(150); // 延时 115ms

        // 恢复
        HID_Keyboard_Buffer[3] = 0x00; // 恢复按键状态
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9); // 发送键盘数据
        HAL_Delay(150); // 延时 100ms
    }
			HID_Keyboard_Buffer[1] = 0x00; // 恢复
			HID_Keyboard_Buffer[3] = 0x00; // 恢复
			USBD_LL_Transmit(UsbDevice, ADDR,HID_Keyboard_Buffer,9);	
}

//右键惊雷（八斩刀）
void follow_up(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 循环 6 次，模拟右键惊雷操作
    for (int i = 0; i < 6; i++)
    {
        // 右键按下
        HID_Mouse_Buffer[1] = 0x02;  // 设置鼠标缓冲区的第二个字节为 0x02（右键按下）
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
        HAL_Delay(200);  // 延时 200ms

        // 右键释放
        HID_Mouse_Buffer[1] = 0x00;  // 设置鼠标缓冲区的第二个字节为 0x00（右键释放）
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
        HAL_Delay(500);  // 延时 500ms
    }

    // 恢复键盘和鼠标的状态
    HID_Keyboard_Buffer[1] = 0x00;  // 恢复键盘状态
    HID_Keyboard_Buffer[3] = 0x00;  // 恢复键盘状态
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据

    HID_Mouse_Buffer[1] = 0x00;  // 恢复鼠标状态
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
}


void double_jump1(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 第一次空格起跳键按下
    HID_Keyboard_Buffer[7] = 0x2C;  // 空格键按下
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(350);  // 延时 400ms

    // 第一次空格起跳键松开
    HID_Keyboard_Buffer[7] = 0x00;  // 空格键松开
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(200);  // 延时 200ms

    // 第二次空格起跳键按下
    HID_Keyboard_Buffer[7] = 0x2C;  // 空格键按下
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(350);  // 延时 200ms

    // 第二次空格起跳键松开
    HID_Keyboard_Buffer[7] = 0x00;  // 空格键松开
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
	HAL_Delay(10);  // 延时 10ms
}


void double_jump(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
	
	    // 空格打断蓄力状态
	  HID_Keyboard_Buffer[7] = 0x2C;  // 空格键按下
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
		HAL_Delay(100);  
	    HID_Keyboard_Buffer[7] = 0x00;  // 空格键松开
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(100);  
	  
	
    // 空格起跳键按下
    HID_Keyboard_Buffer[7] = 0x2C;  // 空格键粘滞
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
		HAL_Delay(200);  // 延时 400ms
		HID_Mouse_Buffer[1] = 0x00;  
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 松开左键蓄力
    HAL_Delay(5);  // 延时 400ms
    HID_Keyboard_Buffer[7] = 0x00;  // 空格键松开
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(150);  // 延时 200ms
		
		 
    // 第二次空格起跳键按下
    HID_Keyboard_Buffer[7] = 0x2C;  // 空格键按下
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
    HAL_Delay(350);  // 延时 200ms

    // 第二次空格起跳键松开
    HID_Keyboard_Buffer[7] = 0x00;  // 空格键松开
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // 发送键盘数据
	HAL_Delay(10);  // 延时 10ms
}

void cut_blue(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 切换武器
    HID_Mouse_Buffer[4] = 100;  // 设置鼠标缓冲区的第四个字节为 100
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
    HAL_Delay(10);  // 延时 10ms

    // 恢复鼠标状态
    HID_Mouse_Buffer[4] = 0;  // 将第四个字节恢复为 0
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据

    // 左键长蓄力
    HID_Mouse_Buffer[1] = 0x01;  // 设置鼠标缓冲区的第二个字节为 0x01（左键按下）
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // 发送鼠标数据
    HAL_Delay(80);  // 延时 500ms
	
}

