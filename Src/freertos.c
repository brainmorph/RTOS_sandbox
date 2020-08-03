/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId_t blinkTestHandle;
osThreadId_t readUARTHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartBlinkTestTask(void *argument);
void StartReadUARTTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of blinkTest */
  const osThreadAttr_t blinkTest_attributes = {
    .name = "blinkTest",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  blinkTestHandle = osThreadNew(StartBlinkTestTask, NULL, &blinkTest_attributes);

  /* definition and creation of readUART */
  const osThreadAttr_t readUART_attributes = {
    .name = "readUART",
    .priority = (osPriority_t) osPriorityBelowNormal,
    .stack_size = 128
  };
  readUARTHandle = osThreadNew(StartReadUARTTask, NULL, &readUART_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartBlinkTestTask */
/**
  * @brief  Function implementing the blinkTest thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartBlinkTestTask */
void StartBlinkTestTask(void *argument)
{
    
    
    

  /* USER CODE BEGIN StartBlinkTestTask */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(BLINK_LED_GPIO_Port, BLINK_LED_Pin);
    osDelay(500);
  }

  // This should never be reached but just in case
  osThreadTerminate(NULL);

  /* USER CODE END StartBlinkTestTask */
}

/* USER CODE BEGIN Header_StartReadUARTTask */
/**
* @brief Function implementing the readUART thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReadUARTTask */
void StartReadUARTTask(void *argument)
{
  /* USER CODE BEGIN StartReadUARTTask */
  /* Infinite loop */
  for(;;)
  {
	volatile uint8_t uartReceivedData[2] = {0};

	volatile HAL_StatusTypeDef status = HAL_UART_Receive(&huart6, (uint8_t *)uartReceivedData,
    		sizeof(uartReceivedData), 2000); // 10 ms timeout

	if(status != HAL_OK)
    {
    	continue; // ignore packets that time out
    }

	volatile uint16_t data = (uartReceivedData[0] << 8) | uartReceivedData[1];
	data = data;

    static unsigned int lastReceivedCount = 0;
    if(uartReceivedData[0] == (lastReceivedCount + 1))
    {
    	// yay we're not dropping anything

    }
    else
    {
    	// we're dropping packets
    	static unsigned int droppedPackets = 0;
    	unsigned int expectedCount = lastReceivedCount + 1;
    	droppedPackets += uartReceivedData[0] - expectedCount;
    }

    lastReceivedCount = uartReceivedData[0];


    osDelay(1);
  }
  /* USER CODE END StartReadUARTTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
