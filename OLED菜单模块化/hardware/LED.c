#include "stm32f10x.h"                  // Device header

/**
  * @brief  Initialize LED GPIO port
  * @param  None
  * @retval None
 **/
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // Enable GPIOA clock
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       // Configure as push-pull output mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_0; // Configure pins 1, 2, and 0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // Set GPIO speed to 50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 // Initialize GPIOA
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_0);          // Default to turn off LEDs (set high level)
}

/**
  * @brief  Turn on LED1 (light up LED1)
  * @param  None
  * @retval None
 **/
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // Set low level to light up LED1
}

/**
  * @brief  Turn off LED1 (turn off LED1)
  * @param  None
  * @retval None
 **/
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);    // Set high level to turn off LED1
}

/**
  * @brief  Toggle LED1 state (if LED1 is on, turn it off; if it's off, turn it on)
  * @param  None
  * @retval None
 **/
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) // Check current state of LED1
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);    // Current is low level, set to high level to turn off LED1
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);  // Current is high level, set to low level to light up LED1
	}
}

/**
  * @brief  Turn on LED2 (light up LED2)
  * @param  None
  * @retval None
 **/
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // Set low level to light up LED2
}

/**
  * @brief  Turn off LED2 (turn off LED2)
  * @param  None
  * @retval None
 **/
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);    // Set high level to turn off LED2
}

/**
  * @brief  Toggle LED2 state (if LED2 is on, turn it off; if it's off, turn it on)
  * @param  None
  * @retval None
 **/
void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) // Check current state of LED2
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);    // Current is low level, set to high level to turn off LED2
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);  // Current is high level, set to low level to light up LED2
	}
}

/**
  * @brief  Turn on LED3 (light up LED3)
  * @param  None
  * @retval None
 **/
void LED3_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // Set low level to light up LED3
}

/**
  * @brief  Turn off LED3 (turn off LED3)
  * @param  None
  * @retval None
 **/
void LED3_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);    // Set high level to turn off LED3
}

/**
  * @brief  Toggle LED3 state (if LED3 is on, turn it off; if it's off, turn it on)
  * @param  None
  * @retval None
 **/
void LED3_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0) == 0) // Check current state of LED3
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);    // Current is low level, set to high level to turn off LED3
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // Current is high level, set to low level to light up LED3
	}
}
