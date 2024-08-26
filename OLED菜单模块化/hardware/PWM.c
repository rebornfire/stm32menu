#include "stm32f10x.h"                  // Device header

/**
  * @brief  初始化PWM
  * @param  无
  * @retval 无
 **/
void PWM_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
    // GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 配置为复用推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2; // 配置引脚0
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置GPIO速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 初始化GPIOA
    
    TIM_InternalClockConfig(TIM2); // 配置定时器内部时钟
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1; // 自动重装载值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; // 预分频器
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 重复计数器
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure); // 初始化定时器2
    
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure); // 初始化输出比较结构
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // 配置为PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性高
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出
    TIM_OCInitStructure.TIM_Pulse = 0; // 设置脉冲值
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // 初始化定时器2通道1输出比较
    TIM_OC2Init(TIM2, &TIM_OCInitStructure); // 初始化定时器2通道2输出比较
    TIM_OC3Init(TIM2, &TIM_OCInitStructure); // 初始化定时器2通道3输出比较
    TIM_Cmd(TIM2, ENABLE); // 使能定时器2
}

/**
  * @brief  设置PWM比较值
  * @param  Compare 比较值
  * @retval 无
 **/
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2, Compare); // 设置定时器2通道1比较值
    TIM_SetCompare2(TIM2, Compare); // 设置定时器2通道1比较值
    TIM_SetCompare3(TIM2, Compare); // 设置定时器2通道1比较值
}

