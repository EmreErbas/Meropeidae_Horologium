/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nixie.h"

#ifdef superUserMode
	#include <stdio.h>
	#include "usbd_cdc_if.h"
	extern USBD_HandleTypeDef hUsbDeviceFS;

	uint8_t CMD_Buffer[256], CMD_Len = 0;
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
uint8_t NumOfNodes, IDBuffer[10];

uint8_t image_data_nixie5[199] = { 0x01,  //PWM Page address
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x06, 0x08, 0x0a, 0x09, 0x05, 0x02, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x05, 0x0c, 0x0e, 0x11, 0x11, 0x0a, 0x07, 0x05, 0x05, 0x01, 0x00,
	0x02, 0x01, 0x01, 0x03, 0x08, 0x0b, 0x09, 0x0c, 0x14, 0x47, 0x87, 0x95, 0x63, 0x23, 0x08, 0x05, 0x02, 0x00,
	0x03, 0x02, 0x03, 0x06, 0x8e, 0x26, 0x0f, 0x14, 0x5c, 0xa1, 0x21, 0x20, 0x56, 0x97, 0x17, 0x07, 0x02, 0x00,
	0x02, 0x02, 0x04, 0x0c, 0xa6, 0x27, 0x0f, 0x1e, 0x95, 0x27, 0x0f, 0x0c, 0x1b, 0x66, 0x56, 0x08, 0x02, 0x00,
	0x03, 0x03, 0x04, 0x08, 0x96, 0x2a, 0x12, 0x2b, 0x7d, 0x16, 0x11, 0x09, 0x11, 0x31, 0x78, 0x0d, 0x03, 0x00,
	0x01, 0x03, 0x08, 0x11, 0x90, 0x3b, 0x15, 0x1c, 0x96, 0x13, 0x09, 0x08, 0x0c, 0x55, 0x63, 0x0e, 0x03, 0x00,
	0x03, 0x01, 0x02, 0x11, 0x85, 0x98, 0x88, 0x74, 0xc4, 0x5d, 0x0d, 0x0a, 0x2a, 0x91, 0x2b, 0x04, 0x01, 0x00,
	0x04, 0x03, 0x02, 0x07, 0x14, 0x1b, 0x23, 0x37, 0x44, 0x33, 0x08, 0x06, 0x5f, 0x33, 0x04, 0x02, 0x01, 0x00,
	0x01, 0x01, 0x01, 0x03, 0x07, 0x0b, 0x08, 0x09, 0x0c, 0x08, 0x05, 0x11, 0x04, 0x03, 0x03, 0x01, 0x00, 0x00,
	0x01, 0x01, 0x01, 0x02, 0x06, 0x05, 0x03, 0x08, 0x08, 0x09, 0x0f, 0x02, 0x02, 0x04, 0x02, 0x02, 0x00, 0x00
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */


#ifdef superUserMode
  NixiBusInit(hi2c1, &hUsbDeviceFS);
#else
  NixiBusInit(hi2c1, NULL);
#endif

  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#ifdef superUserMode
	  superUserRunForever(CMD_Buffer, &CMD_Len);
#endif  //superUserMode


		I2C_Buffer[0] = CommandRegisterWriteLock;
		I2C_Buffer[1] = CommandRegisterWriteUnlock;
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

		I2C_Buffer[0] = CommandRegister;
		I2C_Buffer[1] = PWMRegister;
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);

		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, image_data_nixie5, 199, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, image_data_nixie5, 199, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, image_data_nixie5, 199, 1000);
		HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, image_data_nixie5, 199, 1000);


	  HAL_Delay(1000);

		I2C_Buffer[0] = 0x01;
		for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
		{
			I2C_Buffer[loop] = 0x0;
		}
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 199, 1000);

		HAL_Delay(100);

//
//		I2C_Buffer[0] = 0x01;
//		for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
//		{
//			I2C_Buffer[loop] = 0x1F;
//		}
//			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 199, 1000);
//			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 199, 1000);
//			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 199, 1000);
//			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 199, 1000);
//
//		HAL_Delay(2000);


		I2C_Buffer[0] = 0x01;
		for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
		{
			I2C_Buffer[loop] = 0x0;
		}
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 199, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 199, 1000);

		HAL_Delay(500);


		for(uint8_t loop = 1; loop < 0xC7 ; loop ++)
		{
			I2C_Buffer[0] = loop;
			I2C_Buffer[1] = 0x1F;
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftLeft, I2C_Buffer, 2, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_LeftRight, I2C_Buffer, 2, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightLeft, I2C_Buffer, 2, 1000);
			HAL_I2C_Master_Transmit(&NixieBus, Nixie_ID_RightRight, I2C_Buffer, 2, 1000);
		HAL_Delay(50);
		}
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 4199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD_RED_GPIO_Port, LD_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD_RED_Pin */
  GPIO_InitStruct.Pin = LD_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD_RED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
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
