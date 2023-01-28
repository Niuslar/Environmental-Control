/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
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
QueueHandle_t commandsIn;
/* USER CODE END Variables */
/* Definitions for temperatureCont */
osThreadId_t temperatureContHandle;
const osThreadAttr_t temperatureCont_attributes = {
  .name = "temperatureCont",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for commsTask */
osThreadId_t commsTaskHandle;
const osThreadAttr_t commsTask_attributes = {
  .name = "commsTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for humidityControl */
osThreadId_t humidityControlHandle;
const osThreadAttr_t humidityControl_attributes = {
  .name = "humidityControl",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for co2ControlTask */
osThreadId_t co2ControlTaskHandle;
const osThreadAttr_t co2ControlTask_attributes = {
  .name = "co2ControlTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for messagesOut */
osMessageQueueId_t messagesOutHandle;
const osMessageQueueAttr_t messagesOut_attributes = {
  .name = "messagesOut"
};
/* Definitions for commandsIn */
osMessageQueueId_t commandsInHandle;
const osMessageQueueAttr_t commandsIn_attributes = {
  .name = "commandsIn"
};
/* Definitions for commsInOut */
osEventFlagsId_t commsInOutHandle;
const osEventFlagsAttr_t commsInOut_attributes = {
  .name = "commsInOut"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* ---- CONTROL TASK ------ */
void TemperatureControllerInit();
void TemperatureControllerRun();
void HumidityControllerInit();
void HumidityControllerRun();
void CO2ControllerInit();
void CO2ControllerRun();

/* ---- COMMS TASK ------ */
void CommsControllerInit();
void CommsControllerRun();
/* USER CODE END FunctionPrototypes */

void StartTempControlTask(void *argument);
void StartCommsTask(void *argument);
void StartHumidityControlTask(void *argument);
void StartCo2ControlTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of messagesOut */
  messagesOutHandle = osMessageQueueNew (20, 50, &messagesOut_attributes);

  /* creation of commandsIn */
  commandsInHandle = osMessageQueueNew (20, 50, &commandsIn_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of temperatureCont */
  temperatureContHandle = osThreadNew(StartTempControlTask, NULL, &temperatureCont_attributes);

  /* creation of commsTask */
  commsTaskHandle = osThreadNew(StartCommsTask, NULL, &commsTask_attributes);

  /* creation of humidityControl */
  humidityControlHandle = osThreadNew(StartHumidityControlTask, NULL, &humidityControl_attributes);

  /* creation of co2ControlTask */
  co2ControlTaskHandle = osThreadNew(StartCo2ControlTask, NULL, &co2ControlTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of commsInOut */
  commsInOutHandle = osEventFlagsNew(&commsInOut_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTempControlTask */
/**
* @brief Function implementing the temperatureCont thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTempControlTask */
void StartTempControlTask(void *argument)
{
  /* USER CODE BEGIN StartTempControlTask */

	TemperatureControllerInit();
  /* Infinite loop */
  for(;;)
  {
	  TemperatureControllerRun();
	  osDelay(1);
  }
  /* USER CODE END StartTempControlTask */
}

/* USER CODE BEGIN Header_StartCommsTask */
/**
* @brief Function implementing the commsTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCommsTask */
void StartCommsTask(void *argument)
{
  /* USER CODE BEGIN StartCommsTask */
	CommsControllerInit();
  /* Infinite loop */
  for(;;)
  {
	  CommsControllerRun();
	  osDelay(1);
  }
  /* USER CODE END StartCommsTask */
}

/* USER CODE BEGIN Header_StartHumidityControlTask */
/**
* @brief Function implementing the humidityControl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartHumidityControlTask */
void StartHumidityControlTask(void *argument)
{
  /* USER CODE BEGIN StartHumidityControlTask */
	HumidityControllerInit();
  /* Infinite loop */
  for(;;)
  {
	  HumidityControllerRun();
	  osDelay(1);
  }
  /* USER CODE END StartHumidityControlTask */
}

/* USER CODE BEGIN Header_StartCo2ControlTask */
/**
* @brief Function implementing the co2ControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCo2ControlTask */
void StartCo2ControlTask(void *argument)
{
  /* USER CODE BEGIN StartCo2ControlTask */
	CO2ControllerInit();
  /* Infinite loop */
  for(;;)
  {
	  CO2ControllerRun();
	  osDelay(1);
  }
  /* USER CODE END StartCo2ControlTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

