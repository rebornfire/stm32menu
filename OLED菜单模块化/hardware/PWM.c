#include "stm32f10x.h"                  // Device header

/**
  * @brief  Initialize PWM
  * @param  None
  * @retval None
 **/
void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable TIM2 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable GPIOA clock
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Configure as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // Configure pin 1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Set GPIO speed to 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // Initialize GPIOA
    
    TIM_InternalClockConfig(TIM2); // Configure timer internal clock
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // Clock division
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // Up counter mode
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; // Auto-reload value
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // Prescaler
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // Repetition counter
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure); // Initialize timer 2
    
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); // Initialize output compare structure
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // Configure as PWM mode 1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // Output polarity high
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable output
    TIM_OCInitStructure.TIM_Pulse = 0; // Set pulse value
    TIM_OC2Init(TIM2, &TIM_OCInitStructure); // Initialize timer 2 channel 2 output compare
    
    TIM_Cmd(TIM2, ENABLE); // Enable timer 2
}

/**
  * @brief  Set PWM compare value
  * @param  Compare Compare value
  * @retval None
 **/
void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2, Compare); // Set timer 2 channel 2 compare value
}
