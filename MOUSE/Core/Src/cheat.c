#include "cheat.h"


//��ʾ��
void Parry(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    HID_Mouse_Buffer[1] = 0x08;  // ������껺�����ĵڶ����ֽ�Ϊ 0x08
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // ��������
    HAL_Delay(1000);  // ��ʱ 1000ms
}


//���ץ
void catch_Left(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // �������
    HID_Mouse_Buffer[1] = 0x01;  // ������껺�����ĵڶ����ֽ�Ϊ 0x01��������£�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // ��������
    HAL_Delay(200);  // ��ʱ 200ms

    // ����ͷ�
    HID_Mouse_Buffer[1] = 0x00;  // ������껺�����ĵڶ����ֽ�Ϊ 0x00������ͷţ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // ��������
    HAL_Delay(200);  // ��ʱ 200ms
}

//����
void rise(uint8_t* HID_Keyboard_Buffer, uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // 'C' ���¶�
    HID_Keyboard_Buffer[3] = 0x06;  // 'C' ���� HID ����
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(200);  // ��ʱ 200ms

    // ����
    HID_Mouse_Buffer[1] = 0x02;  // ������껺�����ĵڶ����ֽ�Ϊ 0x02���Ҽ����£�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
    HAL_Delay(100);  // ��ʱ 100ms

    // ����ȡ��
    HID_Mouse_Buffer[1] = 0x00;  // ������껺�����ĵڶ����ֽ�Ϊ 0x00���Ҽ��ͷţ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
    HAL_Delay(100);  // ��ʱ 100ms
}

//˫���鴤����к�
void convulsion(uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    for (int i = 0; i < 5; i++)
    {
        // Ctrl����
        HID_Keyboard_Buffer[1] = 0x01; // Ctrl������
        HID_Keyboard_Buffer[3] = 0x00; // 'Q' ��ȡ��
        HID_Keyboard_Buffer[3] = 0x1A; // 'W' ������
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9); // ���ͼ�������
        HAL_Delay(150); // ��ʱ 115ms

        // �ָ�
        HID_Keyboard_Buffer[3] = 0x00; // �ָ�����״̬
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9); // ���ͼ�������
        HAL_Delay(150); // ��ʱ 100ms
    }
			HID_Keyboard_Buffer[1] = 0x00; // �ָ�
			HID_Keyboard_Buffer[3] = 0x00; // �ָ�
			USBD_LL_Transmit(UsbDevice, ADDR,HID_Keyboard_Buffer,9);	
}

//�Ҽ����ף���ն����
void follow_up(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // ѭ�� 6 �Σ�ģ���Ҽ����ײ���
    for (int i = 0; i < 6; i++)
    {
        // �Ҽ�����
        HID_Mouse_Buffer[1] = 0x02;  // ������껺�����ĵڶ����ֽ�Ϊ 0x02���Ҽ����£�
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
        HAL_Delay(200);  // ��ʱ 200ms

        // �Ҽ��ͷ�
        HID_Mouse_Buffer[1] = 0x00;  // ������껺�����ĵڶ����ֽ�Ϊ 0x00���Ҽ��ͷţ�
        USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
        HAL_Delay(500);  // ��ʱ 500ms
    }

    // �ָ����̺�����״̬
    HID_Keyboard_Buffer[1] = 0x00;  // �ָ�����״̬
    HID_Keyboard_Buffer[3] = 0x00;  // �ָ�����״̬
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������

    HID_Mouse_Buffer[1] = 0x00;  // �ָ����״̬
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
}


void double_jump1(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // ��һ�οո�����������
    HID_Keyboard_Buffer[7] = 0x2C;  // �ո������
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(350);  // ��ʱ 400ms

    // ��һ�οո��������ɿ�
    HID_Keyboard_Buffer[7] = 0x00;  // �ո���ɿ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(200);  // ��ʱ 200ms

    // �ڶ��οո�����������
    HID_Keyboard_Buffer[7] = 0x2C;  // �ո������
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(350);  // ��ʱ 200ms

    // �ڶ��οո��������ɿ�
    HID_Keyboard_Buffer[7] = 0x00;  // �ո���ɿ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
	HAL_Delay(10);  // ��ʱ 10ms
}


void double_jump(uint8_t* HID_Mouse_Buffer, uint8_t* HID_Keyboard_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
	
	    // �ո�������״̬
	  HID_Keyboard_Buffer[7] = 0x2C;  // �ո������
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
		HAL_Delay(100);  
	    HID_Keyboard_Buffer[7] = 0x00;  // �ո���ɿ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(100);  
	  
	
    // �ո�����������
    HID_Keyboard_Buffer[7] = 0x2C;  // �ո��ճ��
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
		HAL_Delay(200);  // ��ʱ 400ms
		HID_Mouse_Buffer[1] = 0x00;  
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �ɿ��������
    HAL_Delay(5);  // ��ʱ 400ms
    HID_Keyboard_Buffer[7] = 0x00;  // �ո���ɿ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(150);  // ��ʱ 200ms
		
		 
    // �ڶ��οո�����������
    HID_Keyboard_Buffer[7] = 0x2C;  // �ո������
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
    HAL_Delay(350);  // ��ʱ 200ms

    // �ڶ��οո��������ɿ�
    HID_Keyboard_Buffer[7] = 0x00;  // �ո���ɿ�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Keyboard_Buffer, 9);  // ���ͼ�������
	HAL_Delay(10);  // ��ʱ 10ms
}

void cut_blue(uint8_t* HID_Mouse_Buffer, uint8_t ADDR, USBD_HandleTypeDef* UsbDevice)
{
    // �л�����
    HID_Mouse_Buffer[4] = 100;  // ������껺�����ĵ��ĸ��ֽ�Ϊ 100
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
    HAL_Delay(10);  // ��ʱ 10ms

    // �ָ����״̬
    HID_Mouse_Buffer[4] = 0;  // �����ĸ��ֽڻָ�Ϊ 0
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������

    // ���������
    HID_Mouse_Buffer[1] = 0x01;  // ������껺�����ĵڶ����ֽ�Ϊ 0x01��������£�
    USBD_LL_Transmit(UsbDevice, ADDR, HID_Mouse_Buffer, 9);  // �����������
    HAL_Delay(80);  // ��ʱ 500ms
	
}

