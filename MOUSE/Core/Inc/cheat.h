#ifndef __CHEAT_H__
#define __CHEAT_H__

#include "main.h"
#include "usbd_hid.h"
#include "usb_device.h"

void Parry(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void catch_Left(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void rise(uint8_t* HID_Keyboard_Buffer, uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void convulsion(uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void follow_up(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void double_jump1(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void double_jump(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);
void cut_blue(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice);

#endif /*__ GPIO_H__ */

