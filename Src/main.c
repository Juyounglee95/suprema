/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "dht11.h"
#include "sfm6020.h"
#include "stepper.h"
#include "stm32f4xx.h"
#include  <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "usb_device.h"
#include "UF_SysParameter.h"
#include "UF_API.h"
#include "UF_Packet.h"
#include "UF_Error.h"
#include "UF_Command.h"
#include "UF_Enroll.h"
#include "defines.h"
#include "stm32fxxx_hal.h"
#include "tm_stm32_delay.h"
#include "STM_MY_LCD16X2.h"
/* Include my libraries here */

/*******************************/
#define RS 9
#define E  10

#define D4 5
#define D5 6
#define D6 7 
#define D7 15


#define uart6_TX GPIO_PIN_14
#define uart6_RX GPIO_PIN_9
#define uart6_TX_GPIO_port GPIOG
#define uart6_RX_GPIO_port GPIOG


#include <stdbool.h>
//#define input GPIO_PIN_2
//#define input_GPIO_port GPIOF
//#define PIN5 GPIO_PIN_5
//#define PIN5_GPIO_Port GPIOA
//#define echo GPIO_PIN_2
//#define echo_GPIO_Port GPIOE
//#define Trig GPIO_PIN_3
//#define Trig_Port GPIOE
//#define OFFSET 0.8
//#define ras7 GPIO_PIN_7
//#define ras7_GPIO_port GPIOC
#define Buzzer GPIO_PIN_8
#define Buzzzer_GPIO_Port GPIOB

#define finger_enroll GPIO_PIN_3
#define finger_identify GPIO_PIN_10
#define finger_delete GPIO_PIN_12
#define finger_enroll_GPIO_Port GPIOF
#define finger_identify_GPIO_Port GPIOF
#define finger_delete_GPIO_Port GPIOG
#define finger_boot GPIO_PIN_10
#define finger_boot_GPIO_Port GPIOG
//#define LED1_TASK_PRIO             (tskIDLE_PRIORITY+1)
//#define READ_TASK_PRIO             (tskIDLE_PRIORITY+1)
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart6_tx;
DMA_HandleTypeDef hdma_usart6_rx;

osThreadId defaultTaskHandle;
osThreadId dht11Handle;
osThreadId buttonHandle;


TIM_HandleTypeDef htim7;
UART_HandleTypeDef huart1;
/* USER CODE BEGIN PV */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
 #define GETCHAR_PROTOTYPE int __io_getchar(int chr)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)	
#endif /* __GNUC__ */
/* Private variables ---------------------------------------------------------*/


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}
GETCHAR_PROTOTYPE
{
    uint8_t inputChar;
    HAL_UART_Receive(&huart2, (uint8_t *)&inputChar, 1, 0xFFFFFFFF);
    //HAL_UART_Receive_IT(&huart2, (uint8_t *)&inputChar, 1);
    return inputChar;
}




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART6_UART_Init(void);
void StartDefaultTask(void const * argument);
void startDHT11Task(void const * argument);
void startButtonTask(void const * argument);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void GPIO_external_LED(void);
float Read_Distance(void);
float distance;
void ultrasonic_sensor(void);

void button(void);

void finger_button_init(void);
void finger_boot_init(void);
void buzzer_init(void);
void buzzer_start(int);
void dht_init(void);
void dht_read(void);
void dht_print(void);

void GPIO_LCD_Init(void);
void LED1_Toggle_Task(void * pvParameters);



/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

//global variable



int count=1;
float distance;


/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
 TM_DELAY_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();

  /* USER CODE BEGIN 2 */ 
	
		finger_boot_init();
		finger_button_init();
		buzzer_init();
		LCD_clear();
		LCD_begin4BIT(GPIOB,RS, E, GPIOA,D4,  D5, D6,  D7);
	

	 LCD_print("Push Start");
	 LCD_setCursor(2,1);
	 LCD_print("Button");
	 HAL_Delay(3000);
	 LCD_clear();
	//buzzer_init();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityBelowNormal, 0, 256);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	osThreadDef(dht11Task, startDHT11Task, osPriorityAboveNormal, 0,configMINIMAL_STACK_SIZE);
  dht11Handle = osThreadCreate(osThread(dht11Task), NULL);
	osThreadDef(buttonTask, startButtonTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	buttonHandle = osThreadCreate(osThread(buttonTask), NULL);
	
  /* USER CODE BEGIN RTOS_THREADS */
	
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
 osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	
  while (1)
  {
		/* Every 1 second */
		
	
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 48000;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 499;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D4_Pin|D5_Pin|D6_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RS_Pin|E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D4_Pin D5_Pin D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RS_Pin E_Pin */
  GPIO_InitStruct.Pin = RS_Pin|E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */



void buzzer_init(void)
{
GPIO_InitTypeDef GPIO_buzzer;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_buzzer.Pin = Buzzer;
	GPIO_buzzer.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_buzzer.Pull = GPIO_NOPULL;
	GPIO_buzzer.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_buzzer);


}
void buzzer_start(int a) //success : once , fail : twice 
{
	
		for(int i =0; i<a; i++){
		HAL_GPIO_WritePin(GPIOB, Buzzer, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GPIOB, Buzzer, GPIO_PIN_RESET);
		HAL_Delay(100);
			}
	
		return;
			
	

}


void finger_boot_init(void)
{
	GPIO_InitTypeDef GPIO_finger_boot;
	__HAL_RCC_GPIOG_CLK_ENABLE();
	GPIO_finger_boot.Pin = finger_boot;
	GPIO_finger_boot.Mode = GPIO_MODE_INPUT;
	GPIO_finger_boot.Pull = GPIO_PULLUP;
	GPIO_finger_boot.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOG, &GPIO_finger_boot);
	
}
void finger_button_init(void)
{
	GPIO_InitTypeDef GPIO_finger_button;
	GPIO_InitTypeDef GPIO_finger_delete;
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	GPIO_finger_button.Pin = finger_enroll|finger_identify;
	GPIO_finger_button.Mode = GPIO_MODE_INPUT;
	GPIO_finger_button.Pull = GPIO_PULLUP;
	GPIO_finger_button.Speed = GPIO_SPEED_MEDIUM;
	GPIO_finger_delete.Pin =finger_delete;
	GPIO_finger_delete.Mode = GPIO_MODE_INPUT;
	GPIO_finger_delete.Pull = GPIO_PULLUP;
	GPIO_finger_delete.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOF, &GPIO_finger_button);
	HAL_GPIO_Init(GPIOG, &GPIO_finger_delete);
	
}

/*void ultrasonic_sensor(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitStruct.Pin = Trig;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = echo;
	GPIO_InitStruct.Mode =GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
}
float Read_Distance(void)
{
	__IO uint8_t flag = 0;
	__IO uint32_t disTime=0;
	float distance;
	HAL_GPIO_WritePin(GPIOE, Trig, GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOE, Trig, GPIO_PIN_SET);	
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOE, Trig, GPIO_PIN_RESET);
	
	while(flag == 0 )
	{
	
		while(HAL_GPIO_ReadPin(GPIOE, echo)==SET)
			{
			//HAL_Delay(500);
			disTime++;
			flag=1;
		}
			
	}
		distance = disTime * 0.01715+ OFFSET;

	return distance;
}
	*/
	
void startDHT11Task(void const * argument)
{
	for(;;){
	
	DHT11Read();
	//distance = Read_Distance();

	osDelay(1000);
	
	
	}
}

void startButtonTask(void const * argument)
{

	while(1)
	{	
		
		if(!HAL_GPIO_ReadPin(GPIOF, finger_enroll))
		{
			LCD_clear();
			dht_LCDprint();
			HAL_Delay(1000);
			LCD_clear();
			LCD_print("ENROLL");
			HAL_Delay(1000);
			Enroll();
			
	
			
		}
		if(!HAL_GPIO_ReadPin(GPIOF, finger_identify))
		{
			LCD_clear();
			
			dht_LCDprint();
			HAL_Delay(1000);
			LCD_clear();
			LCD_print("IDENTIFY");
			HAL_Delay(1000);
			
			Identify();
	
		}
		if(!HAL_GPIO_ReadPin(GPIOG, finger_delete))
		{
			LCD_clear();
			dht_LCDprint();
			HAL_Delay(1000);
			LCD_clear();
			LCD_print("Delete");
			HAL_Delay(1000);
			
			Delete_all();
		}
		osDelay(1);
	}
}

/* USER CODE END 4 */

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
		
		
  /* Infinite loop */
  for(;;)
  {		
	
			
			
				
			if(!HAL_GPIO_ReadPin(GPIOG,finger_boot))
				{
				Connect();	
				}
		

  }
  /* USER CODE END 5 */ 
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
