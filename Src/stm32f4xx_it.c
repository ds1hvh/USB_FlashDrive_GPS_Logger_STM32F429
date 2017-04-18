/**
  ******************************************************************************
  * @file    FatFs/FatFs_USBDisk/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h" 
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern HCD_HandleTypeDef hhcd;

extern uint8_t rx_buff[100];
extern HAL_StatusTypeDef status;
extern int new_msg;
extern UART_HandleTypeDef huart5;
extern FIL log_file;                   /* File object */
extern int i;
extern void Error_Handler(void);
void open_n_log(char* txt);


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles USB-On-The-Go FS global interrupt requests.
  * @param  None
  * @retval None
  */
void OTG_HS_IRQHandler(void)
{
  HAL_HCD_IRQHandler(&hhcd);
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
* @brief This function handles UART5 global interrupt.
*/
void UART5_IRQHandler(void)
{
	
	
//	uint8_t RX[100] = {0};
	
  HAL_UART_IRQHandler(&huart5);
	
	status = HAL_UART_Receive_IT(&huart5 , rx_buff, 100);
	
	//open_n_log((char *)RX);
	
	//HAL_NVIC_ClearPendingIRQ(UART5_IRQn);
}



void open_n_log(char* txt)
{
	 FRESULT res;
	/* Create and Open a new text file object with write access */
	if(f_open(&log_file, "GPS_LOG.TXT",  FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) 
	{
		/* 'STM32.TXT' file Open for write Error */
		Error_Handler();
	}
	else
	{		
		res = f_lseek(&log_file, f_size(&log_file));
		if (res != FR_OK)
		{
				f_close(&log_file);
				Error_Handler();
		}
		
		/// ICI COMMENCE LA COLLECTE DE DONN2ES
		/// On laisse le travail au IRQ_Handler
/*		int k =0;
		for(;k<5;k++)
		{
			HAL_GPIO_TogglePin(GPIOG , GPIO_PIN_13);
			HAL_Delay(500);
		}
	*/	
					//		HAL_Delay(3000);

	//	while(i < 10  ) //f_size(&log_file) < 2000   )
	//	{
			//status = HAL_UART_Receive_IT(&huart5 , rx_buff, 100);
		//	status = HAL_UART_Receive(&huart5, rx_buff, 100, 100);
		//	if (status == HAL_OK) i++;
			
		//	if(HAL_UART_Receive_IT(&huart5 , rx_buff, 100) == HAL_OK)  //;new_msg == 1)
		//	{
				f_printf(&log_file, "%d -> %s\n" , i, txt);  //rx_buff);
				i++;
			//	f_sync(&log_file);
			//	new_msg = 0;
	//			i++;
	//			HAL_GPIO_TogglePin(GPIOG , GPIO_PIN_13);
	//		HAL_Delay(100);
		//	}
			
					
	//	}
		
		f_close(&log_file);
		
		
			HAL_GPIO_TogglePin(GPIOG , GPIO_PIN_14);
			
	
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
