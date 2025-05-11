/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
# include "usbd_hid.h"
#include "paw3212_driver.h"
extern USBD_HandleTypeDef hUsbDeviceFS;

static uint8_t current_buttons = 0;
	_Bool mouse_macro=0;
static uint8_t HID_Mouse_Buffer[9] = {2,0,0,0,0,0,0,0,0};		//切换鼠标第一个元素索引值为1
static uint8_t HID_Keyboard_Buffer[9] = {1,0,0,0,0,0,0,0,0};	//切换键盘第一个元素索引值为1
	uint8_t HID_Mouse_clean[9] = {2,0,0,0,0,0,0,0,0};//鼠标清空
	uint8_t HID_Keyboard_clean[9] = {1,0,0,0,0,0,0,0,0};//键盘清空
	

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void CTRL_CV_MONITOR(void)
{
    // 处理 Ctrl+C
    if (HAL_GPIO_ReadPin(CC_GPIO_Port, CC_Pin) == GPIO_PIN_RESET) {
        // 发送 Ctrl + C
        HID_Keyboard_Buffer[1] = 0x01;  // Ctrl
        HID_Keyboard_Buffer[3] = 0x06;  // 'C'
        USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);

        // 等待按键释放或消抖
        HAL_Delay(300);
        if (HAL_GPIO_ReadPin(CC_GPIO_Port, CC_Pin) == GPIO_PIN_RESET) {
            // 释放按键
            HID_Keyboard_Buffer[1] = 0x00;
            HID_Keyboard_Buffer[3] = 0x00;
            USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);
            HAL_Delay(5);
        }
    }
    else if (HAL_GPIO_ReadPin(CV_GPIO_Port, CV_Pin) == GPIO_PIN_RESET) // 处理 Ctrl+V
    {
        // 发送 Ctrl + V
        HID_Keyboard_Buffer[1] = 0x01;  // Ctrl
        HID_Keyboard_Buffer[3] = 0x19;  // 'V'
        USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);

        // 等待按键释放或消抖
        HAL_Delay(300);
        if (HAL_GPIO_ReadPin(CV_GPIO_Port, CV_Pin) == GPIO_PIN_RESET) {
            // 释放按键
            HID_Keyboard_Buffer[1] = 0x00;
            HID_Keyboard_Buffer[3] = 0x00;
            USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);
            HAL_Delay(5);
        }
    }
    else {
        // 确保空报告
        HID_Keyboard_Buffer[1] = 0x00;
        HID_Keyboard_Buffer[3] = 0x00;
        USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);
        HAL_Delay(5);
    }
}



/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int32_t encoderDiff = 0;
extern TIM_HandleTypeDef htim4;

void Encoder_Init(void)
{
  // 启动编码器接口
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  
  // 重置计数器
  __HAL_TIM_SET_COUNTER(&htim4, 0);
  
  printf("编码器初始化完成\r\n");
}

/**
  * @brief  获取编码器值并清零
  * @retval 编码器值
  */
int32_t Get_Encoder_Value(void)
{
  // 读取当前值
  int32_t value = (int32_t)__HAL_TIM_GET_COUNTER(&htim4);
  
  // 立即清零计数器
  __HAL_TIM_SET_COUNTER(&htim4, 0);
  
  // 返回读取的值
  return value;
}


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint8_t key;
	int i=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
int8_t dx, dy;
	uint8_t motion;
	uint8_t dpi_data=30;
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_USB_DEVICE_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  
  /* USER CODE BEGIN 2 */
	PAW3212_Init();
	 Encoder_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		
		//DPI DATA
		if(HAL_GPIO_ReadPin(DPI_GPIO_Port,DPI_Pin)==0)	PAW3212_DPI(dpi_data);
		else	dpi_data = (dpi_data + 20 > 60) ? 10 : (dpi_data + 20);
		
		
//		if(HAL_GPIO_ReadPin(DEFINE_GPIO_Port,DEFINE_Pin)==0)
//		{
//					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);//切换宏
//					mouse_macro=1;
//		}
//		else
//		{
//					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
//					mouse_macro=0;
//		}

			//鼠标滚轮与移动	
		encoderDiff = Get_Encoder_Value();
		PAW3212_ReadMotion(&dx, &dy, &motion);
		if(motion){
				HID_Mouse_Buffer[2] = dx;
				HID_Mouse_Buffer[3] = -dy;}
		else
		{
				HID_Mouse_Buffer[2] = 0;
				HID_Mouse_Buffer[3] = 0;
		}
				HID_Mouse_Buffer[4] = -encoderDiff;
				USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Mouse_Buffer, 9);  // 发送数据
				HAL_Delay(10);  // 延时 200ms
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static uint8_t cc_sent = 0;
// EXTI 中断回调
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t btn_state;

    if (GPIO_Pin == LEFT_Pin)
    {
        btn_state = HAL_GPIO_ReadPin(LEFT_GPIO_Port, LEFT_Pin);
        if (btn_state == GPIO_PIN_RESET) {
            // 左键按下，置位 bit0
            current_buttons |=  0x01;
        } else {
            // 左键抬起，清除 bit0
            current_buttons &= ~0x01;
        }
    }
    else if (GPIO_Pin == RIGHT_Pin)
    {
        btn_state = HAL_GPIO_ReadPin(RIGHT_GPIO_Port, RIGHT_Pin);
        if (btn_state == GPIO_PIN_RESET) {
            // 右键按下，置位 bit1
            current_buttons |=  0x02;
        } else {
            // 右键抬起，清除 bit1
            current_buttons &= ~0x02;
        }
    }
    else if (GPIO_Pin == LB_Pin)
    {
        btn_state = HAL_GPIO_ReadPin(LB_GPIO_Port, LB_Pin);
			if(mouse_macro==0)
			{
					if (btn_state == GPIO_PIN_RESET) {
							// 右键按下，置位 bit1
							current_buttons |=  0x10;
					} else {
							// 右键抬起，清除 bit1
							current_buttons &= ~0x10;
					}
			}
			else
			{

			}
    }
		    else if (GPIO_Pin == RB_Pin)
    {
        btn_state = HAL_GPIO_ReadPin(RB_GPIO_Port, RB_Pin);
        if (btn_state == GPIO_PIN_RESET) {
            // 右键按下，置位 bit1
            current_buttons |=  0x08;
        } else {
            // 右键抬起，清除 bit1
            current_buttons &= ~0x08;
        }
    }
    // 更新 HID 报文里按钮字节
    HID_Mouse_Buffer[1] = current_buttons;
    USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Mouse_Buffer, 9);
		    HID_Keyboard_Buffer[1] = 0x00;
        HID_Keyboard_Buffer[3] = 0x00;
        USBD_LL_Transmit(&hUsbDeviceFS, HID_EPIN_ADDR, HID_Keyboard_Buffer, 9);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
